// =====================================================================================
// 
//       Filename:  vector.cpp
//        Created:  2017년 04월 06일 23시 19분 16초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;

template <class T>
class _vector {
public:
	int n;
	int _size;
	T *arr;
	_vector() {
		n = 0;
		_size = 32;
		arr = new T[_size];
	}
	_vector(int k) {
		n = k;
		_size = k;
		arr = new T[_size];
	}
	void resize(int k) {
		T *temp;
		temp = new T[k];
		for (int i = 0; i < n; i++)
			temp[i] = arr[i];
		delete[] arr;
		arr = temp;
		n=k;
	}
	int size() const{
		return n;
	}
	T* begin() const{
		return &arr[0];
	}
	T* end() const{
		return &arr[0] + n;
	}
	void push_back(T val) {
		if (n == _size) {
			resize(_size * 2);
			n=_size;
			_size *= 2;
		}
		arr[n] = val;
		n++;
	}
	void pop_back() {
		n--;
	}
	T& operator [](int idx) {
		return arr[idx];
	}
	T operator [](int idx)const{
		return arr[idx];
	}
};
