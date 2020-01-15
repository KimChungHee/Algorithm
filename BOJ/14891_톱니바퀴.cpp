#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <cmath>

using namespace std;
//�´��� ����� ���� �ٸ���, �ݴ�������� ȸ��
//N�� - 0, S�� - 1 , 1 -> �ð�, -1 -> �ݽð�
int ans, K;
int arr[5][9];
struct pos {
	int num; int dir;
};
vector<pos> v;

void init() {
	for (int i = 1; i <= 4; i++) {
		string s;
		cin >> s;
		for (int j = 1; j <= 8; j++) {
			arr[i][j] = s[j - 1] - '0';
		}
	}

	cin >> K;
	for (int i = 1; i <= K; i++) {
		int a, b; cin >> a >> b;
		v.push_back({ a,b });//ȸ�� ����
	}
}

void rotate(int num, int dir) {
	int info[5] = { 0, };//ȸ������

	if (num == 1) {
		info[num] = dir;
		if (arr[1][3] != arr[2][7]) {
			info[2] = -dir;
			if (arr[2][3] != arr[3][7]) {
				info[3] = dir;
				if (arr[3][3] != arr[4][7])
					info[4] = -dir;
			}
		}
	}
	else if (num == 2) {
		info[num] = dir;
		if (arr[2][7] != arr[1][3]) info[1] = -dir;
		if (arr[2][3] != arr[3][7]) {
			info[3] = -dir;
			if (arr[3][3] != arr[4][7]) {
				info[4] = dir;
			}
		}
	}
	else if (num == 3) {
		info[num] = dir;
		if (arr[3][3] != arr[4][7]) info[4] = -dir;
		if (arr[3][7] != arr[2][3]) {
			info[2] = -dir;
			if (arr[2][7] != arr[1][3]) {
				info[1] = dir;
			}
		}
	}
	else if (num == 4) {
		info[num] = dir;
		if (arr[4][7] != arr[3][3]) {
			info[3] = -dir;
			if (arr[3][7] != arr[2][3]) {
				info[2] = dir;
				if (arr[2][7] != arr[1][3]) {
					info[1] = -dir;
				}
			}
		}
	} 

	for (int i = 1; i <= 4; i++) {//���� ȸ��
		if (info[i] == 1) {//�ð�
			int tmp = arr[i][8];
			for (int j = 8; j >= 2; j--) {
				arr[i][j] = arr[i][j - 1];
			}
			arr[i][1] = tmp;
		}
		else if (info[i] == -1) {//�ݽð�
			int tmp = arr[i][1];
			for (int j = 1; j <= 7; j++) {
				arr[i][j] = arr[i][j + 1];
			}
			arr[i][8] = tmp;
		}
	}
}

void findans() {
	for (int i = 1; i <= 4; i++) {
		if (arr[i][1] == 1) {
			ans += pow(2, i - 1);
		}
	}
}

void play() {
	for (int i = 0; i < K; i++) {
		int num = v[i].num; int dir = v[i].dir;
		rotate(num, dir);//ȸ��
	}
	findans();
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	cout << ans;
	return 0;
}