#include<bits/stdc++.h>

using namespace std;

long long n, s;

bool foo(long long b)
{
    long long sum = 0;
    long long buf = n;

    while(buf > 0)
    {
        sum += buf % b;
        buf /= b;
    }

    return sum == s;
}

int main()
{

    cin >> n >> s;

    if(s > n)
    {
        cout << "-1\n";
        return 0;
    }

    if(s == n)
    {
        cout << n + 1 << '\n';
        return 0;
    }

    long long d = n - s;

    long long ans = 1e12;

    for(long long i = 1; i * i <= d; ++i)
    {
        if(d % i == 0)
        {
            if(foo(i + 1))
            {
                ans = min(ans, i + 1);
            }
            if(foo(1 + (d/i)))
            {
                ans = min(ans, 1 + (d/i));
            }
        }
    }

    if(ans != 1e12)
    {
        cout << ans << '\n';
    } else {
        cout << "-1\n";
    }


}