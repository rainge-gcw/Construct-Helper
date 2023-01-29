//
// Created by hadoop on 22-11-27.
//

#ifndef CLION_USEROPERATION_H
#define CLION_USEROPERATION_H
#include <utility>

#include "fileOperation.h"
#include "logOperation.h"
class UserOperator{
public:
    string usr_name;
    string usr_password;

    UserOperator(string,string);
    ~UserOperator();
    [[nodiscard]] int check_user_exists() const;
    int registered(string& error_info);
    [[nodiscard]] int password_login() const;
    static int token_login();
};
UserOperator::UserOperator(std::string string1, std::string string2) {usr_name=std::move(string1);usr_password=std::move(string2);}
UserOperator::~UserOperator() = default;
//1 存在 0不存在
int UserOperator::check_user_exists() const{
    if(FileOperator::exists_dir(FileOperator::user_id_to_url(usr_name))){
        fprintf(stderr, "exists");
        return 1;
    }
    return 0;
}

//0注册成功 1注册失败:已经有人注册 2创建失败
int UserOperator::registered(string& error_info) {
    if(check_user_exists()){
        fprintf(stderr, "exists");
        error_info="usr_id_exists";
        return 1;
    }
    string url=FileOperator::user_id_to_url(usr_name);
    string s=baseUrl;
    for(auto i:usr_name){
        s+='/';s+=i;
        if(!FileOperator::exists_dir(s))
            FileOperator::create_dir(s);
    }
    if(!FileOperator::create_dir(url)){
        error_info="system_error,create fail";
        return 2;
    }else{
        FileOperator::create_txt(url+"/user_information.txt");
        FileOperator::create_dir(url+"/problem_list");
        FileOperator::write_txt(url+"/user_information.txt","user_id "+usr_name+"\nuser_password "+usr_password);
        return 0;
    }
}
//帐号密码登录
//登录成功返回0
int UserOperator::password_login() const  {
    if(check_user_exists()==0)
        return 2;
    string url=FileOperator::user_id_to_url(usr_name)+"/user_information.txt";
    string tmp;
    FileOperator::read_password(url,tmp);
    if(tmp==usr_password){
        return 0;
    }else{
        return 1;
    }
}

int UserOperator::token_login() {
    return 0;
}


#endif //CLION_USEROPERATION_H
