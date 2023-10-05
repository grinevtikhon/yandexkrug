#include<bits/stdc++.h>

using namespace std;

long long f_pow(long long a, long long b)
{
    if(b == 0)
    {
        return 1;
    }
    return f_pow(a, b-1) * a;
}

int main()
{
    long long n;
    cin >> n;
    vector<long long> a(n), b(n);

    for(long long i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for(long long i =0 ;i < n; ++i)
    {
        cin >> b[i];
    }

    vector<bool> ans(52, false);

    for(int i = 0; i < n; ++i)
    {
        int d = a[i] - b[i];

        for(int j = b[i] + 1; j <= d; ++j)
        {
            if(d % j == 0)
            {
                ans[j] = true;
                break;
            }
        }
    }

    vector<bool> ok(n, false);
    int cnt = 0;

    for(int i = 0; i < n; ++i)
    {
        if(a[i] == b[i])
        {
            ok[i] = true;
            ++cnt;
        }
    }

    long long otv = 0;

    for(int i = ans.size() - 1; i > 0; --i)
    {
        if(ans[i] == false)
        {
            continue;
        }

        bool used = false;

        for(int j = 0; j < n; ++j)
        {
            if((a[j] % i == b[j]) && (ok[j] == false))
            {
                ok[j] = true;
                ++cnt;
                used = true;
            }
        }

        if(used)
        {
            otv += f_pow(2, i);
        }
    }


    if(cnt == n)
    {
        cout << otv << '\n';
    } else {
        cout << "-1\n";
    }

}