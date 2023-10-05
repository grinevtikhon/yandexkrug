#include<bits/stdc++.h>

using namespace std;

vector<int> coord;

struct D_o
{
    int n;
    vector<vector<int>> vec;
    vector<vector<int>> t;

    D_o(vector<vector<int>> &_vec)
    {
        vec = _vec;
        n = coord.size();
        t.resize(4 * n);
        
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

        t[v].resize(t[2 * v + 1].size() + t[2 * v + 2].size());

        merge(t[2 * v + 1].begin(), t[2 * v + 1].end(), t[2 * v + 2].begin(), t[2 * v + 2].end(), t[v].begin());
    }

    int get(int v, int tl, int tr, int l, int r, int y1, int y2)
    {
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return upper_bound(t[v].begin(), t[v].end(), y2) - lower_bound(t[v].begin(), t[v].end(), y1);
        }

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r, y1, y2) + get(2 * v + 2, tm, tr, l, r, y1, y2);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> dot(n);

    for(int i =0; i < n; ++i)
    {
        cin >> dot[i].first >> dot[i].second;
        coord.push_back(dot[i].first);
    }

    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    for(int i = 0; i < n; ++i)
    {
        dot[i].first = lower_bound(coord.begin(), coord.end(), dot[i].first) - coord.begin();
    }

    vector<vector<int>> v(coord.size());
    for(int i = 0; i < n; ++i)
    {
        v[dot[i].first].push_back(dot[i].second);
    }
    for(int i = 0; i < v.size(); ++i)
    {
        sort(v[i].begin(), v[i].end());
    }

    D_o gg(v);

    int m;
    cin >> m;

    for(int i = 0; i < m; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 = lower_bound(coord.begin(), coord.end(), x1) - coord.begin();
        x2 = upper_bound(coord.begin(), coord.end(), x2) - coord.begin();

        cout << gg.get(0, 0, gg.n, x1, x2, y1, y2) << '\n';

    }
}