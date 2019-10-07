#include<bits/stdc++.h>
#define  inf 1e13

using namespace std;

struct line 
{
	double a, b, c;
};
struct point {
	double x, y;
};
struct node 
{
	node *l, *r;
	int num_left, num_right;
	line lin;
	node(line li) {
		this->l = this->r = NULL;
		this->num_left = this->num_right = 0;
		this->lin = li;
	}
};

point inter(line a1, line a2) 
{
	double d = (a1.a * a2.b - a1.b * a2.a);
	double a = (a2.b * a1.c - a1.b * a2.c);
	double b = (a1.a * a2.c - a2.a * a1.c);
	point t;
	if (d) t.x = a / d, t.y = b / d;
	return t;
}

double value(line li, point k) {
	return li.a * k.x + li.b * k.y - li.c;
}

node* buildtree(line li,point p1,point p2,node* root)
{
	if(p1.x==p2.x&&p1.y==p2.y)
		return NULL;
	if(root==NULL)
	{
		root= new node(li);
		return root;
	}

	auto t1=value(root->lin,p1);
	auto t2=value(root->lin,p2);

	if (t1 * t2 > 0) 
	{
		if (root->lin.a) 
		{
			if (t1 * (root->lin).a > 0) root->r = buildtree(li, p1, p2, root->r);
			else	root->l = buildtree(li, p1, p2, root->l);
		}
		else 
		{
			if (t1 > 0)	root->r = buildtree(li, p1, p2, root->r);
			else	root->l = buildtree(li, p1, p2, root->l);
		}
	}

	else if (t1 != 0 || t2 != 0) 
	{
		if(t1>0&&t2<0)
		{
			point p = inter(li, root->lin);
			root->l = buildtree(li, p, p2, root->l);
			root->r = buildtree(li, p1, p, root->r);
	
		}
		else
		{
			point p = inter(li, root->lin);
			root->l = buildtree(li, p1, p, root->l);
			root->r = buildtree(li, p, p2, root->r);
		}
	}
	return root;
}


int nulls(node* root)
{
	if(root==NULL)
		return 1;
	else
		return nulls(root->l) +nulls(root->r);
}

int height(node* root)
{
	if(root==NULL)
		return 0;
	else
		return max(height(root->l),height(root->r))+1;	
}

vector<int> cnt;

void insert(point pt, node* root)
{
	if(root==NULL)
	{
		return;
	}
	auto t1=value(root->lin,pt);
/*	if (root->lin.a) 
	{
		if (t1 * (root->lin).a > 0) 
		{
			root->num_right++;
			insert(pt,root->r);
		}
		else	
		{
			root->num_left++;	
			insert(pt,root->l);
		}
		return;
	}*/
	if (t1 > 0)	
	{
		root->num_right++;
		insert(pt,root->r);
	}
	else if(t1<0)	
	{	
		root->num_left++;
		insert(pt,root->l);
	}
}


void cntr(node* root)
{
	if(root->l==NULL)
		cnt.push_back(root->num_left);
	else
		cntr(root->l);
	if(root->r==NULL)
		cnt.push_back(root->num_right);
	else
		cntr(root->r);
}

vector<pair<int,int>> V;


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	line li;
	point k1, k2;

	node* root = NULL;
	for (int i = 0; i < n; i++) {
		cin >> li.a >> li.b >> li.c;
		if(li.a<0)
		{
			li.a*=-1;
			li.b*=-1;
			li.c*=-1;
		}
		if (li.b == 0) {
			k1.x = k2.x = li.c / li.a;
			k1.y = -inf, k2.y = inf;
		}
		else if (li.a == 0) {
			if(li.b<0)
			{
				li.a*=-1;
				li.b*=-1;
				li.c*=-1;
			}
			k1.y = k2.y = li.c / li.b;
			k1.x = -inf, k2.x = inf;
		}
		else {
			k1.x = -inf, k2.x = inf;
			k1.y = (li.c - li.a * k1.x) / li.b;
			k2.y = (li.c - li.a * k2.x) / li.b;
		}
		root = buildtree(li, k1, k2, root);
		//cout<<nulls(root)<<" "<<height(root)<<endl;
	}

	cout<<nulls(root)<<" "<<height(root)<<endl;
	double x,y;
	point pt;
	while(m--)
	{
		cin>>pt.x>>pt.y;
		insert(pt,root);
	}
	cntr(root);
	cnt.push_back(-1);

	sort(cnt.begin(), cnt.end());
	for(int i=1;i<cnt.size();i++)
	{
		if(cnt[i]!=cnt[i-1])
		{
			V.push_back(pair<int,int>(cnt[i],1));
		}
		else
		{
			V[V.size()-1].second++;
		}
	}

	for(auto i:V)
	{
		cout<<i.first<<" "<<i.second<<endl;
	}
	return 0;
}