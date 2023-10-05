#include<bits/stdc++.h>

using namespace std;

const long long acc = 5;

long long n, m, k;
long long x1, x2, y2;
long long yy1;


bool cool(long long x, long long y, long long x3, long long y3)
{
    long long dx = x3 - x;
    long long dy = y3 - y;
    x = x1 - x;
    y = yy1 - y;

    if(x * dy == dx * y && x * dx + y * dy < 0)
    {
        return true;
    }
    return false;

}

bool foo(long long x, long long y)
{

    long long cnt = 0;

    long long dx = x - x1;
    long long dy = y - yy1;

    long long beg = min(x, x1) / n;
    beg -= acc;
    long long endd = max(x, x1) / n;
    endd += acc;

    long long yl = min(y, yy1) / m;
    yl -= acc;
    long long yr = max(y, yy1) / m;
    yr += acc;

    for(long long i = beg; i <= endd; ++i)
    {

        for(long long j = yl; j <= yr; ++j)
        {
            long long dot_x = n*i;

            if(i % 2 == 0)
            {
                dot_x += x2;
            } else {
                dot_x += n - x2;
            }

            long long dot_y = m*j;
            if(j % 2 == 0)
            {
                dot_y += y2;
            } else {
                dot_y += m - y2;
            }

            if(cool(dot_x, dot_y, x, y))
            {
                ++cnt;
            }

            if( cool(n*i, m*j, x, y))
            {
                return false;
            }

        }
    }

    if(cnt == 1)
    {
        return true;
    }
    return false;
}

int main()
{
    
    cin >> n >> m >> k;

    
    cin >> x1 >> yy1 >> x2 >> y2;

    long long ans = k + 1;

    for(long long i = 0; i <= k; ++i)
    {
        long long x;
        long long y;

        x = -i * n;
        for(long long j = -i; j <= i+1; ++j)
        {
            y = j * m;
            long long cnt = i;
            if(j <= 0)
            {
                cnt += -j;
            }
            if(j > 0)
            {
                cnt += j-1;
            }
            if(cnt > k)
            {
                continue;
            }
            
            if(foo(x, y))
            {
                
                ans = min(ans, cnt);
            }
        }

        x = (i + 1) * n;
        for(long long j = -i; j <= i+1; ++j)
        {
            y = j * m;
            long long cnt = i;
            if(j <= 0)
            {
                cnt += -j;
            }
            if(j > 0)
            {
                cnt += j-1;
            }
            if(cnt > k)
            {
                continue;
            }
            if(foo(x, y))
            {
                
                ans = min(ans, cnt);
            }
        }

        y = -i *m;
        for(long long j = -i; j <= i+1; ++j)
        {
            x = j * n;
            long long cnt = i;
            if(j <= 0)
            {
                cnt += -j;
            }
            if(j > 0)
            {
                cnt += j-1;
            }
            if(cnt > k)
            {
                continue;
            }
            if(foo(x, y))
            {   
                ans = min(ans, cnt);
            }
        }

        y = (i + 1) * m;
        for(long long j = -i; j <= i+1; ++j)
        {
            x = j * n;
            long long cnt = i;
            if(j <= 0)
            {
                cnt += -j;
            }
            if(j > 0)
            {
                cnt += j-1;
            }
            if(cnt > k)
            {
                continue;
            }
            if(foo(x, y))
            {
                ans = min(ans, cnt);
            }
        }
    }

    if(ans == k+1)
    {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}