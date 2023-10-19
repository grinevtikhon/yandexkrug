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

        bool fl = false;

        for(int i = 0; i < str.size()-1; ++i)
        {

            if(fl)
            {
                if(str[i] == 'N')
                {
                    cout << '1';
                } else {
                    cout << '0';
                }
            } else {
                if(str[i] == 'X')
                {
                    cout << '1';
                    fl = true;
                } else {
                    cout << '0';
                }
            }
        }

        cout << '\n';
        return 0;
    } else {
        int n;
        cin >> n;

        string s;
        cin >> s;
        s+='1';

        vector<bool> used(n);

        int fr = 0;

        for(int i = 0; i < s.size(); ++i)
        {
            if(s[i] == '1')
            {
                fr = i;
                break;
            }
        }

        for(int j = fr + 1; j < s.size(); ++j)
        {
            if(s[j] == '1')
            {
                for(int l = j-1; l > fr; --l)
                {
                    if(used[l])
                    {
                        break;
                    }

                    cout << l << ' ';
                    used[l] = true;
                }
                cout << j << ' ';
                used[j] = true;
            }
        }

        for(int i = 0; i < s.size(); ++i)
        {
            if(!used[i])
            {
                cout << i << ' ';
            }
        }


        return 0;
    }
}