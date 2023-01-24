//
// Created by hadoop on 1/16/23.
//

#ifndef CLION_TOOL_H
#define CLION_TOOL_H
typedef unsigned long long ull;
#include<string>
using std::string;
class Tool{
public:
    static ull str_to_ull(const  string& s);
}tool;

ull Tool::str_to_ull(const string &s) {
    ull res=0;
    for(auto i:s){
        res*=10;
        res+=(i-'0');
    }
    return res;
}

#endif //CLION_TOOL_H
