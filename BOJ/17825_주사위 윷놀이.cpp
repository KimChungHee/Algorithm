#include <iostream>
#include <cstring>

using namespace std;
int ans;
int dice[10];
int horse[5];//�� ��ġ
int map[33];//�� ��� ��ȣ
int score[33];//������
int turn[33];//��ȯ�� ����
bool check[33];

void init() {
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}

	for (int i = 0; i < 21; i++) {
		map[i] = i + 1;
	}
	map[21] = 21; map[22] = 23; map[23] = 24; map[24] = 25;
	map[25] = 31; map[29] = 30; map[30] = 25;
	map[28] = 27; map[27] = 26; map[26] = 25;
	map[31] = 32; map[32] = 20;

	for (int i = 0; i < 21; i++) {
		score[i] = i * 2;
	}
	score[22] = 13; score[23] = 16; score[24] = 19; score[25] = 25;
	score[26] = 26; score[27] = 27; score[28] = 28;
	score[29] = 22; score[30] = 24; score[31] = 30; score[32] = 35;

	//��ȯ�� ����
	turn[5] = 22; turn[10] = 29; turn[15] = 28;
}

void dfs(int cnt, int val) {
	if (cnt == 10) {
		if (val > ans) ans = val;
		return;
	}

	for (int i = 1; i <= 4; i++) {
		int prev = horse[i];//���� ���� ����ȣ
		int now = prev;
		int num = dice[cnt];

		if (turn[now] > 0) {//�� ��ġ�� ��ȯ���̸�
			now = turn[now];//���� ��ȯ
			num--;//�̵��ϴ� ĭ �� - 1
		}

		while (num--) {//�̵�
			now = map[now];
		}

		if (now != 21 && check[now]) {//�������� ���� ���� ��, �ٸ� ���� �ִٸ� �̵� �Ұ�
			continue;
		}

		check[prev] = false;
		check[now] = true;
		horse[i] = now;

		dfs(cnt + 1, val + score[now]);

		check[prev] = true;
		check[now] = false;
		horse[i] = prev;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(0, 0);
	cout << ans;
	return 0;
}