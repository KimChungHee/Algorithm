#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, K, ans;
int arr[9][9];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct pos {
	int row; int col;
};
queue<pos> start;
bool check[9][9];

void init() {
	cin >> N >> K;
	ans = 0;
	int maxi = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			maxi = max(maxi, arr[i][j]);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (arr[i][j] == maxi) {
				start.push({ i,j });//가장 높은 봉우리들
			}
		}
	}
}

void dfs(int r, int c, int use, int cnt) {
	if (cnt > ans) ans = cnt;

	if (use == 0) {//공사를 안했다면
		for (int i = 0; i < 4; i++) {
			int nr = r + dy[i]; int nc = c + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) continue;
			if (arr[nr][nc] < arr[r][c]) {//다음 칸이 더 작다면
				check[nr][nc] = true;
				dfs(nr, nc, use, cnt + 1);
				check[nr][nc] = false;
			}
			else {
				if (arr[nr][nc] - (arr[r][c] - 1) <= K) {//공사가 가능하면
					int tmp = arr[nr][nc];
					arr[nr][nc] = arr[r][c] - 1;
					check[nr][nc] = true;
					dfs(nr, nc, use + 1, cnt + 1);
					check[nr][nc] = false;
					arr[nr][nc] = tmp;
				}
			}
		}
	}
	if (use == 1) {//공사를 했다면
		for (int i = 0; i < 4; i++) {
			int nr = r + dy[i]; int nc = c + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) continue;
			if (arr[nr][nc] < arr[r][c]) {//다음 칸이 더 작다면
				check[nr][nc] = true;
				dfs(nr, nc, use, cnt + 1);
				check[nr][nc] = false;
			}
		}
	}
}

void play() {
	while (!start.empty()) {
		pos cur = start.front(); start.pop();
		int cr = cur.row; int cc = cur.col;
		check[cr][cc] = true;
		dfs(cr, cc, 0, 1);
		memset(check, false, sizeof(check));
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}