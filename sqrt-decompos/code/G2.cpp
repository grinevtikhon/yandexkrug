#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>

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

    vector<pair<int, int>> zap;

    for(int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        if(x > y)
        {
            swap(x, y);
        }
        zap.emplace_back(x, y);
    }

    sort(zap.begin(), zap.end());

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

    vector<vector<int>> gg(cnt2.size());

    for(int i = cnt.size()-1; i >= 0; --i)
    {
        int pos = lower_bound(cnt2.begin(), cnt2.end(), cnt[i]) - cnt2.begin();
        gg[pos].push_back(coord[i]);
    }

    // for(int i = 0; i < gg.size(); ++i)
    // {
    //     sort(gg[i].begin(), gg[i].end());
    //     reverse(gg[i].begin(), gg[i].end());
    // }

    long long ans = -1;

    for(int ix = 0; ix < gg.size(); ++ix)
    {
        for(int iy = ix + 1; iy < gg.size(); ++iy)
        {
            int sz = cnt2[ix] + cnt2[iy];

            for(auto x : gg[ix])
            {
                for(auto y : gg[iy])
                {
                    long long n_ans = ((long long)x + (long long)y) * (long long)sz;


                    if(n_ans < ans)
                    {
                        break;
                    }

                    auto gaga = lower_bound(zap.begin(), zap.end(), make_pair(min(x, y), max(x, y)));
                    if(gaga != zap.end() && (*gaga) == make_pair(min(x, y), max(x, y)))
                    {
                        continue;
                    }

                    ans = max(ans, ((long long)x + (long long)y) * (long long)sz);
                    break;
                }
            }

        }
    }

    for(int i = 0; i < gg.size(); ++i)
    {
        int sz = cnt2[i] * 2;
        for(int ix = 0; ix < gg[i].size(); ++ix)
        {
            for(int iy = ix + 1; iy < gg[i].size(); ++iy)
            {
                int x = gg[i][ix];
                int y = gg[i][iy];

                long long n_ans = ((long long)x + (long long)y) * (long long)sz;

                if(n_ans < ans)
                {
                    break;
                }

                auto gaga = lower_bound(zap.begin(), zap.end(), make_pair(min(x, y), max(x, y)));
                if(gaga != zap.end() && (*gaga) == make_pair(min(x, y), max(x, y)))
                {
                    continue;
                }
                ans = max(ans, (long long)sz*((long long)x + (long long)y));
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