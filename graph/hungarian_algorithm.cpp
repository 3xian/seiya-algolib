//#include <algorithm>
//using namespace std;
//const int N = 32;

int left_num;
int right_num;
bool mat[N][N];
bool path[N];
int right_link[N];

bool aug(int i) {
    for (int j = 0; j < right_num; j++) {
        if (mat[i][j] and not path[j]) {
            path[j] = true;
            if (right_link[j] < 0 or aug(right_link[j])) {
                right_link[j] = i;
                return true;
            }
        }
    }
    return false;
}

int hung() {
    int ret = 0;
    fill(right_link, right_link + right_num, -1);
    for (int i = 0; i < left_num; i++) {
        memset(path, 0, right_num);
        if (aug(i)) ret++;
    }
    return ret;
}
