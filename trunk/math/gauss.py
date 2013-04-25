from fractions import gcd

def lcm(a, b):
    return a / gcd(a, b) * b

def gaussian_elimination(m):
    rows = len(m)
    cols = len(m[0])

    r = 0
    c = 0
    while r < rows and c + 1 < cols:
        t = r
        for i in xrange(r + 1, rows):
            t = i if abs(m[i][c]) > abs(m[t][c]) else t
        m[r], m[t] = m[t], m[r]

        if m[r][c] == 0:
            c += 1
            continue

        for i in xrange(r + 1, rows):
            if m[i][c] != 0:
                l = lcm(m[i][c], m[r][c])
                x, y = abs(l/m[i][c]), abs(l/m[r][c])
                if m[i][c] * m[r][c] < 0:
                    y = -y
                for j in xrange(c, cols):
                    m[i][j] = m[i][j] * x - m[r][j] * y

        r += 1
        c += 1

    for i in xrange(r, rows):
        if m[i][c] != 0:
            return 'no solution'

    return 'some solutions'
