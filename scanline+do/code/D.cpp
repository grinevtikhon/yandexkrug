#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    int n;
    vector<int> t;

    D_o()
    {
        n = (2e5) + 239;

        t.resize(4 * n);

        build(0, 0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = 0;
            return;
        }

        int tm = (tl + tr) / 2;
        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
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

    void update(int v, int tl, int tr, int pos, int x)
    {
        if(tr <= pos || pos + 1 <= tl)
        {
            return;
        }

        if(tl == pos && tr == pos+1)
        {
            t[v] = x;
            return;
        }

        int tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, pos, x);
        update(2 * v + 2, tm, tr, pos, x);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
};


int main()
{
    int n;
    cin >> n;

    D_o gg;

    for(int i = 0; i < n; ++i)
    {
        int a;
        cin >> a;
        if(a > 0)
        {
            --a;
            int l = a;
            int r = (2e5) + 239;

            while(r - l > 1)
            {
                int m = (l + r) / 2;

                int sum = gg.get(0, 0, gg.n, a, m);
                
                if(sum == m - a)
                {
                    l = m;
                } else {
                    r = m;
                }
            }


            int num = l;
            gg.update(0, 0, gg.n, num, 1);
            cout << num + 1 << '\n';
        } else {
            a *= -1;
            --a;
            gg.update(0, 0, gg.n, a, 0);
        }
    }

}