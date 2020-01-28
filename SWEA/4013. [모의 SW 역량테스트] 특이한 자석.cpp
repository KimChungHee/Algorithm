#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, K, ans;
int arr[5][9];
struct pos {
	int num; int dir;
};
queue<pos> q;
int info[5];

void init() {
	ans = 0;
	cin >> K;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 8; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 1; i <= K; i++) {
		int a, b; cin >> a >> b;
		q.push({ a,b });
	}
}

void rotate() {//1 시계, -1 반시계
	for (int i = 1; i <= 4; i++) {
		if (info[i] == 1) {//시계
			int tmp = arr[i][8];
			for (int j = 8; j >= 2; j--) {
				arr[i][j] = arr[i][j - 1];
			}
			arr[i][1] = tmp;
		}
		if (info[i] == -1) {//반시계
			int tmp = arr[i][1];
			for (int j = 1; j <= 7; j++) {
				arr[i][j] = arr[i][j + 1];
			}
			arr[i][8] = tmp;
		}
	}
	memset(info, 0, sizeof(info));
}

void play() {
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int num = cur.num; int d = cur.dir;

		if (num == 1) {//1번 톱니
			info[1] = d;
			if (arr[1][3] != arr[2][7]) {
				info[2] = -d;
				if (arr[2][3] != arr[3][7]) {
					info[3] = d;
					if (arr[3][3] != arr[4][7])
						info[4] = -d;
				}
			}
		}
		else if (num == 2) {
			info[2] = d;
			if (arr[2][7] != arr[1][3]) {
				info[1] = -d;
			}
			if (arr[2][3] != arr[3][7]) {
				info[3] = -d;
				if (arr[3][3] != arr[4][7]) {
					info[4] = d;
				}
			}
		}
		else if (num == 3) {
			info[3] = d;
			if (arr[3][3] != arr[4][7]) {
				info[4] = -d;
			}
			if (arr[3][7] != arr[2][3]) {
				info[2] = -d;
				if (arr[2][7] != arr[1][3]) {
					info[1] = d;
				}
			}
		}
		else {
			info[4] = d;
			if (arr[4][7] != arr[3][3]) {
				info[3] = -d;
				if (arr[3][7] != arr[2][3]) {
					info[2] = d;
					if (arr[2][7] != arr[1][3]) {
						info[1] = -d;
					}
				}
			}
		}
		rotate();
	}
	for (int i = 1; i <= 4; i++) {
		if (arr[i][1] == 1) {
			ans += pow(2, i - 1);
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