class convex_t
{
	set<point_t> p;
public:
	void clear() { p.clear(); }
	void insert(const point_t& q) {
		if (cover(q)) return;
		itr(p) pq = p.insert(q).first;
		itr(p) pa = pq;
		++pa;
		while (pa != p.end()) {
			itr(p) pb = pa;
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
			itr(p) pb = pa;
			--pb;
			if (sgn(cross(*pa - *pq, *pb - *pq)) > 0) break;
			p.erase(pa);
			pa = pb;
		}
	}
	bool cover(const point_t& q) const {
		itr(p) pr = p.lower_bound(q);
		if (pr == p.end()) return false;
		if (pr == p.begin()) return sgn(pr->x - q.x) == 0;
		itr(p) pl = pr; --pl;
		return sgn(cross(*pl - *pr, q - *pr)) >= 0;
	}
};

class hull_t
{
	convex_t uh;
	convex_t lh;
public:
	void clear() {
		uh.clear();
		lh.clear();
	}
	void insert(const point_t& p) {
		uh.insert(p);
		lh.insert(point_t(p.x, -p.y));
	}
	bool is_contain(const point_t& p) const {
		return uh.cover(p) && lh.cover(point_t(p.x, -p.y));
	}
};
