/*
  Name: convex_hull_online.cpp
  Copyright: 
  Author: seiya
  Date: 04/04/11 12:19
  Description:
		������͹����ά������������������
		ע��������������������ܻ���ڹ����㡣 
		��O(logn)��ѯһ�����Ƿ���͹���ڲ����˰汾�����ڱ��ϣ���
*/

class Convex {
public:
	void clear() {
		p.clear();
	}
	void insert(const Point& q) {
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
	bool cover(const Point& q) const {
		itr(p) pr = p.lower_bound(q);
		if (pr == p.end()) return false;
		if (pr == p.begin()) return sgn(pr->x - q.x) == 0;
		itr(p) pl = pr; --pl;
		return sgn(cross(*pl - *pr, q - *pr)) >= 0;
	}

private:
	set<Point> p;
};

class Hull {
public:
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

private:
	Convex uh;
	Convex lh;
};
