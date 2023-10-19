#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> vec;

void dfs(vector<int> v)
{
    if(v.size() == 7)
    {
        vec.push_back(v);
        return;
    }

    for(int i = -2; i <= 2; ++i)
    {
        v.push_back(i);
        dfs(v);
        v.pop_back();
    }
}

long long fo(vector<int> v, int x)
{
    long long ans = 0;

    for(int i = 0; i < v.size(); ++i)
    {
        ans += pow(x, i) * v[i];
    }

    return ans;
}

int main()
{
    dfs({});

    cout << "calculated!!\n";

    long long ans = -1e9;

    vector<int> aboba;

    for(int i = 0; i < vec.size(); ++i)
    {
        if(fo(vec[i], 3) == -1343)
        {
            
            if(ans < fo(vec[i], 4))
            {
                ans = fo(vec[i], 4);
                aboba = vec[i];
            }
            // cout << fo(vec[i], 4) << '\n';
        }
    }

    cout << ans << '\n';

    for(int i = 0; i < aboba.size(); ++i)
    {
        cout << "a" << i << " = " << aboba[i] << '\n';
    }
}