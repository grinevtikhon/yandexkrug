#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    long long n;
    vector<long long> t;
    vector<long long> promis;

    D_o(long long _n)
    {
        n = _n;
        t.resize(4 * n);
        promis.resize(4 * n);

        build(0, 0, n);
    }

    void build(long long v, long long tl, long long tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = 0;
            return;
        }

        long long tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);
    }

    void push(long long v, long long tl, long long tr)
    {
        t[v] += promis[v];

        if(tl + 1 != tr)
        {
            promis[2 * v + 1] += promis[v];
            promis[2 * v + 2] += promis[v];
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

    void update(long long v, long long tl, long long tr, long long l, long long r, long long d)
    {
        push(v, tl, tr);
        if(tr <= l || r <= tl)
        {
            return;
        }

        if(l <= tl && tr <= r)
        {
            promis[v] += d;
            push(v, tl, tr);
            return;
        }

        long long tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, l, r, d);
        update(2 * v + 2, tm, tr, l, r, d);
    }


};

signed main()
{   
    long long n;
    cin >> n;

    vector<long long> a(n);

    for(long long i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    long long p;
    cin >> p;

    long long ans = 0;

    for(long long i = 0; i < n; ++i) a[i] -= p;
    for(long long i = 1; i < n; ++i) a[i] += a[i-1];
    for(long long i = 0; i < n; ++i)
    {
        if(a[i] >= 0){
            ++ans;
        }
    }

    vector<long long> b = a;

    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());



    D_o gg(b.size());

    long long sum = 0;
    
    for(long long i = 0; i < n; ++i)
    {
        long long buf = a[i];
        buf = lower_bound(b.begin(), b.end(), buf) - b.begin();
        ans += gg.get(0, 0, gg.n, buf, buf+1);

        gg.update(0, 0, gg.n, buf, gg.n, 1);
    }

    cout << ans << '\n';



}