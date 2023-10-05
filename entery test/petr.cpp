#include<bits/stdc++.h>

using namespace std;

#define INF 1e9


long long MOD = 998244353;

void stabilisate(long long &x)
{
    x = (((x % MOD) + MOD) % MOD);
}

int main()
{
    long long n;

    cin >> n;

    vector<long long> a(n);

    for(long long i = 0; i < n; ++i){
        cin >> a[i];
    }


    map<long long, long long> st;
    map<long long, long long> min_st;
    vector<long long> w(n);

    st.insert({0, 1});
    min_st.insert({-INF, 1});

    long long ans = 0;

    for(long long i = 0; i < n; ++i)
    {
        while((*st.begin()).first < a[i])
        {
            ans += (a[i] - (*st.begin()).first) * (*st.begin()).second;
            stabilisate(ans);
            st[a[i]] += (*st.begin()).second;
            stabilisate(st[a[i]]);
            st.erase(st.begin());
        }

        while((*min_st.begin()).first < -a[i])
        {
            if((*min_st.begin()).first == -INF)
            {
                ans += -a[i] * (*min_st.begin()).second;
            } else {
                ans += (-a[i] - (*min_st.begin()).first) * (*min_st.begin()).second;
            }
            stabilisate(ans);
            min_st[-a[i]] += (*min_st.begin()).second;
            stabilisate(min_st[-a[i]]);
            min_st.erase(min_st.begin());
        }

        st.insert({0, ans});
        min_st.insert({-INF, ans});

    }

    cout << ans << '\n';

}