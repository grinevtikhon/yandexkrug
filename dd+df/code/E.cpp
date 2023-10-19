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
        t.resize(4 * n);

        build(0, 0, n);
    }

    void build(int v, int tl, int tr)
    {
        if(tl == tr - 1)
        {
            t[v] = {vec[tl]};
            return;
        }

        int tm = (tl + tr) / 2;
        
        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm, tr);

        t[v].resize(t[2 * v + 1].size() + t[2 * v + 2].size());

        merge(t[2 * v + 1].begin(), t[2 * v + 1].end(), t[2 * v + 2].begin(), t[2 * v + 2].end(), t[v].begin());
    }

    int get(int v, int tl, int tr, int l, int r)
    {
        if(tr <= l || r <= tl)
        {
            return 0;
        }

        if(l <= tl && tr <= r)
        {
            return (upper_bound(t[v].begin(), t[v].end(), l-1) - t[v].begin());
        }

        int tm = (tl + tr) / 2;

        return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(m);
    vector<int> b(n);

    for(int i = 0; i < m; ++i)
    {
        cin >> a[i];
        --a[i];
    }

    for(int i = 0; i < n; ++i)
    {
        cin >> b[i];
        --b[i];
    }

    vector<bool> used(n);

    vector<int> str;

    int num = 0;

    for(int i = 0; i < m; ++i)
    {
        int el = a[i];
        if(used[el])
        {
            str.push_back(a[i]);
        } else {
            while(!used[el])
            {
                str.push_back(b[num]);
                used[b[num]] = true;
                ++num;
            }
        }
    }


    vector<int> prev(str.size());

    vector<int> pos(n, -1);

    for(int i = 0; i < str.size(); ++i)
    {
        prev[i] = pos[str[i]];
        pos[str[i]] = i;
    }

    vector<int> nex(str.size());
    pos.clear();
    pos.resize(n, -1);
    for(int i = str.size() - 1; i>= 0; --i)
    {
        nex[i] = pos[str[i]];
        pos[str[i]] = i;
    }

    D_o sm(prev);

    cout << str.size() << '\n';

    for(int i = 0; i < str.size(); ++i)
    {
        if(nex[i] == -1)
        {
            cout << n << ' ';
        } else {
            cout << sm.get(0, 0, sm.n, i, nex[i]) << ' ';
        }
    }
    cout << '\n';

}