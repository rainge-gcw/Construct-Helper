//
// Created by hadoop on 22-12-11.
//

#ifndef CLION_CONSTRUCTOPERATION_H
#define CLION_CONSTRUCTOPERATION_H

//#include <bits/stdc++.h>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <random>
#include "httplib.h"
using std::string;
using std::vector;
using std::swap;
using std::pair;
using std::map;
using std::min;
using std::max;
using std::queue;
using std::set;
using httplib::Request;
#define int long long
struct node_val_int {
    int u, v, w;
};
struct node_val_double {
    int u, v;
    double w;
};

struct n_l_r_unique_val{
    int n,l,r,unique_val;
    int init(const httplib::Request& req){
        if(!req.has_param("n"))
            return 1;
        this->n=stoll(req.get_param_value("n"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(this->l>this->r)
            return 2;

        if(this->unique_val&&r-l<n)
            return 3;
        return 0;
    }
};
struct n_l_r_unique_val_k{
    int n,l,r,unique_val,k;
    int init(const httplib::Request& req){
        if(!req.has_param("n"))
            return 1;
        this->n=stoll(req.get_param_value("n"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(!req.has_param("k"))this->k=2;
        else this->k=stoll(req.get_param_value("k"));

        if(this->l>this->r)return 2;
        if(this->unique_val&&r-l<n)return 3;

        return 0;
    }
};
struct n_m_ring_l_r_unique_val{
    int n,m,ring,l,r,unique_val;
    int init(const httplib::Request& req){
        if(!req.has_param("n")||!req.has_param("m")||!req.has_param("ring"))
            return 1;

        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));
        this->ring=stoll(req.get_param_value("ring"));



        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));
        if(this->l>this->r)return 2;
        if(this->unique_val&&r-l<n)return 3;
        if(this->m<this->n-1)return 4;
        if(this->ring&&this->l<0)return 5;//可能会构造出负环



        return 0;
    }
};
struct n_m_l_r_unique_val{
    int n,m,l,r,unique_val;
    int init(const httplib::Request& req){
        if(!req.has_param("n")||!req.has_param("m"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(this->l>this->r)return 2;
        if(this->unique_val&&r-l<n)return 3;

        return 0;
    }
};
struct n_m_l_r_unique_val2{//for star_graph
    int n,m,l,r,unique_val;
    int init(const httplib::Request& req){
        if(!req.has_param("n")||!req.has_param("m"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(this->unique_val&&r-l<n)return 3;

        return 0;
    }
};
struct n_m_l_r_unique_val_half{
    int n,m,l,r,unique_val,half;
    int init(const httplib::Request& req){
        if(!req.has_param("n")||!req.has_param("m"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(!req.has_param("half"))this->half=0;
        else this->half=stoll(req.get_param_value("half"));

        if(this->l>this->r)return 2;
        if(this->unique_val&&r-l<n)return 3;

        return 0;
    }
};
struct n_{
    int n;
    int init(const httplib::Request& req){
        if(!req.has_param("n"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        return 0;
    }
};
struct n_m_l_r{
    int n,m,l,r;
    bool init(const httplib::Request& req){
        if(!req.has_param("n")||!req.has_param("m"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));
        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(this->l>this->r)return 2;

        return 0;
    }
};
struct n_m_cnt_l_r_unique_val{
    int n,m,cnt,l,r,unique_val;
    int init(const httplib::Request& req) {
        if(!req.has_param("n")||!req.has_param("m"))
            return 1;
        this->n=stoll(req.get_param_value("n"));
        this->m=stoll(req.get_param_value("m"));

        if(!req.has_param("cnt"))this->cnt=this->n/2;
        else this->cnt=stoll(req.get_param_value("cnt"));

        if(!req.has_param("l"))this->l=1;
        else this->l=stoll(req.get_param_value("l"));

        if(!req.has_param("r"))this->r=1e9;
        else this->r=stoll(req.get_param_value("r"));

        if(!req.has_param("unique_val"))this->unique_val=0;
        else this->unique_val=stoll(req.get_param_value("unique_val"));

        if(this->l>this->r)return 2;
        if(this->unique_val&&r-l<n)return 3;

        return 0;
    }
};

class constructOperator{
public:
    static int xs_string_to_int(const string& s);
    static vector<int> xs_split_string_int(string& s);
    static int randed_int(int a, int b);
    static double random_double(double l, double r);
    static vector<int> get_array_int(int n, int l, int r, bool unique_val, bool shuffle);
    static vector<double> get_array_double(int n, double l, double r, bool unique_val, double eps, bool shuffle);
    static vector<node_val_int> get_tree_lineval_int(int n, int l, int r, bool unique_val);
    static vector<node_val_double> get_tree_lineval_double(int n, double l, double r, double eps, bool unique_val);
    static vector<node_val_int> get_k_tree(int n, int l, int r, int unique, int k);
    static vector<node_val_int> get_map_lineval_int_aim_link(int n, int m, bool ring, int l, int r,bool unique_val);
    static vector<node_val_int> get_map_lineval_int_unaim_link(int n, int m, bool ring, int l, int r,bool unique_val);
    static bool check_negative_ring(vector<node_val_int> map_line, int n, int m);
    static vector<node_val_int> get_negative_ring(int n, int m, int l, int r, bool unique_val);
    static vector<node_val_int> get_dichotomous_chart(int Lcnt, int Rcnt, int m, int l, int r, bool unique_val);
    static vector<node_val_int> get_bipartite_graph(int n,int m,int cnt,int l,int r,bool unique_val);
    static vector<node_val_int>get_cactus(int n,int l, int r, bool unique_val);
    static vector<node_val_int> get_eulerian(int n, int m, int l, int r, int unique_val, bool half);
    static vector<node_val_int> get_star_graph(int n, int m, int l, int r, int unique_val);
    static vector<int> get_primes(int n);
    static int qmi(int a, int k, int p);
    static bool check_big_primes(int n);
    static int get_big_primes(int l, int r);
    static vector<int> get_eulers(int n);
    static vector<int> hack_unordered_map(int n);
    static vector<node_val_int> hack_spfa(int n, int m, int l, int r);
    static int work(const Request& req,const string& url){
        string type=req.get_param_value("type");
        //sam优化?
        if(type=="tree"){
            n_l_r_unique_val limit{};
            if(limit.init(req)){
                return 1;
            }
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<'\n';
            auto data= get_tree_lineval_int(limit.n,limit.l,limit.r,limit.unique_val);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="K-trees"){
            n_l_r_unique_val_k limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<'\n';
            auto data= get_k_tree(limit.n,limit.l,limit.r,limit.unique_val,limit.k);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="DAG"||type=="DCG"){
            n_m_ring_l_r_unique_val limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            auto data= get_map_lineval_int_aim_link(limit.n,limit.m,limit.ring,limit.l,limit.r,limit.unique_val);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="no_DAG"||type=="no_DCG"){//无向无环图
            n_m_ring_l_r_unique_val limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            auto data= get_map_lineval_int_unaim_link(limit.n,limit.m,limit.ring,limit.l,limit.r,limit.unique_val);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="NRG"){
            n_m_l_r_unique_val limit{};
            if(limit.init(req))return 1;
            if(limit.l>0||abs(limit.l)<limit.r)return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            //notice:可以改成挂负环的方式
            auto data= get_negative_ring(limit.n,limit.m,limit.l,limit.r, false);
            for(const auto&i:data){
                ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
            }
            ofs.close();
            return 0;
        }
        else if(type=="bipartite_graph"){
            n_m_cnt_l_r_unique_val limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            auto data= get_bipartite_graph(limit.n,limit.m,limit.cnt,limit.l,limit.r,limit.unique_val);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="cactus_graph"){//
            n_l_r_unique_val limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            auto data= get_cactus(limit.n,limit.l,limit.r,limit.unique_val);
            ofs<<limit.n<<" "<<data.size()<<'\n';
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="euler_graph"){
            n_m_l_r_unique_val_half limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            auto data= get_eulerian(limit.n,limit.m,limit.l,limit.r,limit.unique_val,limit.half);
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="star_graph"){
            n_m_l_r_unique_val2 limit{};
            if(limit.init(req))return 1;
            auto data=get_star_graph(limit.n,limit.m,limit.l,limit.r,limit.unique_val);
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<'\n';
            if(req.has_param("l")&&req.has_param("r")&&req.has_param("unique_val")){
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
                }
            }else{
                for(const auto&i:data){
                    ofs<<i.u<<" "<<i.v<<'\n';
                }
            }
            ofs.close();
            return 0;
        }
        else if(type=="hack_map"){
            n_ limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<'\n';
            auto data= hack_unordered_map(limit.n);
            for(const auto&i:data){
                ofs<<i<<' ';
            }
            ofs.close();
            return 0;
        }
        else if(type=="hack_spfa"){
            n_m_l_r limit{};
            if(limit.init(req))return 1;
            ofstream ofs(url,ios::out);
            ofs<<limit.n<<" "<<limit.m<<'\n';
            auto data= hack_spfa(limit.n,limit.m,limit.l,limit.r);
            for(const auto&i:data){
                ofs<<i.u<<" "<<i.v<<" "<<i.w<<'\n';
            }
            ofs.close();
            return 0;
        }
        else if(type=="hack_one_hash"){

        }
        else if(type=="hack_ull_hash"){

        }
        else if(type=="DSU"){

        }else{
            return 2;
        }
    }
};

int constructOperator::xs_string_to_int(const string& s) {
    int w=1,res=0;
    for(auto i:s){
        res*=10;
        if(i=='-')w=-1;
        else{
            res+=i-'0';
        }
    }
    return res*w;
}

vector<int>
constructOperator::xs_split_string_int(string &s) {
    string tmp;
    vector<int>g;
    for(auto i:s){
        if(i==' '||i=='\n'){
            if(!tmp.empty()){
                g.push_back(xs_string_to_int(tmp));
                tmp.clear();
            }
        }else{
            tmp+=i;
        }
    }
    if(!tmp.empty())
        g.push_back(xs_string_to_int(tmp));
    return g;
}

int constructOperator::randed_int(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

double constructOperator::random_double(double l, double r) {
    return (double)rand() / RAND_MAX * (r - l) + l;
}

vector<int>
constructOperator::get_array_int(int n, int l, int r, bool unique, bool shuffle) {
    if (l > r)
        swap(l, r);
    vector<int>g;
    if (unique) {
        if (r - l + 1 < n)
            return g;//不可能构造
        if (r - l <= n * 10) {//在这个值领区间里,不适合使用随机性算法进行构造
            for (int i = l; i <= r; i++) {
                g.push_back(i);
            }
            random_shuffle(g.begin(),g.end());
            //shuffle(g.begin(), g.end(), std::mt19937(std::random_device()()));
            g.erase(g.begin() + n, g.end());//把n之后的全删

            if (shuffle)
                sort(g.begin(), g.end());
            return g;
        } else { //密度较低,可以使用随机性算法
            map<int, int>mp;
            for (int i = 1; i <= n; i++) {
                int u = randed_int(l, r);
                while (mp[u]) {
                    u = randed_int(l, r);
                }
                mp[u] = 1;
                g.push_back(u);
            }
            if (shuffle)
                sort(g.begin(), g.end());
            return g;
        }

    }
    for (int i = 1; i <= n; i++) {
        g.push_back(randed_int(l, r));
    }
    if (shuffle)
        sort(g.begin(), g.end());
    return g;
}

vector<double>
constructOperator::get_array_double(int n, double l, double r, bool unique, double eps, bool shuffle) {
    if (l > r)
        swap(l, r);
    vector<double>g;
    if (unique) {
        if (l + n * eps  > r)
            return g;//不可能生成
        if ((l + n * eps) * 10 < r) { //密度过大
            double now = l;
            while (now < r) {
                g.push_back(now);
                l += eps;
            }
            random_shuffle(g.begin(), g.end());
            g.erase(g.begin() + n, g.end());//把n之后的全删

            if (shuffle)
                sort(g.begin(), g.end());
            return g;
        }
        for (int i = 1; i <= 10 * n; i++) {
            g.push_back(random_double(l, r));
        }
        sort(g.begin(), g.end());
        vector<double>tmp;
        double pre = 0;
        for (auto i : g) {
            if (!tmp.empty() && fabs(i - pre) < eps)
                continue;
            pre = i;
            tmp.push_back(i);
        }
        if (tmp.size() < n) {
            return {0};
        }
        random_shuffle(tmp.begin(), tmp.end());
        tmp.erase(tmp.begin() + n, tmp.end());
        if (shuffle)
            sort(tmp.begin(), tmp.end());
        return tmp;
    }
    for (int i = 1; i <= n; i++) {
        g.push_back(random_double(l, r));
    }
    if (shuffle)
        sort(g.begin(), g.end());
    return g;
}

vector<node_val_int>
constructOperator::get_tree_lineval_int(int n, int l, int r, bool unique) {
    if (unique && l + n > r)
        return {{0, 0, 0}};
    vector<node_val_int>g_line;
    vector<int>tree_val = get_array_int(n - 1, l, r, unique, 0);
    if (tree_val.size() != n - 1)
        return {{0, 0, 0}};
    for (int i = 2; i <= n; i++) {
        int fa = randed_int(1, i - 1);
        g_line.push_back({fa, i, tree_val[i - 2]});
    }
    return g_line;
}

vector<node_val_double>
constructOperator::get_tree_lineval_double(int n, double l, double r, double eps, bool unique) {
    if (unique && l + n > r)
        return {{0, 0, 0}};
    vector<node_val_double>g_line;
    vector<double>tree_val = get_array_double(n - 1, l, r, unique, eps, 0);
    if (tree_val.size() != n - 1)
        return {{0, 0, 0}};
    for (int i = 2; i <= n; i++) {
        int fa = randed_int(1, i - 1);
        g_line.push_back({fa - 1, i, tree_val[i - 2]});
    }
    return g_line;
}

vector<node_val_int>
constructOperator::get_k_tree(int n, int l, int r, int unique, int k) {
    vector<int>tree_val = get_array_int(n - 1, l, r, unique, false);
    vector<node_val_int>tree_line;
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            tree_line.push_back({i, ++cnt, tree_val[cnt - 2]});
            if (cnt >= n)
                break;
        }
        if (cnt >= n)
            break;
    }
    return tree_line;
}

vector<node_val_int>
constructOperator::get_map_lineval_int_aim_link(int n, int m, bool ring, int l, int r, bool unique_val) {
    map<pair<int, int>, bool>st;
    int dag_maxn_line = n * (n - 1) / 2; //有向无环图的最大边数
    int maxn_line = n * (n - 1); //有向环图的最大边数
    if ((!ring && m > dag_maxn_line) || (ring && m > maxn_line))//不可能构造
        return {{0, 0, 0}};

    vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
    vector<node_val_int> map_line = get_tree_lineval_int(n, l, r, unique_val);
    for (auto i : map_line) { //防重边
        st[ {i.u, i.v}] = true;
    }
    if (m * 10 < maxn_line) { //密度较小,可以rand
        for (int i = n; i <= m; i++) {
            int u = randed_int(1, n ), v = randed_int(1, n );
            while (u == v || st[ {u, v}]) {
                u = randed_int(1, n ), v = randed_int(1, n );
            }
            if (u > v)
                swap(u, v);
            if (ring) {
                swap(u, v);
            }
            st[ {u, v}] = true;
            map_line.push_back({u, v, 0});
            for (int i = 0; i < m; i++) {
                map_line[i].w = map_val[i];
            }
        }
    } else {//过大,枚举后打乱
        vector < pair<int, int>>tmp;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (i == j)
                    continue;
                if (ring)
                    swap(i, j);
                tmp.emplace_back(i, j);
            }
        }
        shuffle(tmp.begin(), tmp.end(), std::mt19937(std::random_device()()));
        int idx = 0;
        for (int i = n; i <= m; i++) {
            while (st[ {tmp[idx].first, tmp[idx].second}]) {
                idx++;
            }
            st[ {tmp[idx].first, tmp[idx].second}] = true;
            map_line.push_back({tmp[idx].first, tmp[idx].second});
        }
        for (int i = 0; i < m; i++) {
            map_line[i].w = map_val[i];
        }

    }
    return map_line;
}

vector<node_val_int>
constructOperator::get_map_lineval_int_unaim_link(int n, int m, bool ring, int l, int r, bool unique_val) {
    vector<node_val_int> map_line = get_tree_lineval_int(n, l, r, unique_val);
    vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
    if (!ring) {
        if (m != n - 1)
            return {{0, 0, 0}};
        return map_line;
    }
    map<pair<int, int>, bool>st;
    for (auto i : map_line) {
        st[ {i.u, i.v}] = true;
    }
    if (m * 10 < n * (n - 1)) { //可随机
        vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
        for (int i = n; i <= m; i++) {
            int u = 0, v = 0;
            while (u == v) {
                u = randed_int(1, n ), v = randed_int(1, n);
            }
            map_line.push_back({u, v, 0});
        }
    } else {
        vector < pair<int, int>>tmp;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j)
                    continue;
                tmp.push_back({i, j});
            }
        }
        random_shuffle(tmp.begin(), tmp.end());
        int idx = 0;
        for (int i = n; i <= m; i++) {
            while (st[ {tmp[idx].first, tmp[idx].second}]) {
                idx++;
            }
            st[ {tmp[idx].first, tmp[idx].second}] = true;
            map_line.push_back({tmp[idx].first, tmp[idx].second});
        }
    }

    for (int i = 0; i < m; i++) {
        map_line[i].w = map_val[i];
    }
    return map_line;
}

bool constructOperator::check_negative_ring(vector<node_val_int> map_line, int n, int m) {
    vector < pair<int, int>>g[n + 10];
    for (auto i : map_line) {
        g[i.u].push_back({i.v, i.w});
    }
    vector<int>st(n + 10), dist(n + 10), cnt(n + 10);
    queue<int>q;
    for (int i = 1; i <= n; i++)
        dist[i] = 1e18;
    for (int i = 1; i <= n; i++) {
        q.push(i);
        st[i] = true;
    }
    while (q.size()) {
        int t = q.front();
        st[t] = false;
        for (auto i : g[t]) {
            if (dist[i.first] > dist[t] + i.second) {
                dist[i.first] = dist[t] + i.second;
                cnt[i.first] = cnt[t] + 1;
                if (cnt[i.first] >= n)
                    return true;
                if (!st[i.first]) {
                    st[i.first] = true;
                    q.push(i.first);

                }
            }
        }
    }
    return false;
}

vector<node_val_int>
constructOperator::get_negative_ring(int n, int m, int l, int r, bool unique_val) {
    vector<node_val_int>map_line = get_map_lineval_int_aim_link(n, m, 1, l, r, unique_val);
    while (!check_negative_ring(map_line, n, m)) {
        map_line = get_map_lineval_int_aim_link(n, m, 1, l, r, unique_val);
    }
    return map_line;
}

vector<node_val_int>
constructOperator::get_dichotomous_chart(int Lcnt, int Rcnt, int m, int l, int r, bool unique_val) {
    vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
    map<pair<int, int>, bool>st;
    vector<node_val_int>map_line;
    if (m * 10 <= Lcnt * Rcnt) { //密度较低
        for (int i = 0; i < m; i++) {
            int u = 0, v = 0;
            while (u == v || st[ {u, v}]) {
                u = randed_int(1, Lcnt), v = randed_int(1, Rcnt);
            }
            map_line.push_back({u, v, map_val[i]});
            st[ {u, v}] = true;
        }
    } else {
        vector<pair<int, int>>tmp;
        for (int i = 1; i <= Lcnt; i++) {
            for (int j = 1; j <= Rcnt; j++) {
                tmp.emplace_back(i, j);
            }
        }
        random_shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < m; i++) {
            map_line.push_back({tmp[i].first, tmp[i].second, map_val[i]});
        }
    }
    return map_line;
}

vector<node_val_int>
constructOperator::get_cactus(int n,int l, int r, bool unique_val) {
    int m=n-1;
    mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
    vector<int>head(n+5),a(n+5),b(n+5),top(n+5),fa(n+5),ver(n*2+5),Next(n*2),vis(n+5);
    int tot=0;
    auto add=[&](auto add,int x,int y){
        ver[++tot] = y;
        Next[tot] = head[x];
        head[x] = tot;
    };
    for(int i=2;i<=n;i++){
        a[i-1]=i,b[i-1]=rnd() % (i - 1) + 1;
        add(add,a[i - 1], b[i - 1]), add(add,b[i - 1], a[i - 1]);
    }
    int rt = rnd() % n + 1;
    auto dfs=[&](auto &dfs,int x,int f,int p)->void {
        top[x] = p, fa[x] = f;
        if (head[x] && ver[head[x]] != f)
            dfs(dfs,ver[head[x]], x, p);
        for (int i = Next[head[x]], y; i; i = Next[i]) {
            if ((y = ver[i]) == f)continue;
            dfs(dfs,y, x, y);
        }
    };
    dfs(dfs,rt,0,rt);
    for (int i = 1; i <= n; i++)
        if (!vis[top[i]] && top[i] != i && top[i] != fa[i])
            a[++m] = i, b[m] = top[i], vis[top[i]] = true;
    vector<int>map_val = get_array_int(m, l, r, unique_val, false);
    vector<node_val_int>map_line;
    for (int i = 1; i <= m; i++) {
        map_line.push_back({a[i], b[i], map_val[i - 1]});
    }
    return map_line;

}

/*
vector<node_val_int>
constructOperator::get_cactus(int n, int l, int r, bool unique_val) {
    vector<vector<int>>g(n+10);
    vector<int>vis(n + 10);
    int m = n - 1;
    vector<int>tp(n + 10), x(n + 10), y(n + 10);
    for (int i = 2; i <= n; i++) {
        int a = randed_int(1, i - 1), b = i;
        x[i - 1] = a, y[i - 1] = b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto dfs = [&](auto dfs, int u, int p) -> void {
        int jud=0;
        for (auto v : g[u]) {
            if (v == p)
                continue;
            if (!jud) {
                tp[v] = tp[u];
                jud = 1;
            } else {
                tp[v] = v;
            }
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, 0, -1);
    int cnt = randed_int(1, 10);
    for (int i = 1; i <= cnt; i++) {
        int aa = randed_int(1, n), bb = tp[aa];
        if (aa != bb && !vis[bb]) {
            x[++m] = aa, y[m] = bb;
            vis[bb] = 1;
        }
    }
    vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
    vector<node_val_int>map_line;
    for (int i = 1; i <= m; i++) {
        map_line.push_back({x[i], y[i], map_val[i - 1]});
    }
    return map_line;
}*/

vector<node_val_int>
constructOperator::get_eulerian(int n, int m, int l, int r, int unique, bool half) {
    vector<int>map_val = get_array_int(m, l, r, unique, 0);
    int u = 1;
    vector<node_val_int>map_line;
    for (int i = 0; i < m - 2; i++) {
        int v = 0;
        while ((v = randed_int(1, n)) == u);
        map_line.push_back({u, v, map_val[i]});
        u = v;
    }
    if (half) { //最后一个点不能是起点
        int t1 = randed_int(1, n), t2;
        while ((t2 = randed_int(2, n)) == t1);
        map_line.push_back({u, t1, map_val[m - 2]});
        map_line.push_back({t1, t2, map_val[m - 1]});
    } else { //最后的点必须是起点
        int t1 = randed_int(2, n), t2 = 1;
        map_line.push_back({u, t1, map_val[m - 2]});
        map_line.push_back({t1, t2, map_val[m - 1]});
    }
    return map_line;
}

vector<int>
constructOperator::get_primes(int n) {
    int cnt = 0;
    vector<int>primes(n + 5);
    vector<bool>st(n + 5);
    for (int i = 2; i <= n; i ++ ) {
        if (!st[i])
            primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ ) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    return primes;
}

int constructOperator::qmi(int a, int k, int p) {
    int res = 1;
    while (k) {
        if (k & 1)
            res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}

bool constructOperator::check_big_primes(int n) {
    if (n < 3 || n % 2 == 0)
        return n == 2;
    int a = n - 1, b = 0;
    while (a % 2 == 0)
        a /= 2, ++b;
    int test_time = 10;
    for (int i = 1, j; i <= test_time; ++i) {
        int x = rand() % (n - 2) + 2, v = qmi(x, a, n);
        if (v == 1)
            continue;
        for (j = 0; j < b; ++j) {
            if (v == n - 1)
                break;
            v = (long long)v * v % n;
        }
        if (j >= b)
            return false;
    }
    return true;
}

int constructOperator::get_big_primes(int l, int r) {
    for (int i = l; i <= r; i++) {
        if (check_big_primes(i))
            return i;
    }
    return 0;
}

vector<int>
constructOperator::get_eulers(int n) {
    int cnt = 0;
    vector<int>primes(n + 10), euler(n + 10), st(n + 10);
    euler[1] = 1;
    for (int i = 2; i <= n; i ++ ) {
        if (!st[i]) {
            primes[cnt ++ ] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j ++ ) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
    return euler;
}

vector<int>
constructOperator::hack_unordered_map(int n) {
    vector<int>g;
    for (int i = 1; i <= n; i++) {
        g.push_back(126271 * i);
    }
    return g;
}

vector<node_val_int>
constructOperator::hack_spfa(int n, int m, int l, int r) {
    set<pair<int, int>>s;
    vector<int>d(n + 10);
    d[1] = 0;
    vector<int>map_val = get_array_int(m, l, r, 0, 0);
    vector<node_val_int>map_line;
    for (int i = 2; i <= n; i++) {
        int ll = max(i - 5, 1ll), rr = i;
        int v = randed_int(ll, rr), u = i;
        d[i] = d[v] + 1;
        s.insert({u, v});
        s.insert({v, u});
        map_line.push_back({u, v, map_val[i - 2]});
    }
    for (int i = 1; i <= m - (n - 1); i++) {
        int u = randed_int(1, n), v = randed_int(1, n);
        if (s.find({u, v}) != s.end() || u == v) {
            i--;
            continue;
        }
        s.insert({u, v});
        s.insert({v, u});
        int ll = abs(d[u] - d[v]), rr = l + 5;
        ll = max(min(ll, r), l);
        rr = max(min(rr, r), l); //保证在值域内
        map_line.push_back({u, v, randed_int(ll, rr)});
    }
    return map_line;
}

vector<node_val_int>
constructOperator::get_bipartite_graph(int n, int m, int cnt, int l,int r, bool unique_val) {
    //随机生存ID序列
    if(cnt>=n||l>r)return {};
    vector<node_val_int>res;
    auto arr= get_array_int(m,l,r,unique_val,true);
    for(int i=1;i<=m;i++){
        int ls= randed_int(1,cnt);
        int rs= randed_int(cnt+1,n);
        res.push_back({ls,rs,arr[i-1]});
    }
    return res;
}

vector<node_val_int>
constructOperator::get_star_graph(int n,int m, int l, int r,int unique_val) {//总节点数,重心数
    if(m>n)
        return {};
    //res已经获取了m-1条边,将重心构成了一个树,之后再不断添加
    vector<int> data=get_array_int(n-m,l,r,unique_val,true);
    vector<node_val_int> res= get_tree_lineval_int(m,l,r,unique_val);
    for(int i=m+1;i<=n;i++){
        res.push_back({i, randed_int(1,m),data[i-m-1]});
    }
    return res;
}

#undef int
#endif //CLION_CONSTRUCTOPERATION_H
