#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, ans;
int arr[4001][4001];
struct pos {
	int x, y, dir, k;
};
vector<pos> v;
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	ans = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		v.push_back({ a * 2 + 2000,b * 2 + 2000,c,d });
	}
}

void play() {
	int a = 0;
	while (1) {
		for (int i = 0; i < v.size(); i++) {
			pos cur = v[i];
			int nx = cur.x; int ny = cur.y; int dir = cur.dir; int k = cur.k;
			v[i].x += dx[dir]; v[i].y += dy[dir];
			if (v[i].x < 0 || v[i].x>4000 || v[i].y < 0 || v[i].y>4000) {
				v.erase(v.begin() + i); i--;
			}
			else {
				arr[v[i].y][v[i].x] += k;//맵에 에너지 추가
			}
		}

		for (int i = 0; i < v.size(); i++) {
			if (arr[v[i].y][v[i].x] == 0) {
				v.erase(v.begin() + i); i--;
			}
			else if (arr[v[i].y][v[i].x] == v[i].k) {
				arr[v[i].y][v[i].x] = 0;
			}
			else {
				ans += arr[v[i].y][v[i].x];
				arr[v[i].y][v[i].x] = 0;
				v.erase(v.begin() + i); i--;
			}
		}
		if (v.empty() || v.size() == 1) {
			v.clear(); break;
		}
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