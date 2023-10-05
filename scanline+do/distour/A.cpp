#include<bits/stdc++.h>

using namespace std;

int main()
{
    string l, r;
    cin >> l >> r;

    long long ans = 0;

    for(int sz = l.size(); sz <= r.size(); ++sz)
    {
        if(sz == 1)
        {
            ans += 9;
        } else {
            ans += 90;
        }
    }

    if(l.size() == 1)
    {
        ans -= (l[0] - '0') - 1;
    }
    if(r.size() == 1)
    {
        ans -= 9 - (r[0] - '0');
    }

    for(int a = 1; a <= 9; ++a)
    {
        for(int d = 0; d <= 9; ++d)
        {
            int c = a;

            if(l.size() != 1)
            {

                for(int i = 0; i < l.size(); ++i)
                {
                    if(c < l[i] - '0')
                    {
                        --ans;
                        break;
                    }
                    if(c > l[i] - '0')
                    {
                        break;
                    }
                    c = (c + d) % 10;
                }
                c = a;
            }


            if(r.size() != 1)
            {
                for(int i = 0; i < r.size(); ++i)
                {
                    if(c < r[i] - '0')
                    {
                        break;
                    }
                    if(c > r[i] - '0')
                    {
                        --ans;
                        break;
                    }
                    c = (c + d) % 10;
                }
            }
        }
    }
    cout << ans << '\n';
}