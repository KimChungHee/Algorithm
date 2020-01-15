#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int R, C, M, ans;
struct pos {
	int s, d, z;
};
vector<pos> v[101][101], tmp[101][101];

void init() {
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
		v[a][b].push_back({ c,d,e });
	}
}

void fishing(int c) {
	for (int i = 1; i <= R; i++) {
		if (v[i][c].size() > 0) {
			ans += v[i][c][0].z;
			v[i][c].pop_back();
			break;
		}
	}
}

void fishmove() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (v[i][j].size() > 0) {
				int r = i; int c = j;
				int s = v[i][j][0].s; int d = v[i][j][0].d; int z = v[i][j][0].z;
				int speed = 0;
				if (d == 1 || d == 2) {
					speed = s % ((R - 1) * 2);
					while (speed--) {
						if (d == 1 && r == 1) {
							d = 2;
						}
						else if (d == 2 && r == R) {
							d = 1;
						}

						if (d == 1) r--;
						else r++;
					}
				}
				if (d == 3 || d == 4) {
					speed = s % ((C - 1) * 2);
					while (speed--) {
						if (d == 3 && c == C) {
							d = 4;
						}
						else if (d == 4 && c == 1) {
							d = 3;
						}

						if (d == 3) c++;
						else c--;
					}
				}
				v[i][j].pop_back();
				if (tmp[r][c].size() == 0) {
					tmp[r][c].push_back({ s,d,z });
				}
				else {
					if (tmp[r][c][0].z < z) {
						tmp[r][c].pop_back();
						tmp[r][c].push_back({ s,d,z });
					}
				}
			}
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (tmp[i][j].size() > 0) {
				v[i][j].push_back(tmp[i][j][0]);
				tmp[i][j].pop_back();
			}
		}
	}
}

void play() {
	for (int i = 1; i <= C; i++) {
		fishing(i);
		fishmove();
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	cout << ans;
}