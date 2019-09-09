#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll input[1000005];
ll weights[1000005];
ll dist[1000005];

queue<pair<int, int> > ansq;

stack<int> swapem;
stack<int> wanna_go_right;

int main() {
	int n; cin >> n;
	ll ans = 0;
	int swap_count = 0;

	for (int i = 0; i < n; i++) {
		cin >> input[i];
		if(input[i] - i > 0) {
			wanna_go_right.push(i);
		}
	}
	for (int i = 0; i < n; i++) {
		cin >> weights[i];
	}
	dist[0]=0;
	for (int i = 1; i < n; i++) {
		int temp; cin >> temp;
		dist[i] = dist[i-1] + temp;
	}


	while(!wanna_go_right.empty()) {
		int x = wanna_go_right.top();
		wanna_go_right.pop();

		// fill swapem
		int target = input[x];
		while(true) {
			if(target <= x) {
				input[x] = target;
				break;
			}
			else {
				swapem.push(target);
				// cout << "[ushing" << target << endl;
				target = input[target];
			}
		}


		// swap the stack
		while (!swapem.empty()) {
			int toswap = swapem.top();
			swapem.pop();

			ans += (dist[toswap] - dist[x]) * (weights[toswap] + weights[x]);
			ll temp1 = weights[toswap];
			weights[toswap] = weights[x];
			weights[x] = temp1;
			swap_count ++;
			ansq.push(make_pair(x,toswap));
			x = toswap;
		} 
	}

	cout << ans << endl << swap_count << endl;

	while(!ansq.empty()) {
		pair<int, int> temp = ansq.front();
		ansq.pop();
		cout << temp.first << " " << temp.second << endl;
	}
}