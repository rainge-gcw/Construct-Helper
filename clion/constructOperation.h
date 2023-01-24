//
// Created by hadoop on 22-12-11.
//

#ifndef CLION_CONSTRUCTOPERATION_H
#define CLION_CONSTRUCTOPERATION_H

#include <bits/stdc++.h>
using std::string;
using std::vector;
using std::swap;
using std::pair;
using std::map;
using std::min;
using std::max;
using std::queue;
using std::set;
#define int long long
struct node_val_int {
    int u, v, w;
};
struct node_val_double {
    int u, v;
    double w;
};
class constructOperator{
public:
    static int xs_string_to_int(string s);
    static vector<int> xs_split_string_int(string& s);
    static int randed_int(int a, int b);
    static double random_double(double l, double r);
    static vector<int> get_array_int(int n, int l, int r, bool unique, bool shuffle);
    static vector<double> get_array_double(int n, double l, double r, bool unique, double eps, bool shuffle);
    static vector<node_val_int> get_tree_lineval_int(int n, int l, int r, bool unique);
    static vector<node_val_double> get_tree_lineval_double(int n, double l, double r, double eps, bool unique);
    static vector<node_val_int> get_k_tree(int n, int l, int r, int unique, int k);
    static vector<node_val_int> get_map_lineval_int_aim_link(int n, int m, bool ring, int l, int r,bool unique_val);
    static vector<node_val_int> get_map_lineval_int_unaim_link(int n, int m, bool ring, int l, int r,bool unique_val);
    static bool check_negative_ring(vector<node_val_int> map_line, int n, int m);
    static vector<node_val_int> get_negative_ring(int n, int m, int l, int r, bool unique_val);
    static vector<node_val_int> get_dichotomous_chart(int Lcnt, int Rcnt, int m, int l, int r, bool unique_val);
    static vector<node_val_int>get_cactus(int n, int l, int r, bool unique_val);
    static vector<node_val_int> get_eulerian(int n, int m, int l, int r, int unique, bool half, bool unique_val);
    static vector<int> get_primes(int n);
    static int qmi(int a, int k, int p);
    static bool check_big_primes(int n);
    static int get_big_primes(int l, int r);
    static vector<int> get_eulers(int n);
    static vector<int> hack_unordered_map(int n);
    static vector<node_val_int> hack_spfa(int n, int m, int l, int r);
};

int constructOperator::xs_string_to_int(string s) {
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

vector<int> constructOperator::xs_split_string_int(string &s) {
    string tmp;
    vector<int>g;
    for(auto i:s){
        if(i==' '||i=='\n'){
            if(tmp.size()>0){
                g.push_back(xs_string_to_int(tmp));
                tmp.clear();
            }
        }else{
            tmp+=i;
        }
    }
    if(tmp.size()>0)
        g.push_back(xs_string_to_int(tmp));
    return g;
}

int constructOperator::randed_int(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

double constructOperator::random_double(double l, double r) {
    return (double)rand() / RAND_MAX * (r - l) + l;
}

vector<int> constructOperator::get_array_int(int n, int l, int r, bool unique, bool shuffle) {
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
            random_shuffle(g.begin(), g.end());
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

vector<double> constructOperator::get_array_double(int n, double l, double r, bool unique, double eps, bool shuffle) {
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
            if (tmp.size() && fabs(i - pre) < eps)
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

vector<node_val_int> constructOperator::get_tree_lineval_int(int n, int l, int r, bool unique) {
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

vector<node_val_double> constructOperator::get_tree_lineval_double(int n, double l, double r, double eps, bool unique) {
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

vector<node_val_int> constructOperator::get_k_tree(int n, int l, int r, int unique, int k) {
    vector<int>tree_val = get_array_int(n - 1, l, r, unique, 0);
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

vector<node_val_int> constructOperator::get_negative_ring(int n, int m, int l, int r, bool unique_val) {
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
                tmp.push_back({i, j});
            }
        }
        random_shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < m; i++) {
            map_line.push_back({tmp[i].first, tmp[i].second, map_val[i]});
        }
    }
    return map_line;
}

vector<node_val_int> constructOperator::get_cactus(int n, int l, int r, bool unique_val) {
    vector<vector<int>>g(n);
    vector<bool>vis(n + 10);
    int m = n - 1;
    vector<int>tp(n + 10), x(n + 10), y(n + 10);
    for (int i = 2; i <= n; i++) {
        int a = randed_int(1, i - 1), b = i;
        x[i - 1] = a, y[i - 1] = b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto dfs = [&](auto dfs, int u, int p, int jud) -> void {
        for (auto v : g[u]) {
            if (v == p)
                continue;
            if (!jud) {
                tp[v] = tp[u];
                jud = 1;
            } else {
                tp[v] = v;
            }
            dfs(dfs, v, u, 0);
        }
    };
    dfs(dfs, 0, -1, 0);
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
}

vector<node_val_int>
constructOperator::get_eulerian(int n, int m, int l, int r, int unique, bool half, bool unique_val) {
    vector<int>map_val = get_array_int(m, l, r, unique_val, 0);
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

vector<int> constructOperator::get_primes(int n) {
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
            return 0;
    }
    return 1;
}

int constructOperator::get_big_primes(int l, int r) {
    for (int i = l; i <= r; i++) {
        if (check_big_primes(i))
            return i;
    }
    return 0;
}

vector<int> constructOperator::get_eulers(int n) {
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

vector<int> constructOperator::hack_unordered_map(int n) {
    vector<int>g;
    for (int i = 1; i <= n; i++) {
        g.push_back(126271 * i);
    }
    return g;
}

vector<node_val_int> constructOperator::hack_spfa(int n, int m, int l, int r) {
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

#undef int
#endif //CLION_CONSTRUCTOPERATION_H
