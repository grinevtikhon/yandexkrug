#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, q, a, b;
    cin >> n >> q >> a >> b;

    if(a > b){
        swap(a, b);
    }

    map<pair<int, int>, long long> mp;

    mp[make_pair(a, b)] = 0;

    for(int i = 0; i < q; ++i)
    {

        int pos;
        cin >> pos;

        map<pair<int, int>, long long> pr_mp;
        swap(mp, pr_mp);

        for(auto i : pr_mp)
        {
            int x = i.first.first;
            int y = i.first.second;

            int z = i.second;

            if(x == pos)
            {
                mp[{x, y}] = z;
                continue;
            }
            if(y == pos)
            {
                mp[{x, y}] = z;
                continue;
            }

            

            int time = 0;

            if(pos > x)
            {

                time = mp[{x, pos}];

                if(time == 0 || z + abs(pos - y) < time)
                {
                    mp[{x, pos}] = z + abs(pos - y);
                }
            }

            if(pos < y)
            {
                time = mp[{pos, y}];

                if(time == 0 || z + abs(pos - x) < time)
                {
                    mp[{pos, y}] = z + abs(pos - x);
                }
            }
        }
    }

    long long ans = 1e15;

    for(auto i : mp)
    {

        if(i.first.first > i.first.second)
        {
            return 1;
        }
        ans = min(ans, i.second);
    }

    cout << ans << '\n';
}