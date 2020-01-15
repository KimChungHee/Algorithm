#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int area, sr, sc;
int ans = 1e9;
int arr[11][11];
int paper[5] = { 5,5,5,5,5 };
bool flag;

void init() {
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1 && !flag) {
				sr = i; sc = j;
				flag = true;
			}
			if (arr[i][j] == 1) area++;
		}
	}
}

bool isok(int r, int c, int k) {
	for (int i = r; i <= r + k; i++) {
		for (int j = c; j <= c + k; j++) {
			if (arr[i][j] == 0) return false;
		}
	}
	return true;
}

void change(int r, int c, int k, int a) {//4번째 인자로 1또는 0으로 변경
	for (int i = r; i <= r + k; i++) {
		for (int j = c; j <= c + k; j++) {
			arr[i][j] = a;
		}
	}
}


void dfs(int r, int c, int cnt, int num) {
	if (num >= ans) {
		return;
	}
	if (cnt == area) {//모든 칸을 채우면
		ans = min(ans, num);
		return;
	}

	if (c > 10) {
		r++; c = 1;
	}

	for (int i = r; i <= 10; i++) {
		if (i > r) c = 1;
		for (int j = c; j <= 10; j++) {
			if (arr[i][j] == 1) {
				for (int k = 4; k >= 0; k--) {
					if (i + k > 10 || j + k > 10) continue;
					if (isok(i, j, k) && paper[k] > 0) {
						paper[k]--;
						change(i, j, k, 0);
						dfs(i, j + k + 1, cnt + (k + 1) * (k + 1), num + 1);
						change(i, j, k, 1);
						paper[k]++;
					}
				}
			}
			if (arr[i][j] == 1) return;
		}
	}

}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(sr, sc, 0, 0);
	if (ans == 1e9) {
		cout << -1;
	}
	else cout << ans;
}