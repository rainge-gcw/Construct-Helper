
#include <iostream>
#include <queue>
#include "fileOperation.h"
#include "json.hpp"
#include "httplib.h"
#include "tokenOperation.h"
#include "base64.h"
#include "userOperation.h"
#include "constructOperation.h"
#include "judgeOperation.h"
#include "tool.h"
#include "logOperation.h"
using namespace std;
#define SERVER_PORT 8080  //定义端口号
#define ERROR_CODE "{\"code\":\"1\"}"
#define PASS_CODE "{\"code\":\"0\"}"
#define debug 1
using Server=httplib::Server;
using Request=httplib::Request;
using Response=httplib::Response;
using json=nlohmann::json;
#define header_init res.set_header("Access-Control-Allow-Origin", "*");\
res.set_header("Access-Control-Allow-Credentials", "true");\
res.set_header("Access-Control-Expose-Headers", "content-type");\
res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");\
res.set_header("Access-Control-Allow-Headers", "Content-Type,Access-Control-Allow-Headers,Authorization,X-Requested-With"); \
logOperator::log_http(req);
#define int long long
typedef unsigned long long ull;

signed main(){

    Server srv;
    logOperator::init();
    TokenOperator tokenOperator;
    FileOperator::init();
    srv.Post("/register", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("register")){
            if(req.get_param_value("register")=="1"){
                UserOperator usr(req.get_param_value("user_id"),req.get_param_value("user_password"));
                string massage;
                int st=usr.registered(massage);
                if(!st){
                    res.set_content(PASS_CODE, "text/json");
                }else{
                    if(st==1){//已经存在
                        logOperator::log_user_error(req.body+" "+massage);
                    }else if(st==2){
                        logOperator::log_system_error(req.body+" "+massage);
                    }
                    res.set_content(ERROR_CODE, "text/json");
                }
            }else{
                logOperator::log_user_error(req.body+" register!=1");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_user_error(req.body+" no register");
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
                    ull token=0;
                    tokenOperator.register_token(req.get_param_value("user_id"),token);
                    js["token"]=token;
                }else if(st==1){//密码不对
                    logOperator::log_user_error(req.body+" password_error");
                    js["token"]=0;
                }else if(st==2){//用户不存在
                    logOperator::log_user_error(req.body+" no_user");
                    js["token"]=0;
                }
                res.set_content(js.dump(),"text/json");
            }
            else if(req.get_param_value("login")=="2"){//使用token登录
                if(req.has_param("token")){
                    int st=tokenOperator.check(tool.str_to_ull(req.get_param_value("token")),req.get_param_value("user_id"));
                    json js;
                    js["code"]=st;
                    if(st==1){
                        logOperator::log_user_error(req.body+" no_this_token");
                    }else if(st==2){
                        logOperator::log_system_error(req.body+" hash_error");
                    }
                    res.set_content(js.dump(),"text/json");
                }else{//没有token
                    logOperator::log_system_error(req.body+" no_token_and_use_token_log");
                    res.set_content(ERROR_CODE,"text/json");
                    return;
                }
            }
            else{//login数字不对
                logOperator::log_system_error(req.body+" use error login number");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{//没有login
            logOperator::log_system_error(req.body+" have no login");
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
                if(!FileOperator::get_dir(FileOperator::user_id_to_url(url) + "/problem_list", g)){
                    logOperator::log_system_error(req.body+" get_dir_error");
                    res.set_content(ERROR_CODE,"text/json");
                    return;
                }
                string Title;
                for(int i=0;i<g.size();i++){
                    Title+=g[i];
                    if(i!=g.size()-1)Title+=',';
                }
                if(Title.empty())Title="no";
                json js;
                js["code"]="0";
                js["Title"]=Title;
                js["sum"]=g.size();
                cout<<js.dump()<<endl;
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="2"){
                string url=FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/statement.md";
                string tmp;
                if(!FileOperator::read_txt(url,tmp)){
                    logOperator::log_system_error(req.body+" read_statement_error");
                    res.set_content(ERROR_CODE,"text/json");
                    return;
                }
                json js;
                js["txt"]=tmp;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(query_id=="3"){
                /*
                string url=FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/type.txt";
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
                 */
            }
            else if(query_id=="4"||query_id=="5"){
                /*
                string url=FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/spj_code.txt";
                ifstream ifs(url,ios::in);
                string s;char ch;
                while(ifs.get(ch))s+=ch;
                json js;
                if(req.get_param_value("query")=="4"){
                    if(!s.empty()){
                        js["have"]="1";
                    }else{
                        js["have"]="0";
                    }
                }else{
                    js["data"]=s;
                }
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
                 */
            }
            else if(query_id=="6"||query_id=="7"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"))+"/date/"+req.get_param_value("data_name");
                if(query_id=="6"){
                    url+=".in";
                }else if(query_id=="7"){
                    url+=".out";
                }
                ifstream ifs(url,ios::in);
                if(!ifs){
                    logOperator::log_system_error(req.body+" open file fail");
                    res.set_content(ERROR_CODE,"text/json");
                    return;
                }
                string data;
                char ch;
                while(ifs.get(ch)){
                    data+=ch;
                    if(data.size()>=2000)break;
                }
                ifs.close();
                if(data.empty())data=" ";
                json js;
                js["data"]=data;
                js["code"]=0;
                res.set_content(js.dump(),"text/json");
            }
            else if(query_id=="8"){

            }
            else if(query_id=="9"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"))+"/date";
                DIR* d = opendir(url.c_str());
                if(d==nullptr){
                    logOperator::log_system_error(req.body+" open dir fail");
                    res.set_content(ERROR_CODE, "text/json");
                    return;
                }
                struct dirent* entry;
                set<string>s;
                while ((entry=readdir(d)) != nullptr){
                    string tmp;
                    auto len=strlen(entry->d_name);
                    for(int i=0;i<len;i++){
                        if(entry->d_name[i]=='.')break;
                        tmp+=entry->d_name[i];
                    }
                    if(!tmp.empty())
                        s.insert(tmp);
                }
                entry=nullptr;
                closedir(d);
                json js;
                string data;
                for(const auto& i:s){
                    data+=i+',';
                }
                if(!data.empty())
                    data.pop_back();
                js["data"]=!data.empty()?data:"";
                js["code"]="0";
                res.set_content(js.dump(),"text/json");
            }
            else{
                logOperator::log_system_error(req.body+" use error number");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_system_error(req.body+" no query");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/add", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("add")){
            if(req.get_param_value("add")=="1"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                if(FileOperator::exists_dir(url)){
                    res.set_content(ERROR_CODE, "text/json");
                    logOperator::log_user_error(req.body+" live problem");
                    return;
                }

                if(!FileOperator::create_dir(url)||
                    !FileOperator::create_dir(url+"/date")||
                    !FileOperator::create_txt(url+"/type.txt")||
                    !FileOperator::create_txt(url+"/statement.md"))
                {
                    res.set_content(ERROR_CODE, "text/json");
                    logOperator::log_user_error(req.body+" create fail");
                    return;
                }


                if(req.get_param_value("judge_type")=="SPJ"){
                    if(FileOperator::create_txt(url+"/spj_code.cpp")){
                        res.set_content(ERROR_CODE, "text/json");
                        logOperator::log_user_error(req.body+" create spj fail");
                        return;
                    }
                }


                string tmp="Title "+req.get_param_value("Title")+"\n"+req.get_param_value("judge_type")+"\n0";
                if(!FileOperator::write_txt(url+"/type.txt",tmp)){
                    res.set_content(ERROR_CODE, "text/json");
                    logOperator::log_user_error(req.body+" write fail");
                    return;
                }
                res.set_content(PASS_CODE, "text/json");
            }
            else if(req.get_param_value("add")=="2"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                if(!FileOperator::exists_dir(url)){
                    res.set_content(ERROR_CODE, "text/json");
                    logOperator::log_system_error(req.body+" no dir");
                    return ;
                }
                string data_name=req.get_param_value("data_name");
                if(FileOperator::exists_txt(url+"/date/"+ data_name+".in")){
                    logOperator::log_user_error(req.body+" same name");
                    res.set_content(ERROR_CODE, "text/json");
                    return ;
                }
                if(!FileOperator::create_txt(url+"/date/"+ data_name+".in")||
                !FileOperator::create_txt(url+"/date/"+ data_name+".out")){
                    res.set_content(ERROR_CODE, "text/json");
                    logOperator::log_system_error(req.body+" create fail");
                    return ;
                }

                json js;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(req.get_param_value("add")=="3"){
                /*
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string tmp=req.get_param_value("code");
                FileOperator::write_txt(url+"/spj_code.cpp",tmp);
                if(FileOperator::compile_code(url)){
                    res.set_content(PASS_CODE, "text/json");
                }else{
                    res.set_content(ERROR_CODE, "text/json");
                }
                 */
            }
            else{
                logOperator::log_system_error(req.body+" no number");
                res.set_content(ERROR_CODE, "text/json");
            }

        }else{
            logOperator::log_system_error(req.body+" no add");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/delete", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("delete")){
            if(req.get_param_value("delete")=="1"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                if(!FileOperator::delete_dir(url)){
                    logOperator::log_system_error(req.body+" delete error");
                    res.set_content(ERROR_CODE, "text/json");
                    return;
                }
                res.set_content(PASS_CODE, "text/json");
            }else if(req.get_param_value("delete")=="2"){
                FileOperator::Type t;
                string url=FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title")+"/date/"+req.get_param_value("data_name");
                if(FileOperator::exists_dir(url+".in")){
                    if(!FileOperator::delete_file(url+".in")){
                        logOperator::log_system_error(req.body+" delete error");
                        res.set_content(ERROR_CODE, "text/json");
                        return ;
                    }
                }
                else{
                    logOperator::log_system_error(req.body+" no exists");
                    res.set_content(ERROR_CODE, "text/json");
                    return ;
                }
                if(FileOperator::exists_dir(url+".out")) {
                    if (!FileOperator::delete_file(url + ".out")) {
                        logOperator::log_system_error(req.body+" delete error");
                        res.set_content(ERROR_CODE, "text/json");
                        return ;
                    }
                }
                else{
                    logOperator::log_system_error(req.body+" no exists");
                    res.set_content(ERROR_CODE, "text/json");
                    return ;
                }
                res.set_content(PASS_CODE, "text/json");
            }else{
                logOperator::log_system_error(req.body+" no number");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_system_error(req.body+" no delete");
            res.set_content(ERROR_CODE, "text/json");
        }
        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/modify", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("modify")) {
            if(req.get_param_value("modify")=="1"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string tmp=req.get_param_value("txt");
                if(!FileOperator::write_txt(url+"/statement.md",tmp)){
                    logOperator::log_system_error(req.body+" write fail");
                    res.set_content(ERROR_CODE, "text/json");
                    return;
                }
                res.set_content(PASS_CODE, "text/json");
            }else if(req.get_param_value("modify")=="2"){
                /*
                FileOperator::Type t;
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("old_Title"));
                t.type_read(url+"/type.txt");
                t.Title=req.get_param_value("new_Title");
                t.type_write(url+"/type.txt");
                FileOperator::rename_dir(string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("old_Title")),
                                string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("new_Title")));
                res.set_content(PASS_CODE, "text/json");
                 */
            }else{
                logOperator::log_system_error(req.body+" no modify num");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_system_error(req.body+" no modify");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/download", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("download")){
            if(req.get_param_value("download")=="1"){

            }
            else if(req.get_param_value("download")=="2"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                vector<string>files;
                FileOperator::getFileNames(url+"/date",files);
                string resUrl=FileOperator::zip(files,url,false);
                res.set_header("Content-Disposition","blob");
                ifstream ifs(resUrl,ios::binary|ios::in);
                json js;
                js["code"]="0";
                string tmp((istreambuf_iterator<char>(ifs)),istreambuf_iterator<char>());
                char * enc=( char *)oceanstar::acl_base64_encode(tmp.c_str(),tmp.size());
                try {
                    js["data"]=enc;
                    if(enc){
                        free(enc);
                        enc= nullptr;
                    }
                    res.set_content(js.dump(), "application/x-zip-compressed;");
                    if(!FileOperator::delete_file(resUrl)){
                        logOperator::log_system_error(req.body+" no modify num");
                        res.set_content(ERROR_CODE, "text/json");
                        return;
                    }
                }catch (...){
                    if(enc){
                        free(enc);
                        enc= nullptr;
                    }
                }
            }
            else{
                logOperator::log_system_error(req.body+" no download num");
                res.set_content(ERROR_CODE, "text/json");
            }
        }
        else{
            logOperator::log_system_error(req.body+" no download");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/build", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("build")){
            if(req.get_param_value("build")=="1"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"))+"/date/"+req.get_param_value("data_name")+".in";
                if(!FileOperator::exists_txt(url)){
                    res.set_content(PASS_CODE, "text/json");
                    logOperator::log_system_error(req.body+" no txt");
                    return;
                }
                if(constructOperator::work(req,url)){//error
                    logOperator::log_system_error(req.body+" construct fail");
                    res.set_content(ERROR_CODE, "text/json");
                }else{
                    res.set_content(PASS_CODE, "text/json");
                }
            }
            else if(req.get_param_value("build")=="2"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                info it=JudgeOperator::construct_input(req.get_param_value("txt"),url+"/date/"+req.get_param_value("data_name")+".out",url+"/date/"+req.get_param_value("data_name")+".in");
                json js;
                js["code"]=1;
                js["info"]="ok";
                if(it.res.result==0&&it.res.error==0)js["code"]=0;
                else js["info"]=it.information;
                res.set_content(js.dump(), "text/json");
            }else if(req.get_param_value("build")=="3"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                info it=JudgeOperator::construct_input(req.get_param_value("txt"),url+"/date/"+req.get_param_value("data_name")+".in",url+"/date/"+req.get_param_value("data_name")+".out");
                json js;
                js["code"]=1;
                js["info"]="ok";
                if(it.res.result==0&&it.res.error==0)js["code"]=0;
                else js["info"]=it.information;
                res.set_content(js.dump(), "text/json");
            }else{
                logOperator::log_system_error(req.body+" no build num");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_system_error(req.body+" no build");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.Post("/test", [&](const Request& req, Response& res) {
        header_init
        if(req.has_param("test")){
            if(req.get_param_value("test")=="1"){
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                auto judge_res=JudgeOperator::stand_judge(req.get_param_value("txt"),url+"/date/"+req.get_param_value("data_name")+".in",url+"/date/"+req.get_param_value("data_name")+".out");
                std::shared_ptr<result> r=std::make_shared<result>(judge_res.res);
                cout<<r->cpu_time<<endl;
                cout<<r->real_time<<endl;
                cout<<r->memory<<endl;
                cout<<r->signal<<endl;
                cout<<r->exit_code<<endl;
                cout<<r->result<<endl;
                cout<<r->error<<endl;
                json js;
                js["return"]=judge_res.information;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
            }
            else if(req.get_param_value("test")=="2"){
                /*
                string url=string(FileOperator::user_id_to_url(req.get_param_value("user_id"))+"/problem_list/"+req.get_param_value("Title"));
                string id=req.get_param_value("id");
                FileOperator::write_txt(url+"/test.cpp",req.get_param_value("txt"));
                string order="g++ -Wall -std=c++17 "+url+"/test.cpp -o "+url+"/test";
                system(order.c_str());
                FileOperator::write_txt(url+"/tmp.out","");
                order=url+"/test < "+url+"/date/"+id+".in > "+url+"/date/out_"+id+".txt";
                system(order.c_str());
                order=url+"/spj_code "+url+"/date/"+id+".in "+url+"/date/"+id+".out "+
                        url+"/date/out_"+id+".txt "+url+"/data/res_"+id+".txt";
                system(order.c_str());
                string re;
                FileOperator::read_txt(url+"/data/res_"+id+".txt",re);
                json js;
                js["return"]=re;
                js["code"]="0";
                res.set_content(js.dump(), "text/json");
                 */
            }else{
                logOperator::log_system_error(req.body+" no test num");
                res.set_content(ERROR_CODE, "text/json");
            }
        }else{
            logOperator::log_system_error(req.body+" no test");
            res.set_content(ERROR_CODE, "text/json");
        }

        std::cout << "Received a request of POST [get_info]." << std::endl;
    });

    srv.listen("0.0.0.0", SERVER_PORT);
}

