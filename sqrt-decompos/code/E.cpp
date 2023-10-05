#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

const long long p = 999999733;
const long long mod = 999999893;
long long mod_2 = 0;

const int inf = (1e5) + 10;

long long P[inf];
long long hsh[inf];



long long get(int l, int r)
{
    long long ans = hsh[r + 1] - hsh[l]*P[r-l+1];
    ans = (ans + mod_2) % mod;
    // ans = ((ans % mod) + mod) % mod;
    return ans;
}

signed main()
{
    mod_2 = mod * mod;

    // for(int i = 1e9; i > 1e9 - 1e3; --i)
    // {
    //     bool fl = true;
    //     for(int j = 2; j < i; ++j)
    //     {
    //         if(i % j == 0)
    //         {
    //             fl = false;
    //             break;
    //         }
    //     }
    //     if(fl)
    //     {
    //         cout << i << '\n';
    //     }
    // }
    // return 0;


    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    P[0] = 1;
    for(int i = 1; i < inf; ++i)
    {
        P[i] = (P[i-1] * p) % mod;
    }

    string str;
    cin >> str;


    // assert(str.size() <= 1e5);
    hsh[0] = 0;

    {
        long long buf = 0;

        for(int i = 0; i < str.size(); ++i)
        {
            buf = (buf * p + str[i]) % mod;
            hsh[i + 1] = buf;
        }
    }

    int n;

    cin >> n;

    vector<string> ss(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> ss[i];
    }

    sort(ss.begin(), ss.end(), [&](string a, string b){return a.size() < b.size();});


    int qsz;
    cin >> qsz;

    vector<pair<int, int>> q(qsz);
    int ans[qsz];

    for(int i = 0; i < qsz; ++i)
    {
        ans[i] = 0;
        int l, r;
        cin >> l >> r;
        q[i] = {l-1, r-1};
    }

    int cnt[inf];
    int pr[inf];
    for(int i = 0; i < inf; ++i)
    {
        cnt[i] = 0;
        pr[i] = 0;
    }

    __gnu_pbds::gp_hash_table<long long, int> mp;
    vector<vector<int>> kost(1);


    
    
    

    for(int i = 0; i < n; ++i)
    {
        string s = ss[i];

        long long h = 0;
        for(int j = 0; j < s.size(); ++j)
        {
            h = (h * p + s[j]) % mod;
        }

        vector<int> myaso;

        if((double)s.size() >= sqrt((double)str.size()))
        {
            for(int j = 0; j  + s.size() - 1 < str.size(); ++j)
            {
                if(get(j, j + s.size() - 1) == h && s[0] == str[j]){
                    myaso.push_back(j);
                }
            }
        } else {

            if(mp.empty())
            {
                for(int j = 0; j  + s.size() - 1 < str.size(); ++j)
                {
                    auto& jj = mp[get(j, j + s.size() - 1)];

                    if(jj == 0)
                    {
                        jj = kost.size();
                        kost.push_back({j});
                    } else {
                        kost[jj].push_back(j);
                    }
                }
            }

            myaso = kost[mp[h]];
        }

        if(myaso.size() < 1000)
        {
            for(int j = 0; j < myaso.size(); ++j)
            {
                if(str[myaso[j]] == s[0])
                {
                    cnt[myaso[j]] += 1;
                }
            }
        } else {

            for(int j = 0; j < myaso.size(); ++j)
            {
                //if(str[myaso[j]] == s[0])
                //{
                    cnt[myaso[j]] += 1;
                //}
            }
        }

        if(i == n-1 || ss[i+1].size() != s.size())
        {
            if(s.size() != 1)
            {
                pr[0] = cnt[0];
                for(int j = 1; j < str.size(); ++j)
                {
                    pr[j] = pr[j-1] + cnt[j];
                    if(j - (int)s.size() + 1 >= 0)
                    {
                        pr[j] -= cnt[j - ((int)s.size()) + 1];
                    }
                }
            }

            for(int j = 1; j < str.size(); ++j)
            {
                cnt[j] += cnt[j-1];
            }

            for(int j = 0; j < q.size(); ++j){
                if(q[j].second - q[j].first + 1 < s.size())
                {
                    continue;
                }
                int l = q[j].first;
                int r = q[j].second;

                ans[j] += cnt[r];
                ans[j] -= pr[r];
                if(l - 1 >= 0)
                {
                    ans[j] -= cnt[l-1];
                }
            }
            for(int i = 0; i < str.size(); ++i){
                cnt[i] = 0;
                pr[i] = 0;
            }
            mp.clear();
            kost.clear();
            kost.push_back({});

        }
    }

    for(int i = 0; i < qsz; ++i)
    {
        cout << ans[i] << ' ';
    }


    cout << '\n';
}