#include<iostream>
#include<vector>
#define REP(i, n) for (int i = 0, i##_len = (n); i < i##_len; ++i)

int abs(int a) {
    if (a > 0) return a;
    else return -a;
}

int main() {
    int N;

    std::cin >> N;
    std::vector<int> x(N);
    std::vector<int> y(N);

    REP(i, N) {
        std::cin >> x[i] >> y[i];
    }

    int count = 0;
    REP(i, N) {
        REP(j, i) {
            int xi = x[i];
            int yi = y[i];

            int xj = x[j];
            int yj = y[j];

            int katamuki = abs(yi - yj) / abs(xi - xj);
            int amari = abs(yi - yj) % abs(xi - xj);

            if (abs(katamuki) == 1 && amari != 0) {
                continue;
            }

            if (-1 <= katamuki && katamuki <= 1) {
                count += 1;
            }
        }
    }
    std::cout << count << std::endl;
}