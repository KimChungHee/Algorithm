#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, ans = 1, profit;
int arr[21][21];
bool check[21][21];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct pos {
	int row; int col;
};

void init() {
	ans = 1;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void bfs(int r, int c) {
	memset(check, false, sizeof(check));

	int homecnt = 0; int K = 1;

	queue<pos> q; q.push({ r,c }); check[r][c] = true;
	if (arr[r][c] == 1) homecnt++;

	while (!q.empty()) {
		int qsize = q.size();

		while (qsize--) {
			pos cur = q.front(); q.pop();
			int cr = cur.row; int cc = cur.col;
			for (int i = 0; i < 4; i++) {
				int nr = cr + dy[i]; int nc = cc + dx[i];
				if (nr<0 || nr>N || nc<0 || nc>N || check[nr][nc]) continue;
				check[nr][nc] = true;
				q.push({ nr,nc });
				if (arr[nr][nc] == 1) homecnt++;
			}
		}
		K++;
		profit = homecnt * M - (K * K + (K - 1) * (K - 1));
		if (profit >= 0) ans = max(ans, homecnt);
		if (K == 2 * N - 1) {
			break;
		}
	}
}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				bfs(i, j);
			}
		}
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}