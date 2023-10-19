#include<bits/stdc++.h>

using namespace std;


vector<long long> calc_pref(vector<long long> a)
{
    for(long long i = 1; i < a.size(); ++i)
    {
        a[i] = a[i-1] + a[i];
    }
    return a;
}
struct D_o
{
    vector<long long> vec;
    vector<vector<long long>> t;
    vector<vector<long long>> pref;
    long long n;

    D_o(vector<long long> &_vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4 * n);
        pref.resize(4 * n);

        build(0, 0, n);
    }

    void build(long long v, long long tl, long long tr)
    {
        if(tl == tr-1)
        {
            t[v] = {vec[tl]};
            pref[v] = calc_pref(t[v]);
            return;
        }

        long long tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v].resize(t[2 * v + 1].size() + t[2 * v + 2].size());

        merge(t[2 * v + 1].begin(), t[2 * v + 1].end(), t[2 * v + 2].begin(), t[2 * v + 2].end(), t[v].begin());
        pref[v] = calc_pref(t[v]);
    }

    void get(long long v, long long tl, long long tr, long long l, long long r, vector<long long> &gg)
    {
        if(tr <= l || r <= tl)
        {
            return;
        }

        if(l <= tl && tr <= r)
        {
            gg.push_back(v);
            return;
        }

        long long tm = (tl + tr) / 2;
        get(2 * v + 1, tl, tm, l, r, gg);
        get(2 * v + 2, tm, tr, l, r, gg);
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    long long n, m;
    cin >> n >> m;
    
    vector<long long> a(n);

    for(long long i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    D_o sm(a);

    for(long long t = 0; t < m; ++t)
    {
        long long l, r;
        cin >> l >> r;
        --l;
        --r;

        vector<long long> gg;
        sm.get(0, 0, sm.n, l, r + 1, gg);

        long long ans = 1;
        long long pr_ans = 0;

        while(ans != pr_ans)
        {
            pr_ans = ans;

            ans = 1;

            for(auto i : gg)
            {
                long long gran = upper_bound(sm.t[i].begin(), sm.t[i].end(), pr_ans) - sm.t[i].begin() - 1;

                if(gran == -1)
                {
                    continue;
                }

                ans += sm.pref[i][gran];
            }
        }

        cout << ans << '\n';

    }


}