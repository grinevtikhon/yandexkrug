#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> v{0, 1, 2, 2, 2, 6, 8};

    auto cmp = [&](int a, int b){ return a < b;};
            
    for(int i = 0; i < v.size(); ++i)
    {
        
        cout << cmp(2, v[i]) << ' ';
    }

    cout << '\n';

    cout << upper_bound(v.begin(), v.end(), 2) - v.begin() << '\n';

    cout << lower_bound(v.begin(), v.end(), 2, cmp) - v.begin() << '\n';

    cout << upper_bound(v.begin(), v.end(), 2, cmp) - v.begin() << '\n';
}