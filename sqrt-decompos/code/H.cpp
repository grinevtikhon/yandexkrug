#include<bits/stdc++.h>

using namespace std;

int con = 300;

vector<vector<int>> gr;
vector<int> ver;
vector<int> sum;

vector<map<int, int>> hv;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n >> m;

    gr.resize(n);
    ver.resize(n);
    sum.resize(n);
    hv.resize(n);

    for(int i = 0; i < n; ++i) cin >> ver[i];

    for(int i = 0; i < m; ++i)
    {
        int v, u;
        cin >> v >> u;
        --v;
        --u;
        gr[v].push_back(u);
        gr[u].push_back(v);
    }

    int ans = 0;

    for(int i = 0; i < n; ++i)
    {

        sort(gr[i].begin(), gr[i].end(), [&](int a, int b){return gr[a].size() > gr[b].size();});

        for(auto u : gr[i])
        {
            if(ver[i] == ver[u])
            {
                ++ans;
            }
            
            if(gr[i].size() >= con && gr[u].size() < con)
            {
                hv[i][ver[u]] += 1;
            }
        }
    }

    ans /= 2;


    int q;
    cin >> q;

    for(int i = 0; i < q; ++i)
    {
        int c, n_v;
        cin >> c >> n_v;
        --c;

        if(gr[c].size() < con)
        {   

            for(auto u : gr[c])
            {

                if(ver[c] == ver[u])
                {
                    --ans;
                }

                if(n_v == ver[u])
                {
                    ++ans;
                }

                if(gr[u].size() >= con)
                {
                    hv[u][ver[c]]--;
                    hv[u][n_v]++;
                }
            }
            ver[c] = n_v;
        } else {

            ans -= hv[c][ver[c]];
            ans += hv[c][n_v];

            for(auto u : gr[c])
            {
                if(gr[u].size() < con)
                {
                    break;
                }

                if(ver[c] == ver[u])
                {
                    --ans;
                }

                if(n_v == ver[u])
                {
                    ++ans;
                }
            }

            ver[c] = n_v;
        }

        cout << m - ans << '\n';

    }
}