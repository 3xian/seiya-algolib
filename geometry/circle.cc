struct Circle
{
    Point o;
    double r;

    Circle() {
    }

    Circle(const Point &_o, double _r)
        : o(_o), r(_r) {
    }

    bool is_inside(const Circle &rhs) const {
        return (o - rhs.o).len() + r < rhs.r + EPS;
    }

    vector<Point> intersect(const Circle &rhs) const {
        vector<Point> p;
        double d = (o - rhs.o).len();
        if (d < EPS) {
            return p;
        }
        double t = (d + (sqr(r) - sqr(rhs.r)) / d) * 0.5;
        if (r - t < -EPS) {
            return p;
        }
        double h = sqrt(fabs(sqr(r) - sqr(t)));
        Point v = rhs.o - o;
        p.push_back(o + v.scale(t) + v.turn_right().scale(h));
        if (h > EPS) {
            p.push_back(o + v.scale(t) + v.turn_left().scale(h));
        }
        return p;
    }
};
