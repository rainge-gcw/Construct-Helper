
#include <iostream>
#include <queue>
#include "fileOperation.h"
#include "json.hpp"
#include "httplib.h"
#include "tokenOperation.h"
#include "base64.h"
//#include "mysqlOperation.h"
#include "userOperation.h"
#include "constructOperation.h"
#include "judgeOperation.h"
//#include "runner.c"
#include "tool.h"
using namespace std;
#define SERVER_PORT 8080  //定义端口号
#define ERROR_CODE "{\"code\":\"1\"}"
#define PASS_CODE "{\"code\":\"0\"}"
#define debug 1
using Server=httplib::Server;
using Request=httplib::Request;
using Response=httplib::Response;
using json=nlohmann::json;
#define header_init res.set_header("Access-Control-Allow-Origin", "*");res.set_header("Access-Control-Allow-Credentials", "true");res.set_header("Access-Control-Expose-Headers", "content-type");res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");res.set_header("Access-Control-Allow-Headers", "Content-Type,Access-Control-Allow-Headers,Authorization,X-Requested-With");
#define int long long
typedef unsigned long long ull;

signed main(){
    //int a;
    //cin>>a;
    //JudgeOperator::test("/home/gcw/test/1/1","/home/gcw/test/1/1.in","/home/gcw/test/1/1.out","/home/gcw/test/1/err.txt","/home/gcw/test/1/log.txt");
    /*JudgeOperator::test(1000,104857600,"/home/gcw/test/test_clion/1",
                        "/home/gcw/test/test_clion/1.in","/home/gcw/test/test_clion/1.out",
                        "/home/gcw/test/test_clion/err.txt","/home/gcw/test/test_clion/log.txt");*/
    fprintf(stderr, "123");
    string code="#include<stdio.h>\n"
                "int main(){\n"
                "  int a;\n"
                "  scanf(\"%d\",&a);\n"
                "  if(a==123)puts(\"yes\");\n"
                "  else puts(\"no\");\n"
                "  return 0;\n"
                "}";
    string input="/home/gcw/test/test_clion/1.in";
    string output="/home/gcw/test/test_clion/1.out";
    auto it=JudgeOperator::stand_judge(code,input,output);
    cout<<it.information<<endl;
    auto *r=&it.res;
    cout<<r->cpu_time<<endl;
    cout<<r->real_time<<endl;
    cout<<r->memory<<endl;
    cout<<r->signal<<endl;
    cout<<r->exit_code<<endl;
    cout<<r->result<<endl;
    cout<<r->error<<endl;

    return 0;
    Server srv;
    TokenOperator tokenOperator;


    srv.Post("/register", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("register")){
            if(req.get_param_value("register")=="1"){
                UserOperator usr(req.get_param_value("user_id"),req.get_param_value("user_password"));
                int st=usr.registered();
                if(!st){
                    res.set_content(PASS_CODE, "text/json");
                }else{
                    res.set_content(ERROR_CODE, "text/json");
                }
            }else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }
        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/login", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("login")) {
            if(req.get_param_value("login")=="1"){
                UserOperator usr(req.get_param_value("user_id"),req.get_param_value("user_password"));
                int st=usr.password_login();
                json js;
                js["code"]=st;
                if(st==0){
                    if(debug)cout<<"存在帐号"<<endl;
                    ull token=0;
                    tokenOperator.register_token(req.get_param_value("user_id"),token);
                    cout<<token<<endl;
                    js["token"]=token;
                }else if(st==1){
                    js["token"]=0;
                }
                res.set_content(js.dump(),"text/json");
            }
            else if(req.get_param_value("login")=="2"){//使用token登录
                if(req.has_param("token")){
                    /*
                    string s_token=req.get_param_value("token");
                    string user_id=req.get_param_value("user_id");
                    ull token=tool.str_to_ull(s_token);
                     后面还要留日志
                     */
                    int st=tokenOperator.check(tool.str_to_ull(req.get_param_value("token")),req.get_param_value("user_id"));
                    json js;
                    js["code"]=st;
                    res.set_content(js.dump(),"text/json");
                }else{//没有token
                    res.set_content(ERROR_CODE,"text/json");
                    return;
                }
            }
            else{//login数字不对
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{//没有login
            res.set_content(ERROR_CODE, "text/json");
        }
        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/query", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("query")){
            string query_id=req.get_param_value("query");
            if(query_id=="1"){
                vector<string>g;
                string url=string(req.get_param_value("user_id"));
                file.get_dir(file.user_id_to_url(url)+"/problem_list",g);
                string Title;
                for(int i=0;i<g.size();i++){
                    Title+=g[i];
                    if(i!=g.size()-1)Title+=',';
                }
                json js;
                js["code"]="0";
                js["Title"]=Title;
                js["sum"]=g.size();
                cout<<js.dump()<<endl;
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="2"){
                string url=file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/statement.md";
                string tmp;
                file.read_txt(url,tmp);
                json js;
                js["txt"]=tmp;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="3"){
                string url=file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/type.txt";
                ifstream ifs(url,ios::in);
                string type,judge,tmp,limit;
                int sum;
                ifs>>tmp>>tmp>>judge>>sum;
                json js;
                js["sum"]=sum;
                js["judge"]=judge;
                for(int i=1;i<=sum;i++){
                    ifs>>tmp;
                    type+=tmp;
                    if(tmp=="other"){
                        tmp.clear();
                        char ch;
                        while(ifs.get(ch))
                            if(ch=='\n')break;
                    }else{
                        tmp.clear();char ch;
                        while(ifs.get(ch)){
                            if(ch=='\n')break;
                            tmp+=ch;
                        }
                    }
                    limit+=tmp;
                    if(i!=sum){
                        type+=",";limit+=",";
                    }
                }
                js["type"]=type;
                js["limit"]=limit;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="4"||query_id=="5"){
                string url=file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/spj_code.txt";
                ifstream ifs(url,ios::in);
                string s;char ch;
                while(ifs.get(ch))s+=ch;
                json js;
                if(req.get_param_value("query")=="4"){
                    if(s.size()!=0){
                        js["have"]="1";
                    }else{
                        js["have"]="0";
                    }
                }else{
                    js["data"]=s;
                }
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="6"||query_id=="7"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"))+"/date/"+req.get_param_value("data_name");
                if(query_id=="6"){
                    url+=".in";
                }else if(query_id=="7"){
                    url+=".out";
                }
                ifstream ifs(url,ios::in);
                string data;
                char ch;
                while(ifs.get(ch)){
                    data+=ch;
                    if(data.size()>=200)break;
                }
                ifs.close();
                if(debug)cout<<data<<endl;
                if(data.size()<0)data=" ";
                json js;
                js["data"]=data;
                js["code"]=0;
                res.set_content(js.dump(),"text/json");
            }
            else if(query_id=="8"){

            }
            else if(query_id=="9"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"))+"/date";
                DIR* d = opendir(url.c_str());
                if(d==nullptr){
                    res.set_content(ERROR_CODE, "text/json");return;
                }
                struct dirent* entry;
                set<string>s;
                while ((entry=readdir(d)) != nullptr){
                    string tmp;
                    int len=strlen(entry->d_name);
                    for(int i=0;i<len;i++){
                        if(entry->d_name[i]=='.')break;
                        tmp+=entry->d_name[i];
                    }
                    if(tmp.size()>0)
                        s.insert(tmp);
                }
                closedir(d);
                json js;
                string data;
                for(auto i:s){
                    data+=i+',';
                }
                if(data.size())
                    data.pop_back();
                if(debug)cout<<data<<endl;
                js["data"]=data.size()?data:"";
                js["code"]="0";
                res.set_content(js.dump(),"text/json");
            }
            else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/add", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("add")){
            if(req.get_param_value("add")=="1"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                if(FileOperator::exists_dir(url)){
                    res.set_content(ERROR_CODE, "text/json");
                    return;
                }
                file.create_dir(url);
                file.create_dir(url+"/date");
                file.create_txt(url+"/type.txt");
                file.create_txt(url+"/statement.md");
                if(req.get_param_value("judge_type")=="SPJ")file.create_txt(url+"/spj_code.cpp");
                string tmp="Title "+req.get_param_value("Title")+"\n"+req.get_param_value("judge_type")+"\n0";
                file.write_txt(url+"/type.txt",tmp);
                res.set_content(PASS_CODE, "text/json");
            }
            else if(req.get_param_value("add")=="2"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                cout<<url<<endl;
                if(!file.exists_dir(url)){
                    cout<<"没有这个文件"<<endl;
                    res.set_content(ERROR_CODE, "text/json");
                    return ;
                }
                string data_name=req.get_param_value("data_name");
                if(file.exists_txt(url+"/date/"+ data_name+".in")){
                    cout<<"有重名数据"<<endl;
                    res.set_content(ERROR_CODE, "text/json");
                    return ;
                }

                file.create_txt(url+"/date/"+ data_name+".in");
                file.create_txt(url+"/date/"+ data_name+".out");
                if(file.read_judge_type(url+"/type.txt")=="SPJ"){
                    file.create_txt(url+"/date/out_"+ data_name+".txt");
                    file.create_txt(url+"/date/res_"+ data_name+".txt");
                }
                string tmp;
                if(req.get_param_value("data_type")=="mat"||req.get_param_value("data_type")=="GraphWithValue"){
                    tmp=req.get_param_value("data_type")+" "+req.get_param_value("n")+" "+
                            req.get_param_value("m")+" "+req.get_param_value("l")+" "+
                            req.get_param_value("r")+" "+req.get_param_value("unique");
                }else if(req.get_param_value("data_type")=="GraphWithOutValue"){
                    tmp=req.get_param_value("data_type")+" "+req.get_param_value("n")+" "+
                        req.get_param_value("m");
                }else{
                    tmp=req.get_param_value("data_type");
                }
                file.add_date(url+"/type.txt",tmp);
                json js;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(req.get_param_value("add")=="3"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string tmp=req.get_param_value("code");
                file.write_txt(url+"/spj_code.cpp",tmp);
                if(file.compile_code(url)){
                    res.set_content(PASS_CODE, "text/json");
                }else{
                    res.set_content(ERROR_CODE, "text/json");
                }
            }
            else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/delete", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("delete")){
            if(req.get_param_value("delete")=="1"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                file.delete_dir(url);
                res.set_content(PASS_CODE, "text/json");
            }else if(req.get_param_value("delete")=="2"){
                FileOperator::Type t;
                string url=file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/date/"+req.get_param_value("data_name");
                if(file.exists_dir(url+".in"))
                    file.delete_file(url+".in");
                if(file.exists_dir(url+".out"))
                    file.delete_file(url+".out");

                res.set_content(PASS_CODE, "text/json");
            }else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }
        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/modify", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("modify")) {
            if(req.get_param_value("modify")=="1"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string tmp=req.get_param_value("txt");
                file.write_txt(url+"/statement.md",tmp);
                res.set_content(PASS_CODE, "text/json");
            }else if(req.get_param_value("modify")=="2"){
                FileOperator::Type t;
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("old_Title"));
                t.type_read(url+"/type.txt");
                t.Title=req.get_param_value("new_Title");
                t.type_write(url+"/type.txt");
                file.rename_dir(string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("old_Title")),
                                string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("new_Title")));
                res.set_content(PASS_CODE, "text/json");
            }else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/download", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("download")){
            if(req.get_param_value("download")=="1"){
                /*
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                vector<string>g;
                g.push_back(url+"/date/"+req.get_param_value("id")+".in");
                g.push_back(url+"/date/"+req.get_param_value("id")+".out");
                g.push_back(url+"/date/out_"+req.get_param_value("id")+".txt");
                g.push_back(url+"/date/res_"+req.get_param_value("id")+".txt");
                string resUrl=file.zip(g,url+"/date",0);
                res.set_header("Content-Disposition","blob");
                ifstream ifs(resUrl,ios::binary|ios::in);
                json js;
                js["code"]="0";
                string tmp((istreambuf_iterator<char>(ifs)),istreambuf_iterator<char>());
                char * enc=( char *)oceanstar::acl_base64_encode(tmp.c_str(),tmp.size());
                js["data"]=enc;
                res.set_content(js.dump(), "application/x-zip-compressed;");
                file.delete_file(resUrl);
                if(enc){
                    free(enc);
                    enc= nullptr;
                }else{
                }
                 */
            }
            else if(req.get_param_value("download")=="2"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                vector<string>files;
                file.getFileNames(url+"/date",files);
                string resUrl=file.zip(files,url,0);
                res.set_header("Content-Disposition","blob");
                ifstream ifs(resUrl,ios::binary|ios::in);
                json js;
                js["code"]="0";
                string tmp((istreambuf_iterator<char>(ifs)),istreambuf_iterator<char>());
                char * enc=( char *)oceanstar::acl_base64_encode(tmp.c_str(),tmp.size());
                js["data"]=enc;
                res.set_content(js.dump(), "application/x-zip-compressed;");
                file.delete_file(resUrl);
                if(enc){
                    free(enc);
                    enc= nullptr;
                }else{
                }
            }
            else{

            }

        }
        else{

        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/build", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("build")){
            if(req.get_param_value("build")=="1"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                vector<pair<string,string>>g=file.read_date_type(url);
                for(int i=0;i<g.size();i++){
                    if(to_string(i+1)!=req.get_param_value("id"))continue;
                    vector<int>lim=constructOperator::xs_split_string_int(g[i].second);
                    if(g[i].first=="mat"){
                        vector<long long>data=constructOperator::get_array_int(lim[0]*lim[1],lim[2],lim[3],lim[4],0);
                        string res;
                        res+=to_string(lim[0])+" "+to_string(lim[1])+'\n';
                        for(int j=0;j<data.size();j++){
                            res+=to_string(data[j])+" ";
                            if(j%lim[1]==lim[1]-1)res+='\n';
                        }
                        file.write_txt(url+"/date/"+to_string(i+1)+".in",res);
                    }else if(g[i].first=="GraphWithValue"){
                        vector<node_val_int>data=constructOperator::get_map_lineval_int_aim_link(lim[0],lim[1],0,lim[2],lim[3],lim[4]);

                        string res=to_string(lim[0])+" "+to_string(lim[1])+'\n';
                        for(auto i:data){
                            res+=to_string(i.u)+" "+to_string(i.v)+" "+to_string(i.w)+'\n';
                        }
                        file.write_txt(url+"/date/"+to_string(i+1)+".in",res);
                    }else if(g[i].first=="GraphWithOutValue"){
                        vector<node_val_int>data=constructOperator::get_map_lineval_int_aim_link(lim[0],lim[1],0,0,1e9,0);

                        string res=to_string(lim[0])+" "+to_string(lim[1])+'\n';
                        for(auto i:data){
                            res+=to_string(i.u)+" "+to_string(i.v)+" "+'\n';
                        }
                        file.write_txt(url+"/date/"+to_string(i+1)+".in",res);
                    }
                }
                res.set_content(PASS_CODE, "text/json");
            }
            else if(req.get_param_value("build")=="2"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                file.write_txt(url+"/tmp.cpp",req.get_param_value("txt"));
                string tmp="g++ -Wall -std=c++17 "+url+"/tmp.cpp -o "+url+"/tmp";
                system(tmp.c_str());
                tmp=url+"/tmp > "+url+"/date/"+req.get_param_value("data_name")+".in";
                system(tmp.c_str());
                res.set_content(PASS_CODE, "text/json");
            }else if(req.get_param_value("build")=="3"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                file.write_txt(url+"/work.cpp",req.get_param_value("txt"));
                string tmp="g++ -Wall -std=c++17 "+url+"/work.cpp -o "+url+"/work";
                system(tmp.c_str());
                tmp=url+"/work < "+url+"/date/"+req.get_param_value("data_name")+".in" +" > "+url+"/date/"+req.get_param_value("data_name")+".out";
                system(tmp.c_str());
                res.set_content(PASS_CODE, "text/json");
            }else{
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/test", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("test")){
            if(req.get_param_value("test")=="1"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                file.write_txt(url+"/test.cpp",req.get_param_value("txt"));
                string tmp="g++ -Wall -std=c++17 "+url+"/test.cpp -o "+url+"/test";
                system(tmp.c_str());
                file.write_txt(url+"/tmp.out","");
                string order=url+"/test < "+url+"/date/"+req.get_param_value("data_name")+".in > "+url+"/tmp.out";
                system(order.c_str());
                string usr_out,stand_out;
                file.read_txt(url+"/date/"+req.get_param_value("data_name")+".out",stand_out);
                file.read_txt(url+"/tmp.out",usr_out);
                usr_out=file.clear_oher(usr_out);
                stand_out=file.clear_oher(stand_out);
                json js;
                if(usr_out==stand_out)js["return"]="AC";
                else js["return"]="WA";
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(req.get_param_value("test")=="2"){
                string url=string(file.user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string id=req.get_param_value("id");
                file.write_txt(url+"/test.cpp",req.get_param_value("txt"));
                string order="g++ -Wall -std=c++17 "+url+"/test.cpp -o "+url+"/test";
                system(order.c_str());
                file.write_txt(url+"/tmp.out","");
                order=url+"/test < "+url+"/date/"+id+".in > "+url+"/date/out_"+id+".txt";
                system(order.c_str());
                order=url+"/spj_code "+url+"/date/"+id+".in "+url+"/date/"+id+".out "+
                        url+"/date/out_"+id+".txt "+url+"/data/res_"+id+".txt";
                system(order.c_str());
                string re;
                file.read_txt(url+"/data/res_"+id+".txt",re);
                json js;
                js["return"]=re;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
        }else{
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.listen("0.0.0.0", SERVER_PORT);
}

