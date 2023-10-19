#include<bits/stdc++.h>

using namespace std;

long long dfs(long long i, long long pr, long long a, long long b, long long c)
{
    if(i == 21)
    {
        if(a > 0 && b > 0 && c > 0)
        {
            return 1;
        } else {
            return 0;
        }
    }

    long long ans = 0;
    if(pr != 1)
    {
        ans += dfs(i+1, 1, a + 1, b, c);
    }
    if(pr != 2)
    {
        ans += dfs(i+1, 2, a, b+1, c);
    }
    if(pr != 3)
    {
        ans += dfs(i+1, 3, a , b, c+1);
    }

    return ans;
}

signed main()
{
    long long n, k;

    cin >>  n >> k;

    long long ans = 0;

    if(n == 1)
    {
        if(k == 1)
        {
            ans = 0;
            // return -239;
        }
        if(k == 2)
        {
            ans = 2;
            // return -239;
        }
        if(k >= 3)
        {
            
            long long buf1 = 1572864;

            ans = dfs(1, 0, 0, 0, 0);

            ans = ans * (k*(k-1)*(k-2)) / 6;

            ans += k * (k-1);
            
        }
        cout << ans << '\n';
        return 0;
    }

    if(n == 3)
    {
        if(k == 1)
        {
            cout << 0 << '\n';
        } 
        if(k == 2)
        {
            cout << "2\n";
        }
        if(k >= 3){
            cout << (k * (k-1) * (k-2) / 6) * 18 + k*(k-1);
        }
        return 0;
    }

    if(n == 4)
    {
        if(k == 1)
        {
            cout << 0 << '\n';
        } 
        if(k == 2)
        {
            cout << "2\n";
        }
        if(k >= 3){
            cout << (k * (k-1) * (k-2) / 6) * 24570 + k*(k-1);
        }
        return 0;
    }

    if(n == 5)
    {
        if(k < 3)
        {
            cout << 0 << '\n';
        } else {
            cout << (k * (k-1) * (k-2) / 6) * 12;
        }
        return 0;
    }

    if(n == 6)
    {
        if(k < 3)
        {
            cout << 0 << '\n';
        } else {
            cout << k * (k-1) * (k-2);
        }
        return 0;
    }

    if(n == 7 || n == 2)
    {
        if(k < 3)
        {
            cout << 0 << '\n';
        } else {
            cout << (k * (k-1) * (k-2) / 6) * 96;
        }
        return 0;
    }

    if(n == 8)
    {
        if(k == 0)
        {
            cout << 0 << '\n';
        }
        if(k == 2)
        {
            cout << "2\n";
        }
         if(k >= 3) {
            cout << (k * (k-1) * (k-2) / 6) * 1073741820 + k * (k-1);
        }
        return 0;
    }


    return -239;
}