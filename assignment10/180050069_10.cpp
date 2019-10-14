#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll bit[500005];
ll input[500005];
ll zeros[500005];

// ll sum(ll r) {
//     ll ret = 0;
//     for (; r >= 0; r = (r & (r + 1)) - 1)
//         ret += bit[r];
//     return ret;
// }

// void add(ll idx, ll delta) {
//     for (; idx < n; idx = idx | (idx + 1))
//         bit[idx] += delta;
// }

// ll getSum(ll BITree[], ll index) 
// { 
//     ll sum = 0; // Iniialize result 
  
//     // index in BITree[] is 1 more than the index in arr[] 
//     index = index + 1; 
  
//     // Traverse ancestors of BITree[index] 
//     while (index>0) 
//     { 
//         // Add current element of BITree to sum 
//         sum += BITree[index]; 
  
//         // Move index to parent node in getSum View 
//         index -= index & (-index); 
//     } 
//     return sum; 
// } 
  
// // Updates a node in Binary Index Tree (BITree) at given index 
// // in BITree. The given value 'val' is added to BITree[i] and  
// // all of its ancestors in tree. 
// void updateBIT(ll BITree[], ll n, ll index, ll val) 
// { 
//     // index in BITree[] is 1 more than the index in arr[] 
//     index = index + 1; 
  
//     // Traverse all ancestors and add 'val' 
//     while (index <= n) 
//     { 
//     // Add 'val' to current node of BI Tree 
//     BITree[index] += val; 
  
//     // Update index to that of parent in update View 
//     index += index & (-index); 
//     } 
// } 
  
// // Constructs and returns a Binary Indexed Tree for given 
// // array of size n. 
// ll *constructBITree(ll arr[], ll n) 
// { 
//     // Create and initialize BITree[] as 0 
//     ll *BITree = new ll[n+1]; 
//     for (ll i=1; i<=n; i++) 
//         BITree[i] = 0; 
  
//     // Store the actual values in BITree[] using update() 
//     for (ll i=0; i<n; i++) 
//         updateBIT(BITree, n, i, arr[i]); 
  
//     // Uncomment below lines to see contents of BITree[] 
//     //for (ll i=1; i<=n; i++) 
//     //     cout << BITree[i] << " "; 
  
//     return BITree; 
// }

ll query(int i) {
	ll s = 0;
	while(i>0) {
		s+= bit[i];
		i-=i&(-i);
	}
	return s;
}

void update(ll i, ll val) {
	while (i < 500005) {
		bit[i] += val;
		i+=i&(-i);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n; cin >> n;
    for(ll i = 0; i < n; i++) {
    	cin >> input[i];
    }

    // finding ijk
    ll countIJK = 0;
    // ll* bit = constructBITree(zeros, 500005);
    for(ll i = 0; i < 500005; i++) {
    	bit[i] = 0;
    }
    for(ll j = 0; j < n; j++) {
    	ll tempPrefix = query(input[j]);
    	ll tempSuffix = n-j-input[j]+tempPrefix;
    	countIJK += tempPrefix * tempSuffix;
    	update(input[j], 1);
    }

    // ll* bit = constructBITree(zeros, 500005)
    for(ll i = 0; i < 500005; i++) {
    	bit[i] = 0;
    }

    ll countIJK_IKJ = 0;
    for(ll i = n-1; i >= 0; i--) {
    	ll tempSuffix = query(500004) - query(input[i]);
    	countIJK_IKJ += (tempSuffix*(tempSuffix-1))/2;
    	update(input[i], 1);
    }

    for(ll i = 0; i < 500005; i++) {
    	bit[i] = 0;
    }

    ll countIKJ = countIJK_IKJ - countIJK;

    cout << countIKJ << " ";

	for(ll i = 0; i < 500005; i++) {
    	bit[i] = 0;
    }    

    ll countIKJ_JKI = 0;
    for(ll j = 0; j < n; j++) {
    	ll tempPrefix = query(input[j]);
    	ll tempSuffix = query(500004)-tempPrefix;
    	countIKJ_JKI += tempPrefix * tempSuffix;
    	update(input[j], 1);
    }

    ll countJKI = countIKJ_JKI - countIKJ;
    cout << countJKI << endl;
}