#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

long double pr(long long x1, long long y1, long long x2, long long y2){
    return -1*((((x2-x1))/(hypot(x2-x1,y2-y1))));
}

long double pr1(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    return((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1));
}

long double pr3(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    return ((x2-x1)*(x3-x1)+(y2-y1)*(y3-y1));
}

int line(int x1, int y1, int x2, int y2){
    return(-(x2 - x1)/(y1 - y2));
}

int main() {
    long long n, x, y;
    cin>>n>>x>>y;
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
    vector<pair<long double,long long>>sorry;
    for(int i=id;i<n+id;i++){
        if(i!=id){
            sorry.push_back({pr(cord[id].first, cord[id].second, cord[i%n].first, cord[i%n].second), i-id});
        }
    }
    sort(sorry.begin(), sorry.end());
    sorry.push_back({0, id});
    vector<long long>sharp;
    sharp.push_back(id);
    for(int i=0;i<n;i++){
        if(sharp.size()>=2){
            if(pr1(cord[sharp[sharp.size()-1]].first, cord[sharp[sharp.size()-1]].second, cord[sharp[sharp.size()-2]].first, cord[sharp[sharp.size()-2]].second, cord[(sorry[i].second+id)%n].first, cord[(sorry[i].second+id)%n].second)>=0 && i<n-1){
                sharp.pop_back();
            }
            if(i==n-1 && pr1(cord[sharp[sharp.size()-1]].first, cord[sharp[sharp.size()-1]].second, cord[sharp[sharp.size()-2]].first, cord[sharp[sharp.size()-2]].second, cord[sorry[i].second].first, cord[sorry[i].second].second)>=0){
                sharp.pop_back();
            }
        }
        if(i!=n-1){
            sharp.push_back((sorry[i].second+id)%n);
        }
        else{
            sharp.push_back(id);
        }
    }
    int ans=0;
    for(int i=0;i<sharp.size()-1;i++){
        if(pr3(cord[sharp[i]].first, cord[sharp[i]].second, cord[sharp[i+1]].first, cord[sharp[i+1]].second, x, y)>0 && pr3(cord[sharp[i+1]].first, cord[sharp[i+1]].second, cord[sharp[i]].first, cord[sharp[i]].second, x, y)>0){
            ans+=1;
        }
    }
    cout<<ans;
}