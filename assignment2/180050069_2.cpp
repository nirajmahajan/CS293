#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <queue>
using namespace std;
#define int long long

long long fact[19];
int counter[26];

void populate_fact() {
	fact[0] = 1;
	for (int i = 1; i <= 18; i++) {
		fact[i] = i * fact[i-1];
	}
}

string delete_last(string s) {
	return s.substr(0, s.length()-1);
}

bool match_from_start(string a, string b) {
	if (a.length() > b.length()) {
		return (b == a.substr(0, b.length()));
	} else {
		return (a == b.substr(0, a.length()));
	}
}

long long allPerms(multiset<char> characters) {
	set<char> single_chars;
	for (auto c : characters) {
		single_chars.insert(c);
	}

	int total = 0;
	queue<int> counts;
	for(auto c : single_chars) {
		int temp_count = characters.count(c);
		counts.push(temp_count);
		total += temp_count;
	}
	long long ans = fact[total];
	while(!counts.empty()) {
		int elem = counts.front();
		counts.pop();
		ans = ans / fact[elem];
	}
	return ans;
}


long long totalKeepingi(int i, int pos, string s) {
	int sum = s.size() - pos - 1;
	long long ans = fact[sum];

	for (int j = 0; j < 26; j++) {
		if (i == j) {
			ans = ans / fact[counter[j] - 1];
		}
		else 
		ans = ans / fact[counter[j]];
	}

}

 main () {
	populate_fact();

	for (int i = 0 ;i < 26; i++) {
		counter[i] = 0;
	}

	string s; long long n;
	cin >> s >> n;
	// sort(s.begin(), s.end());
	// cout << s << endl;

	// init counter
	for (int i = 0; i < s.length(); i++) {
		counter[s[i]-'a']++;
	}

	set<char> temp_input;
	multiset<char> inventory;

	for (auto c : s) {
		temp_input.insert(c);
		inventory.insert(c);
	}
	string lexo = "";

	for(auto i : temp_input) {
		lexo += i;
	}
	sort(lexo.begin(), lexo.end());

	string part2_lexo = lexo;
	multiset<char> part2_inventory = inventory;
	long long part2_rank = 0;
	string part2_varying = "";

	string varying = "";
	long long rank = 0;

	while(varying != s) {
		for(auto c : lexo) {
			if (inventory.count(c) == 0) {
				continue;
			}

			varying += c;

			if (match_from_start(varying, s)) {
				inventory.erase(inventory.find(c));
				break;
			}

			// not matching
			// cout << "not matching " << varying << " with " << s << endl;
			// cout << "were checking  " << c << endl;
			inventory.erase(inventory.find(c));
			// cout << "old rank " << rank << endl;
			rank += allPerms(inventory);
			// cout << "new rank " << rank  << endl;
			inventory.insert(c);
			varying = delete_last(varying);
			// cout << "new varying " << varying << endl;
		}
	}

	cout << rank << " ";

	// part2

	vector<char> part2_ans;



	while(part2_ans.size() != s.length()) {

		// for(int i = 0; i < 26; i++) {
		// 	if(counter[i] == 0) {
		// 		continue;
		// 	}
		// 	// cout<<"hs"<<endl;
		// 	long long new_rank = part2_rank + totalKeepingi(i, part2_ans.size(), s);

		// 	if (new_rank > n) {
		// 		counter[i]--;
		// 		char temp_add = (char) (i + (int)'a');
		// 		 // cout << temp_add << endl;
		// 		part2_ans.push_back(temp_add);
		// 		break;
		// 	} else {
		// 		part2_rank = new_rank;
		// 	}
		// }

		for(auto c : part2_lexo) {
			if (part2_inventory.count(c) == 0) {
				continue;
			}
			part2_varying += c;


			// cout << "not matching " << varying << " with " << s << endl;
			// cout << "were checking  " << c << endl;
			part2_inventory.erase(part2_inventory.find(c));
			// cout << "old rank " << rank << endl;
			int new_rank = part2_rank + allPerms(part2_inventory);
			if (new_rank > n) {
				part2_ans.push_back(c);
				break;
			}

			// cout << "new rank " << rank  << endl;
			part2_rank = new_rank;
			part2_inventory.insert(c);
			part2_varying = delete_last(part2_varying);
			// cout << "new varying " << varying << endl;
		}
	}	

	for(auto c : part2_ans) {
		cout << c;
	}
	cout << endl;

}
