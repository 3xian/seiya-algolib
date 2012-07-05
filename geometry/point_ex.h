inline double cross_prod(const Point& a, const Point& b) {
  return a.x * b.y - b.x * a.y;
}

inline double cross_prod(const Point& a, const Point& b, const Point& o) {
  return cross_prod(a - o, b - o);
}

inline double dot_prod(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}

double oppo_site(const Point& p1, const Point& p2, const Line& line) {
  return sign(cross_prod(p1, line.first, line.second)) * sign(cross_prod(p2, line.first, line.second)) < 0;
}

Point intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  double s1 = cross_prod(b - a, c - a);
  double s2 = cross_prod(b - a, d - a);
  return Point(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
}

Point foot(const Point& p, const Line& line) {
  return intersect(p, p + (line.second - line.first).turn_left(), line.first, line.second);
}

