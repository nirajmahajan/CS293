#include <iostream>
#include <vector>

using namespace std;

// int stoi(char a) {
// 	return (int)a - '0';
// }


pair<char, int> input[1000001];
int SminI[1000001];
bool filled[1000001] = {false};
vector<int> types;
vector<int> yesTypes;

void resetfilled() {
	for (int i = 0; i < 1000001; i++) {
		filled[i] = false;
	}
}

int main () {
	int n; cin >> n;

	for (int i = 1; i <= n; i++) {
		char type; cin >> type;
		int num; cin >> num;
		input[i] = make_pair(type, num);

		if (!filled[num]) {
			SminI[num] = 0;
			filled[num] = true;
			types.push_back(num);
		}
		if (type == 'e') {
			SminI[num]--;
		} else {
			SminI[num]++;
		}
	}
	resetfilled();
	// cout << "TYPES SIZEW : " << types.size() << endl;

	for (auto type : types) {
		if (SminI[type] == 0) {
			// cout << "YES" << endl;
			yesTypes.push_back(type);
		} else {
		}
	}

	vector<int> typesSatAfterCutAfter[n+1];

	for (auto type : yesTypes) {
	// for (int type = 3; type < 4; type ++) {
		// cout << "curr type is " << type << endl;
		int min = 0;
		int curr = 0;
		vector<int> ans;
		for (int i = 1; i <= n; i++) {
			// cout << curr << "i sis " << i << endl;
			if (input[i].second != type) {
				if (min == curr) {
					ans.push_back(i);
				}
				continue;
			}
			char style = input[i].first;

			if (style == 'e') {
				curr--;
				if (curr < min) {
					min = curr;
					ans.clear();
					ans.push_back(i);
					// cout << "DEBUG " << ans.size()  << "pushing back pos " << i << endl;
					// cout << "DEBUG Type: " << type << endl;
				} else if (curr == min) {
					ans.push_back(i);
				}
			} else {
				curr++;
			}

		}

		//now ans has all positions for type 'type'
		for (auto temp1 : ans) {
			typesSatAfterCutAfter[temp1].push_back(type);
		}
	}

	int maxSize = 0;
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		int size = typesSatAfterCutAfter[i].size();
		// cout << "size of cut at " << i << " is " << size << endl;
		if (size > maxSize) {
			maxSize = size;
			ans = i;
		}
	}

	ans++;
	if (ans == n+1) {
		ans = 1;
	}

	cout << ans << " " << maxSize << " ";
	vector<int> notSat;

	int dels = 0;
	int index = ans-1;
	if (index == 0) {
		index = n;
	}
	for (int i = 0; i < n; i++) {
		index = (index)%n + 1;
		// cout << "INDEx " << index << endl;
		char style = input[index].first;
		int type = input[index].second;
		// cout << "lala is " << type << " index is " << index << endl;

		if (!filled[type]) {
			notSat.push_back(type);
			filled[type]= true;
			SminI[type]= 0;
		}

		if (style == 'e') {
			SminI[type]--;
		} else {
			SminI[type]++;
		}
		if (SminI[type] < 0) {
			dels++;
			SminI[type]++;
			// cout << "deletin " << style << type << endl;
		}

	}

	for (auto noSat : notSat) {

		dels += SminI[noSat];
	}
	cout << dels << endl;
}