template<typename T> is_prime(T n) {
    if (n < 2 or n % 2 == 0) {
        return n == 2;
    }
    for (T i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
