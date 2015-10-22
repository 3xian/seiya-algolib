def euclid(a, b):
    if b == 0:
        return a, 1, 0
    d, y, x = euclid(b, a % b)
    return d, x, y-a/b*x

def chinese_remainder(divisors, remainders):
    m = reduce(lambda x, y: x*y, divisors)
    res = 0
    for i in xrange(len(divisors)):
        mi = m / divisors[i]
        _, x, _ = euclid(mi, divisors[i])
        res = (res + mi * x * remainders[i]) % m
    return (res + m) % m
