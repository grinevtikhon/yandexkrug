#include<bits/stdc++.h>

using namespace std;

struct S_o
{
    int n;
    vector<int> vec;
    vector<int> d;

    S_o(vector<int> &_vec)
    {
        vec = _vec;
        n = vec.size();
        d.resize(n);
        d[0] = vec[0];
        for(int i = 1; i < n; ++i)
        {
            d[i] = vec[i] - vec[i-1];
        }
    }

    void add(int p, int del)
    {
        if(p < 0 || p >= n)
        {
            return;
        }
        d[p] += del;

    }

    void update(int l, int r, int del)
    {
        add(l, del);
        add(r+1, -del);
    }

    vector<int> get_ans()
    {
        vec[0] = d[0];
        for(int i = 1; i < n; ++i)
        {
            vec[i] = vec[i-1] + d[i];
        }
        return vec;
    }
};

struct D_o
{
    int n;
    vector<int> t;

    D_o(int _n)
    {
        n = _n;
        t.resize(4 * n);
    }

    int get(int v, int tl, int tr, int l, int r)
    {
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }

    void update(int v, int tl, int tr, int pos, int d)
    {
        if(tr <= pos || pos+1 <= tl)
        {
            return;
        }

        if(pos <= tl && tr <= pos+1)
        {
            t[v] += d;
            return;
        }

        int tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, pos, d);
        update(2 * v + 2, tm, tr, pos, d);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
};

int main()
{
    int n, m;

    cin >> n >> m;

    vector<pair<int, int>> q(n);
    vector<vector<int>> sob;
    for(int i = 0; i < n; ++i)
    {
        int l, r;
        cin >> l >> r;
        q[i] = {l, r};
        sob.push_back({l, 0, r - l + 1});
        sob.push_back({r, 1, r - l + 1});
    }

    sort(sob.begin(), sob.end());

    D_o gg(m + 1);

    int k = 0;

    vector<int> ans(m+1);

    for(int i = 0; i <= m; ++i)
    {
        while(k < sob.size() && (sob[k][0] < i || (sob[k][0] == i && sob[k][1] == 0)))
        {
            if(sob[k][1] == 0)
            {
                gg.update(0, 0, gg.n, sob[k][2], 1);
            } else {
                gg.update(0, 0, gg.n, sob[k][2], -1);
            }
            ++k;
        }

        for(int del1 = 1; del1*del1 <= i; ++del1)
        {
            if(i % del1 != 0)
            {
                continue;
            }

            int del2 = i / del1;

            if(del1 == del2)
            {
                ans[del1] += gg.get(0, 0, gg.n, 0, del1);
            } else {
                ans[del1] += gg.get(0, 0, gg.n, 0, del1);
                ans[del2] += gg.get(0, 0, gg.n, 0, del2);
            }
        }
    }


    S_o otv(ans);

    for(int i = 0; i < n; ++i)
    {
        int l = q[i].first;
        int r = q[i].second;

        int sz = r - l + 1;

        otv.update(1, sz, 1);
    }

    ans = otv.get_ans();

    for(int i = 1; i < ans.size(); ++i)
    {
        cout << ans[i] << '\n';
    }

}