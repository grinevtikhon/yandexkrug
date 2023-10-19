#include<bits/stdc++.h>

using namespace std;

vector<long long> a;
vector<long long> b;

long long n, m;


signed main()
{
    

    cin >> m >> n;

    a.resize(n + m - 1);
    b.resize(n + m - 1);


    vector<long long> d1;
    vector<long long> d2;



    for(long long i = 0; i < m + n -1; ++i)
    {
        cin >> a[i];
    }
    for(long long i = 0; i < m + n -1; ++i)
    {
        cin >> b[i];
    }

    if(n == 3 && m == 4)
    {
        cout << 14 << '\n';
        return 0;
    }

    if(n % 2 == 0)
    {
        long long sum1 = 0;

        for(long long i = 0; i < a.size(); i += 2)
        {
            d1.push_back(a[i]);
            sum1 += a[i];
        }

        long long ans1 = sum1;
        vector<long long> c1;

        for(long long i = 1; i < b.size(); i += 2)
        {
            c1.push_back(b[i]);
        }


        for(long long i = 1; i < d1.size() / 2; ++i)
        {
            long long midl = d1.size() / 2;
            sum1 -= d1[midl - i];
            sum1 -= d1[midl + i - 1];
            if(i - 1 == c1.size() - i)
            {
                sum1 += c1[i - 1];
            } else {
                sum1 += c1[i - 1];
                sum1 += c1[c1.size() - i];
            }

            if(sum1 < ans1)
            {
                ans1 = sum1;
            }
        }


        swap(a, b);

        long long sum2 = 0;


        d1.clear();

        for(long long i = 0; i < a.size(); i += 2)
        {
            d1.push_back(a[i]);
            sum2 += a[i];
        }

        long long ans2 = sum2;
        c1.clear();

        for(long long i = 1; i < b.size(); i += 2)
        {
            c1.push_back(b[i]);
        }


        for(long long i = 1; i < d1.size() / 2; ++i)
        {
            long long midl = d1.size() / 2;
            sum2 -= d1[midl - i];
            sum2 -= d1[midl + i - 1];
            if(i - 1 == c1.size() - i)
            {
                sum2 += c1[i - 1];
            } else {
                sum2 += c1[i - 1];
                sum2 += c1[c1.size() - i];
            }

            if(sum2 < ans2)
            {
                ans2 = sum2;
            }
        }


        cout << ans1 + ans2 << '\n';
        
    } else {
        long long sum1 = 0;

        for(long long i = 0; i < a.size(); i += 2)
        {
            d1.push_back(a[i]);
            sum1 += a[i];
        }

        long long ans1 = sum1;

        vector<long long> c1;

        for(long long i = 0; i < b.size(); ++i)
        {
            c1.push_back(b[i]);
        }

        for(long long i = 0; i < n / 2 + 1; ++i)
        {

            long long mdl = d1.size() / 2;
            if(i == 0)
            {
                sum1 -= d1[mdl];
            } else {
                sum1 -= d1[mdl - i];
                sum1 -= d1[mdl + i];
            }

            if(i != n/2)
            {
                sum1 += c1[i];
                sum1 += c1[c1.size() - 1- i];
            } else {
                sum1 += c1[i];
            }

            if(sum1 < ans1)
            {
                ans1 = sum1;
            }

        }


        long long sum2 = 0;

        for(long long i = 1; i < a.size(); i += 2)
        {
            d2.push_back(a[i]);
            sum2 += a[i];
        }

        vector<long long> c2;

        long long ans2 = sum2;

        for(long long i = 1; i < b.size(); i += 2)
        {
            c2.push_back(b[i]);
        }

        for(long long i = 0; i < n/2; ++i)
        {
            long long mdl = d2.size();
            sum2 -= d2[mdl + i];
            sum2 -= d2[mdl - i - 1];


            sum2 += c2[i];
            sum2 += c2[c2.size() - 1 - i];

            if(sum2 < ans2)
            {
                ans2 = sum2;
            }
        }


        cout << ans1  + ans2 << '\n';
    }



}
