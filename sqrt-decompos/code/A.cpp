#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> gr;

bool cmp(int a, int b)
{
    return gr[a].size() < gr[b].size();
}

int main()
{
    int n, m;

    cin >> n >> m;

    gr.resize(n);
    for(int i = 0; i < m; ++i)
    {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }

    vector<int> v(n);
    for(int i = 0; i < n; ++i) v[i] = i;

    sort(v.begin(), v.end(), [&](int a, int b){return gr[a].size() < gr[b].size();});

    vector<int> pos(n);

    for(int i = 0; i < v.size(); ++i)
    {
        pos[v[i]] = i;
    }


    vector<vector<int>> gr2 = gr;

    for(int i = 0; i < n; ++i)
    {
        int u = v[i];
        sort(gr[u].begin(), gr[u].end(), [&](int a, int b){return pos[a] > pos[b];});
        while(!gr[u].empty() && pos[gr[u].back()] < pos[u])
        {
            gr[u].pop_back();
        }
    }

    int ans = 0;

    vector<char> used(n);

    for(int i = 0; i < n; ++i)
    {
        int u = v[i];
        

        for(auto g : gr[u])
        {
            used[g] = 1;
            for(auto l : gr[g])
            {
                if(used[l])
                {
                    ++ans;
                }
            }
        }

        for(auto g : gr[u])
        {
            used[g] = 0;
        }
    }

    cout << ans << '\n';
}