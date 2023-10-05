
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	string s;
	cin >> s;
	int n, w;
	cin >> n;
	string t;
	vector<vector<string>>h(s.size() + 1);
	for (int i = 0; i < n; i++) {
		cin >> t;
		if (t.size() <= s.size()) {
			h[t.size()].push_back(t);
		}
	}
	long long p = 239;
	long long mod1 = 1791791791;
	long long q = 179;
	long long mod2 = 1000000007;
	vector<long long>r(s.size() + 1);
	vector<long long>d(s.size() + 1);
	r[0] = 1;
	d[0] = 1;
	for (int i = 1; i < s.size() + 1; i++) {
		r[i] = (r[i - 1] * p) % mod1;
	}
	for (int i = 1; i < s.size() + 1; i++) {
		d[i] = (d[i - 1] * q) % mod2;
	}
	vector<set<pair<long, long>>>h1(s.size()+1);
	vector<long long>hash1(s.size()+1);
	vector<long long>hash2(s.size()+1);
	for (int i = 1; i < s.size() + 1; i++) {
		hash1[i] = (hash1[i - 1] * p + s[i - 1] - 'a' + 1) % mod1;
		hash2[i] = (hash2[i - 1] * q + s[i - 1] - 'a' + 1) % mod2;
	}
	for (int i = 0; i < s.size() + 1; i++) {
		for (int j = 0; j < h[i].size(); j++) {
			long long summ1 = 0;
			long long summ2 = 0;
			for (int v = 0; v < h[i][j].size(); v++) {
				summ1 = (summ1 * p + h[i][j][v] - 'a' + 1)%mod1;
				summ2 = (summ2 * q + h[i][j][v] - 'a' + 1) % mod2;
			}
			if (summ1 > 0 || summ2 > 0) {
				h1[i].insert({ summ1, summ2 });
			}
		}
	}
	cin >> w;
	vector<long long>ans(w);
	vector<pair<int, int>>z(w);
	for (int i = 0; i < w; i++) {
		cin >> z[i].first >> z[i].second;
	}
	for (int i = 1; i < s.size(); i++) {
		if (h[i].size() > 0) {
			vector<long long>pr(s.size());
			vector<long long>st(s.size() + 1);
			for (int j = 0; j <= s.size()-i; j++) {
				if (h1[i].find({ (hash1[j + i] - hash1[j] * r[i] + mod1 * mod1) % mod1, (hash2[j + i] - hash2[j] * d[i] + mod2 * mod2) % mod2 }) != h1[i].end()) {
					pr[j + i - 1]++;
				}
			}
			for (int j = 1; j < s.size() + 1; j++) {
				st[j] = st[j - 1] + pr[j - 1];
			}
			for (int j = 0; j < w; j++) {
				if (z[j].second - z[j].first + 1 >= i) {
					ans[j] += (st[z[j].second] - st[z[j].first - 1 + i - 1]);
				}
			}
		}
	}
	for (int i = 0; i < w; i++) {
		cout << ans[i] << ' ';
	}
}
