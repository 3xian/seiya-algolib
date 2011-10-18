struct cmp_y {
  bool operator () (Point *a, Point *b) const {
    return a->y < b->y;
  }
};

double dis(const Point& a, const Point& b) {
  return hypot(a.x - b.x, a.y - b.y);
}

double nearest(Point* p, int n, Point& pa, Point& pb) {
  multiset<Point*, cmp_y> s;
  Point t;
  double d = 1e50;
  sort(p, p + n);
  for (int i = 0, lf = 0; i < n; i++) {
    t.y = p[i].y - d;
    for (; lf < i && p[i].x - p[lf].x >= d; lf++) s.erase(s.find(p + lf));
    for (set<Point*, cmp_y>::iterator it = s.upper_bound(&t); it != s.end() && p[i].y + d > (*it)->y; ++it) {
      double k = dis(p[i], **it);
      if (k < d) {
        d = k;
        pa = p[i];
        pb = **it;
      }
    }
    s.insert(p + i);
  }
  return d;
}
