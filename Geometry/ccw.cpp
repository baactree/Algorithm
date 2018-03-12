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
