#include<bits/stdc++.h>

using namespace std;

int n, m;

int block = 300;

vector<int> a;
vector<int> d;
vector<int> dd;
vector<int> b;

vector<vector<int>> q;


void calc_div()
{
    d[0] = a[0];
    for(int i = 1; i < n; ++i) d[i] = a[i] - a[i-1];

    dd[0] = d[0];
    for(int i = 1; i < n; ++i) dd[i] = d[i] - d[i-1];
}

void calc_a()
{
    d[0] = dd[0];
    for(int i = 1; i < n; ++i) d[i] = d[i-1] + dd[i];

    a[0] = d[0];
    for(int i = 0; i < n; ++i) a[i] = a[i-1] + d[i];
}

void foo(int a, int delta)
{
    if(a < 0 || a >= n)
    {
        return;
    }

    dd[a] += delta;
}


void update(int l, int r, int x, int y)
{
    foo(l, x);
    foo(l + 1, -x);

    foo(r + 1, -x);
    foo(r + 2, x);


    foo(l + 1, y);
    foo(r + 1, -y);
    foo(r + 1, -y * (r - l));
    foo(r + 2, y * (r - l));
}

int main()
{
    cin >> n;

    a.resize(n);
    b.resize(n);
    d.resize(n);
    dd.resize(n);

    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];

    cin >> m;
    q.resize(m);

    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            int buf;
            cin >> buf;
            q[i].push_back(buf);
        }

        --q[i][0];
        --q[i][1];
    }

    calc_div();

    vector<int> ans(n, -1);

    for(int i = 0; i < m; ++i)
    {
        update(q[i][0], q[i][1], q[i][2], q[i][3]);

        if(i % block == block - 1 || i == m-1)
        {
            calc_a();
            for(int j = 0; j < n; ++j)
            {
                if(ans[j] == -1 && a[j] >= b[j])
                {
                    ans[j] = i + 1;

                    int k = i;
                    while(k >= 0)
                    {
                        if(q[k][0] <= j && j <= q[k][1])
                        {
                            a[j] -= (q[k][2] + (j - q[k][0]) * q[k][3]);
                        }
                        if(a[j] >= b[j])
                        {
                            --ans[j];
                        } else {
                            break;
                        }
                        --k;
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; ++i) cout << ans[i] << ' ';


    cout << '\n';

}