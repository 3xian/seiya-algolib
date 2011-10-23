int pow(ll a, ll k, int p) {
  ll r = 1;
  a %= p;
  while (k > 0) {
    if (k & 1) r = r * a % p;
    if (k > 1) a = a * a % p;
    k >>= 1;
  }
  return r;
}
