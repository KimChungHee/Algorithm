#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, L, R, ans, num;
struct pos {
	int row; int col;
};
bool check[101][101];
queue<pos> q;
vector<pos> area[2501];
int arr[101][101];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void bfs() {
	queue<pos> tmp = q;//임시 큐
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col;
		for (int i = 0; i < 4; i++) {
			int nr = cr + dy[i]; int nc = cc + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) continue;
			if (abs(arr[nr][nc] - arr[cr][cc]) < L || abs(arr[nr][nc] - arr[cr][cc]) > R) continue;
			check[nr][nc] = true;
			q.push({ nr,nc }); tmp.push({ nr,nc });
		}
	}
	if (tmp.size() == 1) {//연합을 못 만들었으면
		return;
	}
	else {//연합이면
		num++;//연합 번호 증가
		while (!tmp.empty()) {
			pos cur = tmp.front(); tmp.pop();
			int cr = cur.row; int cc = cur.col;
			area[num].push_back({ cr,cc });//영역에 추가
		}
	}
}

void play() {
	while (1) {
		num = 0;//영역 번호 초기화
		memset(check, false, sizeof(check));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (!check[i][j]) {//방문안했거나 area가 아닌 곳에서 bfs
					check[i][j] = true;;
					q.push({ i,j });
					bfs();
				}
			}
		}

		if (num == 0) break;//영역이 없었다면 종료

		for (int i = 1; i <= num; i++) {//영역만큼
			int kan_num = area[i].size();//연합을 이루는 칸의 수
			int people = 0;//연합의 인구수

			for (int j = 0; j < kan_num; j++) {
				people += arr[area[i][j].row][area[i][j].col];
			}
			people /= kan_num;// 연합 인구 / 칸의 수
			for (int j = 0; j < kan_num; j++) {
				arr[area[i][j].row][area[i][j].col] = people;//인구 갱신
			}
			area[i].clear();//이동 다 시킨 후, 영역 클리어
		}

		ans++;//인구 이동이 일어났다면 답 += 1 
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