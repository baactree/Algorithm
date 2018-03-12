
point RotateCCW90(point p)   { return point(-p.y,p.x); }

vector<point> CircleCircleIntersection(point a, point b, double r, double R) {
  vector<point> ret;
  double d = (a-b).norm();
  if (d > r+R || d+min(r, R) < max(r, R)) return ret;
  double x = (d*d-R*R+r*r)/(2*d);
  double y = sqrt(r*r-x*x);
  point v = (b-a)/d;
  ret.push_back(a+v*x + RotateCCW90(v)*y);
  if (y > 0)
    ret.push_back(a+v*x - RotateCCW90(v)*y);
  return ret;
}