/**
 * ������͹����ά����������������
 * ע��������������������ܻ���ڹ�����
 * ��O(logn)��ѯһ�����Ƿ���͹���ڲ����˰汾�����ڱ��ϣ�
 */

struct Convex
{
    set<Point> p;

    void clear() {
        p.clear();
    }

    void insert(const Point& q) {
        if (cover(q)) return;
        auto pq = p.insert(q).first;
        auto pa = pq;
        ++pa;
        while (pa != p.end()) {
            auto pb = pa;
            ++pb;
            if (pb == p.end()) break;
            if (sgn(cross(*pa - *pq, *pb - *pq)) < 0) break;
            p.erase(pa);
            pa = pb;
        }
        pa = pq;
        if (pa == p.begin()) return;
        --pa;
        while (pa != p.begin()) {
            auto pb = pa;
            --pb;
            if (sgn(cross(*pa - *pq, *pb - *pq)) > 0) break;
            p.erase(pa);
            pa = pb;
        }
    }

    bool cover(const Point& q) const {
        auto pr = p.lower_bound(q);
        if (pr == p.end()) return false;
        if (pr == p.begin()) return sgn(pr->x - q.x) == 0;
        auto pl = pr;
        --pl;
        return sgn(cross(*pl - *pr, q - *pr)) >= 0;
    }
};

struct Hull
{
    Convex uh;
    Convex lh;

    void clear() {
        uh.clear();
        lh.clear();
    }

    void insert(const Point& p) {
        uh.insert(p);
        lh.insert(Point(p.x, -p.y));
    }

    bool is_contain(const Point& p) const {
        return uh.cover(p) && lh.cover(Point(p.x, -p.y));
    }
};
