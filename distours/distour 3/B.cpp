#include<bits/stdc++.h>

using namespace std;

struct grib
{
    set<int> st;
    int w;
    set<int> sos;
};


int main()
{
    int n, m;
    cin >> n >> m;

    vector<grib> all_grib(n * m);
    vector<int> sad(n * m);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int num = i * m + j;
            sad[num] = num;
            
        }
    }
}