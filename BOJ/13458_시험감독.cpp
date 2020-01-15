#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
//�� ������ - B��, �� ������ - C��, �Ѱ����� 1��
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
		if (v[i] > B) {//�ΰ����� �ʿ��ϸ�
			v[i] -= B;
			if (v[i] % C == 0) {//�ΰ������� ���� �������� 0�̸�
				ans += 1 + v[i] / C;//�� ���� 1�� + �� �������� ���� ��
			}
			else {
				ans += 2 + v[i] / C;//�� ���� 1�� + �� �������� ���� �� + ������ 1
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