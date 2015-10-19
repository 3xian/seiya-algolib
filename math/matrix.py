class Matrix(object):

    def __init__(self, row_size, col_size, data):
        self.row_size = row_size
        self.col_size = col_size
        self.data = data[:]

    def __mul__(self, other):
        row_size, col_size = self.row_size, other.col_size
        product = Matrix(row_size, col_size, [0]*row_size*col_size)
        for i in xrange(row_size):
            for j in xrange(col_size):
                for k in xrange(self.col_size):
                    product.data[col_size*i + j] += self.get(i, k) *  other.get(k, j)
        return product

    def __pow__(self, k, mod):
        from copy import deepcopy
        pd, pw = deepcopy(self), self
        k -= 1
        while k > 0:
            if k % 2 == 1:
                pd = pd.mulmod(pw, mod)
            if k > 1:
                pw = pw.mulmod(pw, mod)
            k /= 2
        return pd

    def __repr__(self):
        lines = []
        for i in xrange(self.row_size):
            lines.append(' '.join(map(str, self.data[self.col_size*i:self.col_size*(i+1)])))
        return '\n'.join(lines)

    def mulmod(self, other, mod):
        pd = self * other
        for i in xrange(len(pd.data)):
            pd.data[i] %= mod
        return pd

    def get(self, row, col):
        return self.data[self.col_size*row + col]

