#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, D, W, K, ans;
int arr[14][20], origin[14][20];

void init() {
	cin >> D >> W >> K;
	ans = K;
	for (int i = 1; i <= D; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> arr[i][j];
			origin[i][j] = arr[i][j];
		}
	}
}

bool possible() {//성능검사 통과하는지
	for (int i = 1; i <= W; i++) {//열
		int tmp = 1;
		for (int j = 2; j <= D; j++) {
			if (arr[j][i] == arr[j - 1][i]) {//같으면
				tmp++;
			}
			else {
				tmp = 1;
			}
			if (tmp == K) break;
			if (j == D - K + 2) {
				if (tmp + (D - j) < K) return false;
			}
		}
		if (tmp < K) return false;
	}
	return true;

}

void medicine(int r, int num) {
	for (int i = 1; i <= W; i++) {
		arr[r][i] = num;
	}
}

void recover(int r) {
	for (int i = 1; i <= W; i++) {
		arr[r][i] = origin[r][i];
	}
}

void dfs(int s, int cnt, int num) {
	if (cnt >= ans) return;
	if (possible()) {
		ans = cnt;
		return;
	}

	for (int i = s; i <= D; i++) {
		medicine(i, num);
		dfs(i + 1, cnt + 1, num);
		recover(i);
	}

}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		dfs(1, 0, 0);
		dfs(1, 0, 1);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}