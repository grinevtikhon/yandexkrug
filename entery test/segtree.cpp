#include<bits/stdc++.h>

using namespace std;

#define INF 1e9

struct seg_tree{
    vector<int> t;
    vector<int> vec;
    vector<int> promis;

    int n;

    seg_tree(vector<int> &_vec)
    {
        vec = _vec;
        n = vec.size();
        t.resize(4*n);
        promis.resize(4*n);

        build(0, 0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl + 1 == tr)
        {
            t[v] = vec[tl];
            return;
        }

        int tm = (tl + tr) / 2;

        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }

    int get(int v, int tl, int tr, int l, int r)
    {
        if(tr <= l || r <= tl)
        {
            return INF;
        }

        if(l <= tl && tr <= r)
        {
            return t[v];
        }

        int tm = (tl + tr) / 2;
        return min(get(2 * v + 1, tl, tm, l, r), get(2 * v + 2, tm, tr, l, r));
    }

};

int main()
{
    vector<int> v;

    seg_tree st(v);

}