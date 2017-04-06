// =====================================================================================
// 
//       Filename:  queue.cpp
//        Created:  2017년 04월 06일 23시 22분 05초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;

template <class T>
class _queue {
public:
	struct Node {
		T val;
		Node *next;
		Node() {}
		Node(T val) :val(val), next(0){}
	};
	Node *head;
	Node *tail;
	int _size;
	_queue() {
		head = tail = 0;
		_size = 0;
	}
	void push(T val) {
		Node *temp = new Node(val);
		if (head == 0)
			head = tail = temp;
		else {
			tail->next = temp;
			tail = temp;
		}
		_size++;
	}
	void pop() {
		Node *temp = head;
		head = head->next;
		delete temp;
		_size--;
	}
	bool empty() const{
		return _size == 0;
	}
	T front() const{
		return head->val;
	}
	T back() const{
		return tail->val;
	}
	int size() const{
		return _size;
	}
};
