#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    int n;
    vector<int> t;
    vector<int> promis;

    D_o(int _n)
    {
        n = _n;
        t.resize(4 * n);
        promis.resize(4 * n, -1);
    }

    void push(int v, int tl, int tr)
    {
        if(promis[v] == -1)
        {
            return;
        }

        t[v] = (tr - tl) * promis[v];

        if(tl + 1 != tr)
        {
            promis[2 * v + 1] = promis[v];
            promis[2 * v + 2] = promis[v];
        }

        promis[v] = -1;
    }

    int get(int v, int tl, int tr, int l, int r)
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

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }

    void update(int v, int tl, int tr, int l, int r, int x)
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

        int tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, l, r, x);
        update(2 * v + 2, tm, tr, l, r, x);

        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    string s;

    cin >> s;

    vector<D_o> gg(26, n);

    for(int i = 0; i < n; ++i)
    {
        int buf = s[i] - 'a';

        gg[buf].update(0, 0, n, i, i+1, 1);
    }

    for(int i = 0; i < q; ++i)
    {
        int l, r, k;
        cin >> l >> r >> k;
        --l;
        --r;

        vector<int> vec(26);

        for(int j = 0; j < 26; ++j)
        {
            vec[j] = gg[j].get(0, 0, n, l, r+1);
            gg[j].update(0, 0, n, l, r + 1, 0);
        }

        if(k == 1)
        {
            for(int j = 0; j < 26; ++j)
            {
                gg[j].update(0, 0, n, l, l + vec[j], 1);
                l += vec[j];
            }
        } else {
            for(int j = 25; j >= 0; --j)
            {
                gg[j].update(0, 0, n, l, l + vec[j], 1);
                l += vec[j];
            }
        }
    }

    vector<int> ans(n);

    for(int i = 0; i < 26; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(gg[i].get(0, 0, n, j, j + 1) == 1)
            {
                ans[j] = i;
            }
        }
    }

    for(int i = 0; i < n; ++i)
    {
        cout << (char)(ans[i] + 'a');
    }
    cout << '\n';




}