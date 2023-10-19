#include<bits/stdc++.h>

using namespace std;

int main()
{
    int zap;
    cin >> zap;

    if(zap == 1)
    {
        int n;
        cin >> n;

        string str;
        cin >> str;

        for(int i = 1; i < str.size(); ++i)
        {
            if(str[i] == 'N')
            {
                cout << '1';
            } else {
                cout << '0';
            }
        }

        cout << '\n';
        return 0;
    } else {
        int n;
        cin >> n;

        string s;
        cin >> s;

        string str;

        str = '0' + s;

        vector<bool> used(n);

        for(int i = 0; i < str.size(); ++i)
        {
            if(str[i] == '1')
            {
                used[i] = true;
            }
        }

        for(int i = n-1; i >= 0; --i)
        {
            if(used[i] == false)
            {
                cout << i << ' ';
            }
        }

        for(int i = 0; i < n; ++i)
        {
            if(used[i])
            {
                cout << i << ' ';
            }
        }
        cout << '\n';

        return 0;
    }
}