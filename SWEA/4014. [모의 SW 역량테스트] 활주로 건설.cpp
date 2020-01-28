#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, X, ans;
int arr[21][21];

void init() {
	ans = 0;
	cin >> N >> X;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	for (int i = 1; i <= N; i++) {
		int tmp = 1;
		for (int j = 1; j < N; j++) {
			if (arr[i][j] == arr[i][j + 1]) {
				tmp++;
			}
			else if (arr[i][j] - arr[i][j + 1] == -1) {//높은 지형을 만나면
				if (tmp >= X) {//건설 가능하면
					tmp = 1;
				}
				else {//건설 불가하면 종료
					tmp = -1;
					break;
				}
			}
			else if (arr[i][j] - arr[i][j + 1] == 1) {//낮은 지형을 만나면
				if (tmp < 0) break;
				else tmp = 1 - X;
			}
			else {
				tmp = -1; break;
			}
		}
		if (tmp >= 0) {
			ans++;
		}
	}
}

void rotate() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i < j) {
				int tmp = arr[i][j];
				arr[i][j] = arr[j][i];
				arr[j][i] = tmp;
			}
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
		rotate();
		play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}