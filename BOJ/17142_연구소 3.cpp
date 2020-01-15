#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, M, area;
int ans = 1e9;
int arr[51][51];
bool check[51][51];
struct pos {
	int row, col;
};
vector<pos> virus, tmp;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {
				virus.push_back({ i,j });//모든 바이러스 넣어둠
			}
			if (arr[i][j] == 0) area++;
		}
	}
}

void bfs() {
	queue<pos> q;
	memset(check, false, sizeof(check));
	for (int i = 0; i < tmp.size(); i++) {
		q.push(tmp[i]);
		check[tmp[i].row][tmp[i].col] = true;
	}

	int time = 0; int cnt = 0;

	while (!q.empty()) {
		int qsize = q.size();

		if (time >= ans) {
			break;
		}

		if (area == cnt) {
			ans = min(ans, time); break;
		}

		while (qsize--) {
			pos cur = q.front(); q.pop();
			int cr = cur.row; int cc = cur.col;
			for (int i = 0; i < 4; i++) {
				int nr = cr + dy[i]; int nc = cc + dx[i];
				if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc] || arr[nr][nc] == 1) continue;
				if (arr[nr][nc] == 0) {
					check[nr][nc] = true;
					q.push({ nr,nc });
					cnt++;//빈칸에 바이러스 퍼진 수
				}
				else if (arr[nr][nc] == 2) {
					check[nr][nc] = true;
					q.push({ nr,nc });
				}
			}
		}
		time++;//시간 추가
	}
}

void dfs(int s) {
	if (tmp.size() == M) {
		bfs();
		return;
	}

	for (int i = s; i < virus.size(); i++) {
		tmp.push_back(virus[i]);
		dfs(i + 1);
		tmp.pop_back();
	}
}




int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(0);
	if (ans == 1e9) cout << -1;
	else cout << ans;

	return 0;
}