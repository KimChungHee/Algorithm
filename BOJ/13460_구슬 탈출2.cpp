#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
int N, M, ans, srr, src, sbr, sbc;
char arr[11][11];
struct pos {
	int redR, redC, blueR, blueC;
};
bool check[11][11][11][11];
bool flag;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
queue<pos> q;

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'R') {
				srr = i; src = j;
			}
			if (arr[i][j] == 'B') {
				sbr = i; sbc = j;
			}
		}
	}
	q.push({ srr,src,sbr,sbc });//초기 좌표
	check[srr][src][sbr][sbc] = true;
}

void bfs() {
	int cnt = 0;
	while (!q.empty()) {
		int qsize = q.size();
		while (qsize--) {
			pos cur = q.front(); q.pop();
			int rr = cur.redR; int rc = cur.redC; int br = cur.blueR; int bc = cur.blueC;
			int nrr = rr; int nrc = rc; int nbr = br; int nbc = bc;

			if (arr[rr][rc] == 'O') {//골인
				ans = cnt;
				flag = true;
				break;
			}

			for (int i = 0; i < 4; i++) {
				nrr = rr; nrc = rc; nbr = br; nbc = bc;

				while (1) {//이동
					nrr += dy[i]; nrc += dx[i];
					if (arr[nrr][nrc] == 'O') {
						break;
					}
					else if (arr[nrr][nrc] == '#') {
						nrr -= dy[i]; nrc -= dx[i];
						break;
					}
				}
				while (1) {//이동
					nbr += dy[i]; nbc += dx[i];
					if (arr[nbr][nbc] == 'O') {
						break;
					}
					else if (arr[nbr][nbc] == '#') {
						nbr -= dy[i]; nbc -= dx[i];
						break;
					}
				}

				if (nrr == nbr && nrc == nbc && arr[nrr][nrc] != 'O') {//좌표 겹치면, 단 구멍 제외
					int red = abs(nrr - rr) + abs(nrc - rc);
					int blue = abs(nbr - br) + abs(nbc - bc);
					//더 큰 애가 더 멀리온것, 더 큰 애를 한칸 빼줘야함
					if (red > blue) {
						nrr -= dy[i]; nrc -= dx[i];
					}
					else {
						nbr -= dy[i]; nbc -= dx[i];
					}
				}

				if (check[nrr][nrc][nbr][nbc] == true) {//방문했던 곳이면
					continue;
				}
				else if (!check[nrr][nrc][nbr][nbc] && arr[nbr][nbc] != 'O') {
					check[nrr][nrc][nbr][nbc] = true;
					q.push({ nrr,nrc,nbr,nbc });
				}

			}
		}

		cnt++;//횟수 증가
		if (flag) break;
		if (cnt > 10 || q.empty()) {//10번 넘거나, 불가능
			ans = -1; break;
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