#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, ans, sr, sc;
int arr[21][21];
bool check[101];
//����,����,�»�,���
int dy[4] = { 1,1,-1,-1 };
int dx[4] = { 1,-1,-1,1 };

void init() {
	ans = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void dfs(int r, int c, int cnt, int dir, int a, int b, int cc, int d) {
	if (sr == r && sc == c && cnt > 0) {//�簢���� �׸��� ���ƿ���
		ans = max(ans, cnt);
		return;
	}

	int nr = r; int nc = c;
	if (dir == 0) {//����
		nr = r + dy[0]; nc = c + dx[0];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
			check[arr[nr][nc]] = true;
			dfs(nr, nc, cnt + 1, 0, a + 1, b, cc, d);
			check[arr[nr][nc]] = false;
		}

		if (a >= 1) {//���ϸ� �� �� �̻� ������
			nr = r + dy[1]; nc = c + dx[1];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
				check[arr[nr][nc]] = true;
				dfs(nr, nc, cnt + 1, 1, a, b + 1, cc, d);
				check[arr[nr][nc]] = false;
			}
		}
	}

	if (dir == 1) {//����
		nr = r + dy[1]; nc = c + dx[1];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
			check[arr[nr][nc]] = true;
			dfs(nr, nc, cnt + 1, 1, a, b + 1, cc, d);
			check[arr[nr][nc]] = false;
		}

		if (b >= 1) {//���ϸ� �� �� �̻� ������
			nr = r + dy[2]; nc = c + dx[2];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
				check[arr[nr][nc]] = true;
				dfs(nr, nc, cnt + 1, 2, a, b, cc + 1, d);
				check[arr[nr][nc]] = false;
			}
		}
	}

	if (dir == 2) {//�»�
		if (cc < a) {//���Ϻ��� �»��� ������
			nr = r + dy[2]; nc = c + dx[2];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
				check[arr[nr][nc]] = true;
				dfs(nr, nc, cnt + 1, 2, a, b, cc + 1, d);
				check[arr[nr][nc]] = false;
			}
		}

		if (cc == a) {//���϶� �»��� ������
			nr = r + dy[3]; nc = c + dx[3];
			if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
				check[arr[nr][nc]] = true;
				dfs(nr, nc, cnt + 1, 3, a, b, cc, d + 1);
				check[arr[nr][nc]] = false;
			}
		}
	}

	if (dir == 3) {//���
		nr = r + dy[3]; nc = c + dx[3];
		if (nr >= 1 && nr <= N && nc >= 1 && nc <= N && !check[arr[nr][nc]]) {
			check[arr[nr][nc]] = true;
			dfs(nr, nc, cnt + 1, 3, a, b, cc, d + 1);
			check[arr[nr][nc]] = false;
		}
	}
}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		for (int i = 1; i <= N - 2; i++) {
			for (int j = 2; j <= N - 1; j++) {
				sr = i; sc = j;
				dfs(i, j, 0, 0, 0, 0, 0, 0);
			}
		}
		if (ans == 0) {
			ans = -1;
		}
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}