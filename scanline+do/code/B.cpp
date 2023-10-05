#include<bits/stdc++.h>

using namespace std;

vector<int> fo(vector<int> a, vector<int> b)
{
    int l, m, r, sz;

    if(a[0] == a[3])
    {
        l = a[0] + b[0];
    } else {
        l = a[0];
    }

    if(b[2] == b[3])
    {
        r = b[2] + a[2];
    } else {
        r = b[2];
    }

    m = max(max(a[1], b[1]), a[2] + b[0]);

    sz = a[3] + b[3];

    return {l, m, r, sz};
}

struct D_o
{
    int n;
    vector<int> vec;
    vector<vector<int>> t;

    D_o(vector<int> &_vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4 * n);

        build(0, 0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl + 1 == tr)
        {
            if(vec[tl] == 0)
            {
                t[v] = {1, 1, 1, 1};
            } else {
                t[v] = {0, 0, 0, 1};
            }
            return;
        }

        int tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v] = fo(t[2 * v + 1], t[2 * v + 2]);
    }

    vector<int> get(int v, int tl, int tr, int l, int r)
    {
        if(tr <= l || r <= tl)
        {
            return {0, 0, 0, 0};
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        int tm = (tl + tr) / 2;

        return fo(get(2 * v + 1, tl, tm, l, r), get(2 * v + 2, tm, tr, l, r));
    }

    void update(int v, int tl, int tr, int pos, int x)
    {
        if(tr <= pos || pos + 1 <= tl)
        {
            return;
        }

        if(tl == pos && tr == pos + 1)
        {
            if(x == 0)
            {
                t[v] = {1, 1, 1, 1};
            } else {
                t[v] = {0, 0, 0, 1};
            }
            return;
        }

        int tm = (tl + tr) / 2;

        update(2 * v + 1, tl, tm, pos, x);
        update(2 * v + 2, tm, tr, pos, x);

        t[v] = fo(t[2 * v + 1], t[2 * v + 2]);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }

    D_o gg(v);

    int m;
    cin >> m;

    for(int i = 0; i < m; ++i)
    {
        string str;
        cin >> str;

        if(str == "QUERY")
        {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            cout << gg.get(0, 0, gg.n, l, r + 1)[1] << '\n';
        } else {
            int pos, x;
            cin >> pos >> x;
            --pos;
            gg.update(0, 0, gg.n, pos, x);
        }
    }
}