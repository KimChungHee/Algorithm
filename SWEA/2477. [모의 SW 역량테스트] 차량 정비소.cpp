#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, K, A, B, people;
//N-접수창구 수, M-정비창구 수, K-고객 수, A-이용한 접수 번호, B-이용한 정비 번호
int ans = 0;
int customer[1001];//고객 번호 별 도착시간
struct pos {
	int num; int time;
	//고객 번호, 도착 시간
};
struct pos2 {
	int num; int time; int rec_num;
	//고객 번호, 도착 시간, 사용한 접수 번호
};
struct pos3 {
	int num; int rec_num; int fix_num;
	//고객 번호, 사용 접수 번호, 사용 정비 번호
};

int rec_time[11], fix_time[11];
pos rec[11];
pos2 fix[11];
queue<pos> rec_wait;
queue<pos2> fix_wait;
queue<pos3> finish;//끝난 사람들 저장

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

		//접수 대기에 넣을 수 있는지
		for (int i = num; i <= K; i++) {
			if (customer[i] == t) {
				rec_wait.push({ i, t });
				num = i + 1;
			}
		}

		//정비 대기에 넣을 수 있는 지
		for (int i = 1; i <= N; i++) {
			if (rec[i].num > 0 && rec[i].time == t) {
				fix_wait.push({ rec[i].num, rec[i].time, i });
				rec[i].num = 0;
			}
		}

		//접수대기 중에 접수 할 수 있는지
		for (int i = 1; i <= N; i++) {
			if (rec_wait.empty()) break;
			if (rec[i].num == 0) {
				rec[i].num = rec_wait.front().num;
				rec[i].time = t + rec_time[i];
				rec_wait.pop();
			}
		}

		//정비가 끝나면 나감
		for (int i = 1; i <= M; i++) {
			if (fix[i].num > 0 && fix[i].time == t) {//고객있고, 정비가 끝났으면
				finish.push({ fix[i].num, fix[i].rec_num, i });//종료 정보에 추가
				fix[i].num = 0;
			}
		}

		//정비대기 중에 정비할수있는 지 확인
		for (int i = 1; i <= M; i++) {
			if (fix_wait.empty()) break;//정비대기인원 없으면 종료
			if (fix[i].num == 0) {//정비대가 비어잇으면
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