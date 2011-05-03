struct Triangle {
    Point a;
    Point b;
    Point c;

    Triangle() {}
    Triangle(const Point& _a, const Point& _b, const Point& _c) : a(_a), b(_b), c(_c) {}

    double area() const {
        return fabs(cross(a - c, b - c)) / 2.0;
    }
    // 外心
    Point circumcenter() {
        Point p[5];
        perpendicular_bisector(a, b, p[0], p[1]);
        perpendicular_bisector(b, c, p[2], p[3]);
        intersect(p[0], p[1], p[2], p[3], p[4]);
        return p[4];
    }
    // 内心
    Point incenter() {
        Point u1 = a, u2, v1 = b, v2, x;
        double t1 = (atan2(b.y - a.y, b.x - a.x) + atan2(c.y - a.y, c.x - a.x)) / 2.0;
        double t2 = (atan2(a.y - b.y, a.x - b.x) + atan2(c.y - b.y, c.x - b.x)) / 2.0;
        u2 = Point(u1.x + cos(t1), u1.y + sin(t1));
        v2 = Point(v1.x + cos(t2), v1.y + sin(t2));
        intersect(u1, u2, v1, v2, x);
        return x;
    }
    // 垂心
    Point orthocenter() {
        Point u(c.x - a.y + b.y, c.y + a.x - b.x);
        Point v(b.x - a.y + c.y, b.y + a.x - c.x);
        Point x;
        intersect(c, u, b, v, x);
        return x;
    }
    // 重心
    // 1) 到三个顶点距离的平方和最小
    // 2) 到三边距离之积最大
    Point centroid() const {
        return (a + b + c) / 3.0;
    }
};
