#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, M, H;//세로, 가로, 가로선 놓을 수 있는 위치 수
int ans = 1e9;
int a, b;
bool check[12][32];//a번 점선에서 b,b+1이 연결
bool flag;

void init() {
	cin >> N >> M >> H;
	for (int i = 1; i <= M; i++) {
		int a, b; cin >> a >> b;
		check[b][a] = true;//b,b+1 세로선이 a번 점선에서 연결됨
	}
}

bool play() {
	for (int i = 1; i <= N; i++) {//세로선 하나씩 출발
		int tmp = i;
		for (int j = 1; j <= H; j++) {//가로선 놓을 수 있는 위치 탐색
			if (check[tmp - 1][j]) {//좌측과 연결
				tmp--;
			}
			else if (check[tmp][j]) {//우측과 연결
				tmp++;
			}
			else {
				continue;
			}
		}
		if (i != tmp) {
			return false;
		}
	}

	return true;
}

void dfs(int r, int c, int cnt) {
	if (cnt > ans) return;
	//검사 후
	if (play()) {
		ans = min(ans, cnt);
	}
	if (cnt == 3) return;



	if (c > N - 1) {
		r += 1; c = 1;
	}
	for (int i = r; i <= H; i++) {
		if (i > r) c = 1;
		for (int j = c; j <= N - 1; j++) {
			if (!check[j - 1][i] && !check[j][i] && !check[j + 1][i]) {
				check[j][i] = true;
				dfs(i, j, cnt + 1);
				check[j][i] = false;
			}
		}
	}
}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(1, 1, 0);

	if (ans == 1e9) {
		cout << -1;
	}
	else cout << ans;

	return 0;
}