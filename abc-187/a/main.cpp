#include<iostream>

int sum_keta(int a) {
    int sum = 0;
    while (a != 0) {
        sum += a % 10;
        a /= 10;
    }
    return sum;
}

int larger(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main() {
    int a,b;
    std::cin >> a >> b;

    a = sum_keta(a);
    b = sum_keta(b);
    std::cout << larger(a,b) << std::endl;

}