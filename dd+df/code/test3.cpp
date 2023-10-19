#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector<bool> v(1e9 + 1, true);

    for(int i = 2; i < v.size(); ++i)
    {
        if(v[i])
        {
            cout << i << '\n';
        } else {
            continue;
        }

        int nxt = 2 * i;
        while(nxt < v.size())
        {
            v[nxt] = false;
            nxt += i;
        }
    }
}