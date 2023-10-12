#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> ans;

vector<set<int>> v;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        --a[i];
    }

    v.resize(k);

    int cnt = 0;

    for(int i = 0; i < n; ++i)
    {
        int col = a[i];
        v[col].insert(i);
        if(v[col].size() == 1)
        {
            ++cnt;
        }

        if(i > m )
        {
            int cc = a[i - m- 1];

            if(v[cc].find(i-m-1) == v[cc].end())
            {
                
            } else
            {
                v[cc].erase(i-m-1);
                if(v[cc].size() == 0)
                {
                    --cnt;
                }
            }
        }


        if(cnt == k)
        {
            ans.emplace_back();

            for(int j = 0; j < k; ++j)
            {
                int buf = *v[j].begin();
                ans.back().push_back(buf);
                v[j].erase(buf);
                if(v[j].size() == 0)
                {
                    --cnt;
                }
            }
        }
    }

    cout << ans.size() << '\n';

    for(int i = 0; i < ans.size(); ++i)
    {
        for(int j = 0; j < ans[i].size(); ++j)
        {
            cout << ans[i][j] + 1 << ' ';
        }
        cout << '\n';
    }


}