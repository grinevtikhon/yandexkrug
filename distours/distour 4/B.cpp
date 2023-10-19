#include<bits/stdc++.h>
 
using namespace std;
 
vector<vector<int> >gr;
 
struct node
{
    int size;
    int deep;
 
    vector<pair<int, int>> binup;
 
    vector<int> mp;
 
    vector<int> del; 
 
    node()
    {
        binup.resize(15, make_pair(0, 0));
        size = 0;
    }
};
 
vector<node> t;
 
void dfs(int v, int p)
{
    t[v].deep = t[p].deep + 1;
 
    if(v != 0)
    {
 
        t[v].binup[0] = {p, t[v].size};
        for(int i = 1; i < t[v].binup.size(); ++i)
        {
            t[v].binup[i].first = t[t[v].binup[i-1].first].binup[i-1].first;
            t[v].binup[i].second = t[t[v].binup[i-1].first].binup[i-1].second + t[v].binup[i-1].second;
        }
    } else {
        t[v].binup[0] = {0, 0};
        for(int i = 1; i < t[v].binup.size(); ++i)
        {
            t[v].binup[i] = {0, 0};
        }
    }
 
    for(auto u : gr[v])
    {
        if(u == p)
        {
            continue;
        }
        dfs(u, v);
    }
}
 
pair<int, int> up(int v, int k)
{
    int ans = 0;
    for(int i = t[v].binup.size() - 1; i >= 0; --i)
    {
        if((1 << i) <= k)
        {
            k -= (1 << i);
            ans += t[v].binup[i].second;
            v = t[v].binup[i].first;
        }
    }
 
    return {v, ans};
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int n, m, k;
 
    cin >> n >> m >> k;
    --k;
 
    int s;
 
    cin >> s;
    ++s;
 
    gr.resize(n+1);
    t.resize(n+1);
    t[0].deep = -1;
 
    vector<int> pr(n+1);
    pr[0] = -1;
 
    for(int i = 1; i <= n; ++i)
    {
        int p, l;
        cin >> p >> l;
        pr[i] = p;
        gr[i].push_back(p);
        gr[p].push_back(i);
        t[i].size = l + 1;
    }
 
     
 
    dfs(0, 0);
 
 
    // cout << "\n";
 
 
    for(int v = 0; v < t.size(); ++v)
    {
        for(int u = 0; u < t.size(); ++u)
        {
            auto[g, cost] = up(v, t[v].deep - t[u].deep);
            // int cost = up(v, t[v].deep - t[u].deep).second;
 
            if(g == u)
            {
                t[u].del.push_back(cost + s);
            } else {
                t[u].mp.push_back(t[v].binup.back().second + s - t[u].binup.back().second);
            }
        }
    }
 
    for(int i = 0; i < t.size(); ++i)
    {
        sort(t[i].del.begin(), t[i].del.end());
        sort(t[i].mp.begin(), t[i].mp.end());
    }





     
    for(int i = 0; i < m; ++i)
    {
        int p, l;
        cin >> p >> l;
        int path = k;
        path -= l;
        int v = p;
 
        path -= t[v].binup.back().second;
 
         
 
        bool fl = false;
 
        if(path == 0)
        {
            fl = true;
        }


        vector<int> del;

        for(int j = 1; j * j <= path; ++j)
        {
            if(path % j == 0)
            {
                del.push_back(j);
                del.push_back(path / j);
            }
        }
 
        while(v != -1)
        {
            auto buf = lower_bound(t[v].mp.begin(), t[v].mp.end(), path);
            if(buf != t[v].mp.end() && *buf == path)
            {
                fl = true;
                break;
            }

            for(auto del1 : del)
            {
                auto gg = lower_bound(t[v].del.begin(), t[v].del.end(), del1);
                if(gg != t[v].del.end() && *gg == del1)
                {
                    fl = true;
                }
            }
 
            // for(int del = 1; del*del <= path; ++del)
            // {
            //     if(path % del == 0)
            //     {
            //         int del2 = path / del;
 
                    
            //         auto gg2 = lower_bound(t[v].del.begin(), t[v].del.end(), del2);
            //         if(gg2 != t[v].del.end() && *gg2 == del2)
            //         {
            //             fl = true;
            //         }
            //     }
            // }
 
 
            v = pr[v];
            if(fl)
            {
                break;
            }
        }
 
        if(fl)
        {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
 
}