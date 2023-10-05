#include<bits/stdc++.h>


using namespace std;

struct D_o
{
    vector<int> vec;
    vector<int> t;
    vector<int> promis;
    int n;

    D_o(vector<int>& _vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4 * n);
        promis.resize(4 * n);

        build(0, 0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl == tr - 1)
        {
            t[v] = vec[tl];
            return;
        }

        int tm = (tl + tr) / 2;
        build(2 * v + 1, tl, tm);
        build(2 * v + 1, tm, tr);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    void push(int v, int tl, int tr)
    {
        if(promis[v] != 0)
        {
            t[v] = (tr - tl) * promis[v];
        }
        if(tl != tr - 1)
        {
            promis[2 * v + 1] = promis[v];
            promis[2 * v + 2] = promis[v];
        }
        promis[v] = 0;
    }

    int get(int v, int tl, int tr, int l, int r)
    {
        push(v, tl, tr);
        if(tr <= l || r <= tl){
            return 0;
        }
        if(l <= tl && tr <= r)
        {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, int x)
    {
        push(v, tl, tr);
        if(tr <= l || r <= tl){
            return;
        }
        if(l <= tl && tr <= r)
        {
            promis[v] = x;
            push(v, tl, tr);
            return;
        }

        int tm = (tl + tr) / 2;
        
        update(2 * v + 1, tl, tm, l, r, x);
        update(2 * v + 2, tm, tr, l, r, x);

        t[v]  = t[2 * v + 1] + t[2 * v + 2];
    }

};

int main()
{


    map<int, int> mp;


    mp.insert({1, 2});
    mp.insert({5, 6});
    mp.insert({-11, 3});
    mp.insert({1, 12});
    mp.erase(mp.begin());
    

    cout << (*mp.begin()).first  << " " << (*mp.begin()).second;

    return 0;

    int n, m;

    cin >> n >> m;

    vector<int> p(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> p[i];
    }

    D_o da(p);


    for(int i = 0; i < m; ++i)
    {
        int t, k, x;
        cin >> t >> k >> x;

        if(t == 1)
        {
            int l, r;
            l = 0;
            r = k+1;

            while(r - l > 1)
            {
                int mm = (r + l) / 2;
                if(da.get(0, 0, da.n, mm - 1, mm) < x)
                {
                    r = mm;
                } else {
                    l = mm;
                }
            }

            da.update(0, 0, da.n, l, k + 1, x);
        } else {
            int l, r;
            l = 0;
            r = n - k + 2;

            while(r - l > 1)
            {
                int mm = (r + l) / 2;
                if(da.get(0, 0, da.n, 0, k - 1 + mm) - da.get(0, 0, da.n, 0, k-1) < x)
                {
                    r = mm;
                } else {
                    l = mm;
                }
            }

            cout << l << '\n';
        }
    }
}