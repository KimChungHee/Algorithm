#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
struct pos {
	int row; int col; int vol;
};
int R, C, T, ans;
int arr[51][51];
queue<pos> dirty;
vector<pair<int, int> > v;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> R >> C >> T;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == -1) {
				v.push_back({ i, j });
			}
		}
	}
}

void find() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (arr[i][j] > 0) {
				dirty.push({ i,j,arr[i][j] });//먼지 값 입력
			}
		}
	}
}

void cleaner() {
	for (int i = 0; i < v.size(); i++) {
		int r = v[i].first; int c = v[i].second;
		if (i == 0) {
			int temp = arr[r][c + 1];
			arr[r][c + 1] = 0;
			for (int k = c + 2; k <= C; k++) {//윗칸에서 우측방향
				int temp2 = arr[r][k];
				arr[r][k] = temp;
				temp = temp2;
			}
			if (r >= 2) {//공기청정기가 첫줄이 아닐경우
				for (int k = r - 1; k >= 1; k--) {
					int temp2 = arr[k][C];
					arr[k][C] = temp;
					temp = temp2;
				}
				for (int k = C - 1; k >= 1; k--) {
					int temp2 = arr[1][k];
					arr[1][k] = temp;
					temp = temp2;
				}
				for (int k = 2; k <= r; k++) {
					int temp2 = arr[k][1];
					arr[k][1] = temp;
					temp = temp2;
				}
			}
		}
		if (i == 1) {
			int temp = arr[r][c + 1];
			arr[r][c + 1] = 0;
			for (int k = c + 2; k <= C; k++) {
				int temp2 = arr[r][k];
				arr[r][k] = temp;
				temp = temp2;
			}
			if (r < R) {
				for (int k = r + 1; k <= R; k++) {
					int temp2 = arr[k][C];
					arr[k][C] = temp;
					temp = temp2;
				}
				for (int k = C - 1; k >= 1; k--) {
					int temp2 = arr[R][k];
					arr[R][k] = temp;
					temp = temp2;
				}
				for (int k = R - 1; k >= r; k--) {
					int temp2 = arr[k][1];
					arr[k][1] = temp;
					temp = temp2;
				}
			}
		}
	}
	for (int i = 0; i < v.size(); i++) {
		arr[v[i].first][v[i].second] = -1;
	}
}

void cal() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (arr[i][j] > 0) {
				ans += arr[i][j];
			}
		}
	}
}

void bfs() {
	while (T--) {
		find(); //먼지들을 큐에 넣음
		int qsize = dirty.size();
		while (qsize--) {
			int cnt = 0;
			pos cur = dirty.front(); dirty.pop();
			int cr = cur.row; int cc = cur.col; int cv = cur.vol;
			for (int i = 0; i < 4; i++) {
				int nr = cr + dy[i];
				int nc = cc + dx[i];
				if (nr < 1 || nr > R || nc <1 || nc > C || arr[nr][nc] == -1) continue;
				cnt++;//확신 방향 수 증가
				arr[nr][nc] += cv / 5;//확산 양
			}
			int spread = cv / 5;
			arr[cr][cc] = arr[cr][cc] - spread * cnt;//남은 양
		}
		cleaner();//공기청정기 실행
	}
	cal();//먼지양게산
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	bfs();
	cout << ans << '\n';

	return 0;
}