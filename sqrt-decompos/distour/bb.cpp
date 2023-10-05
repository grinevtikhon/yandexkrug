#include<bits/stdc++.h>
 
using namespace std;
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
 
    long long n, m;
 
    cin >> n >> m;
 
    long long sum = 0;
 
    vector<vector<long long>> mat(n, vector<long long>(m));
 
    for(long long i = 0; i < n; ++i)
    {
        for(long long j = 0; j < m; ++j)
        {
            cin >> mat[i][j];
            sum += mat[i][j];
        }
    }
 
    if(n * m % 2 == 1 || sum < 0)
    {
        cout << "-1\n";
        return 0;
    }
 
    vector<pair<long long, long long>> v;
 
    if(n % 2 == 0)
    {
        for(long long i = 0; i < n; ++i)
        {
            if(i % 2 == 0)
            {
                for(long long j = 1; j < m; ++j)
                {
                    v.push_back({i, j});
                }
            } else {
                for(long long j = m-1; j >= 1; --j)
                {
                    v.push_back({i, j});
                }
            }
        }
        for(long long i = n-1; i >= 0; --i)
        {
            v.push_back({i, 0});
        }
    } else {
        for(long long j = 0; j < m; ++j)
        {
            if(j % 2 == 0)
            {
                for(long long i = 1; i < n; ++i)
                {
                    v.push_back({i, j});
                } 
            } else {
                for(long long i = n-1; i >= 1; --i)
                {
                    v.push_back({i, j});
                }
            }
        }
 
        for(long long j = m-1; j >= 0; --j)
        {
            v.push_back({0, j});
        }
    }
 
 
 
    vector<pair<long long, long long>> path;
 
    long long k = 0;
 
    for(long long i = 0; i < v.size(); ++i)
    {
        k = 0;
        path.clear();
        bool fl = true;
        for(long long j = 0; j < v.size(); ++j)
        {
            long long num = (i + j) % (v.size());
 
            path.push_back(v[num]);
 
            k += mat[v[num].first][v[num].second];
            if(k < 0)
            {
                fl = false;
                break;
            }
        }
        if(fl)
        {
            for(long long j = 0; j < path.size(); ++j)
            {
                cout << path[j].first + 1<< " " << path[j].second + 1 << '\n';
            }
            return 0;
        }
    }
}

/*

2 3
2 2
3 2
3 3
3 4
4 4
4 3
4 2
4 1
3 1
2 1
1 1
1 2
1 3
1 4
2 4

*/