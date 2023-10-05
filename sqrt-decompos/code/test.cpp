#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> v{1,2 ,3, 3, 3, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11};


    cout << upper_bound(v.begin(), v.end(), 3, [&](int a, int b){
        return a < b;
    }) - v.begin() << '\n';


    //{1 ,1 , 0, 0,0,0...}

}