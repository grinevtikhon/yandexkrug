#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    int n, m;

    cin >> n >> m;

    long long sum = 0;

    int mat[n][m];

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
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

    vector<pair<int, int>> v;

    if(n % 2 == 0)
    {
        for(int i = 0; i < n; ++i)
        {
            if(i % 2 == 0)
            {
                for(int j = 1; j < m; ++j)
                {
                    v.push_back({i, j});
                }
            } else {
                for(int j = m-1; j >= 1; --j)
                {
                    v.push_back({i, j});
                }
            }
        }
        for(int i = n-1; i >= 0; --i)
        {
            v.push_back({i, 0});
        }
    } else {
        for(int j = 0; j < m; ++j)
        {
            if(j % 2 == 0)
            {
                for(int i = 1; i < n; ++i)
                {
                    v.push_back({i, j});
                } 
            } else {
                for(int i = n-1; i >= 1; --i)
                {
                    v.push_back({i, j});
                }
            }
        }

        for(int j = m-1; j >= 0; --j)
        {
            v.push_back({0, j});
        }
    }



    int path = 0;

    long long k = 0;

    long long mn = 1e18;

    for(int i = 0; i < v.size(); ++i)
    {
        k += mat[v[i].first][v[i].second];

        if(k < mn)
        {
            mn = k;
            path = (i + 1) % v.size();
        }
    }

    k = 0;

    for(int i = 0; i < v.size(); ++i)
    {
        int num = (i + path) % v.size();

        k += mat[v[num].first][v[num].second];

        if(k < 0)
        {
            cout << "alarm!!\n";
        }

        cout << v[num].first + 1 << ' ' << v[num].second + 1 << '\n';
    }
}