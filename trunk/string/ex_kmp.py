def ex_kmp(s):
    length = len(s)
    if length == 0: return []

    pfx = [0] * length
    pfx[0] = length

    if length == 1: return pfx

    for i in xrange(length - 1):
        if s[i] == s[i + 1]:
            pfx[1] += 1
        else:
            break

    k = 1
    for i in xrange(2, length):
        len1 = k + pfx[k]
        len2 = pfx[i - k]
        if len2 < len1 - i:
            pfx[i] = len2
        else:
            j = max(len1 - i, 0)
            while i + j < length and s[j] == s[i + j]:
                j += 1
            pfx[i] = j
            k = i
    return pfx
