#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, R, C, L;
int ans = 1;
//N,M-¸ÊÅ©±â,R,C-¸ÇÈ¦À§Ä¡,L-½Ã°£
int arr[51][51];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct pos {
	int row; int col; int num;
};
bool check[51][51];
queue<pos> q;

void init() {
	ans = 1; memset(check, false, sizeof(check));
	cin >> N >> M >> R >> C >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
	q.push({ R,C, arr[R][C] });
	check[R][C] = true;
}

void play() {
	int t = 1;
	while (!q.empty()) {
		int qsize = q.size();
		while (qsize--) {
			pos cur = q.front(); q.pop();
			int cr = cur.row; int cc = cur.col; int cnum = cur.num;
			for (int i = 0; i < 4; i++) {
				int nr = cr + dy[i]; int nc = cc + dx[i];
				if (nr<0 || nr>N - 1 || nc<0 || nc>M - 1 || check[nr][nc]) continue;

				if (i == 0) {//»ó
					if (arr[cr][cc] == 1 || arr[cr][cc] == 2 || arr[cr][cc] == 4 || arr[cr][cc] == 7) {
						if (arr[nr][nc] == 1 || arr[nr][nc] == 2 || arr[nr][nc] == 5 || arr[nr][nc] == 6) {
							check[nr][nc] = true;
							q.push({ nr,nc,arr[nr][nc] }); ans++;
						}
					}
				}
				else if (i == 1) {//ÇÏ
					if (arr[cr][cc] == 1 || arr[cr][cc] == 2 || arr[cr][cc] == 5 || arr[cr][cc] == 6) {
						if (arr[nr][nc] == 1 || arr[nr][nc] == 2 || arr[nr][nc] == 4 || arr[nr][nc] == 7) {
							check[nr][nc] = true;
							q.push({ nr,nc,arr[nr][nc] }); ans++;
						}
					}
				}
				else if (i == 2) {//ÁÂ
					if (arr[cr][cc] == 1 || arr[cr][cc] == 3 || arr[cr][cc] == 6 || arr[cr][cc] == 7) {
						if (arr[nr][nc] == 1 || arr[nr][nc] == 3 || arr[nr][nc] == 4 || arr[nr][nc] == 5) {
							check[nr][nc] = true;
							q.push({ nr,nc,arr[nr][nc] }); ans++;
						}
					}
				}
				else {//¿ì
					if (arr[cr][cc] == 1 || arr[cr][cc] == 3 || arr[cr][cc] == 4 || arr[cr][cc] == 5) {
						if (arr[nr][nc] == 1 || arr[nr][nc] == 3 || arr[nr][nc] == 6 || arr[nr][nc] == 7) {
							check[nr][nc] = true;
							q.push({ nr,nc,arr[nr][nc] }); ans++;
						}
					}
				}
			}

		}
		t++;
		if (t == L) {
			while (!q.empty()) q.pop();
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
		if (L == 1) {
			ans = 1;
		}
		else play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}