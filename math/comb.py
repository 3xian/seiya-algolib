"""
Lucas 定理，组合数取模
"""

fac = []

def init_fac(p):
    f = [1] * (p + 1)
    for i in xrange(1, len(f)):
        f[i] = f[i-1] * i % p
    return f

def comb(n, m, p):
    if m > n:
        return 0
    return fac[n] * pow(fac[m]*fac[n-m], p-2) % p

def lucas(n, m, p):
    if m == 0:
        return 1
    return comb(n%p, m%p, p) * lucas(n/p, m/p, p) % p
