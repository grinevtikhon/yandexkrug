#include<bits/stdc++.h>

using namespace std;

long long k = 1;

long long fo(long long a)
{
    long long ans = 0;
    while(a > 0)
    {
        ans += a % 2;
        a /= 2;
    }
    return ans;
}

int main()
{
    long long n;
    cin >> n;

    while((1 << k) < n)
    {
        ++k;
    }

    // cout << k << '\n';


    // if((1 << k) == n)
    // {
    //     vector<vector<long long>> ans(k);

    //     for(long long i = 0; i < n; ++i)
    //     {
    //         long long x = i;

    //         long long gr = 0;

    //         while(x > 0)
    //         {
    //             if(x % 2 == 1)
    //             {
    //                 ans[gr].push_back(i);
    //             }

    //             gr += 1;
    //             x /= 2;
    //         }
    //     }

    //     cout << k << " " << ans[0].size() << '\n';

    //     for(long long i = 0; i < ans.size(); ++i)
    //     {
    //         cout << ans[i].size() << ' ';
    //         for(long long j = 0; j < ans[i].size(); ++j)
    //         {
    //             cout << ans[i][j] << ' ';
    //         }
    //         cout << '\n';
    //     }
    // }


    vector<long long> vec((1 << k));

    for(long long i = 0; i < vec.size(); ++i)
    {
        vec[i] = i;
    }

    sort(vec.begin(), vec.end(), [&](long long a, long long b){
        if(fo(a) == fo(b))
        {
            return (b % 239) < (a%239);
        }
        return fo(a) < fo(b);

        });

    long long l = 0;
    long long r = (1<<k) / 2;

    while(r - l > 1)
    {
        long long m = (r + l) / 2;

        vector<long long> cnt(k, m);

        long long ans = 0;

        for(long long i = 0; i < vec.size(); ++i)
        {
            long long buf = vec[i];

            bool fl = true;
            long long gr = 0;

            while(buf > 0)
            {
                if(buf % 2 == 1 && cnt[gr] == 0)
                {
                    fl = false;
                    break;
                }
                ++gr;
                buf /= 2;
            }

            if(fl)
            {
                buf = vec[i];
                gr = 0;
                ++ans;
                while(buf > 0)
                {
                    if(buf % 2 == 1)
                    {
                        --cnt[gr];
                    }
                    ++gr;
                    buf /= 2;
                }
            }
        }

        if(ans >= n)
        {
            r = m;
        } else {
            l = m;
        }
    }

    cout << k << ' ' << r << '\n';

    vector<vector<long long>> otv(k);


    vector<long long> cnt(k, r);

    long long ans = 0;

    for(long long i = 0; i < vec.size(); ++i)
    {
        long long buf = vec[i];

        bool fl = true;
        long long gr = 0;

        while(buf > 0)
        {
            if(buf % 2 == 1 && cnt[gr] == 0)
            {
                fl = false;
                break;
            }
            ++gr;
            buf /= 2;
        }

        if(fl)
        {
            buf = vec[i];
            gr = 0;
            ++ans;
            while(buf > 0)
            {
                if(buf % 2 == 1)
                {
                    --cnt[gr];
                    otv[gr].push_back(ans);
                }
                ++gr;
                buf /= 2;
            }
        }

        if(ans >= n)
        {
            break;
        }
    }

    for(long long i = 0; i < otv.size(); ++i)
    {
        cout << otv[i].size() << ' ';

        for(long long j = 0; j < otv[i].size(); ++j)
        {
            cout << otv[i][j] << ' ';
        }

        cout << '\n';
    }




}