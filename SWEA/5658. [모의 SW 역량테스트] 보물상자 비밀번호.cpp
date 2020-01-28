#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int T, N, K, ans;
string s;
vector<int> v;
void init() {
	v.clear();
	cin >> N >> K;
	cin >> s;
}

void play() {
	int tmp = N / 4 - 1;
	int num = 0;
	for (int i = 0; i < s.size(); i++) {
		if (tmp > 0) {
			if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
				num += (s[i] - '0') * pow(16, tmp);
			}
			else {
				num += (s[i] - 55) * pow(16, tmp);
			}
			tmp--;
		}
		else {
			if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
				num += (s[i] - '0') * pow(16, tmp);
			}
			else {
				num += (s[i] - 55) * pow(16, tmp);
			}
			v.push_back(num);
			num = 0;
			tmp = N / 4 - 1;//다시 갱신
		}
	}


	for (int k = 1; k <= N - 1; k++) {//N-1번 뒤에 걸 앞으로 옮김
		char temp = s.back();
		s.pop_back();
		s.insert(s.begin(), temp);
		for (int i = 0; i < s.size(); i++) {
			if (tmp > 0) {
				if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
					num += (s[i] - '0') * pow(16, tmp);
				}
				else {
					num += (s[i] - 55) * pow(16, tmp);
				}
				tmp--;
			}
			else {
				if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
					num += (s[i] - '0') * pow(16, tmp);
				}
				else {
					num += (s[i] - 55) * pow(16, tmp);
				}
				v.push_back(num);
				num = 0;
				tmp = N / 4 - 1;//다시 갱신
			}
		}
	}
	sort(v.begin(), v.end(), greater<int>());
	v.erase(unique(v.begin(), v.end()), v.end());
	ans = v[K - 1];
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