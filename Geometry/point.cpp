// =====================================================================================
// 
//       Filename:  point.cpp
//        Created:  2017년 01월 15일 02시 43분 36초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

const double PI = 2.0 * acos(0.0);

struct point{
	double x, y;
	explicit point(double x = 0, double y = 0) :x(x), y(y) {}
	bool operator == (const point& rhs)const {
		return x == rhs.x&&y == rhs.y;
	}
	bool operator < (const point& rhs)const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	point operator + (const point&rhs)const {
		return point(x + rhs.x, y + rhs.y);
	}
	point operator - (const point&rhs)const {
		return point(x - rhs.x, y - rhs.y);
	}
	point operator * (int rhs)const {
		return point(x*rhs, y*rhs);
	}
	// 벡터의 길이
	double norm() const {
		return hypot(x,y);
	}
	// 단위 벡터
	point normalize() const {
		return point(x / norm(), y / norm());
	}
	// x축의 양의 방 향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	double polar() const {
		return fmod(atan2(y, x)+2*PI, 2*PI);
	}
	//내적
	double dot(const point&rhs)const {
		return x*rhs.x + y*rhs.y;
	}
	//외적
	double cross(const point&rhs)const {
		return x*rhs.y - rhs.x*y;
	}
};

//수직이등분선 <점,방향벡터>
pair<point, point> perpendicular_bisector(const point &a, const point &b) {
	point c = b - a;
	return make_pair(point((a.x + b.x) / 2, (a.y + b.y) / 2), point(c.y, -c.x));
}
//두 직선의 교점 리턴
point intersection_point(const point &a, const point &b, const point &c, const point &d) {
	double det = b.cross(d);
	return a + b*((c - a).cross(d) / det);
}
//세 점의 외접원의 중점 구하기
point circumscribed_circle(const point &p, const point &a, const point &b) {
	pair<point, point> pa = perpendicular_bisector(p, a);
	pair<point, point> pb = perpendicular_bisector(p, b);
	return intersection_point(pa.first, pa.second, pb.first, pb.second);
}