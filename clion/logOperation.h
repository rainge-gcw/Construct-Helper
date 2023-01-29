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


class logOperator{
public:
    static void init(){
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
    static string get_dir(const string&);
    static void log_system_error(const string &s);
    static void log_user_error(const string &s);
};

#define LOG_HTTP(massage) LOG_FATAL(log_fp, "HTTP: "#massage);

void logOperator::log_http(const Request &req) {//记录所有http请求
    FILE *log_fp = JudgeOperator::log_open(get_dir("http").c_str());
    int log_fd = fileno((FILE *) log_fp);
    if (flock(log_fd, LOCK_EX) == 0){
        if (write(log_fd, (req.body+"\n").c_str(), (size_t) req.body.size()+1) < 0) {
            fprintf(stderr, "write error");
            fprintf(stderr, "%s", (req.body).c_str());
            return;
        }
        flock(log_fd, LOCK_UN);
    }else {
        fprintf(stderr, "flock error");
        return;
    }
    JudgeOperator::log_close(log_fp);
}

string logOperator::get_dir(const string &type) {
    string res=log_base_url+"/"+type+"/";
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    struct tm* tmNow = localtime(&tt);
    res+=to_string(tmNow->tm_year+1900)+"_"+to_string((tmNow->tm_mon + 1))+"_"+to_string((tmNow->tm_mday))+".txt";
    if(!FileOperator::exists_txt(res))FileOperator::create_txt(res);
    return res;
}

void logOperator::log_system_error(const string &s) {
    FILE *log_fp = JudgeOperator::log_open(get_dir("system_error").c_str());
    int log_fd = fileno((FILE *) log_fp);
    if (flock(log_fd, LOCK_EX) == 0){
        if (write(log_fd, (s+"\n").c_str(), (size_t) s.size()+1) < 0) {
            fprintf(stderr, "%s", (s.c_str());
            return;
        }
        flock(log_fd, LOCK_UN);
    }else {
        fprintf(stderr, "flock error");
        return;
    }
    JudgeOperator::log_close(log_fp);
}

void logOperator::log_user_error(const string &s) {
    FILE *log_fp = JudgeOperator::log_open(get_dir("user_error").c_str());
    int log_fd = fileno((FILE *) log_fp);
    if (flock(log_fd, LOCK_EX) == 0){
        if (write(log_fd, (s+"\n").c_str(), (size_t) s.size()+1) < 0) {
            fprintf(stderr, "%s", (s.c_str());
            return;
        }
        flock(log_fd, LOCK_UN);
    }else {
        fprintf(stderr, "flock error");
        return;
    }
    JudgeOperator::log_close(log_fp);
}


#endif //CLION_LOGOPERATION_H
