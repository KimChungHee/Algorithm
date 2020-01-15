#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
int N, M, sr, sc, d, ans;
int arr[51][51];
bool check[51][51];
int dy[4] = {-1,0,1,0 };//북동남서
int dx[4] = {0,1,0,-1 };
int change[4] = { 2,3,0,1 };//후진 바향

struct pos {
	int row; int col; int dir;
};
queue<pos> q;

void init() {
	cin >> N >> M;
	cin >> sr >> sc >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	q.push({ sr, sc, d });//초기 좌표
	check[sr][sc] = true; ans++;//초기 좌표 청소

	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col; int cd = cur.dir;
		int nd = cd;
		bool flag = false;

		for (int i = 1; i <= 4; i++) {//왼쪽 방향으로 탐색
			if (nd - 1 >= 0) nd -= 1;
			else nd = 3;

			int nr = cr + dy[nd]; int nc = cc + dx[nd];
			if (nr<0 || nr>=N || nc<0 || nc>=M || check[nr][nc] || arr[nr][nc]==1) continue;
			else {//범위 벗어나거나 벽 또는 청소한 구역이 아니라면
				flag = true;
				q.push({ nr,nc,nd });//다음 청소할 좌표,방향
				check[nr][nc] = true; ans++;
			}

			if (flag) break;
		}

		if (!flag) {//4 방향 모두 청소 또는 벽이면
			//후진 할 좌표
			int nr = cr + dy[change[cd]]; int nc = cc + dx[change[cd]];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || arr[nr][nc] == 1) {
				//후진 좌표가 벽이라면 작동 중지
			}
			else {//후진 좌표가 벽이 아니면
				q.push({ nr,nc,cd });//방향 유지하고 후진
			}
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