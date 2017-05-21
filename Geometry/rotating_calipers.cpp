// =====================================================================================
// 
//       Filename:  rotating_calipers.cpp
//        Created:  2017년 01월 15일 03시 08분 32초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

double dist(point a, point b){
	return hypot(a.x-b.x, a.y-b.y);
}
double calipus(const vector<point>& p){
	int n = p.size();
	double ret=-1;
	int j=1;
	for(int i=0;i<n;i++){
		int ni=(i+1)%n;
		while(true){
			int nj=(j+1)%m;
			if(ccw(hull[ni]-hull[i], hull[nj]-hull[j])<0)
				j=nj;
			else
				break;
		}
		ret=max(ret, dist(hull[i], hull[j]));
	}
	return ret;
}
