#include<bits/stdc++.h>
using namespace std;

vector<vector<long long>> v;

struct grib
{
    set<long long> st;
    set<pair<long long ,long long>> b_a;
    set<pair<long long ,long long>> c_a;
    set<pair<long long ,long long>> c_b;

    void add(long long i)
    {
        st.insert(i);
        b_a.insert({v[i][1] - v[i][0], i});
        c_a.insert({v[i][2] - v[i][0], i});
        c_b.insert({v[i][2] - v[i][1], i});
    }
    void del(long long i)
    {
        st.erase(i);
        b_a.erase({v[i][1] - v[i][0], i});
        c_a.erase({v[i][2] - v[i][0], i});
        c_b.erase({v[i][2] - v[i][1], i});
    }
};

int main()
{
    long long x, y, z;

    cin >> x >> y >> z;

    vector<pair<long long, long long>> del;

    grib g1, g2, g3;

    for(long long i = 0; i < x + y + z; ++i)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        v.push_back({a, b, c});
        g1.add(i);
    }

    for(long long i = 0; i < y + z; ++i)
    {
        long long el = (*(--g1.b_a.end())).second;
        g2.add(el);
        g1.del(el);
    }

    for(long long i = 0; i < z; ++i)
    {
        if( (*(--g2.c_b.end())).first > (*(--g1.c_a.end())).first - (*g2.b_a.begin()).first)
        {
            long long el = (*(--g2.c_b.end())).second;
            g2.del(el);
            g3.add(el);
        } else {
            long long el1 = (*(--g1.c_a.end())).second;
            long long el2 = (*g2.b_a.begin()).second;

            g1.del(el1);
            g3.add(el1);
            g2.del(el2);
            g1.add(el2);
        }
    }

    long long ans = 0;

    for(auto i : g1.st)
    {
        ans += v[i][0];
    }
    for(auto i : g2.st)
    {
        ans += v[i][1];
    }
    for(auto i : g3.st)
    {
        ans += v[i][2];
    }

    cout << ans << '\n';
    
}