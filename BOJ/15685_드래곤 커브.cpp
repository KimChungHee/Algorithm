#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, x, y, d, g, ans;
//우,상,좌,하
int dy[4] = { 0,-1,0,1 };//y
int dx[4] = { 1,0,-1,0 };//x
bool check[101][101];
struct pos {
	int x, y, d, g;
};
queue<pos> q;//드래곤커브 초기 정보

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> x >> y >> d >> g;
		q.push({ x,y,d,g });
	}
}

void play() {
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int x = cur.x; int y = cur.y; int d = cur.d; int g = cur.g;
		check[y][x] = true;
		vector<int> v;
		v.push_back(d);//초기 방향
		for (int i = 0; i < g; i++) {//세대만큼
			vector<int> tmp = v;
			for (int j = tmp.size() - 1; j >= 0; j--) {
				v.push_back((tmp[j] + 1) % 4);
			}
		}
		for (int i = 0; i < v.size(); i++) {
			x += dx[v[i]]; y += dy[v[i]];
			if (x < 0 || x>100 || y < 0 || y>100 || check[y][x]) continue;
			check[y][x] = true;
		}
	}

	for (int i = 0; i <= 99; i++) {
		for (int j = 0; j <= 99; j++) {
			if (check[i][j] && check[i + 1][j] && check[i][j + 1] && check[i + 1][j + 1]) {
				ans++;
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