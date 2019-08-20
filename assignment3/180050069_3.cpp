#include <bits/stdc++.h>
using namespace std;

vector<int> p;
vector<int> q;
vector<int> r;

void multiply(int P, int Q, int R, int n) {
	if (n <= 16) {
		for(int a1 = 0; a1 < n; a1++) {
			for(int a2 = 0; a2 < n; a2++) {
				r[R+a1+a2] += p[P+a1] * q[Q+a2];
			}
		}
	} else {
		multiply(P, Q, R, n/2);
		multiply(P+n/2, Q+n/2, R+n, n/2);

		vector<int> temp(n,0);
		vector<int> temp2(n,0);

		for(int i = 0; i < n; i++) {
			temp[i] = r[R+i];
			temp2[i] = r[R+i+n];
			r[i+R] = 0;
			r[i+R+n] = 0;
		}

		for(int i = P+n/2; i < P+n; i++) {
			p[i-n/2] += p[i];
		}
		for(int i = Q+n/2; i < Q+n; i++) {
			q[i-n/2] += q[i];	
		}
		multiply(P, Q, R+n/2, n/2);
		for(int i = P+n/2; i < P+n; i++) {
			p[i-n/2] -= p[i];
		}
		for(int i = Q+n/2; i < Q+n; i++) {
			q[i-n/2] -= q[i];	
		}
		for(int i = 0; i < n; i++) {
			r[i+n/2+R] -= (temp[i]+temp2[i]);
			r[R+i] += temp[i];
			r[R+i+n] += temp2[i];
		}
		// for(auto a : temp) {
			// cout << a << " ";
		// }
		// cout << endl;
	}
	// cout << "DEB " << P << " " << Q << " " << R << " " << n << " " << endl;
	// cout << "r is  " << r[0] << " " << r[1] << " " << r[2] << " " << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		int temp; cin >> temp;
		p.push_back(temp);
	}
	for(int i = 0; i < n; i++) {
		int temp; cin >> temp;
		q.push_back(temp);
	}
	for(int i = 0; i < 2*n-1; i++) {
		r.push_back(0);
	}


	multiply(0,0,0,n);

	for (int i = 0; i < 2*n-1; i++) {
		cout << r[i] << " ";
	}
	cout << endl;
}