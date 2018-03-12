// O(nlgn) convex hull
vector<point> graham(vector<point>& input){
	int n = input.size();
	vector<point> hull;
	vector<point> up(n), down(n);
	int iup, idown;
	iup = idown = -1;
	sort(input.begin(),  input.end());
	for(int i=0;i<n;i++){
		while(iup>0&&ccw(up[iup-1], up[iup], input[i])>=0)
			iup--;
		up[++iup]=input[i];
		while(idown>0&&ccw(down[idown-1], down[idown], input[i])<=0)
			idown--;
		down[++idown]=input[i];
	}
	for(int i=0;i<=iup;i++)
		hull.push_back(up[i]);
	for(int i=idown-1;i>0;i--)
		hull.push_back(down[i]);
	return hull;
}
