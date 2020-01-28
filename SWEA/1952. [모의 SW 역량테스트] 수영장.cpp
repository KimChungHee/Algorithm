#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, day, month, three, year, ans;
int plan[13];

void init() {
	cin >> day >> month >> three >> year;
	ans = year;
	for (int i = 1; i <= 12; i++) {
		cin >> plan[i];
	}
}

void dfs(int m, int val) {
	if (val >= ans) return;
	if (m > 12) {
		ans = min(ans, val);
		return;
	}
	dfs(m + 1, val + plan[m] * day);//하루
	dfs(m + 1, val + month);//한달
	dfs(m + 3, val + three);//세달
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		dfs(1, 0);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}