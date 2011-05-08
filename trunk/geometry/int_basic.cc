ll cross(const pii& a, const pii& b) {
    return (ll)a.first * b.second - (ll)b.first * a.second;
}
ll dot(const pii& a, const pii& b) {
    return (ll)a.first * b.first + (ll)a.second * b.second;
}
bool is_onsegment(const pii& p, const pii& s1, const pii& s2) {
    return cross(p - s2, s1 - s2) == 0 && dot(s1 - p, s2 - p) <= 0;
}
