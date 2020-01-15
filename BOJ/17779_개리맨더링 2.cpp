#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int N, ans = 1e9, sum, sr, sc;
int arr[22][22];
bool check[22][22];
int dy[4] = { 1,1,-1,-1 };
int dx[4] = { 1,-1,-1,1 };
vector<int> area;

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			sum += arr[i][j];
		}
	}
}

void find(int one, int two) {//인원 구하기
	area.clear();
	int tmp = 0; int tmpsum = 0;
	for (int i = 1; i < sr + one; i++) {
		for (int j = 1; j <= sc; j++) {
			if (!check[i][j]) tmp += arr[i][j];
			else break;
		}
	}
	area.push_back(tmp); tmpsum += tmp; tmp = 0;
	for (int i = 1; i <= sr + two; i++) {
		for (int j = N; j > sc; j--) {
			if (!check[i][j]) tmp += arr[i][j];
			else break;
		}
	}
	area.push_back(tmp); tmpsum += tmp; tmp = 0;
	for (int i = sr + one; i <= N; i++) {
		for (int j = 1; j < sc - one + two; j++) {
			if (!check[i][j]) tmp += arr[i][j];
			else break;
		}
	}
	area.push_back(tmp); tmpsum += tmp; tmp = 0;
	for (int i = N; i > sr + two; i--) {
		for (int j = N; j >= sc - one + two; j--) {
			if (!check[i][j]) tmp += arr[i][j];
			else break;
		}
	}
	area.push_back(tmp); tmpsum += tmp; tmp = 0;
	area.push_back(sum - tmpsum);//5영역
	sort(area.begin(), area.end());
	ans = min(ans, abs(area[0] - area[4]));
}

void dfs(int r, int c, int aa, int bb, int cc, int dd, int dir) {
	if (check[sr][sc]) {//목적지에 도착하면 종료
		find(bb, aa);
		return;
	}

	int nr = r; int nc = c;
	if (dir == 0) {//우하
		nr = r + dy[0]; nc = c + dx[0];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
			check[nr][nc] = true;
			dfs(nr, nc, aa + 1, bb, cc, dd, 0);
			check[nr][nc] = false;
		}

		if (aa >= 1) {
			nr = r + dy[1]; nc = c + dx[1];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
				check[nr][nc] = true;
				dfs(nr, nc, aa, bb + 1, cc, dd, 1);
				check[nr][nc] = false;
			}
		}
	}

	if (dir == 1) {//좌하
		nr = r + dy[1]; nc = c + dx[1];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
			check[nr][nc] = true;
			dfs(nr, nc, aa, bb + 1, cc, dd, 1);
			check[nr][nc] = false;
		}

		if (bb >= 1) {
			nr = r + dy[2]; nc = c + dx[2];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
				check[nr][nc] = true;
				dfs(nr, nc, aa, bb, cc + 1, dd, 2);
				check[nr][nc] = false;
			}
		}
	}

	if (dir == 2) {//좌상
		nr = r + dy[2]; nc = c + dx[2];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && cc < aa) {
			check[nr][nc] = true;
			dfs(nr, nc, aa, bb, cc + 1, dd, 2);
			check[nr][nc] = false;
		}

		if (cc == aa) {
			nr = r + dy[3]; nc = c + dx[3];
			check[nr][nc] = true;
			dfs(nr, nc, aa, bb, cc, dd + 1, 3);
			check[nr][nc] = false;
		}
	}

	if (dir == 3) {//우상
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N) {
			nr = r + dy[3]; nc = c + dx[3];
			check[nr][nc] = true;
			dfs(nr, nc, aa, bb, cc, dd + 1, 3);
			check[nr][nc] = false;
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	for (int i = 1; i <= N - 2; i++) {
		for (int j = 2; j <= N - 1; j++) {
			sr = i; sc = j;
			dfs(i, j, 0, 0, 0, 0, 0);//시작은 우하
		}
	}
	cout << ans;
	return 0;
}