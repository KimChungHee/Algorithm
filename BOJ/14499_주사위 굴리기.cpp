#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int N, M, x, y, K;
int arr[21][21];
vector<int> v;
int dice[7];
int dy[5] = { 0,0,0,-1,1 };//��,��,��,��
int dx[5] = { 0,1,-1,0,0 };

void init() {
	cin >> N >> M >> x >> y >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];//�� ����
		}
	}
	for (int i = 1; i <= K; i++) {
		int a; cin >> a;
		v.push_back(a);
	}
}

void move(int d) {
	int tmp[7];
	for (int i = 1; i <= 6; i++) {
		tmp[i] = dice[i];
	}
	if (d == 1) {//��
		dice[1] = tmp[3];
		dice[3] = tmp[6];
		dice[4] = tmp[1];
		dice[6] = tmp[4];
	}
	else if (d == 2) {//��
		dice[1] = tmp[4];
		dice[3] = tmp[1];
		dice[4] = tmp[6];
		dice[6] = tmp[3];
	}
	else if (d == 3) {//��
		dice[1] = tmp[2];
		dice[2] = tmp[6];
		dice[5] = tmp[1];
		dice[6] = tmp[5];
	}
	else if (d == 4) {//��
		dice[1] = tmp[5];
		dice[2] = tmp[1];
		dice[5] = tmp[6];
		dice[6] = tmp[2];
	}
}

void play() {
	int nr = x; int nc = y;
	for (int i = 0; i < v.size(); i++) {
		nr += dy[v[i]]; nc += dx[v[i]];//���� ��ǥ
		if (nr < 0 || nr >= N || nc < 0 || nc >= M) {//���� ���̸�
			nr -= dy[v[i]]; nc -= dx[v[i]];//��ǥ ����
			continue;
		}

		move(v[i]);//�ֻ��� �̵�
		if (arr[nr][nc] == 0) {//ĭ�� ���� 0�̸�
			arr[nr][nc] = dice[1];//�ֻ��� �ٴڼ��� ĭ���� ����
			cout << dice[6] << '\n';
		}
		else if (arr[nr][nc] != 0) {
			dice[1] = arr[nr][nc];//ĭ�� ���� �ֻ��� �ٴ����� ����
			arr[nr][nc] = 0;//ĭ�� 0
			cout << dice[6] << '\n';
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	return 0;
}