#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> gr;

#define INF (int)1e9

vector<int> path;
vector<int> loop;

vector<int> used;

void dfs(int v, int p)
{
    used[v] += 1;
    path.push_back(v);

    for(auto u : gr[v])
    {
        if(used[u] == 2)
        {
            continue;
        }
        if(used[u] == 1)
        {
            if(u != p)
            {
                int sz = 1;
                while(path[path.size() - sz] != u)
                {
                    ++sz;
                }
                for(int i = 0; i < sz; ++i)
                {
                    int gg = path[path.size() - 1 - i];
                    loop[gg] = sz;
                }
            }
        } else {
            dfs(u, v);
        }
    }
    used[v] += 1;
    path.pop_back();
}

int main()
{
    int n, k;
    cin >> n >> k;

    gr.resize(n);
    used.resize(n);
    loop.resize(n);

    for(int i = 0; i < k; ++i)
    {
        int v, u;
        cin >> v >> u;
        --v;
        --u;

        gr[u].push_back(v);
        gr[v].push_back(u);
    }


    vector<int> time(n, -INF);

    int start, finish;

    int l;
    cin >> l;


    for(int i = 0; i < l + 1; ++i)
    {
        int u;
        cin >> u;
        --u;
        time[u] = max(-i, time[u]);
        if(i == 0)
        {
            start = u;
        }
    }

    cin >> finish;
    --finish;

    dfs(start, start);

    

    // for(int i = 0; i < loop.size(); ++i)
    // {
    //     cout << loop[i] << '\n';
    // }

    deque<int> dq{start};
    vector<bool> ass(n);
    
    ass[start] = true;

    while(!dq.empty())
    {
        int v = dq.back();
        dq.pop_back();

        for(auto u : gr[v])
        {
            if(ass[u] || time[v] - time[u] == 1 || time[v] - time[u] + 1 < l)
            {
                continue;
            }

            dq.push_front(u);
            time[u] = time[v] + 1;
            ass[u] = true;
        }
        if(time[finish] >= 0)
        {
            cout << time[finish] << '\n';
            return 0;
        }
    }

    int otv = INF;

    vector<int> ans(n);
    ans[finish] = 0;

    ass.clear();
    ass.resize(n);
    ass[finish] = true;
    
    dq.clear();
    dq.push_front(finish);



    while(!dq.empty())
    {
        int v = dq.back();
        dq.pop_back();
        for(auto u : gr[v])
        {
            if(ass[u])
            {
                continue;
            }

            dq.push_front(u);
            ans[u] = ans[v] + 1;
            ass[u] = true;

            if(loop[u] >= l && time[u] >= 0)
            {
                otv = min(otv, ans[u] + loop[u] + time[u]);
            }
        }
    }

    if(otv != INF)
    {
        cout << otv << "\n";
    } else {
        cout << "-1\n";
    }

    


}

/*

6 6
1 2
2 3 
3 4
4 5
5 6
6 3
1
2 1
1

19 20
1 13
13 14
14 15
15 16
16 17
17 18
18 19
1 2
2 3
3 4
3 5
4 6
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 7
5
1 13 14 15 16 17
19


*/