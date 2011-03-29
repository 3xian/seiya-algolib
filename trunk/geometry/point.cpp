const double EPS = 1e-7;

typedef complex<double> point_t;
#define x(a) real(a)
#define y(a) imag(a)
bool operator < (const point_t& a, const point_t& b) { return x(a) + EPS < x(b) || x(a) < x(b) + EPS && y(a) + EPS < y(b); }
double dot(const point_t& a, const point_t& b) { return x(conj(a) * b); }
double cross(const point_t& a, const point_t& b) { return y(conj(a) * b); }
