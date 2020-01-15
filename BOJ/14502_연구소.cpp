#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int N, M, ans, safe;
int arr[9][9], tmp[9][9];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
struct pos {
	int row, col;
};
queue<pos> virus, q;//���̷��� ��ǥ

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2) {//���̷�����
				virus.push({ i,j });
			}
			else if (arr[i][j] == 0) {
				safe++;//�ʱ� ���� ����
			}
		}
	}
}

void copy() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			tmp[i][j] = arr[i][j];
		}
	}
}

void recover() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			arr[i][j] = tmp[i][j];
		}
	}
}

void bfs() {//���̷��� �۶߸�
	int cnt = 0;
	q = virus;//�ʱ� ���̷��� ����
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col;
		for (int i = 0; i < 4; i++) {
			int nr = cr + dy[i];
			int nc = cc + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == 1 || arr[nr][nc] == 2) continue;
			arr[nr][nc] = 2;
			q.push({ nr,nc });
			cnt++;//�۶߸� ���̷��� ��
		}
	}
	ans = max(ans, safe - cnt - 3);// -3�� �� 3���� �������־��� ����
}

void dfs(int r, int c, int cnt) {//�� 3�� ����
	if (cnt == 3) {//�� 3�� ����� 
		copy();
		bfs();
		recover();
		return;
	}

	if (c > M) {
		r += 1; c = 1;
	}

	for (int i = r; i <= N; i++) {
		if (i != r) c = 0;
		for (int j = c; j <= M; j++) {
			if (arr[i][j] == 0) {//��ĭ�̸�
				arr[i][j] = 1;
				dfs(i, j + 1, cnt + 1);
				arr[i][j] = 0;
			}
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	init();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] == 0) {
				arr[i][j] = 1;
				dfs(i, j + 1, 1);
				arr[i][j] = 0;
			}
		}
	}
	cout << ans;
	return 0;
}