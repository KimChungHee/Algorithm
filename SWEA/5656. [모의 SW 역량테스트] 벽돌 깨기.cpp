#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, W, H, ans;
//w-col, h-row
int arr[16][13], origin[16][13];

struct pos {
	int row, col, p;
};
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	ans = 0;
	cin >> N >> W >> H;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			cin >> arr[i][j];
			origin[i][j] = arr[i][j];
			if (arr[i][j] > 0) {
				ans++;//초기 벽돌 갯수
			}
		}
	}
}

void bfs(int r, int c, int p) {
	queue<pos> q; q.push({ r,c,p }); arr[r][c] = 0;//미리 0으로 변경
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col; int cp = cur.p;

		for (int i = 0; i < 4; i++) {
			int nr = cr; int nc = cc;
			for (int j = 0; j < cp - 1; j++) {//크기-1 만큼 이동
				nr += dy[i]; nc += dx[i];
				if (nr<1 || nr>H || nc<1 || nc>W) break;
				if (arr[nr][nc] == 0) continue;
				else if (arr[nr][nc] == 1) {
					arr[nr][nc] = 0;
				}
				else if (arr[nr][nc] > 1) {
					q.push({ nr,nc,arr[nr][nc] });//벽돌 추가
					arr[nr][nc] = 0;
				}
			}
		}
	}

}

void down() {
	for (int i = 1; i <= W; i++) {
		int tmp = H;
		for (int j = H; j >= 1; j--) {
			if (arr[j][i] > 0) {//벽돌이 있으면
				int temp2 = arr[j][i];
				arr[j][i] = 0;
				arr[tmp][i] = temp2;
				tmp--;
			}
		}
	}
}

void dfs(int cnt, int col) {
	int tmp[16][13] = { 0, };
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= W; j++) {
			tmp[i][j] = arr[i][j];
		}
	}

	if (cnt > 0) {//구슬을 내림
		for (int i = 1; i <= H; i++) {
			if (arr[i][col] > 0) {//벽돌이 있으면
				bfs(i, col, arr[i][col]);
				break;
			}
		}

		//벽돌 내리는 작업
		down();

		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				tmp[i][j] = arr[i][j];
			}
		}

	}
	if (cnt == N) {//구슬을 다내리면
		int rock = 0;
		for (int i = 1; i <= H; i++) {
			for (int j = 1; j <= W; j++) {
				if (arr[i][j] > 0) {
					rock++;
				}
			}
		}
		ans = min(ans, rock);
		return;
	}

	for (int i = 1; i <= W; i++) {

		dfs(cnt + 1, i);

		for (int j = 1; j <= H; j++) {
			for (int k = 1; k <= W; k++) {
				arr[j][k] = tmp[j][k];
			}
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		dfs(0, 0);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}