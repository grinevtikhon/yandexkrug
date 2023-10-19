#include<bits/stdc++.h>

using namespace std;

vector<long long> cif(10);

const long long max_sz = 1e2;

vector<long long> fact;

long long global_ans = 0;

long long parsoch(long long n, long long k)
{
    if(n == -1)
    {
        return 0;
    }
    if(n == 0 && k == 0)
    {
        return 1;
    }
    return fact[n] / (fact[n-k] * fact[k]);
}

void calc(vector<long long> &v)
{
    long long ans = 1;

    long long n = 0;
    for(long long i = 0; i < v.size(); ++i)
    {
        n += v[i];
    }

    if(n == v[0])
    {
        return;
    }

    for(long long i = 0; i < v.size(); ++i)
    {
        if(i == 0)
        {
            ans *= parsoch(n-1, v[i]);
        } else {
            ans *= parsoch(n, v[i]);
        }

        n -= v[i];
    }

    global_ans += ans;
}

void dfs(long long i, vector<long long> &v)
{
    if(v.size() == 10)
    {
        calc(v);
        return;
    }

    for(long long j = 0; j <= cif[i]; ++j)
    {
        if(j == 0 && cif[i] != 0)
        {
            continue;
        }
        v.push_back(j);
        dfs(i+1, v);
        v.pop_back();
    }
}


signed main()
{
    fact.resize(max_sz);
    fact[0] = 1;
    for(long long i = 1; i < fact.size(); ++i)
    {
        fact[i] = fact[i-1] * i;
    }

    string str;
    cin >> str;

    for(auto c : str)
    {
        cif[c - '0'] += 1;
    }

    vector<long long> v;
    dfs(0, v);


    cout << global_ans << '\n';

}