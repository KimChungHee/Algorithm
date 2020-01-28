#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, maxi = -1e9, mini = 1e9, ans;
int op[4];
int num[13];

void init() {
	cin >> N;
	ans = 0; maxi = -1e9; mini = 1e9;
	for (int i = 0; i < 4; i++) {
		cin >> op[i];// + , - , *, /
	}
	for (int i = 1; i <= N; i++) {
		cin >> num[i];
	}
}

void dfs(int cnt, int val) {
	if (cnt == N) {//1부터 시작, 연산자 수
		maxi = max(maxi, val);
		mini = min(mini, val);
		return;
	}

	if (op[0] > 0) {//더하기
		op[0]--;
		dfs(cnt + 1, val + num[cnt + 1]);
		op[0]++;
	}
	if (op[1] > 0) {//빼기
		op[1]--;
		dfs(cnt + 1, val - num[cnt + 1]);
		op[1]++;
	}
	if (op[2] > 0) {//곱하기
		op[2]--;
		dfs(cnt + 1, val * num[cnt + 1]);
		op[2]++;
	}
	if (op[3] > 0) {//나누기
		op[3]--;
		dfs(cnt + 1, val / num[cnt + 1]);
		op[3]++;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		dfs(1, num[1]);
		ans = abs(maxi - mini);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}