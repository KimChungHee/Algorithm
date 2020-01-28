#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, K, ans;
int dy[5] = { 0,-1,1,0,0 };// 상 , 하 , 좌, 우
int dx[5] = { 0,0,0,-1,1 };
struct pos {
	int cnt; int dir;
	//미생물 수, 이동방향
};
struct info {
	int r, c, cnt, dir;
};
vector<pos> v[101][101];
vector<info> cluster;
bool cmp(pos a, pos b) {
	return a.cnt > b.cnt;
}


void init() {
	ans = 0; cluster.clear();

	cin >> N >> M >> K;
	for (int i = 1; i <= K; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		cluster.push_back({ a,b,c,d });
	}
}

void play() {
	while (M--) {
		for (int i = 0; i < cluster.size(); i++) {//군집을 돌며
			info cur = cluster[i];
			int nr = cur.r; int nc = cur.c; int ncnt = cur.cnt; int ndir = cur.dir;

			nr += dy[ndir]; nc += dx[ndir];//다음 좌표

			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) {//외곽이면
				ncnt /= 2;//미생물 수를 절반으로 줄임
				if (ncnt == 0) continue;//미생물이 0이되면 군집 사라짐

				if (ndir == 1) ndir = 2;//방향 변경
				else if (ndir == 2) ndir = 1;
				else if (ndir == 3) ndir = 4;
				else ndir = 3;

				v[nr][nc].push_back({ ncnt,ndir });//벡터 맵에 저장
			}
			else {//외곽이 아니면
				v[nr][nc].push_back({ ncnt,ndir });//벡터 맵에 저장
			}
		}

		cluster.clear();//군집 제거

		for (int i = 0; i < N; i++) {//벡터 맵을 돌면서, 확인
			for (int j = 0; j < N; j++) {
				if (v[i][j].size() == 1) {//군집이 한 개 있으면
					cluster.push_back({ i,j,v[i][j][0].cnt,v[i][j][0].dir });
					//군집에 다시 추가
					v[i][j].clear();//맵 클리어
				}
				else if (v[i][j].size() > 1) {//군집이 여러개면
					sort(v[i][j].begin(), v[i][j].end(), cmp);//미생물 순 정렬
					int ccnt = v[i][j][0].cnt; int cdir = v[i][j][0].dir;//가장 큰 군집의 정보
					for (int k = 1; k < v[i][j].size(); k++) {
						ccnt += v[i][j][k].cnt;//나머지 미생물들을 다 더함
					}
					v[i][j].clear();
					cluster.push_back({ i,j,ccnt,cdir });//군집에 합친 것을 추가
				}
			}
		}
	}

	for (int i = 0; i < cluster.size(); i++) {
		ans += cluster[i].cnt;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}