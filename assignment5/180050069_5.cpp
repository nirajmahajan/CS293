#include <bits/stdc++.h>
using namespace std;

struct Triple
{
	int starting, pid, length, request;
};

int ans[1000001];
list<Triple> pendings; 
list<Triple> filled; 

int main() {
	int n, M; cin >> n >> M;
	int num_req = 0;

	while(true) {
		char type; cin >> type;
		// cout << ans[21] << endl;
		// if (!filled.empty()) {
		// 	cout << filled.front().starting << " " << filled.front().pid  << " " << filled.front().length<< endl;
		// }

		// if(num_req == 20 || num_req == 21 || num_req == 27) {
			// cout << "\n\nCurrent state for type " << type << " and req num " << num_req << " \nPendings : \n";
			// for (auto elem : pendings) {
			// 	cout << elem.pid << " " << elem.length << " " << elem.request << endl;
			// }
			// cout << "\nFilled : \n";
			// for (auto elem : filled) {
			// 	cout << elem.pid << " " << elem.starting << " " << elem.length << " " << elem.request << endl;
			// }
			// cout << endl << endl;
		// }



		if (type == 'H') {
			break;
		} else if (type == 'A') {
			int lpid, lmem; cin >> lpid >> lmem;
			Triple element;
			element.starting = 0;
			element.pid = lpid;
			element.length = lmem;
			element.request = num_req;

			if(filled.size() == 0) {
				if(M >= lmem) {
					filled.push_back(element);
					ans[element.request] = 0;
					num_req++;
					continue;
				} else {
					ans[element.request] = -1;
					num_req++;
					continue;
				}
			}

			list<Triple>::iterator vi = filled.begin();
			int prev_end = -1;
			bool inserted = false;
			for(vi = filled.begin(); vi != filled.end(); vi++) {
				Triple temp = *vi;
				if ((temp.starting - prev_end - 1) >= lmem) {
					element.starting = prev_end+1;
					filled.insert(vi, element);
					inserted = true;
					ans[element.request] = element.starting;
					break;
				} else {
					prev_end = temp.starting + temp.length - 1;
				}
			}
			if(!inserted) {
				int end_mem = M-1-prev_end;
				if(end_mem >= lmem){
					element.starting = prev_end+1;
					filled.push_back(element);
					ans[element.request] = element.starting;
				} else {
					ans[element.request] = -1;
					pendings.push_back(element);
					// cout << "pend" << endl;
				}
			}
		} else if (type == 'D') {
			int lpid, lloc; cin >> lpid >> lloc;

			if(filled.size() == 0) {
				ans[num_req] = 1;
			}


			list<Triple>::iterator vi = filled.begin();
			int prev_end = -1;
			int next_start;
			auto lasti = vi;
			bool deleted = false;
			for(vi = filled.begin(); vi != filled.end(); vi++) {
				Triple temp = *vi;
				// cout << "iter.starting " << temp.starting << endl;
				// cout << "lloc " << lloc << endl;
				if (temp.starting == lloc) {
					if(temp.pid == lpid) {
						
						vi++;
						if(vi == filled.end()) {
							next_start = M;
						} else {
							next_start = vi->starting;
						}
						lasti = vi;
						vi--;

						filled.erase(vi);
						// cout << vi->pid << vi->starting << vi->length << endl;
						// cout << lasti->pid << lasti->starting << lasti->length << endl;
						deleted = true;
						ans[num_req] = 0;
						break;
					}else {
						ans[num_req] = 1;
						break;
					}
				} else {
					prev_end = temp.starting + temp.length - 1;
				}
			}

			if (deleted == false) {
				ans[num_req] = 1;
			}

			if(deleted && !pendings.empty()) {
				int new_size = next_start - prev_end-1;
				list<Triple>::iterator pi = pendings.begin();

				for(pi = pendings.begin(); pi != pendings.end(); pi++) {
					new_size = next_start - prev_end-1;
					Triple temp = *pi;

					if(new_size <= 0) {
						break;
					}

					if (temp.length <= new_size) {
						temp.starting = prev_end+1;
						filled.insert(lasti, temp);
						ans[temp.request] = temp.starting;
						prev_end = temp.starting + temp.length - 1;
						pendings.erase(pi);
						pi--;
					}
				}
				// cout << filled.size() << endl;
			}

		} else if (type == 'T') {
			int lpid; cin >> lpid;
			list<Triple> copied;

			if(filled.size() == 0) {
				ans[num_req] = 1;
			}

			list<Triple>::iterator pi = pendings.begin();
			for(pi = pendings.begin(); pi!= pendings.end(); pi++) {
				Triple temp = *pi;
				if(temp.pid == lpid){
					pendings.erase(pi);
					pi--;
				}
			}
			bool deleted = false;
			list<Triple>::iterator fi = filled.begin();
			for(fi = filled.begin(); fi!= filled.end(); fi++) {
				Triple temp = *fi;
				if(temp.pid == lpid){
					filled.erase(fi);
					fi--;
					deleted = true;
				}
			}
			if(deleted == false) {
				ans[num_req] = 1;
				num_req++;
				continue;
			} else if (pendings.empty()){
				num_req ++;
				continue;
				ans[num_req] = 0;
			} else {
				ans[num_req] = 0;
				pi = pendings.begin();

				for(pi = pendings.begin(); pi != pendings.end(); pi++){
					Triple temp = *pi;
					int prev_end = -1;
					bool delted = false;
					fi = filled.begin();
					for(fi = filled.begin(); fi != filled.end(); fi++) {
						Triple ftemp = *fi;
						if(ftemp.starting - prev_end - 1 >= temp.length) {
							temp.starting = prev_end + 1;
							ans[temp.request] = temp.starting;
							filled.insert(fi, temp);
							pendings.erase(pi);
							deleted = true;
							pi--;
							break;
						} else {
							prev_end = ftemp.starting + ftemp.length -1;
						}
					}
					if(!deleted && M - prev_end - 1 >= temp.length) {
						temp.starting = prev_end + 1;
						ans[temp.request] = temp.starting;
						filled.push_back(temp);
						pendings.erase(pi);
						pi--;	
					}
				}
			}
			
		}
		// cout << ans[num_req] << " " ;
		num_req++;
		// cout << type << " type" << endl;

	}

	for(int i = 0; i < num_req ; i++) {
		cout << ans[i] << endl;
	}
}