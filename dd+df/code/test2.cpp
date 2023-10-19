#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(293872938);

signed main()
{

    vector<long long> cnt(10);
    for(long long ii = 0; ii < 2e4; ++ii)
    {
        long long i = rnd() % ((long long) 9e9);
        i += 1e9;
        if(i % 3 == 0)
        {
            continue;
        }
        bool fl = false;
        long long buf = i;
        while(buf > 0)
        {
            if((buf % 10) % 2 == 1)
            {
                fl = true;
                break;
            }
            buf /= 10;
        }
        if(fl == false)
        {
            continue;
        }
        buf = i;

        for(long long j = 0; j < 7; ++j)
        {
            cnt[buf%10]++;
            buf /= 10;
        }
    }

    for(long long i = 0; i < cnt.size(); ++i)
    {
        cout << i << ' ' << cnt[i] << '\n';
    }
}