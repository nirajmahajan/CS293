#include <bits/stdc++.h>
using namespace std;

#define INF 1000000.00
#define MINF -1000000.00

priority_queue<int, int> pointsnregions;

// a is always positive
struct LineSegment
{
	bool isnull;
	double a, b, c;
	double lbx, rbx;
	double lby, rby;
};

struct Node
{
	vector<pair<double,double> > lrp;
	vector<pair<double,double> > rrp;
	LineSegment eqn;
	Node* lt = NULL;
	Node* rt = NULL;
};

pair<double, double> intersection(LineSegment init, double a1, double b1, double c1) {
	double a = init.a;
	double b = init.b;
	double c = init.c;

	if((a*b1 == b*a1)&&(a*c1 == c*a1)) {
		return  make_pair(MINF, MINF);
	}
	else if(a*b1 == b*a1) {
		return make_pair(INF, INF);
	} else {
		double numx = (c*b1 - c1*b);
		double numy = (a*c1 - a1*c);
		double den = (a*b1 - b*a1);
		return make_pair((numx/den), (numy/den));
	}
}

pair<LineSegment, LineSegment> split(LineSegment init, double a1, double b1, double c1) {
	pair<double, double> inter = intersection(init, a1, b1, c1);

	LineSegment l1, l2;
	l1.isnull = false;
	l2.isnull = false;
	l1.a = a1;
	l1.b = b1;
	l1.c = c1;
	l2.a = a1;
	l2.b = b1;
	l2.c = c1;

	if(inter.first == MINF || inter.second == MINF) {
		l1.isnull = true;
		l2.isnull = true;
		return make_pair(l1, l2);
	} else if(inter.first == INF || inter.second == INF) {
		if(c1/a1 > init.c/init.a) {
			l2.isnull = true;
			l1 = init;
			return make_pair(l1, l2);
		} else {
			l2.isnull = true;
			l1 = init;
			return make_pair(l2, l1);
		}
	}
	else if(init.b == 0) {
		if(inter.second <= init.lby) {
			l2.isnull = true;
			l1 = init;
			return make_pair(l2, l1);	
		} else if (inter.second >= init.rby) {
			l2.isnull = true;
			l1 = init;
			return make_pair(l1, l2);
		} else {
			l1.lby = init.lby;
			l1.rby = inter.second;
			l2.lby = inter.second;
			l2.rby = init.rby;
			return make_pair(l1, l2);
		}
	} else {
		if(inter.first <= init.lbx) {
			l2.isnull = true;
			l1 = init;
			return make_pair(l2, l1);	
		} else if (inter.first >= init.rbx) {
			l2.isnull = true;
			l1 = init;
			return make_pair(l1, l2);
		} else {
			l1.lbx = init.lbx;
			l1.rbx = inter.first;
			l2.lbx = inter.first;
			l2.rbx = init.rbx;
			return make_pair(l1,l2);
		}
	}
}

void insertinTree(Node* root, Node* parent, LineSegment segm, char mode) {
	// if(mode == 'i') {
	// 	Node* j;
	// 	j = new Node;
	// 	j->eqn = segm;
	// 	j->lt = NULL;
	// 	j->rt = NULL;
	// 	return;
	// }
	if(root == NULL) {
		Node* j;
		j = new Node;
		j->eqn = segm;
		j->lt = NULL;
		j->rt = NULL;
		if(mode == 'l') {
			parent->lt = j;
		} else {
			parent->rt = j;
		}
		return;
	}

	pair<LineSegment, LineSegment> splitval = split(segm, root->eqn.a, root->eqn.b, root->eqn.c);

	if(splitval.first.isnull && !splitval.second.isnull) {
		insertinTree(root->rt, root, splitval.second, 'r');
	}
	else if(splitval.second.isnull && !splitval.first.isnull){
		insertinTree(root->lt, root, splitval.first, 'l');
	} else if (splitval.second.isnull && splitval.first.isnull) {
		return;
	} else {
		insertinTree(root->lt, root, splitval.first, 'l');
		insertinTree(root->rt, root, splitval.second, 'r');
	}
	

} 

double countRegions(Node* top) {
	if(top == NULL) {
		return 1;
	} else {
		return countRegions(top->lt) + countRegions(top->rt);
	}
}

double populateQ(Node* top) {
	if(top == NULL) {
		return 1;
	} else {
		return countRegions(top->lt) + countRegions(top->rt);
	}
}

double val(double tex, double tey, LineSegment l) {
	return (l.a*tex + l.b*tey - l.c);
}

void insertPointinTree(Node* root, double tex, double tey){
	double ans = val(tex, tey, root->eqn);
	if(ans > 0) {
		if(root->rt == NULL) {
			root->rrp.push_back(make_pair(tex, tey));
			return;
		} else {
			insertPointinTree(root->rt, tex, tey);
			return;
		}
	} else if (ans < 0) {
		if(root->lt == NULL) {
			root->lrp.push_back(make_pair(tex, tey));
			return;
		} else {
			insertPointinTree(root->lt, tex, tey);
			return;
		}
	}
}

double regions = 0;

int main() {
	// LineSegment l1;
	// l1.a = 1;
	// l1.b = -1;
	// l1.c = 0;
	// l1.lbx = 0;
	// l1.rbx = 7;
	// l1.isnull = false;
	
	// pair<double, double> inter = intersection(l1, 1,-1,6);
	// cout << inter.first << " " << inter.second << endl;


	// pair<LineSegment, LineSegment> split_result = split(l1, 1,-1,6);
	// double x1, x2, x3, x4;
	// x1 = split_result.first.lbx;
	// x2 = split_result.first.rbx;
	// x3 = split_result.second.lbx;
	// x4 = split_result.second.rbx;
	// if(split_result.first.isnull == true) {
	// 	x1 = INF;
	// 	x2 = INF;
	// }
	// if(split_result.second.isnull == true){
	// 	x3 = INF;
	// 	x4 = INF;
	// }
	// cout << x1 << " " << x2 << " " << x3 << " " << x4 << endl; 

	double num_lines, num_points; cin >> num_lines >> num_points;

	Node* root = NULL;
	Node* dummy = new Node;
	for(double i = 0 ; i < num_lines; i++) {
		double a, b, c; cin >> a >> b >> c;
		if(a < 0) {
			a = -a;
			b = -b; 
			c = -c;
		}

		LineSegment templ;
		templ.isnull = false;
		templ.a = a;
		templ.b = b;
		templ.c = c;
		if(b == 0) {
			templ.lby = MINF;
			templ.rby = INF;
		} else {
			templ.lbx = MINF;
			templ.rbx = INF;
		}

		insertinTree(root, dummy, templ, 'l');
		root = dummy->lt;
	}

	for(double i = 0; i < num_points; i++) {
		double tex, tey; 
		cin >> tex >> tey;
		insertPointinTree(root, tex, tey);
	}



	cout << countRegions(root) << endl;
}