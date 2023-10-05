#include<bits/stdc++.h>

using namespace std;

vector<int> table;

vector<int> a;

struct Mo
{
    int l, r;

    vector<int> cnt;

    int bl = 400;
    vector<int> sum;

    Mo()
    {
        l = 0;
        r = 0;

        cnt.resize(table.size() + 10);
        sum.resize(table.size() / bl + 10);
        cnt[0] = 1e6;
        sum[0] = 1;
    }

    void add(int p)
    {
        
    }
};

int main()
{
    int n, qsz;
    cin >> n >> qsz;

    a.resize(n);

    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        table.push_back(a[i]);
    }

    vector<vector<int>> change;
    vector<vector<int>> q;

    for(int i = 0; i < qsz; ++i)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            q.push_back({l, r, (int)change.size() - 1});
        } else {
            int p, x;
            cin >> p >> x;
            --p;
            change.push_back({p, x});
            table.push_back(x);
        }
    }

    sort(table.begin(), table.end());
    table.resize(unique(table.begin(), table.end()) - table.begin());

    for(int i = 0; i < n; ++i)
    {
        a[i] = lower_bound(table.begin(), table.end(), a[i]) - table.begin();
    }

    for(int i = 0; i < change.size(); ++i)
    {
        change[i][1] = lower_bound(table.begin(), table.end(), change[i][1]) - table.begin();
    }



        
}