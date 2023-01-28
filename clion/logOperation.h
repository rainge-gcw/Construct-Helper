//
// Created by gcw on 23-1-28.
//

#ifndef CLION_LOGOPERATION_H
#define CLION_LOGOPERATION_H
#include "fileOperation.h"
#include "httplib.h"
#include "poolOperation.h"
#include "judgeOperation.h"
using httplib::Request;
string log_base_url;

ConcurrenceQueue<string>log_queue;

class logOperator{
    logOperator(){
        char tmp[256];
        getcwd(tmp, 256);
        string url=tmp;
        if(!FileOperator::exists_dir(url+"/log")){
            FileOperator::create_dir(url+"/log");
        }
        log_base_url=url+"/log";
        if(!FileOperator::exists_dir(url+"/log/http")){
            FileOperator::create_dir(url+"/log/http");
        }
        if(!FileOperator::exists_dir(url+"/log/user_error")){//检查用户信息时发现的错误
            FileOperator::create_dir(url+"/log/user_error");
        }
        if(!FileOperator::exists_dir(url+"/log/system_error")){//系统运行时出现的错误
            FileOperator::create_dir(url+"/log/system_error");
        }
        //初始化轮询
    }
    static void log_http(const Request& req);
    static string get_http_dir();
};

#define LOG_HTTP(massage) LOG_FATAL(log_fp, "HTTP: "#massage);

void logOperator::log_http(const Request &req) {//记录所有http请求
    string log_data;
    FILE *log_fp = JudgeOperator::log_open(get_http_dir().c_str());
    //LOG_FATAL(log_fp,"http: "#error);
    //log_write(LOG_LEVEL_FATAL, __FILE__, __LINE__, log_fp, ##x);

    JudgeOperator::log_close(log_fp);
}

string logOperator::get_http_dir() {
    string res=log_base_url+"/log/http/";
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm* tmNow = localtime(&tt);
    res+=to_string(tmNow->tm_year+1900)+"_"+to_string((tmNow->tm_mon + 1))+"_"+to_string((tmNow->tm_mday))+".txt";
    if(!FileOperator::exists_txt(res))FileOperator::create_txt(res);
    return res;
}

#endif //CLION_LOGOPERATION_H
