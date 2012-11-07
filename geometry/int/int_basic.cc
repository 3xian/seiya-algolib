typedef long long ll;
typedef std::pair<int, int> pii;

pii operator +(pii a, pii b) {
    return pii(a.first + b.first, a.second + b.second);
}

pii operator -(pii a, pii b) {
    return pii(a.first - b.first, a.second - b.second);
}

pii operator *(pii a, int k) {
    return pii(a.first * k, a.second * k);
}

ll operator *(pii a, pii b) {
    return (ll)a.first * b.first + (ll)a.second * b.second;
}

ll operator %(pii a, pii b) {
    return (ll)a.first * b.second - (ll)a.second * b.first;
}

bool is_onsegment(pii p, pii s1, pii s2) {
    return (p - s2) % (s1 - s2) == 0 && (s1 - p) * (s2 - p) <= 0;
}

bool is_inside(pii p, pii a, pii b, pii c) { // ccw
    return (b - a) % (p - a) >= 0 && (c - b) % (p - b) >= 0 && (a - c) % (p - c) >= 0;
}
