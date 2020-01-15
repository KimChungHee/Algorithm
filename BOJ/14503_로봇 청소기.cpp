#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
int N, M, sr, sc, d, ans;
int arr[51][51];
bool check[51][51];
int dy[4] = {-1,0,1,0 };//�ϵ�����
int dx[4] = {0,1,0,-1 };
int change[4] = { 2,3,0,1 };//���� ����

struct pos {
	int row; int col; int dir;
};
queue<pos> q;

void init() {
	cin >> N >> M;
	cin >> sr >> sc >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	q.push({ sr, sc, d });//�ʱ� ��ǥ
	check[sr][sc] = true; ans++;//�ʱ� ��ǥ û��

	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col; int cd = cur.dir;
		int nd = cd;
		bool flag = false;

		for (int i = 1; i <= 4; i++) {//���� �������� Ž��
			if (nd - 1 >= 0) nd -= 1;
			else nd = 3;

			int nr = cr + dy[nd]; int nc = cc + dx[nd];
			if (nr<0 || nr>=N || nc<0 || nc>=M || check[nr][nc] || arr[nr][nc]==1) continue;
			else {//���� ����ų� �� �Ǵ� û���� ������ �ƴ϶��
				flag = true;
				q.push({ nr,nc,nd });//���� û���� ��ǥ,����
				check[nr][nc] = true; ans++;
			}

			if (flag) break;
		}

		if (!flag) {//4 ���� ��� û�� �Ǵ� ���̸�
			//���� �� ��ǥ
			int nr = cr + dy[change[cd]]; int nc = cc + dx[change[cd]];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || arr[nr][nc] == 1) {
				//���� ��ǥ�� ���̶�� �۵� ����
			}
			else {//���� ��ǥ�� ���� �ƴϸ�
				q.push({ nr,nc,cd });//���� �����ϰ� ����
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