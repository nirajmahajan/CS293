#include <bits/stdc++.h>
using namespace std;

vector<string> input;
int id[10000007];

bool comp(int a, int b) {
	return (input[a] < input[b]);
}

// vector<string> duval(string const& s) {
//     int n = s.size();
//     int i = 0;
//     vector<string> factorization;
//     while (i < n) {
//         int j = i + 1, k = i;
//         while (j < n && s[k] <= s[j]) {
//             if (s[k] < s[j])
//                 k = i;
//             else
//                 k++;
//             j++;
//         }
//         while (i <= k) {
//             factorization.push_back(s.substr(i, j - k));
//             i += j - k;
//         }
//     }
//     return factorization;
// }

vector<string> duvalmod(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] >= s[j]) {
            if (s[k] > s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

string min_cyclic_string(string s) {
    s += s;
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
            i += j - k;
    }
    return s.substr(ans, n / 2);
}

string tonormal(string inp) {
	return min_cyclic_string(inp);
}

// void radixSort( vector<string> & arr, int maxLen )
// {
//     const int BUCKETS = 256;

//     vector<vector<string>> wordsByLength( maxLen + 1 );
//     vector<vector<string>> buckets( BUCKETS );

//     for( string & s : arr )
//         wordsByLength[ s.length( ) ].push_back( std::move( s ) );

//     int idx = 0;
//     for( auto & wordList : wordsByLength )
//         for( string & s : wordList )
//             arr[ idx++ ] = std::move( s );

//     int startingIndex = arr.size( );    
//     for( int pos = maxLen - 1; pos >= 0; --pos )
//     {
//         startingIndex -= wordsByLength[ pos + 1 ].size( );

//         for( int i = startingIndex; i < arr.size( ); ++i )
//             buckets[ arr[ i ][ pos ] ].push_back( std::move( arr[ i ] ) );

//         idx = startingIndex;
//         for( auto & thisBucket : buckets )
//         {
//             for( string & s : thisBucket )
//                 arr[ idx++ ] = std::move( s );

//             thisBucket.clear( );
//         }
//     }
// }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n; cin >> n;
	string first, second;
	for (int i = 0; i < n; i++) {
		string temp; cin >> temp;
		input.push_back(tonormal(temp));
		if (i == 0) {
			first = temp;
		}
		if (i == 1) {
			second = temp;
		}
		id[i]=i;
	}
	sort(id, id + n, comp);
	string prev = "";
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (input[id[i]] == prev) {
			continue;
		} else {
			count++;
			prev = input[id[i]];
		}
	}
	cout << count << endl;

	vector<string> lyndon_first = duvalmod(first);
	vector<string> lyndon_second = duvalmod(second);

	int i = 0, j = 0;
	int imax = lyndon_first.size();
	int jmax = lyndon_second.size();
	string ans = "";
	while(i != imax || j != jmax) {
		if (i == imax) {
			// cout << "before " << ans << endl;
			while (j != jmax) {
				ans += lyndon_second[j];
				j++;
			}
			// cout << "after " << ans << endl;
			continue;
		}
		if (j == jmax) {
			// cout << "before " << ans << endl;
			while (i != imax) {
				ans += lyndon_first[i];
				i++;
			}
			// cout << "after " << ans << endl;
			continue;
		}

		if(lyndon_first[i] == lyndon_second[j]) {
			ans = ans + lyndon_second[j] + lyndon_second[j];
			i++;j++;
		} else if (lyndon_second[j] + "|" < lyndon_first[i] + "|") {
			ans += lyndon_second[j];
			j++;
		} else {
			ans += lyndon_first[i];
			i++;
		}
		// cout << "Debug" << ans << endl;
	}
	cout << ans << endl;
}