""" 
x * x = a (mod n), n is prime
if (x < 0) cout << "No root" << endl;
else if (x + x == n) cout << x << endl;
else cout << x << ' ' << n - x << endl;
"""

def x2_eql_a_mod_p(a, p):
    if p == 2:
        return a % p

    if pow(a, (p - 1) / 2, p) == 1:
        if p % 4 == 3:
            x = pow(a, (p + 1) / 4, p)
        else:
            b = 1
            while pow(b, (p - 1) / 2, p) == 1:
                b += 1
            i = (p - 1) / 2
            k = 0
            while 1:
                i /= 2
                k /= 2
                if (pow(a, i, p) * pow(b, k, p) + 1) % p == 0:
                    k += (p - 1) / 2
                if i % 2 == 1:
                    break
            x = pow(a, (i + 1) / 2, p) * pow(b, k / 2, p) % p
        return x
    return -1
