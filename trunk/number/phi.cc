/**
 * [1..n)中与n互质的数的个数; 该函数能正确处理phi(1)=1
 * 互质数求和为phi(n)*n/2
 */
int phi(int n) {
    int ret = 1;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            n /= i;
            ret *= i - 1;
            while (n % i == 0) {
                n /= i;
                ret *= i;
            }
        }
    }
    if (n > 1) {
        ret *= n - 1;
    }
    return ret;
}
