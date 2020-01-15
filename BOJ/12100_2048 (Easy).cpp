#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int N, ans;
int arr[21][21];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
bool check[21][21];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void move(int dir) {//�迭 �̵� �Լ�
	memset(check, false, sizeof(check));

	if (dir == 0) {//��
		for (int i = 1; i <= N; i++) {//��
			for (int j = 2; j <= N; j++) {//��
				if (arr[j][i] == 0) continue;//��ĭ�� �ǳʶ�
				for (int k = j - 1; k >= 1; k--) {
					if (arr[k][i] == 0) {//������ ��ĭ�̸�
						arr[k][i] = arr[k + 1][i];
						arr[k + 1][i] = 0;
					}
					else if ((arr[k][i] == arr[k + 1][i]) && !check[k][i]) {//���� ������
						arr[k][i] *= 2;
						arr[k + 1][i] = 0;
						check[k][i] = true;
						break;
					}
					else {
						break;//�� �ٸ��� ����
					}
				}
			}
		}
	}
	else if (dir == 1) {//��
		for (int i = 1; i <= N; i++) {//��
			for (int j = N - 1; j >= 1; j--) {//��
				if (arr[j][i] == 0) continue;//��ĭ�� �ǳʶ�
				for (int k = j + 1; k <= N; k++) {
					if (arr[k][i] == 0) {//������ ��ĭ�̸�
						arr[k][i] = arr[k - 1][i];
						arr[k - 1][i] = 0;
					}
					else if ((arr[k][i] == arr[k - 1][i]) && !check[k][i]) {//���� ������
						arr[k][i] *= 2;
						arr[k - 1][i] = 0;
						check[k][i] = true;
						break;
					}
					else {
						break;//�� �ٸ��� ����
					}
				}
			}
		}
	}
	else if (dir == 2) {//��
		for (int i = 1; i <= N; i++) {//��
			for (int j = 2; j <= N; j++) {//��
				if (arr[i][j] == 0) continue;//��ĭ�� �ǳʶ�
				for (int k = j - 1; k >= 1; k--) {
					if (arr[i][k] == 0) {//������ ��ĭ�̸�
						arr[i][k] = arr[i][k + 1];
						arr[i][k + 1] = 0;
					}
					else if ((arr[i][k] == arr[i][k + 1]) && !check[i][k]) {//���� ������
						arr[i][k] *= 2;
						arr[i][k + 1] = 0;
						check[i][k] = true;
						break;
					}
					else {
						break;//�� �ٸ��� ����
					}
				}
			}
		}
	}
	else if (dir == 3) {//��
		for (int i = 1; i <= N; i++) {//��
			for (int j = N - 1; j >= 1; j--) {//��
				if (arr[i][j] == 0) continue;//��ĭ�� �ǳʶ�
				for (int k = j + 1; k <= N; k++) {
					if (arr[i][k] == 0) {//������ ��ĭ�̸�
						arr[i][k] = arr[i][k - 1];
						arr[i][k - 1] = 0;
					}
					else if ((arr[i][k] == arr[i][k - 1]) && !check[i][k]) {//���� ������
						arr[i][k] *= 2;
						arr[i][k - 1] = 0;
						check[i][k] = true;
						break;
					}
					else {
						break;//�� �ٸ��� ����
					}
				}
			}
		}
	}
}

void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}


void dfs(int cnt) {

	int tmp[21][21];
	for (int i = 1; i <= N; i++) {//�ӽ� �迭�� ����
		for (int j = 1; j <= N; j++) {
			tmp[i][j] = arr[i][j];
			if (arr[i][j] > ans) ans = arr[i][j];
		}
	}


	if (cnt == 5) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		move(i);//�̵�
		dfs(cnt + 1);
		for (int j = 1; j <= N; j++) {//���纻�� ���� �迭�� �ű�
			for (int k = 1; k <= N; k++) {
				arr[j][k] = tmp[j][k];
			}
		}
	}

}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(0);
	cout << ans;
}