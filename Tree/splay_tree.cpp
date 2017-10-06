#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T>
struct Splay_tree{
	struct node{
		node *l,*r,*p;
		T key;
		int cnt;
		ll sum,value,lazy;
		bool inv;
	};
	node *tree;
	Splay_tree(){
		tree=NULL;
	}
	~Splay_tree(){
		while(tree)
			erase(tree->key);
	}
	void push(node *x){
		x->value+=x->lazy;
		if(x->l){
			x->l->lazy+=x->lazy;
			x->l->sum+=x->l->cnt*x->lazy;
		}
		if(x->r){
			x->r->lazy+=x->lazy;
			x->r->sum+=x->r->cnt*x->lazy;
		}
		x->lazy=0;
		// reverse
		/*
		if(!x->inv)
			return;
		node *t=x->l;
		x->l=x->r;
		x->r=t;
		x->inv=false;
		if(x->l)
			x->l->inv=!x->l->inv;
		if(x->r)
			x->r->inv=!=x->r->inv;
		*/
	}
	void update(node *x){
		x->cnt=1;
		x->sum=x->value;
		if(x->l){
			x->cnt+=x->l->cnt;
			x->sum+=x->l->sum;
		}
		if(x->r){
			x->cnt+=x->r->cnt;
			x->sum+=x->r->sum;
		}
	}
	void rotate(node *x){
		node *p=x->p;
		node *b;
		if(x==p->l){
			p->l=b=x->r;
			x->r=p;
		}
		else{
			p->r=b=x->l;
			x->l=p;
		}
		x->p=p->p;
		p->p=x;
		if(b) b->p=p;
		(x->p?p==x->p->l?x->p->l:x->p->r:tree)=x;
		update(p);
		update(x);
	}
	void splay(node *x){
		while(x->p){
			node *p=x->p;
			node *g=p->p;
			if(g) rotate((x==p->l)==(p==g->l)?p:x);
			rotate(x);
		}
	}
	void insert(T key){
		node *p=tree,**pp;
		if(!p){
			node *x=new node;
			tree=x;
			x->l=x->r=x->p=NULL;
			x->key=key;
			return;
		}
		while(1){
			if(key==p->key)
				return;
			if(key<p->key){
				if(!p->l){
					pp=&p->l;
					break;
				}
				p=p->l;
			}
			else{
				if(!p->r){
					pp=&p->r;
					break;
				}
				p=p->r;
			}
		}
		node *x=new node;
		*pp=x;
		x->l=x->r=NULL;
		x->p=p;
		x->key=key;
		splay(x);
	}
	bool find(T key){
		node *p=tree;
		if(!p)
			return false;
		while(p){
			if(key==p->key)
				break;
			if(key<p->key){
				if(!p->l)
					break;
				p=p->l;
			}
			else{
				if(!p->r)
					break;
				p=p->r;
			}
		}
		splay(p);
		return key==p->key;
	}
	void erase(T key){
		if(!find(key))
			return;
		node *p=tree;
		if(p->l){
			if(p->r){
				tree=p->l;
				tree->p=NULL;
				node *x=tree;
				while(x->r)
					x=x->r;
				x->r=p->r;
				p->r->p=x;
				splay(x);
				delete p;
				return;
			}
			tree=p->l;
			tree->p=NULL;
			delete p;
			return;
		}
		if(p->r){
			tree=p->r;
			tree->p=NULL;
			delete p;
			return;
		}
		tree=NULL;
	}
	//0-based
	void find_kth(int k){
		node *x=tree;
		push(x);
		while(true){
			while(x->l&&x->l->cnt>k){
				x=x->l;
				push(x);
			}
			if(x->l)
				k-=x->l->cnt;
			if(!k--)
				break;
			x=x->r;
			push(x);
		}
		splay(x);
	}
	void init(int n){
		n+=2;
		node *x;
		tree=x=new node;
		x->l=x->r=x->p=NULL;
		x->cnt=n;
		x->sum=x->value=x->lazy=0;
		for(int i=1;i<n;i++){
			x->r=new node;
			x->r->p=x;
			x=x->r;
			x->l=x->r=NULL;
			x->cnt=n-i;
			x->sum=x->value=x->lazy=0;
		}
	}
	//1-based
	void interval(int l,int r){
		find_kth(l-1);
		node *x=tree;
		tree=x->r;
		tree->p=NULL;
		find_kth(r-l+1);
		x->r=tree;
		tree->p=x;
		tree=x;
	}
	void add(int l, int r, ll val){
		interval(l,r);
		node *x=tree->r->l;
		x->sum+=x->cnt*val;
		x->lazy+=val;
	}
	ll sum(int l,int r){
		interval(l,r);
		return tree->r->l->sum;
	}
	void reverse(int l,int r){
		interval(l,r);
		node *x=tree->r->l;
		x->inv=!x->inv;
	}
};
int n,m,k;
ll arr[1000005];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	Splay_tree<int> sptree;
	sptree.init(n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
		sptree.add(i,i,arr[i]);
	}
	for(int i=0;i<m+k;i++){
		int a;
		scanf("%d",&a);
		if(a==1){
			int b,c;
			ll d;
			scanf("%d%d%lld",&b,&c,&d);
			sptree.add(b,c,d);
		}
		else{
			int b,c;
			scanf("%d%d",&b,&c);
			printf("%lld\n",sptree.sum(b,c));
		}
	}
	return 0;
}