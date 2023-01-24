//
// Created by hadoop on 22-12-1.
//

#ifndef CLION_MYSQLOPERATION_H
#define CLION_MYSQLOPERATION_H


#include <cstdio>
#include "mysql.h"

class MysqlOperator{
public:
    static int add(const string&,const string&,vector<string>&);
    static int del(const string&,const string&);
    static void create_table();
};
void MysqlOperator::create_table() {
    
}


int MysqlOperator::add(const string & base_name, const string &table_name, vector<string> &g) {
    MYSQL conn;
    int res;
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","010927", base_name.c_str(),0,nullptr,CLIENT_FOUND_ROWS)){
        //"root":数据库管理员 "":root密码 "test":数据库的名字
        string s="insert into "+table_name+" values(";
        for(int i=0;i<g.size();i++){
            s+='\'';
            s+=g[i];
            s+='\'';
            if(i!=g.size()-1)s+=',';
        }
        s+=");";
        cout<<s<<endl;
        res=mysql_query(&conn,s.c_str());
        mysql_close(&conn);
        if(res)return res;
    }else{
        return 1;
    }
    return 0;
}

int MysqlOperator::del(const string &, const string &) {
    return 0;
}



#endif //CLION_MYSQLOPERATION_H
