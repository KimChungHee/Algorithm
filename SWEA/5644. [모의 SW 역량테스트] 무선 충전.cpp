#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int ans, T, M, A;
int dy[5] = { 0,-1,0,1,0 };
int dx[5] = { 0,0,1,0,-1 };
struct pos {
	int x, y, c, p;
};
vector<pos> BC;
struct info {
	int x, y;
};
vector<info> one, two;//사용자 두명
bool cmp(pos a, pos b) {
	return a.p > b.p;
}

void init() {
	cin >> M >> A;
	one.clear(); two.clear(); BC.clear(); ans = 0;

	one.push_back({ 1,1 }); two.push_back({ 10,10 });
	for (int i = 1; i <= M; i++) {
		int a; cin >> a;
		one.push_back({ one[one.size() - 1].x + dx[a], one[one.size() - 1].y + dy[a] });
	}
	for (int i = 1; i <= M; i++) {
		int a; cin >> a;
		two.push_back({ two[two.size() - 1].x + dx[a], two[two.size() - 1].y + dy[a] });
	}
	for (int i = 1; i <= A; i++) {
		int x, y, c, p; cin >> x >> y >> c >> p;
		BC.push_back({ x,y,c,p });
	}
	sort(BC.begin(), BC.end(), cmp);//충전량 큰 순서로 정렬
}

void play() {
	for (int i = 0; i < one.size(); i++) {//이동 거리만큼
		int Ax = one[i].x; int Ay = one[i].y;
		int Bx = two[i].x; int By = two[i].y;

		deque<int> posA, posB;
		for (int j = 0; j < BC.size(); j++) {
			if ((abs(Ax - BC[j].x) + abs(Ay - BC[j].y)) <= BC[j].c) {//범위에 속하면
				posA.push_back(j);//BC번호 임시 저장
			}
			if ((abs(Bx - BC[j].x) + abs(By - BC[j].y)) <= BC[j].c) {//범위에 속하면
				posB.push_back(j);//BC번호 임시 저장
			}
		}

		if (posA.empty() && posB.empty()) continue;//둘 다 비었으면 건너뜀

		if (posA.empty() || posB.empty()) {//둘 중 하나만 충전 가능
			if (posA.empty()) ans += BC[posB.front()].p;
			else ans += BC[posA.front()].p;
		}
		else if (posA.size() == 1 && posB.size() == 1) {
			if (posA.front() == posB.front()) {
				ans += BC[posA.front()].p;
			}
			else {
				ans += BC[posA.front()].p;
				ans += BC[posB.front()].p;
			}
		}
		else if (posA.size() >= 2 && posB.size() == 1) {
			if (posA.front() == posB.front()) {//첫 bc가 같으면
				ans += BC[posA.front()].p + BC[posA[1]].p;
			}
			else {
				ans += BC[posA.front()].p;
				ans += BC[posB.front()].p;
			}
		}
		else if (posB.size() >= 2 && posA.size() == 1) {
			if (posA.front() == posB.front()) {//첫 bc가 같으면
				ans += BC[posB.front()].p + BC[posB[1]].p;
			}
			else {
				ans += BC[posA.front()].p;
				ans += BC[posB.front()].p;
			}
		}
		else if (posA.size() >= 2 && posB.size() >= 2) {
			if (posA.front() == posB.front()) {
				ans += BC[posA.front()].p + max(BC[posA[1]].p, BC[posB[1]].p);
			}
			else {
				ans += BC[posA.front()].p;
				ans += BC[posB.front()].p;
			}
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}