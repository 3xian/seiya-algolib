def gauss(mat):
    n = len(mat)
    for i in xrange(n):
        p = i
        for j in xrange(i + 1, n):
            if abs(mat[j][i]) > abs(mat[p][i]):
                p = j
        if p != i:
            mat[i], mat[p] = mat[p], mat[i]
        for j in xrange(i + 1, n):
            t = mat[j][i] / mat[i][i]
            for k in xrange(i, n + 1):
                mat[j][k] -= mat[i][k] * t
    x = [0.0] * n
    for i in xrange(n - 1, -1, -1):
        t = mat[i][n]
        for j in xrange(i + 1, n):
            t -= mat[i][j] * x[j]
        x[i] = t / mat[i][i]
    return x
