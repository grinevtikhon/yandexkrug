    #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    long long t[1000000];
    vector<long long> vec;
    long long promis[1000000];
    long long n;

    void buildD_o(vector<long long> &_vec)
    {
        vec = _vec;
        n = vec.size();

        build(0, 0, n);
    }

    void build(long long v, long long tl, long long tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = vec[tl];
            return;
        }

        long long tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
    
    inline void push(long long v, long long tl, long long tr)
    {
        if(promis[v] == 0)
        {
            return;
        }

        t[v] = (tr - tl) * promis[v];
        if(tl + 1 != tr)
        {
            promis[2 * v + 1] = promis[v];
            promis[2 * v + 2] = promis[v];
        }
        promis[v] = 0;
    }

    long long get(long long v, long long tl, long long tr, long long l, long long r)
    {
        push(v, tl, tr);
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        long long tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }

    void update(long long v, long long tl, long long tr, long long l, long long r, long long x)
    {
        
        push(v, tl, tr);
        
        if(tr <= l || r <= tl)
        {
            return;
        }

        if(l <= tl && tr <= r)
        {
            promis[v] = x;
            push(v, tl, tr);
            return;
        }

        long long tm = (tl + tr) / 2;
        update(2 * v + 1, tl, tm, l, r, x);
        update(2 * v + 2, tm, tr, l, r, x);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
};

D_o sm;




int main()
{

    // vector<long long> vec{1, 2, 2, 3, 5, 12};
    // cout << upper_bound(vec.begin(), vec.end(), 2, [](long long a, long long b){return a < b;}) - vec.begin() << '\n';
    // return 0;

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n, m;
    cin >> n >> m;
    vector<long long> p(n);

    for(long long i = 0; i < n; ++i)
    {
        cin >> p[i];
    }

    sm.buildD_o(p);
    int v[n];
    for(long long i = 0; i < n; ++i)
    {
        v[i] = i;
    }

    for(long long i = 0; i < m; ++i)
    {
        long long t, k, x;

        cin >> t >> k >> x;

        if(t == 1)
        {
            long long l = lower_bound(v, v + k, x, [&](long long a, long long b){a = sm.get(0, 0, sm.n, a, a+1); return a > b;}) - v;
            //cout << l << '\n';

            sm.update(0, 0, sm.n, l, k, x);
        } else {
            long long ans = 0;
            --k;
            while(k < n)
            {
                long long sum = sm.get(0, 0, n, 0, k);
                long long r = lower_bound(v + k, v + n, x, [&](long long a, long long b){a = sm.get(0, 0, sm.n, 0, a+1) - sum; return a <= b;}) - v;
                ans += r - k;
                x -= sm.get(0, 0, sm.n, 0, r) - sum;
                k = r;

                k = lower_bound(v + k, v + n, x, [&](long long a, long long b){a = sm.get(0, 0, sm.n, a, a + 1); return a > b;}) - v;
            }

            cout << ans << '\n';
        }
    }

}