#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
int N, M, ans=1e9;
int arr[9][9];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct pos {
	int row; int col;
};
vector<pos> v;

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] >= 1 && arr[i][j] <= 5) {//cctv면
				v.push_back({ i,j });//cctv 좌표 저장
			}
		}
	}
}

void up(int r, int c, int num) {
	int nr = r; int nc = c;
	while (1) {
		nr += dy[0]; nc += dx[0];
		if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == 6) break;
		if (arr[nr][nc] > 0) continue;
		arr[nr][nc] += num;
	}
}

void down(int r, int c, int num) {
	int nr = r; int nc = c;
	while (1) {
		nr += dy[1]; nc += dx[1];
		if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == 6) break;
		if (arr[nr][nc] > 0) continue;
		arr[nr][nc] += num;
	}
}

void left(int r, int c, int num) {
	int nr = r; int nc = c;
	while (1) {
		nr += dy[2]; nc += dx[2];
		if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == 6) break;
		if (arr[nr][nc] > 0) continue;
		arr[nr][nc] += num;
	}
}

void right(int r, int c, int num) {
	int nr = r; int nc = c;
	while (1) {
		nr += dy[3]; nc += dx[3];
		if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == 6) break;
		if (arr[nr][nc] > 0) continue;
		arr[nr][nc] += num;
	}
}

void dfs(int cnt, int s) {
	if (cnt == v.size()) {//감시카메라 모두 작동하면
		int tmp = 0; bool flag = false;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (arr[i][j] == 0) tmp++;
				if (tmp >= ans) {
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		ans = min(ans, tmp);
		return;
	}

	for (int i = s; i < v.size(); i++) {
		int r = v[i].row; int c = v[i].col; 
		int num = arr[r][c];//cctv 번호

		if (num == 1) {//1번 cctv
			up(r, c, -1); dfs(cnt + 1, i + 1); up(r, c, 1);
			down(r, c, -1); dfs(cnt + 1, i + 1); down(r, c, 1);
			left(r, c, -1); dfs(cnt + 1, i + 1); left(r, c, 1);
			right(r, c, -1); dfs(cnt + 1, i + 1); right(r, c, 1);
		}
		if (num == 2) {
			up(r, c, -1); down(r, c, -1); dfs(cnt + 1, i + 1); up(r, c, 1); down(r, c, 1);
			left(r, c, -1); right(r, c, -1); dfs(cnt + 1, i + 1); left(r, c, 1); right(r, c, 1);
		}
		if (num == 3) {
			up(r, c, -1); right(r, c, -1); dfs(cnt + 1, i + 1); up(r, c, 1); right(r, c, 1);
			down(r, c, -1); left(r, c, -1); dfs(cnt + 1, i + 1); down(r, c, 1); left(r, c, 1);
			left(r, c, -1); up(r, c, -1); dfs(cnt + 1, i + 1); left(r, c, 1); up(r, c, 1);
			right(r, c, -1); down(r, c, -1); dfs(cnt + 1, i + 1); right(r, c, 1); down(r, c, 1);
		}
		if (num == 4) {
			up(r, c, -1); right(r, c, -1); left(r, c, -1); dfs(cnt + 1, i + 1); up(r, c, 1); right(r, c, 1); left(r, c, 1);
			down(r, c, -1); left(r, c, -1); right(r, c, -1); dfs(cnt + 1, i + 1); down(r, c, 1); left(r, c, 1); right(r, c, 1);
			left(r, c, -1); up(r, c, -1); down(r, c, -1); dfs(cnt + 1, i + 1); left(r, c, 1); up(r, c, 1); down(r, c, 1);
			right(r, c, -1); up(r, c, -1); down(r, c, -1); dfs(cnt + 1, i + 1); right(r, c, 1); up(r, c, 1); down(r, c, 1);
		}
		if (num == 5) {
			up(r,c,-1); down(r,c,-1); left(r,c,-1); right(r,c,-1);
			dfs(cnt + 1, i + 1);
			up(r,c,1); down(r,c,1); left(r,c,1); right(r,c,1);
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