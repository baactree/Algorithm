// =====================================================================================
// 
//       Filename:  rotating_calipers.cpp
//        Created:  2017년 01월 15일 03시 08분 32초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

double calipus(const vector<point>& p){
	int n = p.size();

	int left = min_element(p.begin(), p.end())-p.begin();
	int right = max_element(p.begin(), p.end())-p.begin();

	point calipersA(0,1);
	double ret = (p[right]-p[left]).norm();

	vector<point> toNext(n);
	for(int i=0;i<n;i++)
		toNext[i]=(p[(i+1)%n]-p[i]).normalize();

	int a = left, b = right;
	while(a != right || b != left){
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if(a != right && (costThetaA > costThetaB || b == left)){
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = toNext[b] * (-1);
			b = (b + 1) % n;
		}
		ret = max(ret, (p[a]-p[b]).norm());
	}
	return ret;
}
