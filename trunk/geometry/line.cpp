// 直线交点
bool intersect(const Point& a, const Point& b, const Point& c, const Point& d,
		Point& x) {
	double s1 = cross(b - a, c - a);
	double s2 = cross(b - a, d - a);
	if (sgn(s2 - s1) == 0) {
		return false;
	} else {
		x = Point(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
		return true;
	}
}
// 中垂线
// q1为p1p2中点, q2在向量p1p2左边
void perpendicular_bisector(const Point& p1, const Point& p2, Point &q1,
		Point &q2) {
	q1 = (p1 + p2) / 2;
	q2 = q1 + (p2 - p1).turn_left();
}
