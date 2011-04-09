// É¸ËØÊı[1..n]

bool mk[N + 1];
int pr[N + 1];

int prime(int n) {
	//memset(mk, 0, sizeof mk);
	if (n < 0) {
		return 0;
	}
	mk[0] = true;
	if (n == 0) {
		return 0;
	}
	mk[1] = true;
	int cnt = 0;
	for (int i = 2; i <= n; i++) {
		if (!mk[i])
			pr[cnt++] = i;
		for (int j = 0; j < cnt && pr[j] <= n / i; j++) {
			mk[i * pr[j]] = true;
			if (i % pr[j] == 0)
				break;
		}
	}
	return cnt;
}
