#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, L, ans;
int arr[101][101];

void init() {
	cin >> N >> L;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	for (int i = 1; i <= N; i++) {
		int tmp = 1;
		bool flag = false;
		for (int j = 1; j <= N - 1; j++) {
			if (arr[i][j] == arr[i][j + 1]) tmp++;
			else if ((arr[i][j] + 1 == arr[i][j + 1]) && tmp >= L) tmp = 1;
			else if ((arr[i][j] - 1 == arr[i][j + 1]) && tmp >= 0) tmp = 1 - L;
			else {
				flag = true;
				break;
			}
		}
		if (!flag && tmp >= 0) ans++;
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i < j) {
				int tmp = arr[i][j];
				arr[i][j] = arr[j][i];
				arr[j][i] = tmp;
			}
		}
	}
	play();
	cout << ans;
	return 0;
}