#include<bits/stdc++.h>

using namespace std;

int n, m;

int block = 1000;

int power[100000];
int next_pool[100000];
int hit[100000];

inline void update0(int x)
{
    int l = (x / block) * block;
    int r = min(l + block, n);

    for(int i = r-1; i >= l; --i)
    {
        if(i + power[i] >= r)
        {
            hit[i] = 0;
            next_pool[i] = i;
        } else {
            hit[i] = hit[i + power[i]] + 1;
            next_pool[i] = next_pool[i + power[i]];
        }
    }

}

inline void update(int x)
{
    int l = (x / block) * block;
    int r = min(l + block, n);

    if(x + power[x] >= r)
    {
        hit[x] = 0;
        next_pool[x] = x;
    } else {
        hit[x] = hit[x + power[x]] + 1;
        next_pool[x] = next_pool[x + power[x]];
    }

    for(int i = x-1; i >= l; --i)
    {
        if(i + power[i] <= x)
        {
            hit[i] = hit[i + power[i]] + 1;
            next_pool[i] = next_pool[i + power[i]];
        }
    }

}

inline void print_ans(int x)
{

    int cnt = 0;
    int otv = x;
    int lst = x;

    while(lst < n)
    {
        cnt += hit[lst] + 1;
        otv = next_pool[lst];
        lst = otv + power[otv];
    }
    cout << otv + 1 << ' ' << cnt << '\n';
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;


    for(int i = 0; i < n; ++i)
    {
        cin >> power[i];
    }
    for(int i = 0; i < n; i += block)
    {
        update0(i);
    }

    for(int i = 0; i < m; ++i)
    {
        int c;
        cin >> c;

        if(c == 0)
        {
            int a, b;
            cin >> a >> b;
            --a;
            power[a] = b;
            update(a);
        } else {
            int a;
            cin >> a;
            --a;
            print_ans(a);
        }
    }
}