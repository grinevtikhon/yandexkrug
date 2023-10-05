#include<bits/stdc++.h>

using namespace std;

const long long acc = 4;

long long n, m, k;
long long coconut_x, rock_x, rock_y;
long long coconut_y;


int kost = 0;

bool IsPointOnPath(long long x, long long y, long long x3, long long y3)
{
    long long X1 = coconut_x;
    long long Y1 = coconut_y;
    long long X2 = x;
    long long Y2 = y;
    long long X3 = x3;
    long long Y3 = y3;
    
    X1 -= X2;
    Y1 -= Y2;
    X3 -= X2;
    Y3 -= Y2;

    if(X1 * Y3 == X3 * Y1 && X1 * X3 + Y1 * Y3 <= 0)
    {
        return true;
    }

    return false;

}

bool PathCheck(long long endpoint_x, long long endpoint_y)
{

    long long rocks_met = 0;

    long long roi_i_min = min(endpoint_x, coconut_x) / n;
    roi_i_min -= acc;
    long long roi_i_max = max(endpoint_x, coconut_x) / n;
    roi_i_max += acc;

    long long roi_j_min = min(endpoint_y, coconut_y) / m;
    roi_j_min -= acc;
    long long roi_j_max = max(endpoint_y, coconut_y) / m;
    roi_j_max += acc;

    for(long long i = roi_i_min; i <= roi_i_max; ++i)
    {
        for(long long j = roi_j_min; j <= roi_j_max; ++j)
        {
            long long dot_x = n*i;
            long long dot_y = m*j;

            if(i % 2 == 0)
            {
                dot_x += rock_x;
            } else {
                dot_x += n - rock_x;
            }

            if(j % 2 == 0)
            {
                dot_y += rock_y;
            } else {
                dot_y += m - rock_y;
            }
            //ASSUME I BELIEVE IT 2

            if(IsPointOnPath(dot_x, dot_y, endpoint_x, endpoint_y))
            {
                ++rocks_met;
            }

            if(!(n * i == endpoint_x && m * j == endpoint_y))
            {
                if(IsPointOnPath(n*i, m*j, endpoint_x, endpoint_y))
                {
                    return false;
                }
            }

        }
    }

    if(rocks_met == 1)
    {
        return true;
    }
    return false;
}

int main()
{
    
    cin >> n >> m >> k;

    
    cin >> coconut_x >> coconut_y >> rock_x >> rock_y;

    long long ans = k + 1;

    for(long long i = -k - 8; i <= k + 8; ++i)
    {
        for(long long j = -k - 8; j <= k + 8; ++j)
        { 
            long long endpoint_x = i * n;
            long long endpoint_y = j * m;

            long long hits = 0;
            if(i <= 0)
            {
                hits += -i;
            } else {
                hits += i-1;
            }
            if(j <= 0)
            {
                hits += -j;
            } else {
                hits += j-1;
            }
            //ASSUME I BELIEVE IT?
            if (hits > k)
            {
                continue;
            }

            kost = 0;
            if(PathCheck(endpoint_x, endpoint_y))
            {
                hits -= kost;
                ans = min(ans, hits);
                    
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