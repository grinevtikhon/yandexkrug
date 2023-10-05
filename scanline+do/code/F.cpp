#include<bits/stdc++.h>

using namespace std;

const long long p = 998769677;
const long long mod = 1e9 + 7;
long long mod_2 = mod * mod;

vector<long long> P;
vector<long long> pref;

struct D_o
{
    long long n;
    vector<long long> vec;
    vector<long long> t;
    vector<long long> promis;

    D_o(vector<long long> &_vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4 * n);
        promis.resize(4 * n);

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

        t[v] = (t[2*v+2] + t[2*v+1] * P[tr - tm]) % mod;
    }

    void push(long long v, long long tl, long long tr)
    {
        if(promis[v] == 0)
        {
            return;
        }

        t[v] = (promis[v] * pref[tr - tl]) % mod;

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
            return (t[v] * P[r - tr]) % mod;
        }

        long long tm = (tl + tr) / 2;

        long long a = get(2 * v + 1, tl, tm, l, r);
        long long b = get(2 * v + 2, tm, tr, l, r);

        return (a + b) % mod;
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

        int tm = (tl + tr)/2;

        update(2 * v + 1, tl, tm, l, r, x);
        update(2 * v + 2, tm, tr, l, r, x);

        t[v] = (t[2*v+2] + t[2*v+1] * P[tr - tm]) % mod;
    }
};

signed main()
{
    // for(int i = 1e9; i > 1e8; --i)
    // {
    //     bool fl = true;
    //     for(int j = 2; j * j <= i; ++j)
    //     {
    //         if(i % j == 0)
    //         {
    //             fl = false;
    //             break;
    //         }
    //     }
    //     if(fl)
    //     {
    //         cout << i << '\n';
    //     }
    // }

    // return 0;

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    P.resize(2e5);
    pref.resize(2e5);
    P[0] = 1;
    for(long long i = 1; i < P.size(); ++i)
    {
        P[i] = (P[i-1] * p) % mod;
    }

    pref[0] = 1;
    pref[1] = 1;
    for(long long i = 2; i < pref.size(); ++i)
    {
        pref[i] = (pref[i-1] * p + 1) % mod;
    }

    long long n, m;
    cin >> n;

    vector<long long> v(n);
    for(long long i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    D_o gg(v);

    cin >> m;

    for(long long i = 0; i < m; ++i)
    {
        long long q, l, r, k;

        cin >> q >> l >> r >> k;
        --l;
        --r;

        if(q == 0)
        {
            gg.update(0, 0, gg.n, l, r+1, k);
        } else {
            long long a = gg.get(0, 0, gg.n, l, l + k) % mod;
            long long b = gg.get(0, 0, gg.n, r, r + k) % mod;

            if(a == b)
            {
                cout << "+";
            } else {
                cout << '-';
            }
        }
    } 

    cout << '\n';


}