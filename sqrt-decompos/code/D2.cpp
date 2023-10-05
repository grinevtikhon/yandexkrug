#include<bits/stdc++.h>

using namespace std;

const long long p = 239;
const long long mod = 1e9 + 7;

const int inf = 1e5 + 239;
vector<long long> P;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    P.resize(inf);

    P[0] = 1;
    for(int i = 1; i < P.size(); ++i) P[i] = (P[i-1] * p) % mod;

    string str;
    cin >> str;

    int n;
    cin >> n;


    vector<pair<string, pair<int, int>>> q(n); // запросы {строка, k, номер запроса}

    for(int i = 0; i < n; ++i)
    {
        cin >> q[i].second.first;
        cin >> q[i].first;
        
        q[i].second.second = i;
    }

    sort(q.begin(), q.end(), [&](auto a, auto b){return a.first.size() < b.first.size();});


    vector<int> ans(n);

    while(!q.empty())
    {
        long long hsh = 0;
        int sz = q.back().first.size();

        if(sz * sz * 8 > str.size())
        {
            string s = q.back().first;
            int k = q.back().second.first;
            int num = q.back().second.second;
            q.pop_back();

            long long hsh1 = 0;

            for(int i = 0;i < s.size(); ++i)
            {
                hsh1 = (hsh1 * p + s[i]) % mod;
            }

            vector<int> vec;

            for(int i = 0; i < sz; ++i)
            {
                hsh = (hsh * p + str[i]) % mod;
            }

            if(hsh == hsh1)
            {
                vec.push_back(0);
            }

            for(int i = sz; i < str.size(); ++i)
            {
                hsh = (hsh * p + str[i]) % mod;
                hsh = (hsh + mod*mod - P[sz] * str[i - sz]) % mod;
                // h.emplace_back(hsh, i - sz + 1);
                if(hsh == hsh1)
                {
                    vec.push_back(i - sz + 1);
                }
            }


            int l = 0;

            int otv = 1e9;

            while(l + k - 1 < vec.size())
            {
                otv = min(otv, vec[l + k - 1] - vec[l]);
                ++l;
                if(otv == 0)
                {
                    break;
                }
            }

            if(otv < 1e9)
            {
                otv += sz;
            } else {
                otv = -1;   
            }

            ans[num] = otv;


            continue;

        }

        vector<pair<long long, int>> h;  // хэши {хеш длинны sz, место вхождения хэша в str}

        for(int i = 0; i < sz; ++i)
        {
            hsh = (hsh * p + str[i]) % mod;
        }
        h.emplace_back(hsh, 0);

        for(int i = sz; i < str.size(); ++i)
        {
            hsh = (hsh * p + str[i]) % mod;
            hsh = (hsh + mod*mod - P[sz] * str[i - sz]) % mod;
            h.emplace_back(hsh, i - sz + 1);
        }

        sort(h.begin(), h.end());

        while(!q.empty() && q.back().first.size() == sz)
        {
            string s = q.back().first;
            int k = q.back().second.first;
            int num = q.back().second.second;
            q.pop_back();

            hsh = 0;

            for(int i = 0;i < s.size(); ++i)
            {
                hsh = (hsh * p + s[i]) % mod;
            }

            int l = lower_bound(h.begin(), h.end(), make_pair(hsh, (int)0)) - h.begin();

            int otv = 1e9;

            while(l + k - 1 < h.size() && h[l + k - 1].first == hsh)
            {
                otv = min(otv, h[l + k - 1].second - h[l].second);
                ++l;
                if(otv == 0)
                {
                    break;
                }
            }

            if(otv < 1e9)
            {
                otv += sz;
            } else {
                otv = -1;   
            }

            ans[num] = otv;

        }

    }

    for(int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << '\n';
    }
    // cout << '\n';
}