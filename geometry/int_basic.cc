pii operator * (const pii &a, const int &k) {
    return pii(a.first * k, a.second * k);
}
ll operator * (const pii &a, const pii &b) {
    return (ll)a.first * b.first + (ll)a.second * b.second;
}
ll operator % (const pii &a, const pii &b) {
    return (ll)a.first * b.second - (ll)a.second * b.first;
}
bool is_onsegment(const pii &p, const pii &s1, const pii &s2) {
    return (p - s2) % (s1 - s2) == 0 & &(s1 - p) * (s2 - p) <= 0;
}
