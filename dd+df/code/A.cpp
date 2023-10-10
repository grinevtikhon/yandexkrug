#include<bits/stdc++.h>

using namespace std;

struct D_o
{
    vector<int> vec;
    vector<vector<int>> t;
    int n;

    D_o(vector<int> &_vec)
    {
        vec = _vec;
        n = vec.size();

        t.resize(4*n);

        build(0,0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = {vec[tl]};
            return;
        }

        int tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v].resize(t[2 * v + 1].size()+ t[2 * v + 2].size());

        merge(t[2 * v + 1].begin(), t[2 * v + 1].end(), t[2 * v + 2].begin(), t[2 * v + 2].end(), t[v].begin()); 
    }


    int get(int v, int tl, int tr, int l, int r, int a, int b)
    {
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return upper_bound(t[v].begin(), t[v].end(), b) - lower_bound(t[v].begin(), t[v].end(), a);
        }

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r, a, b) + get(2 * v + 2, tm, tr, l, r, a, b);
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> v(n);

    for(int i = 0; i < n; ++i) cin >> v[i];

    D_o sm(v);

    for(int i = 0; i < m; ++i)
    {
        int x, y, k, l;
        cin >> x >> y >> k >> l;

        --x;
        --y;

        cout << sm.get(0, 0, sm.n, x, y+1, k, l) << '\n';

    }

}