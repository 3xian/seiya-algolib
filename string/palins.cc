void palins(const char* s, int n, int rad[N * 2]) {
	for (int i=0, j=0, k=0; i<2*n; i+=k, j-=k) {
		if (j < 0) j = 0;
		while (i-j>=0 && i+j+1<2*n && s[i-j>>1]==s[i+j+1>>1]) ++j;
		for (rad[i]=j, k=1; i-k>=0 && rad[i]-k>=0 && rad[i-k]!=rad[i]-k; ++k) {
			rad[i+k] = min(rad[i-k], rad[i]-k);
		}
	}
}
