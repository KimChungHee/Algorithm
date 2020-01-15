#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int N, ans;
int arr[17][17];
//우,하,우하

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
	arr[1][1] = 1;
	arr[1][2] = 1;
}

void dfs(int r, int c, int dir) {//0-가로,1-세로,2-대각
	if (arr[N][N] == 1) {
		ans++;
		return;
	}

	if (dir == 2) {
		if (c + 1 <= N && arr[r][c + 1] == 0) {
			arr[r][c + 1] = 1;
			dfs(r, c + 1, 0);
			arr[r][c + 1] = 0;
		}
		if (r + 1 <= N && c + 1 <= N && arr[r][c + 1] == 0 && arr[r + 1][c] == 0 && arr[r + 1][c + 1] == 0) {
			arr[r][c + 1] = 1; arr[r + 1][c] = 1; arr[r + 1][c + 1] = 1;
			dfs(r + 1, c + 1, 2);
			arr[r][c + 1] = 0; arr[r + 1][c] = 0; arr[r + 1][c + 1] = 0;
		}
		if (r + 1 <= N && arr[r + 1][c] == 0) {
			arr[r + 1][c] = 1;
			dfs(r + 1, c, 1);
			arr[r + 1][c] = 0;
		}
	}

	if (dir == 1) {
		if (r + 1 <= N && c + 1 <= N && arr[r][c + 1] == 0 && arr[r + 1][c] == 0 && arr[r + 1][c + 1] == 0) {
			arr[r][c + 1] = 1; arr[r + 1][c] = 1; arr[r + 1][c + 1] = 1;
			dfs(r + 1, c + 1, 2);
			arr[r][c + 1] = 0; arr[r + 1][c] = 0; arr[r + 1][c + 1] = 0;
		}
		if (r + 1 <= N && arr[r + 1][c] == 0) {
			arr[r + 1][c] = 1;
			dfs(r + 1, c, 1);
			arr[r + 1][c] = 0;
		}
	}

	if (dir == 0) {
		if (c + 1 <= N && arr[r][c + 1] == 0) {
			arr[r][c + 1] = 1;
			dfs(r, c + 1, 0);
			arr[r][c + 1] = 0;
		}
		if (r + 1 <= N && c + 1 <= N && arr[r][c + 1] == 0 && arr[r + 1][c] == 0 && arr[r + 1][c + 1] == 0) {
			arr[r][c + 1] = 1; arr[r + 1][c] = 1; arr[r + 1][c + 1] = 1;
			dfs(r + 1, c + 1, 2);
			arr[r][c + 1] = 0; arr[r + 1][c] = 0; arr[r + 1][c + 1] = 0;
		}
	}

}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	if (arr[N][N] == 1) {
		cout << 0;
	}
	else {
		dfs(1, 2, 0);
		cout << ans;
	}
}