#include<bits/stdc++.h>
using namespace std;

long long parent[1001];
long long capacity[1001];
long long allCost[1001];
list<string> addresses[1001];
unordered_map<string, list<string>::iterator> nodeMaps[1001];

long long runQuery(string q, long long node) {
	if(node == 0) {
		// cout << "returning " << allCost[0] << endl;
		return allCost[0];
	}
	if(nodeMaps[node].find(q) == nodeMaps[node].end()) {
		// cout << "not found " << node << endl;
		long long ans = allCost[node] + runQuery(q, parent[node]);
		// cout << ans << endl << endl;

		if(addresses[node].size() == capacity[node]) {
			string toBeErased = addresses[node].back();
			nodeMaps[node].erase(toBeErased);
			addresses[node].pop_back();
			addresses[node].push_front(q);
			nodeMaps[node][q] = addresses[node].begin();

			return ans;
		} else {
			addresses[node].push_front(q);
			nodeMaps[node][q] = addresses[node].begin();
			return ans;
		}
	} else {
		auto targetIterator = nodeMaps[node][q];
		addresses[node].erase(targetIterator);
		addresses[node].push_front(q);
		nodeMaps[node][q] = addresses[node].begin();
		return allCost[node];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	long long n,m; cin >> n >> m;
	for(long long i = 1; i < n; i++) {
		cin >> parent[i];
	}
	for(long long i = 1; i < n; i++) {
		cin >> capacity[i];
		allCost[i] = 1 + floor(log2(capacity[i]));
	}
	capacity[0] = m;
	allCost[0] = 1 + floor(log2(m));
	long long cost = 0;
	for(long long i = 0; i < m; i++) {
		string q; long long node; cin >> q >> node;
		cost += runQuery(q, node);
		// cout << cost << endl;
	}
	cout << cost << endl;
}