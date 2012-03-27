/**
 * @brief   count coprimes in [1, n]
 * @note    1) it is true that phi(1) = 1 by definition
 *          2) sum(coprimes) = phi(n) * n / 2 (except n = 1)
 */
int phi(int n) {
	int rez = 1;
	for (int i = 2; (long long)i * i <= n; i++) {
		if (n % i == 0) {
			n /= i;
            rez *= i - 1;
			while (n % i == 0) {
                n /= i;
                rez *= i;
            }
		}
    }
	if (n > 1) {
        rez *= n - 1;
    }
	return rez;
}
