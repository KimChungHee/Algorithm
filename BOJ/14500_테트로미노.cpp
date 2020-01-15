#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
int N, M, ans;
int arr[501][501];
bool check[501][501];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
		}
	}
}

void dfs(int r, int c, int cnt, int sum) {
	if (cnt == 4) {
		if (sum > ans) ans = sum;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nr = r + dy[i]; int nc = c + dx[i];
		if (nr<1 || nr>N || nc<1 || nc>M || check[nr][nc]) continue;
		check[nr][nc] = true;
		dfs(nr, nc, cnt + 1, sum + arr[nr][nc]);
		check[nr][nc] = false;
	}
}

void play() {
	//で,ぬ,っ,た
	for (int i = 2; i <= N; i++) {//で
		for (int j = 2; j <= M - 1; j++) {
			int tmp = arr[i][j] + arr[i - 1][j] + arr[i][j - 1] + arr[i][j + 1];
			if (tmp > ans) ans = tmp;
		}
	}

	for (int i = 1; i <= N - 1; i++) {//ぬ
		for (int j = 2; j <= M - 1; j++) {
			int tmp = arr[i][j] + arr[i][j - 1] + arr[i][j + 1] + arr[i + 1][j];
			if (tmp > ans) ans = tmp;
		}
	}

	for (int i = 2; i <= N - 1; i++) {//っ
		for (int j = 2; j <= M; j++) {
			int tmp = arr[i][j] + arr[i - 1][j] + arr[i + 1][j] + arr[i][j - 1];
			if (tmp > ans) ans = tmp;
		}
	}

	for (int i = 2; i <= N - 1; i++) {//た
		for (int j = 1; j <= M - 1; j++) {
			int tmp = arr[i][j] + arr[i - 1][j] + arr[i + 1][j] + arr[i][j + 1];
			if (tmp > ans) ans = tmp;
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			check[i][j] = true;
			dfs(i, j, 1, arr[i][j]);
			check[i][j] = false;
		}
	}
	play();
	cout << ans;

	return 0;
}