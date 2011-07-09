struct Circle
{
  Point o;
  double r;

  Circle() {
  }

  Circle(const Point& o, double r)
    : o(o), r(r) {
  }

  bool inside(const Circle& rhs) const {
    return (o - rhs.o).len() + r < rhs.r + EPS;
  }

  vector<Point> intersect(const Circle& rhs) const {
    vector<Point> p;
    double d = (o - rhs.o).len();
    if (d < EPS) return p;
    double t = (d + (sqr(r) - sqr(rhs.r)) / d) * 0.5;
    if (r - t < -EPS) return p;
    double h = sqrt(max(sqr(r) - sqr(t), 0.0));
    Point v = rhs.o - o;
    p.push_back(o + v.scale(t) + v.turn_right().scale(h));
    if (h > EPS) {
      p.push_back(o + v.scale(t) + v.turn_left().scale(h));
    }
    return p;
  }
};

bool Point::inside(const Circle& c, bool border) const {
  return (*this - c.o).len() < (border ? c.r + EPS : c.r - EPS);
}
