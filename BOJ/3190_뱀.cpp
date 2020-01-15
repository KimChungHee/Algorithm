#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int N, K, L, ans;
//C-왼, D-오른, 뱀의 시작 방향 - 오른쪽
int arr[101][101];
bool check[101][101];
struct info {
	int t; char c;
};
struct pos {
	int r, c, d;
};
queue<info> q;//방향 전환 정보
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
deque<pos> snake;

void init() {
	cin >> N >> K;
	for (int i = 1; i <= K; i++) {
		int a, b; cin >> a >> b;
		arr[a][b] = 1;//사과 표시
	}
	cin >> L;
	for (int i = 1; i <= L; i++) {
		int a; char b;
		cin >> a >> b;
		q.push({ a,b });//방향 전환 정보
	}
	snake.push_back({ 1,1,3 });//초기 뱀
	check[1][1] = true;
}

int dirchange(int d, char a) {
	if (a == 'L') {//왼쪽 회전
		if (d == 0) d = 2;
		else if (d == 1) d = 3;
		else if (d == 2) d = 1;
		else d = 0;
	}
	else {//우측
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
		pos cur = snake.front();//뱀의 머리
		int cr = cur.r; int cc = cur.c; int cd = cur.d;
		int nr = cr; int nc = cc; int nd = cd;//다음 좌표
		nr = cr + dy[cd]; nc = cc + dx[cd];

		if (nr<1 || nr>N || nc<1 || nc>N || check[nr][nc]) {//다음 칸이 벽 또는 자신이면
			ans = t + 1; break;
		}

		if (arr[nr][nc] == 1) {//다음 칸이 사과면
			snake.push_front({ nr,nc,nd });//머리를 다음칸에 삽입
			arr[nr][nc] = 0;//사과 먹음
			check[nr][nc] = true;//방문 표시
		}
		else if (arr[nr][nc] == 0) {//다음 칸이 사과 아니면
			snake.push_front({ nr,nc,nd });//머리를 다음칸에 삽입
			check[nr][nc] = true;//방문 표시
			check[snake.back().r][snake.back().c] = false;//꼬리 방문 표시 해제
			snake.pop_back();//꼬리 삭제
		}

		t++;//시간 추가

		if (!q.empty()) {//방향 전환 정보가 남아있고
			if (q.front().t == t) {//방향 전환 시킬 시간이면
				snake.front().d = dirchange(cd, q.front().c);//뱀 머리 방향 전환
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