#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int N, ans;
struct pos {
	int t, p;
};
vector<pos> v;

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int a, b; cin >> a >> b;
		v.push_back({ a,b });
	}
}

void dfs(int day, int sum) {
	if (day > N - 1) {
		ans = max(ans, sum);
		return;
	}

	for (int i = day; i < v.size(); i++) {
		if (i + v[i].t <= N) {
			dfs(i + v[i].t, sum + v[i].p);
		}
		else {
			dfs(i + v[i].t, sum);
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(0, 0);
	cout << ans;
	return 0;
}