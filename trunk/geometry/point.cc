const double AES = 1e-10;
const double EPS = 1e-7;
const double PI = acos(-1.0);

class Point;
class Circle;

inline int sgn(double x) { return x<-EPS ? -1 : x>EPS; }

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  bool operator ==(const Point& e) const { return sgn(x-e.x)==0 && sgn(y-e.y)==0; }
  bool operator <(const Point& e) const { return x+EPS<e.x || x<e.x+EPS && y+EPS<e.y; }
  Point operator +(const Point& e) const { return Point(x+e.x, y+e.y); }
  Point operator -(const Point& e) const { return Point(x-e.x, y-e.y); }
  Point operator *(double k) const { return Point(x*k, y*k); }
  Point operator /(double k) const { return Point(x/k, y/k); }
  double norm() const { return x*x + y*y; }
  double len() const { return sqrt(norm()); }
  Point to(double k) const { return (*this) * (k / len()); }
  Point turn_left() { return Point(-y, x); }
  Point turn_right() { return Point(y, -x); }
  bool read() { return scanf("%lf%lf", &x, &y) != EOF; }
  void print() const { printf("%.2f %.2f\n", x, y); }
};

double cross(Point a, Point b) {
  return a.x * b.y - b.x * a.y;
}
double dot(Point a, Point b) {
  return a.x * b.x + a.y * b.y;
}
bool inter(Point a, Point b, Point c, Point d, Point& x) {
  double u=cross(b-a,c-a), v=cross(b-a,d-a); if (sgn(v-u)==0) return false;
  x = Point(c.x*v-d.x*u, c.y*v-d.y*u) / (v-u); return true;
}
Point foot(Point p, Point a, Point b) {
  Point t; inter(p,p+(b-a).turn_left(),a,b,t); return t;
}
bool onseg(Point p, Point a, Point b, bool end=true) {
  return sgn(cross(p-a,p-b))==0 && dot(a-p,b-p)<(end?EPS:-EPS);
}
double p2l(Point p, Point a, Point b) {
  return fabs(cross(p-b,a-b)) / (a-b).len();
}
double p2s(Point p, Point a, Point b) {
  double d = min((p-a).len(), (p-b).len());
  if (onseg(foot(p,a,b),a,b)) mil(d, p2l(p,a,b));
  return d;
}
double s2s(Point p1, Point p2, Point q1, Point q2) {
  return min(min(p2s(p1,q1,q2), p2s(p2,q1,q2)),
             min(p2s(q1,p1,p2), p2s(q2,p1,p2)));
}
bool incircle(Point p, Point a, Point b, Point c) { // ccw
  return cross(c-b,p-b)*a.norm() - cross(c-a,p-a)*b.norm()
      + cross(b-a,p-a)*c.norm() - cross(b-a,c-a)*p.norm() > EPS;
}
