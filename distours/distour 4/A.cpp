#include<bits/stdc++.h>

using namespace std;

int foo(int l, int r, char c, string& str)
{
    bool fl = false;

    for(int i = l; i <= r; ++i)
    {


        if(str[i] != c)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);

    string s, t;
    cin >> s >> t;

    vector<int> pref(s.size() + 1, t.size());
    vector<int> suff(s.size() + 1, -1);

    pref[0] = 0;
    suff[0] = t.size()-1;

    int num = 0;

    for(int i = 0; i < t.size() && num < s.size(); ++i)
    {
        if(t[i] == s[num])
        {
            ++num;
            pref[num] = i + 1;
        }
    }

    num = s.size() - 1;

    for(int i = t.size() - 1; i >= 0 && num >= 0; --i)
    {
        if(t[i] == s[num])
        {
            suff[s.size() - num] = i-1;
            --num;
        }
    }

    for(int i = 0; i < s.size(); ++i)
    {
        int l = pref[i];
        int r = suff[s.size() - i - 1];

        int gg = foo(l, r, s[i], t);
        if(gg != -1)
        {
            cout << i+1 << ' ' << t[gg] << '\n';
            return 0;
        }

    }
}

// alsdkjfhalsd
// alsdkgfhalsd