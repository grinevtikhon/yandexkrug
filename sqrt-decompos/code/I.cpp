#include<bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> gr;

vector<int> euler;
vector<int> tin;
vector<int> reb;
int n, qq;


void dfs(int v, int p)
{
    tin[v] = euler.size();

    for(auto u : gr[v])
    {
        if(u.first == p)
        {
            continue;
        }
        euler.push_back(u.second);
        dfs(u.first, v);
        euler.push_back(u.second);
    }
}


struct mo
{
    int l, r;
    vector<int> cnt;
    set<int> st;

    int ans;

    mo()
    {
        for(int i = 0; i < (1e5) +10; ++i)
        {
            st.insert(i);
        }
        cnt.resize(n);
        l = 0;
        r = 0;
    }

    void add(int x)
    {
        if(cnt[x] % 2 == 0)
        {
            st.insert(reb[x]);
            cnt[x] = 1;
        } else {
            st.erase(reb[x]);
            cnt[x] = 0;
        }
    }


    void move(int _l, int _r)
    {
        while(r > _r)
        {
            add(euler[r-1]);
            --r;
        }
        while(r < _r)
        {
            add(euler[r-1]);
            ++r;
        }
        while(l > _l)
        {
            add(euler[l]);
            --l;
        }
        while(l < _l)
        {
            add(euler[l]);
            ++l;
        }
    }

    int mex()
    {
        
    }
};

int main()
{
    
    cin >> n >> qq;

    gr.resize(n);
    reb.resize(n-1);
    tin.resize(n);

    for(int i = 0; i < n-1; ++i)
    {
        int v, u, x;
        cin >> v >> u >> x;
        --v;
        --u;
        gr[v].push_back({u, i});
        gr[u].push_back({v, i});
        reb[i] = x;
    }

    dfs(0, 0);







}