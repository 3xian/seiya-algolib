def phi(n):
    res = 1
    for i in xrange(2, int((n+0.5)**0.5) + 1):
        if n % i == 0:
            n /= i
            res *= i - 1
            while n % i == 0:
                n /= i
                res *= i
    if n > 1:
        res *= n - 1
    return res
