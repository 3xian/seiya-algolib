#include <iostream>
#include <map>

int main()
{
    using namespace std;

    string a;
    string b;
    cin >> a >> b;

    int bull = 0;
    int cow = 0;
    map<char, int> counter;

    for (int i = 0; i < 4; ++i) {
        if (a[i] == b[i]) {
            ++bull;
        } else {
            ++counter[a[i]];
            ++counter[b[i]];
        }
    }

    for (char c = '0'; c <= '9'; ++c) {
        if (counter[c] == 2) {
            ++cow;
        }
    }

    cout << bull << ' ' << cow;

    return 0;
}
