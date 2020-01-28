#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, K, A, B, people;
//N-����â�� ��, M-����â�� ��, K-�� ��, A-�̿��� ���� ��ȣ, B-�̿��� ���� ��ȣ
int ans = 0;
int customer[1001];//�� ��ȣ �� �����ð�
struct pos {
	int num; int time;
	//�� ��ȣ, ���� �ð�
};
struct pos2 {
	int num; int time; int rec_num;
	//�� ��ȣ, ���� �ð�, ����� ���� ��ȣ
};
struct pos3 {
	int num; int rec_num; int fix_num;
	//�� ��ȣ, ��� ���� ��ȣ, ��� ���� ��ȣ
};

int rec_time[11], fix_time[11];
pos rec[11];
pos2 fix[11];
queue<pos> rec_wait;
queue<pos2> fix_wait;
queue<pos3> finish;//���� ����� ����

void init() {
	ans = 0;
	cin >> N >> M >> K >> A >> B;
	for (int i = 1; i <= N; i++) {
		cin >> rec_time[i];
	}
	for (int i = 1; i <= M; i++) {
		cin >> fix_time[i];
	}
	for (int i = 1; i <= K; i++) {
		cin >> customer[i];
	}
}

void play() {
	int t = 0; int cnt = 0; int num = 1;
	while (1) {

		//���� ��⿡ ���� �� �ִ���
		for (int i = num; i <= K; i++) {
			if (customer[i] == t) {
				rec_wait.push({ i, t });
				num = i + 1;
			}
		}

		//���� ��⿡ ���� �� �ִ� ��
		for (int i = 1; i <= N; i++) {
			if (rec[i].num > 0 && rec[i].time == t) {
				fix_wait.push({ rec[i].num, rec[i].time, i });
				rec[i].num = 0;
			}
		}

		//������� �߿� ���� �� �� �ִ���
		for (int i = 1; i <= N; i++) {
			if (rec_wait.empty()) break;
			if (rec[i].num == 0) {
				rec[i].num = rec_wait.front().num;
				rec[i].time = t + rec_time[i];
				rec_wait.pop();
			}
		}

		//���� ������ ����
		for (int i = 1; i <= M; i++) {
			if (fix[i].num > 0 && fix[i].time == t) {//���ְ�, ���� ��������
				finish.push({ fix[i].num, fix[i].rec_num, i });//���� ������ �߰�
				fix[i].num = 0;
			}
		}

		//������ �߿� �����Ҽ��ִ� �� Ȯ��
		for (int i = 1; i <= M; i++) {
			if (fix_wait.empty()) break;//�������ο� ������ ����
			if (fix[i].num == 0) {//����밡 ���������
				pos2 cur = fix_wait.front();
				fix[i].num = cur.num;
				fix[i].rec_num = cur.rec_num;
				fix[i].time = t + fix_time[i];
				fix_wait.pop();
			}
		}


		if (finish.size() == K) {
			while (!finish.empty()) {
				pos3 cur = finish.front(); finish.pop();
				if (cur.rec_num == A && cur.fix_num == B) {
					ans += cur.num;
				}
			}
			break;
		}

		t++;
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		if (ans == 0) ans = -1;
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}