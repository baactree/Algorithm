// =====================================================================================
// 
//       Filename:  stable_sort.cpp
//        Created:  2017년 04월 07일 12시 37분 13초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <iostream>
#include <string.h>
#include <string>
using namespace std;
template <class T>
class Vector {
public:
	int n;
	int _size;
	T *arr;
	Vector() {
		n = 0;
		_size = 32;
		arr = new T[_size];
	}
	Vector(int k) {
		n = 0;
		_size = k;
		arr = new T[_size];
	}
	void resize(int n) {
		T *temp;
		temp = new T[n];
		for (int i = 0; i < _size; i++)
			temp[i] = arr[i];
		delete[] arr;
		arr = temp;
	}
	int size() {
		return n;
	}
	T* begin() {
		return &arr[0];
	}
	T* end() {
		return &arr[0] + n;
	}
	void push_back(T val) {
		if (n == _size) {
			resize(_size * 2);
			_size *= 2;
		}
		arr[n] = val;
		n++;
	}
	T& operator [](int idx) {
		return arr[idx];
	}
};

struct Node {
	string name;
	int k, e, m;
};
int n;
Vector<Node> arr;
bool cmp(const Node &a, const Node &b) {
	if (a.k == b.k) {
		if (a.e == b.e) {
			if (a.m == b.m) {
				return a.name < b.name;
			}
			return a.m > b.m;
		}
		return a.e < b.e;
	}
	return a.k > b.k;
}
template<class T>
void _swap(T &a, T &b) {
	T t;
	t = a;
	a = b;
	b = t;
}
template<class It, class Cmp>
void _stable_sort(It begin, It end, Cmp cmp) {
	if (begin == end)
		return;
	It mid = begin+(end-begin)/2;
	_stable_sort(begin, mid, cmp);
	_stable_sort(mid+1, end, cmp);

}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char name[101];
		int a, b, c;
		scanf("%s%d%d%d", name, &a, &b, &c);
		string temp = name;
		arr.push_back({ temp,a,b,c });
	}
	sort(arr.begin(), arr.end(), cmp);
	for (int i = 0; i < n; i++)
		cout << arr[i].name << '\n';
}
