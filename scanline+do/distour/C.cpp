#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

int nesootv = 0;

struct grib
{
    __gnu_pbds::gp_hash_table<int, int> mp;
    set<int> st;


    grib()
    {
    }

    grib(int p, int q, int i)
    {
        add(p, 1);
        add(q, -1);

        st.insert(i);
    }

    void add(int key, int del)
    {
        if(mp[key] == 0)
        {
            ++nesootv;
        }
        mp[key] += del;
        if(mp[key] == 0)
        {
            --nesootv;
        }
    }

    void merge(grib &o)
    {
        for(auto i : o.mp)
        {
            add(i.first, i.second);
            if(i.second != 0)
            {
                --nesootv;
            }
        }

        for(auto i : o.st)
        {
            st.insert(i);
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> p(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> p[i];
    }

    vector<int> q = p;
    sort(q.begin(), q.end());

    vector<grib> all_gribs;

    vector<int> sad;
    for(int i = 0; i < n; ++i)
    {
        all_gribs.emplace_back(p[i], q[i], i);
        sad.emplace_back(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int qq;
        cin >> qq;

        if(qq == 1)
        {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
     
            int l, r;

            l = sad[a];
            r = sad[b];

            all_gribs[l].add(p[a], -1);
            all_gribs[l].add(p[b], 1);

            all_gribs[r].add(p[a], 1);
            all_gribs[r].add(p[b], -1);

            swap(p[a], p[b]);
        }
        if(qq == 2)
        {
            int a, b;
            cin >> a >> b;
            --a;
            --b;

            int l = sad[a];
            int r = sad[b];

            if(l == r)
            {
                continue;
            }

            if(all_gribs[l].mp.size() < all_gribs[r].mp.size())
            {
                swap(l, r);
            }

            for(auto j : all_gribs[r].st)
            {
                sad[j] = l;
            }

            all_gribs[l].merge(all_gribs[r]);

            __gnu_pbds::gp_hash_table<int, int> tmp1;
            set<int> tmp2;

            swap(all_gribs[r].mp, tmp1);
            swap(all_gribs[r].st, tmp2);
        }

        if(qq == 3)
        {

            if(nesootv == 0)
            {
                cout << "DA\n";
            } else {
                cout << "NE\n";
            }
        }
    }
}