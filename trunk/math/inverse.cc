ll inverse(ll a, ll m) {
    ll b = m, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return (u % m + m) % m;
}
