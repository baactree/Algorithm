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
	int _size;
	int capacity;
	T *arr;
	_vector() {
		_size = 0;
		capacity = 32;
		arr = new T[capacity];
	}
	_vector(int k) {
		_size = k;
		capacity = k;
		arr = new T[capacity];
	}
	void resize(int k) {
		T *temp;
		temp = new T[k];
		for (int i = 0; i < _size; i++)
			temp[i] = arr[i];
		delete[] arr;
		arr = temp;
		_size=capacity=k;
	}
	int size() const{
		return _size;
	}
	T* begin() const{
		return &arr[0];
	}
	T* end() const{
		return &arr[0] + _size;
	}
	void push_back(T val) {
		if (_size == capacity) {
			resize(_size * 2);
			_size /=2;
		}
		arr[_size++] = val;
	}
	void pop_back() {
		_size--;
	}
	T& operator [](int idx) {
		return arr[idx];
	}
	T operator [](int idx)const{
		return arr[idx];
	}
};
