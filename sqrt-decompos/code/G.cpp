#include<bits/stdc++.h>

using namespace std;


void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    map<long long, bool> zap;

    for(int i = 0; i < m; ++i)
    {
        long long x, y;
        cin >> x >> y;
        if(x > y)
        {
            swap(x, y);
        }
        zap[x * (1e9) + y] = true;
    }

    vector<int> coord = a;
    sort(coord.begin(), coord.end());
    coord.resize(unique(coord.begin(), coord.end()) - coord.begin());

    vector<int> cnt(coord.size());

    for(int i = 0; i < a.size(); ++i)
    {
        int pos = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin();
        ++cnt[pos];
    }

    vector<int> cnt2 = cnt;
    sort(cnt2.begin(), cnt2.end());
    cnt2.resize(unique(cnt2.begin(), cnt2.end()) - cnt2.begin());

    vector<vector<long long>> gg(cnt2.size());

    for(int i = 0; i < cnt.size(); ++i)
    {
        int pos = lower_bound(cnt2.begin(), cnt2.end(), cnt[i]) - cnt2.begin();
        gg[pos].push_back(coord[i]);
    }

    for(int i = 0; i < gg.size(); ++i)
    {
        sort(gg[i].begin(), gg[i].end());
        reverse(gg[i].begin(), gg[i].end());
    }

    long long ans = -1;

    for(int ix = 0; ix < gg.size(); ++ix)
    {
        for(int iy = ix + 1; iy < gg.size(); ++iy)
        {
            long long sz = cnt2[ix] + cnt2[iy];


            for(auto x : gg[ix])
            {
                for(auto y : gg[iy])
                {
                    if(zap[min(x, y) * (1e9) + max(x, y)])
                    {
                        continue;
                    }

                    ans = max(ans, (x + y) * sz);
                    zap.erase(min(x, y) * (1e9) + max(x, y));
                    break;
                }
            }

        }
    }

    for(int i = 0; i < gg.size(); ++i)
    {
        long long sz = cnt2[i] * 2;
        for(int ix = 0; ix < gg[i].size(); ++ix)
        {
            for(int iy = ix + 1; iy < gg[i].size(); ++iy)
            {
                long long x = gg[i][ix];
                long long y = gg[i][iy];

                if(zap[min(x, y) * (1e9) + max(x, y)])
                {
                    continue;
                }
                ans = max(ans, sz*(x + y));
                zap.erase(min(x, y) * (1e9) + max(x, y));
                break;
            }
        }
    }

    cout << ans << '\n';

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    
    int t;
    cin >> t;
    for(int i = 0; i < t; ++i)
    {
        solve();
    }
}