#include<bits/stdc++.h>

using namespace std;

vector<vector<long long>> gr;

long long n = 30;

bool ckeck(vector<long long> col)
{
    bool fl = true;

    long long a, b, c;
    a = b = c = 0;
    for(long long i = 0; i < n; ++i)
    {
        if(col[i] == 1)
        {
            ++a;
        }
        if(col[i] == 2)
        {
            ++b;
        }
        if(col[i] == 3)
        {
            ++c;
        }
        for(auto v : gr[i])
        {
            if(col[v] == col[i])
            {
                fl = false;
                return false;
            }
        }
    }

    if(a > 0 && b > 0 && c > 0)
    {
        return true;
    } else {
        return false;
    }
    // return true;


}

long long dfs(long long i, vector<long long> col)
{
    if(i == n)
    {
        if(ckeck(col))
        {
            return 1;
        } else {
            return 0;
        }
    }

    
    long long ans = 0;

    col.push_back(1);
    ans += dfs(i + 1, col);
    col.pop_back();

    col.push_back(2);
    ans += dfs(i + 1, col);
    col.pop_back();

    col.push_back(3);
    ans += dfs(i + 1, col);

    return ans;
}

signed main()
{
    

    vector<vector<int>> v(3, vector<int>(3));

    v[0][0] = 1;
    v[1][1] = 1;
    v[2][2] = 1;

    for(int i = 0; i < 29; ++i)
    {
        vector<vector<int>> pr_v = v;
        v[0][0] = pr_v[0][1] + pr_v[0][2];
        v[0][1] = pr_v[0][2] + pr_v[0][0];
        v[0][2] = pr_v[0][0] + pr_v[0][1];

        v[1][0] = pr_v[1][1] + pr_v[1][2];
        v[1][1] = pr_v[1][2] + pr_v[1][0];
        v[1][2] = pr_v[1][0] + pr_v[1][1];

        v[2][0] = pr_v[2][1] + pr_v[2][2];
        v[2][1] = pr_v[2][2] + pr_v[2][0];
        v[2][2] = pr_v[2][0] + pr_v[2][1];
    }

    long long ans = 0;

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(i != j)
            {
                ans += v[i][j];
            }
        }
    }

    cout << ans << '\n';


}