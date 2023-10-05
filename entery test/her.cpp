#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map>

using namespace std;

struct Vec {
    long double x, y;

    Vec(long double x, long double y) : x(x), y(y) {};

    Vec operator+ (Vec v) {
        return Vec(x + v.x, y + v.y);
    }

    Vec operator- (Vec v) {
        return Vec(x - v.x, y - v.y);
    }

    int operator* (Vec v) {
        return x * v.y - y * v.x;
    }

    int operator% (Vec v) {
        return x * v.x + y * v.y;
    }
};

long double lenn(Vec a){
    return hypot(a.x, a.y);
}

long double pr(Vec a){
    return -1*(a.x)/(hypot(a.x, a.y));
}

int main() {

    // vector<long double> v(100);

    // cout.setf(ios::fixed);
    // cout.precision(20);

    // for(int i = 0; i < 100; ++i)
    // {
    //     v[i] = pr(Vec(-i, -i));
    // } 

    // for(int j = 0; j < 100; ++j)
    // {
    //     cout << j << " : " << v[j] << " | ";

    //     if(v[j] != v[1])
    //     {
    //         cout << j << " : ALAAAAARM!!!! " << v[j] << " != " << v[1];
    //     }

    //     cout << '\n';
    // }

    // return 0;

    long long n, x, y;
    cin>>n>>x>>y;
    map<pair<long double,long double>,int>m;
    vector<pair<long,long>>cord(n);
    int minn=10000;
    for(int i=0;i<n;i++){
        cin>>cord[i].first>>cord[i].second;
        if(cord[i].second<minn){
            minn=cord[i].second;
        }
    }
    int minn2=2000;
    int id=0;
    for(int i=0;i<n;i++){
        if(cord[i].second==minn && minn2>cord[i].first){
            minn2=cord[i].first;
            id=i;
        }
    }
    vector<pair<long double, long double>>sorry;
    for(int i=0;i<n;i++){
        if(i!=id){
            Vec a(cord[i].first, cord[i].second);
            Vec b(cord[id].first, cord[id].second);
            Vec c=a-b;
            sorry.push_back({pr(c), lenn(c)});
            m[{pr(c), lenn(c)}]=i;
        }
    }
    sort(sorry.begin(), sorry.end());
    sorry.push_back({0, 0});
    m[{0, 0}]=id;
    vector<int>sharp;
    sharp.push_back(id);
    for(int i=0;i<n;i++){
        if(sharp.size()>=2){
            Vec a(cord[sharp[sharp.size()-1]].first, cord[sharp[sharp.size()-1]].second);
            Vec b(cord[sharp[sharp.size()-2]].first, cord[sharp[sharp.size()-2]].second);
            Vec c(cord[m[sorry[i]]].first, cord[m[sorry[i]]].second);
            b=b-a;
            c=c-a;
            if(b*c>=0){
                sharp.pop_back();
            }
        }
        sharp.push_back(m[sorry[i]]);
    }
    int ans=0;
    for(int i=0;i<sharp.size()-1;i++){
        Vec a(cord[sharp[i]].first, cord[sharp[i]].second);
        Vec b(cord[sharp[i+1]].first, cord[sharp[i+1]].second);
        Vec c(x, y);
        Vec b1=b-a;
        Vec c1=c-a;
        Vec a1=a-b;
        Vec c2=c-b;
        if(b1%c1>0 && a1%c2>0){
            ans++;
        }
    }
    cout<<ans;
}


/*


5 0 14
0 0 
9 9
0 18
-9 9
-6 6
*/