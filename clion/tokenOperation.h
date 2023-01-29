//
// Created by hadoop on 1/15/23.
//

#ifndef CLION_TOKENOPERATION_H
#define CLION_TOKENOPERATION_H
#include<unordered_map>
#include<time.h>
typedef unsigned long long ull;
typedef pair<int,int> pii;
using std::unordered_map;
using std::string;
struct TokenOperator{
    map<ull,string>mp;
    ull base1=133331;
    int register_token(const string &id,ull &token);

    static ull calc_hash(const string&s,ull base);

    ull get_key(const string &s) const;

    int check(const ull &s,const string &id);

};

int TokenOperator::register_token(const string &id, ull &token) {
    ull key=get_key(id);
    token=key;
    if(mp.count(key)){//live
        return 1;
    }else{
        mp[key]=id;
        return 0;
    }
}

ull TokenOperator::calc_hash(const string &s, ull base) {
    ull res=0;
    for(auto i:s){
        res=res*base+ull(i);
    }
    return res;
}

ull TokenOperator::get_key(const string &s) const {
    return calc_hash(s,base1);
}

int TokenOperator::check(const ull &s, const string &id) {
    ull key= get_key(id);
    if(!mp.count(key))return 1;
    else if(mp[key]!=id)return 2;
    return 0;
}


/*
class TokenOperator{
public:
    static map<ull,string>mp=map<ull,string>;//token->user_id
    //static queue<pair<ull,ull>,>
    static ull base1=133331;
    /*
     * 注册用户的token
     * 传入
     * id:用户id
     * token:返回的token值,用传参获取
     * 返回值为运行结果
     * 0:运行正常
     * 1:这个用户的token已经存在
     *
    static int register_token(const string &id,ull &token);


    static ull calc_hash(const string&s,ull base);


    static ull get_key(const string &s);

    /*
     * 检查一个用户的状态
     * 传入:用户id
     * 11:mp中不存在这个id对应的token
     * 12:存在token,但id对不上(冲突应该怎么解决?)
     * 0:存在token 并且与id对的上
     *
    static int check(const ull &s,const string &id);
};
ull TokenOperator::calc_hash(const string &s,ull base) {
    ull res=0;
    for(auto i:s){
        res=res*base+ull(i);
    }
    return res;
}
ull TokenOperator::get_key(const string &s) {
    return calc_hash(s,base1);
}
int TokenOperator::register_token(const string &id,ull &token) {
    ull key=get_key(id);
    token=key;
    if(mp.count(key)){//live
        return 1;
    }else{
        mp[key]=id;
        return 0;
    }
}

int TokenOperator::check(const ull &s, const string &id) {
    ull key= get_key(id);
    if(key!=s)return 13;
    if(!mp.count(key))return 11;
    else if(mp[key]!=id)return 12;
    return 0;
}
*/

#endif //CLION_TOKENOPERATION_H
