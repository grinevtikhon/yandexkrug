#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> spar;

vector<int> logs;

int inf = 1e6;

 vector<int> vec;

int foo(int a, int b)
{
    if(vec[a] > vec[b])
    {
        return a;
    }
    return  b;
}

void build()
{
    int n = vec.size();

    spar.resize(logs[n] + 10, vector<int>(n));


    for(int i = 0; i < n; ++i)
    {
        spar[0][i] = i;
    }

    for(int lvl = 0; lvl < spar.size()-1; ++lvl)
    {
        for(int i = 0; i + (1 << lvl) < n; ++i)
        {
            spar[lvl + 1][i] = foo(spar[lvl][i], spar[lvl][i + (1 << lvl)]);
        }
    }
}

int get(int l, int r)
{
    int sz = (r - l) + 1;

    int lvl = logs[sz];

    return foo(spar[lvl][l], spar[lvl][r - (1 << lvl) + 1]);
}


int main()
{
    long long x, y;

    x = 1e9;
    y = 1e9;
    long long ans = x * 1e9 + y;

    cout << ans << '\n';

    



}