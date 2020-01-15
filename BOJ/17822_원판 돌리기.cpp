#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int N, M, T, ans;
int arr[52][52];
bool check[52][52];
bool flag;
struct pos {
	int x; int d; int k;
};
vector<pos> v;
struct info {
	int row; int col;
};
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 1; i <= T; i++) {
		int a, b, c; cin >> a >> b >> c;
		v.push_back({ a,b,c });
	}
}

void rotate(int x, int d, int k) {
	if (d == 0) {//시계
		for (int i = 1; i <= k; i++) {
			int tmp = arr[x][M];
			for (int j = M; j >= 2; j--) {
				arr[x][j] = arr[x][j - 1];
			}
			arr[x][1] = tmp;
		}
	}

	if (d == 1) {//반시계
		for (int i = 1; i <= k; i++) {
			int tmp = arr[x][1];
			for (int j = 1; j <= M - 1; j++) {
				arr[x][j] = arr[x][j + 1];
			}
			arr[x][M] = tmp;
		}
	}
}

void bfs(int r, int c) {
	queue<info> q; q.push({ r,c });
	while (!q.empty()) {
		info cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col;
		for (int i = 0; i < 4; i++) {
			int nr = cr + dy[i]; int nc = cc + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>M || check[nr][nc]) continue;
			if (arr[cr][cc] == arr[nr][nc]) {//인접하고 같으면
				check[cr][cc] = true;
				check[nr][nc] = true;
				q.push({ nr,nc });
				flag = true;
			}
		}
	}
}

void play() {
	for (int t = 0; t < v.size(); t++) {//회전 수 만큼
		int x = v[t].x; int d = v[t].d; int k = v[t].k;
		memset(check, false, sizeof(check));
		flag = false; int sum = 0; int cnt = 0;

		for (int i = 1; i <= N; i++) {//판을 돌면서
			if (i % x == 0) {//x의 배수이면
				rotate(i, d, k);//회전
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (arr[i][j] > 0) {
					sum += arr[i][j]; cnt++;
				}
				if (arr[i][j] == 0 || check[i][j]) continue;
				bfs(i, j);
			}
		}

		if (cnt == 0) break;

		for (int i = 1; i <= N; i++) {
			if (arr[i][1] == 0) continue;
			if (arr[i][1] == arr[i][M]) {
				check[i][1] = true;
				check[i][M] = true;
				flag = true;
			}
		}

		if (flag) {
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (check[i][j]) arr[i][j] = 0;
				}
			}
		}
		else {
			double ave = (double)sum / cnt;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= M; j++) {
					if (arr[i][j] == 0) continue;
					if (arr[i][j] > ave) arr[i][j]--;
					else if (arr[i][j] < ave) arr[i][j]++;
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			ans += arr[i][j];
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	cout << ans;
	return 0;
}