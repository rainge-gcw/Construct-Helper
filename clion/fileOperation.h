//
// Created by hadoop on 22-9-8.
//
#ifndef CLION_FILEOPERATION_H
#define CLION_FILEOPERATION_H
#include <dirent.h>
#include "iostream"
#include "string"
#include "algorithm"
#include "fstream"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <cstdio>
using namespace std;
//#define baseUrl "/home/gcw/Construct_helper/DateSpace/"
string baseUrl;
class FileOperator{
public:
    FileOperator(){
        char tmp[256];
        getcwd(tmp, 256);
        string url=tmp;
        if(!FileOperator::exists_dir(url+"/DateSpace")){
            FileOperator::create_dir(url+"/DateSpace");
        }
        baseUrl=url+"/DateSpace";
    }
    struct Type{
        string Title;
        string judge_type;
        int cnt;
        vector<pair<string,string>>g;
        void init(){
            g.clear();
        }
        void type_read(const string& url){
            ifstream ifs(url,ios::in);
            string tmp;
            ifs>>tmp>>Title>>judge_type>>cnt;
            string key,value;char ch;
            while(ifs>>key){
                while(ifs.get(ch)){
                    if(ch=='\n')break;
                    value+=ch;
                }
                //cout<<value<<endl;
                g.emplace_back(key,value);
                value.clear();
            }
            ifs.close();
        }
        void type_write(const string& url){
            ofstream ofs(url,ios::out);
            ofs<<"Title "<<Title<<'\n';
            ofs<<judge_type<<'\n';
            ofs<<cnt<<'\n';
            for(const auto& i:g){
                ofs<<i.first<<i.second<<'\n';
            }
            ofs.close();
        }
    };
    static string user_id_to_url(const string& id){
        string tmp;
        for(char i : id){
            tmp+=i;
            tmp+='/';
        }
        return baseUrl+tmp+"userDate";
    }
    static bool get_dir(const string& url,vector<string>& g){
        DIR* p=opendir((url).c_str());;
        cout<<url<<endl;
        if(p==nullptr)return false;
        struct dirent* ptr;
        while((ptr = readdir(p))!=nullptr) {
            if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
                cout<<ptr->d_name<<endl;
                g.emplace_back(ptr->d_name);
            }
        }
        closedir(p);
        return true;
    }
    static bool exists_char(const string& url,const char& ch){
        for(char i:url){
            if(i==ch)return true;
        }
        return false;
    }
    static bool exists_dir(const string& url){
        if(access(url.c_str(),00)==0)return true;
        else return false;
    }
    static bool exists_txt(const string& url){
        ifstream ifs(url,ios::in);
        if(!ifs)return false;
        return true;
    }
    static bool create_dir(const string& url){
        if(exists_txt(url))return false;//exists
        if(mkdir(url.c_str(),0777)==0)return true;
        else return false;
    }
    static bool create_txt(const string& url){
        if(exists_txt(url))return false;//exists
        ofstream ofs(url,ios::out);
        return true;
    }
    static bool rename_txt(const string& oldName,const string& newName){
        if(!exists_txt(oldName))return false;
        if(rename(oldName.c_str(),newName.c_str())==0)return true;
        else return false;
    }
    static bool rename_dir(const string& oldName,const string& newName){
        if(exists_dir(newName))return false;
        if(rename(oldName.c_str(),newName.c_str())==0)return true;
        else return false;
    }
    static bool read_txt(const string& url,string& date){
        ifstream ifs(url,ios::in);
        if(!ifs){
            ifs.close();
            return false;
        }
        char ch;
        while((ch=ifs.get())!=EOF){
            date+=ch;
        }
        ifs.close();
        return true;
    }
    static string clear_oher(const string& s){
        string ss;
        for(auto i:s){
            if(i==' '||i=='\n')continue;
            ss+=i;
        }
        return ss;
    }
    static bool read_password(const string& url,string& date){
        string key,value;
        ifstream ifs(url,ios::in);
        if(!ifs){
            ifs.close();
            return false;
        }
        while(ifs>>key>>value){
            if(key=="user_password"){
                ifs.close();
                date=value;return true;
            }
        }
        ifs.close();
        return false;
    }
    static bool write_txt(const string& url,const string& date){
        ofstream ofs(url,ios::out);
        if(!ofs) return false;
        ofs<<date;
        ofs.close();
        return true;
    }
    static int read_date_cnt(const string& url){
        ifstream ifs(url,ios::in);
        string tmp;int k;
        ifs>>tmp>>tmp>>tmp>>k;
        ifs.close();
        return k;
    }
    static string read_judge_type(const string& url){
        ifstream ifs(url,ios::in);
        string tmp;
        ifs>>tmp>>tmp>>tmp;
        ifs.close();
        return tmp;
    }

    static vector<pair<string,string>> read_date_type(const string& url){
        Type t;
        t.type_read(url+"/type.txt");
        return t.g;
    }

    static void add_date(const string& url,const string& date){
        string tmp,add;
        ifstream ifs(url,ios::in);
        ifs>>add>>tmp;
        add+=" "+tmp+"\n";
        ifs>>tmp;
        add+=tmp+"\n";
        int cnt;
        ifs>>cnt;
        add+= to_string(cnt+1)+"\n";
        char ch;
        while(ifs.get(ch)){
            add+=ch;
        }
        if(add[add.size()-1]!='\n'){
            add+='\n';
        }
        add+=date;
        string add2;
        for(int i=0;i<add.size();i++){
            if(i!=0&&add[i]=='\n'&&add[i]==add[i-1])continue;
            add2+=add[i];
        }
        ifs.close();
        ofstream ofs(url,ios::out);
        ofs<<add2;
        ofs.close();
        return ;
    }
    static void delete_file(const string& url){
        remove(url.c_str());
    }
    static void delete_dir(const string& url){
        system(("rm -rf "+url).c_str());
    }
    static bool compile_code(const string& url){
        delete_file(url+"/spj_code");
        string tmp="g++ -Wall -std=c++17 "+url+"/spj_code.cpp -o "+url+"/spj_code";
        system(tmp.c_str());
        if(exists_dir(url+"/spj_code"))return true;
        return false;
    }
    static string zip(const vector<string>& url,const string& saveUrl,bool dir){
        string tmp="zip ";
        tmp+=" -j ";
        tmp+=saveUrl+"/data.zip ";
        for(auto i:url){
            tmp+=i+" ";
        }
        system(tmp.c_str());
        return saveUrl+"/data.zip";
    }
    static void delete_zip(const string& str){
        if(remove(str.c_str())!=0){
            cout<<"delete_zip_fail!"<<endl;
        }
    }
    static void get_all_filename(const string& url){
        DIR* d = opendir(url.c_str());

    }
    static void getFileNames(string path, vector<string>& files){
        struct dirent *ptr;
        DIR *dir;
        dir=opendir(path.c_str());
        string tmp;
        while((ptr=readdir(dir))!=NULL){
            if(ptr->d_name[0] == '.')
                continue;
            tmp=path+"/"+ptr->d_name;
            files.push_back(path+"/"+ptr->d_name);
        }
    }
    static bool read_txt_limit(const string &url,string &data,int limit){
        ifstream ifs(url,ios::in);
        if(!ifs){
            ifs.close();
            return false;
        }
        char ch;
        while((ch=ifs.get())!=EOF&&limit){
            data+=ch;
            --limit;
        }
        ifs.close();
        return true;
    }
    static string read_txt_without_end_of_line(const string&url){
        string data;
        ifstream ifs(url,ios::in);
        if(!ifs){
            ifs.close();
            return "";
        }
        string tmp;
        char ch;
        while((ch=ifs.get())!=EOF){
            if(ch=='\n')continue;
            data+=ch;
        }
        ifs.close();
        return data;
    }

}file;
#endif //CLION_FILEOPERATION_H