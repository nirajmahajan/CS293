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
					cout << "pend" << endl;
				}
			}
		} else if (type == 'D') {
			int lpid, lloc; cin >> lpid >> lloc;

			if(filled.size() == 0) {
				ans[num_req] = 1;
			}


			list<Triple>::iterator vi = filled.begin();
			list<Triple>::iterator lasti;
			int prev_end = -1;
			int next_start;
			bool deleted = false;
			for(vi = filled.begin(); vi != filled.end(); vi++) {
				Triple temp = *vi;
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

			if(deleted && !pendings.empty()) {
				// cout << "enter";
				int new_size = next_start - prev_end-1;
				// cout << new_size << "sad";
				list<Triple>::iterator pi = pendings.begin();

				for(pi = pendings.begin(); pi != pendings.end(); pi++) {
					Triple temp = *pi;

					if (temp.length <= new_size) {
						temp.starting = prev_end+1;
						if (lasti == filled.end()) {
							filled.push_back(temp);
						} else {
							filled.insert(lasti, temp);
						}
						ans[temp.request] = temp.starting;
						pendings.erase(lasti);
						break;
					}
				}
			}

		} else if (type == 'T') {
			int lpid; cin >> lpid;
			list<Triple> copied;

			if(filled.size() == 0) {
				ans[num_req] = 1;
			}

			list<Triple>::iterator vi = filled.begin();
			bool deleted = false;
			for(vi = filled.begin(); vi != filled.end(); vi++) {
				Triple temp = *vi;
				if(temp.pid == lpid) {
					deleted = true;
				} else {
					copied.push_back(temp);
				}
			}
			// created copied
			// swap now
			filled.swap(copied);

			if(!deleted) {
				ans[num_req] = 1;
			} else if(!pendings.empty()){
				ans[num_req] = 0;
				list<Triple>::iterator pi = pendings.begin();

				
				if(filled.empty()) {
					list<Triple> copied_left;
					int end = -1;
					for(pi = pendings.begin(); pi != pendings.end(); pi++) {
						Triple temp = *pi;
						if(temp.pid == lpid) {
							continue;
						}
						if(temp.length <= M - 1 - end) {
							filled.push_back(temp);
							end = temp.starting + temp.length - 1;
						} else {
							copied_left.push_back(temp);
						}
					}
					pendings.swap(copied_left);
					break;
				}

				list<Triple>::iterator fi = filled.begin();

				// filled is not empty so search along
///////////////////////////////////

				list<Triple> copied_left;
				for(pi = pendings.begin(); pi != pendings.end(); pi++) {
					Triple element = *pi;
					if(element.pid == lpid) {
						continue;
					}

					list<Triple>::iterator vi = filled.begin();
					int prev_end = -1;
					bool inserted = false;
					for(vi = filled.begin(); vi != filled.end(); vi++) {
						Triple temp = *vi;
						if ((temp.starting - prev_end - 1) >= element.length) {
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
						if(end_mem >= element.length){
							element.starting = prev_end+1;
							filled.push_back(element);
							ans[element.request] = element.starting;
						} else {
							copied_left.push_back(element);
						}
					}
				}
				////////////////////////
				pendings.swap(copied_left);
			}
		} 
		num_req++;
		// cout << type << "type" << endl;
	}

	for(int i = 0; i < num_req ; i++) {
		cout << i << " " << ans[i] << endl;
	}
}