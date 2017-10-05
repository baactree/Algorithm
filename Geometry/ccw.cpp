// =====================================================================================
// 
//       Filename:  ccw.cpp
//        Created:  2017년 01월 15일 02시 56분 38초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

//원점 기준 b가 a의 반시계 > 0, 시계 < 0, 평행 = 0
int ccw(point a, point b){
	double ret=a.cross(b);
	if(ret<0)
		return -1;
	if(ret>0)
		return 1;
	return 0;
}

//p 기준 b가 a의 반시계 > 0, 시계 < 0, 평행 = 0
int ccw(point p, point a, point b){
	return ccw(a-p, b-p);
}
