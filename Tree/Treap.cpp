// =====================================================================================
// 
//       Filename:  Treap.cpp
//        Created:  2017년 03월 23일 15시 30분 56초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename KeyType>
struct Treap{
	struct Node {
		KeyType key;
		int priority, size;
		Node *left, *right;
		Node(const KeyType key):key(key),priority(rand()),size(1),left(NULL),right(NULL){}
		void setLeft(Node *newLeft) {
			left = newLeft;
			calcSize();
		}
		void setRight(Node *newRight) {
			right = newRight;
			calcSize();
		}
		void calcSize() {
			size = 1;
			if (left)
				size += left->size;
			if (right)
				size += right->size;
		}
	};
	Node *root;
	Treap(){
		root=0;
	}
	Node* make_Node(KeyType key){
		Node* ret=new Node(key);
		return ret;
	}
	typedef pair<Node*, Node*> NodePair;
	NodePair split(Node *root, KeyType key) {
		if (root == NULL)return NodePair(NULL, NULL);
		if (root->key < key) {
			NodePair rs = split(root->right, key);
			root->setRight(rs.first);
			return NodePair(root, rs.second);
		}
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(ls.first, root);
	}
	Node* insert(Node *root, Node *node) {
		if (root == NULL)
			return node;
		if (root->priority < node->priority) {
			NodePair splitted = split(root, node->key);
			node->setLeft(splitted.first);
			node->setRight(splitted.second);
			return node;
		}
		else if (root->key < node->key) {
			root->setRight(insert(root->right, node));
		}
		else
			root->setLeft(insert(root->left, node));
		return root;
	}
	Node* merge(Node *a, Node *b) {
		if (a == NULL)
			return b;
		if (b == NULL)
			return a;
		if (a->priority < b->priority) {
			b->setLeft(merge(a, b->left));
			return b;
		}
		a->setRight(merge(a->right, b));
		return a;
	}
	Node* erase(Node *root, KeyType key) {
		if (root == NULL)
			return root;
		if (root->key == key) {
			Node *ret = merge(root->left, root->right);
			delete root;
			return ret;
		}
		if (root->key < key)
			root->setRight(erase(root->right, key));
		else
			root->setLeft(erase(root->left, key));
		return root;
	}
	int countLessThan(Node* root, KeyType key){
		if(root==NULL)return 0;
		if(root->key>=key)
			return countLessThan(root->left, key);
		int ls=(root->left?root->left->size:0);
		return ls+1+countLessThan(root->right, key);
	}
};

int a[200001];
Treap<int> tree[200001];
int n, q;
void update(int idx, int val){
	while(idx<=n){
		tree[idx].root=tree[idx].insert(tree[idx].root, tree[idx].make_Node(val));
		idx+=idx&(-idx);
	}
}
void erase(int idx, int val){
	while(idx<=n){
		tree[idx].root=tree[idx].erase(tree[idx].root, val);
		idx+=idx&(-idx);
	}
}
ll query(int idx, int val){
	ll ret=0;
	while(idx>0){
		ret+=tree[idx].countLessThan(tree[idx].root, val);
		idx-=idx&(-idx);
	}
	return ret;
}
int main(){
	scanf("%d%d", &n, &q);
	for(int i=1;i<=n;i++){
		a[i]=i;
		update(i, i);
	}
	long long ans=0;
	for(int i=0;i<q;i++){
		int b, c;
		scanf("%d%d", &b, &c);
		if(b>c)
			swap(b, c);
		if(b==c){
			printf("%lld\n", ans);
			continue;
		}
		int now, lcnt, rcnt;

		now=query(b, a[b]);//b보다 왼쪽으로 a[b]보다 작은 값의 수
		lcnt=b-1-now;//b보다 왼쪽으로 a[b]보다 큰 값의 수
		rcnt=a[b]-1-now;//b보다 오른쪽으로 a[b]보다 작은 값의 수
		ans-=(lcnt+rcnt);
		erase(b, a[b]);

		now=query(c, a[c]);
		lcnt=c-2-now;
		rcnt=a[c]-1-now-(a[b]<a[c]?1:0);
		ans-=(lcnt+rcnt);
		erase(c, a[c]);

		swap(a[b], a[c]);
		
		update(b, a[b]);	
		now=query(b, a[b]);
		lcnt=b-1-now;
		rcnt=a[b]-1-now-(a[c]<a[b]?1:0);
		ans+=(lcnt+rcnt);


		update(c, a[c]);
		now=query(c, a[c]);
		lcnt=c-1-now;
		rcnt=a[c]-1-now;
		ans+=(lcnt+rcnt);

		printf("%lld\n", ans);
	}
}
