template<typename T> is_prime(T n) {
    if (n < 2) {
        return false;
    }
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename T> void usort(vector<T>& x) {
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
}
