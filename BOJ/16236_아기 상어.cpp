#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include <list>

using namespace std;
typedef pair<int, int> pii;
int N, ans;
int arr[21][21];
struct pos {
	int row, col, val, eat;
};
queue<pos> shark;
struct info {
	int row, col;
};
bool check[21][21];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
priority_queue< pii, vector<pii>, greater<pii> > possible;//먹이 후보

void init() {
	ans = 0;
	memset(check, false, sizeof(check));
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9) {
				shark.push({ i,j,2,0 });//초기 상어
				arr[i][j] = 0;
			}
		}
	}
}

void bfs() {
	int t = 0;
	while (!shark.empty()) {
		int qsize = shark.size();
		int v = shark.front().val; int e = shark.front().eat;

		while (qsize--) {
			pos cur = shark.front(); shark.pop();
			int cr = cur.row; int cc = cur.col; int cv = cur.val; int ce = cur.eat;
			check[cr][cc] = true;

			for (int i = 0; i < 4; i++) {
				int nr = cr + dy[i]; int nc = cc + dx[i];
				if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc] || arr[nr][nc] > cv) continue;
				if (arr[nr][nc] == cv || arr[nr][nc] == 0) {//크기 같으면
					shark.push({ nr,nc,cv,ce });
					check[nr][nc] = true;
				}
				else if (arr[nr][nc] < cv) {//크기 작으면
					possible.push({ nr,nc });//후보에 넣음
					check[nr][nc] = true;
				}
			}
		}

		t++;

		if (possible.size() > 0) {//먹이 후보가 있으면
			while (!shark.empty()) shark.pop();//기존 큐 제거
			pii cur = possible.top();
			int nr = cur.first; int nc = cur.second;
			arr[nr][nc] = 0;
			if (v - e == 1) {//하나 먹으면 몸이 커진다면
				shark.push({ nr,nc,v + 1,0 });
			}
			else shark.push({ nr,nc,v,e + 1 });
			memset(check, false, sizeof(check));
			while (!possible.empty()) possible.pop();
			ans = t;
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	bfs();
	cout << ans;
	return 0;
}