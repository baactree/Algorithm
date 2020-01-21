#include <iostream>
using namespace std;
template <class T>
struct vector{
	T *arr;
	int c, s;
	vector(){
		arr=new T[4];
		c=4;
		s=0;
	}
	vector(int n){
		arr=new T[n];
		c=n;
		s=n;
	}
	void resize(int n){
		T *t=new T[n];
		for(int i=0;i<s;i++)
			t[i]=arr[i];
		delete[] arr;
		arr=t;
		c=s=n;
	}
	void push_back(T d){
		if(c==s){
			resize(c*2);
			s/=2;
		}
		arr[s++]=d;
	}
	void pop_back(){
		s--;
	}
	T& operator [] (int idx){
		return arr[idx];
	}
};
template <class T>
struct priority_queue{
	vector<T> tree;
	int s;
	priority_queue(){
		tree.resize(1);
		s=0;
	}
	void push(T d){
		tree.push_back(d);
		s++;
		int idx=s;
		while(idx>1){
			if(tree[idx]>tree[idx/2])
				swap(tree[idx], tree[idx/2]);
			else
				break;
			idx/=2;
		}
	}
	T top(){
		return tree[1];
	}
	bool empty(){
		return s==0;
	}
	void pop(){
		swap(tree[1], tree[s]);
		tree.pop_back();
		int idx=1;
		s--;
		while(true){
			int next=-1;
			int now=tree[idx];
			if(idx*2<=s&&now<tree[idx*2]){
				now=tree[idx*2];
				next=idx*2;
			}
			if(idx*2+1<=s&&now<tree[idx*2+1]){
				now=tree[idx*2+1];
				next=idx*2+1;
			}
			if(next==-1)
				break;
			swap(tree[idx], tree[next]);
			idx=next;
		}
	}
};
int n;
int main(){
	scanf("%d", &n);
	priority_queue<int> pq;
	while(n--){
		int x;
		scanf("%d", &x);
		if(x){
			pq.push(x);
		}
		else{
			if(pq.empty())
				printf("0\n");
			else{
				printf("%d\n", pq.top());
				pq.pop();
			}
		}
	}
	return 0;

}