#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> > Rcor;
vector<pair<int, int> > Bcor;

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n; cin >> n;

    for(int i = 0; i < n; i++) {
    	int tempx, tempy;
    	cin >> tempx >> tempy;
    	Rcor.push_back(make_pair(tempx, tempy));
    }

    for(int i = 0; i < n; i++) {
    	int tempx, tempy;
    	cin >> tempx >> tempy;
    	Bcor.push_back(make_pair(tempx, tempy));
    }

    sort(Rcor.begin(), Rcor.end());
    sort(Bcor.begin(), Bcor.end());

    multiset<int> stackUp;

    int ans = 0;
    int Riterator = 0;
    for(auto Bcoriter : Bcor){
    	int curr_blue_x = Bcoriter.first;
    	int curr_blue_y = Bcoriter.second;

    	while(true){
    		if(Riterator >= n) {
    			break;
    		}
    		if(Rcor[Riterator].first <= curr_blue_x) {
    			stackUp.insert(Rcor[Riterator].second);
    			Riterator++;
    		} else {
    			break;
    		}
    	}
    	if(stackUp.empty()) {
    		continue;
    	}

    	auto to_delete = stackUp.upper_bound(curr_blue_y);

    	if(to_delete == stackUp.end()) {
    		to_delete--;
    	}
    	else if(*to_delete > curr_blue_y) {
    		if(to_delete == stackUp.begin()) {
    			continue;
    		} else {
    			to_delete--;
    		}
    	} else {
    		continue;
    	}


    	stackUp.erase(to_delete);
    	ans++;
    }
    cout << ans << endl;
}
