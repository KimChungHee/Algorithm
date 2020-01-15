#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
//총 감독관 - B명, 부 감독관 - C명, 총감독은 1명씩
int N, B, C;
long long ans;
vector<int> v;

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int a; cin >> a;
		v.push_back(a);
	}
	cin >> B >> C;
}

void play() {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > B) {//부감독이 필요하면
			v[i] -= B;
			if (v[i] % C == 0) {//부감독으로 나눈 나머지가 0이면
				ans += 1 + v[i] / C;//총 감독 1명 + 부 감독으로 나눈 몫
			}
			else {
				ans += 2 + v[i] / C;//총 감독 1명 + 부 감독으로 나눈 몫 + 나머지 1
			}
		}
		else ans += 1;
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