#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, L, R, ans, num;
struct pos {
	int row; int col;
};
bool check[101][101];
queue<pos> q;
vector<pos> area[2501];
int arr[101][101];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void bfs() {
	queue<pos> tmp = q;//�ӽ� ť
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col;
		for (int i = 0; i < 4; i++) {
			int nr = cr + dy[i]; int nc = cc + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) continue;
			if (abs(arr[nr][nc] - arr[cr][cc]) < L || abs(arr[nr][nc] - arr[cr][cc]) > R) continue;
			check[nr][nc] = true;
			q.push({ nr,nc }); tmp.push({ nr,nc });
		}
	}
	if (tmp.size() == 1) {//������ �� ���������
		return;
	}
	else {//�����̸�
		num++;//���� ��ȣ ����
		while (!tmp.empty()) {
			pos cur = tmp.front(); tmp.pop();
			int cr = cur.row; int cc = cur.col;
			area[num].push_back({ cr,cc });//������ �߰�
		}
	}
}

void play() {
	while (1) {
		num = 0;//���� ��ȣ �ʱ�ȭ
		memset(check, false, sizeof(check));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (!check[i][j]) {//�湮���߰ų� area�� �ƴ� ������ bfs
					check[i][j] = true;;
					q.push({ i,j });
					bfs();
				}
			}
		}

		if (num == 0) break;//������ �����ٸ� ����

		for (int i = 1; i <= num; i++) {//������ŭ
			int kan_num = area[i].size();//������ �̷�� ĭ�� ��
			int people = 0;//������ �α���

			for (int j = 0; j < kan_num; j++) {
				people += arr[area[i][j].row][area[i][j].col];
			}
			people /= kan_num;// ���� �α� / ĭ�� ��
			for (int j = 0; j < kan_num; j++) {
				arr[area[i][j].row][area[i][j].col] = people;//�α� ����
			}
			area[i].clear();//�̵� �� ��Ų ��, ���� Ŭ����
		}

		ans++;//�α� �̵��� �Ͼ�ٸ� �� += 1 
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