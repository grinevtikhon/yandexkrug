#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

vector<vector<pair<int, int>>> gr;

vector<int> euler;
vector<int> tin;
vector<int> reb;
int n, qq;


int block = 700;

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
    int bl = 500;
    vector<int> mp;
    vector<int> sum;

    int ans;

    mo()
    {
        mp.resize(1e5 + 10);
        sum.resize(((1e5) / bl) + 10);
        cnt.resize(n);
        l = 0;
        r = 0;
    }

    void add(int x)
    {
        if(reb[x] > 1e5)
        {
            return;
        }
        if(cnt[x] % 2 == 0)
        {
            mp[reb[x]] += 1;
            if(mp[reb[x]] == 1)
            {
                sum[reb[x] / bl] += 1;
            }
            cnt[x] = 1;
        } else {
            mp[reb[x]] -= 1;
            if(mp[reb[x]] == 0)
            {
                sum[reb[x] / bl] -= 1;
            }
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
            ++r;
            add(euler[r-1]);
            
        }
        while(l > _l)
        {
            --l;
            add(euler[l]);
            
        }
        while(l < _l)
        {
            add(euler[l]);
            ++l;
        }
    }

    int mex()
    {
        int n_bl = 0;

        while(sum[n_bl] == bl)
        {
            ++n_bl;
        }

        for(int i = n_bl * bl; true; ++i){
            if(mp[i] == 0)
            {
                return i;
            }
        }
    }
};

int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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

    int qsz = qq;

    mo momo;

    vector<pair<pair<int, int>, int>> q(qsz);

    for(int i = 0; i < qsz; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        int l, r;

        l = tin[a];
        r = tin[b];
        if(l > r)
        {
            swap(l, r);
        }
        q[i] = {{l, r}, i};
    }

    sort(q.begin(), q.end(), [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
        a.first.first /= block;
        b.first.first /= block;
        if(a.first.first == b.first.first)
        {
            if(a.first.first % 2 == 0)
            {
                return a.first.second < b.first.second;
            } else {
                return a.first.second > b.first.second;
            }
        }
        return a.first < b.first;
    });

    vector<int> ans(qsz);

    for(int i = 0; i < q.size(); ++i)
    {
        int l = q[i].first.first;
        int r = q[i].first.second;


        if(l > r)
        {
            swap(l, r);
        }

        momo.move(l, r);
        ans[q[i].second] = momo.mex();
    }

    for(int i = 0; i < qsz; ++i)
    {
        cout << ans[i] << '\n';
    }







}