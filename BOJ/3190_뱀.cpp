#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int N, K, L, ans;
//C-��, D-����, ���� ���� ���� - ������
int arr[101][101];
bool check[101][101];
struct info {
	int t; char c;
};
struct pos {
	int r, c, d;
};
queue<info> q;//���� ��ȯ ����
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
deque<pos> snake;

void init() {
	cin >> N >> K;
	for (int i = 1; i <= K; i++) {
		int a, b; cin >> a >> b;
		arr[a][b] = 1;//��� ǥ��
	}
	cin >> L;
	for (int i = 1; i <= L; i++) {
		int a; char b;
		cin >> a >> b;
		q.push({ a,b });//���� ��ȯ ����
	}
	snake.push_back({ 1,1,3 });//�ʱ� ��
	check[1][1] = true;
}

int dirchange(int d, char a) {
	if (a == 'L') {//���� ȸ��
		if (d == 0) d = 2;
		else if (d == 1) d = 3;
		else if (d == 2) d = 1;
		else d = 0;
	}
	else {//����
		if (d == 0) d = 3;
		else if (d == 1) d = 2;
		else if (d == 2) d = 0;
		else d = 1;
	}
	return d;
}

void play() {
	int t = 0;

	while (1) {
		pos cur = snake.front();//���� �Ӹ�
		int cr = cur.r; int cc = cur.c; int cd = cur.d;
		int nr = cr; int nc = cc; int nd = cd;//���� ��ǥ
		nr = cr + dy[cd]; nc = cc + dx[cd];

		if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) {//���� ĭ�� �� �Ǵ� �ڽ��̸�
			ans = t + 1; break;
		}

		if (arr[nr][nc] == 1) {//���� ĭ�� �����
			snake.push_front({ nr,nc,nd });//�Ӹ��� ����ĭ�� ����
			arr[nr][nc] = 0;//��� ����
			check[nr][nc] = true;//�湮 ǥ��
		}
		else if (arr[nr][nc] == 0) {//���� ĭ�� ��� �ƴϸ�
			snake.push_front({ nr,nc,nd });//�Ӹ��� ����ĭ�� ����
			check[nr][nc] = true;//�湮 ǥ��
			check[snake.back().r][snake.back().c] = false;//���� �湮 ǥ�� ����
			snake.pop_back();//���� ����
		}

		t++;//�ð� �߰�

		if (!q.empty()) {//���� ��ȯ ������ �����ְ�
			if (q.front().t == t) {//���� ��ȯ ��ų �ð��̸�
				snake.front().d = dirchange(cd, q.front().c);//�� �Ӹ� ���� ��ȯ
				q.pop();
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