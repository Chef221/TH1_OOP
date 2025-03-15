#include <iostream>
#include <cmath>
using namespace std;
// Hàm tính giai thừa của 1 số tự nhiên bằng vòng lặp
long long giaithua(int n) {
    // Khởi tạo giá trị kết quả ban đầu bằng 0
    long long gt = 1;
    // Duyệt vòng lặp và cập nhật giá trị kết quả
    for (int i = 2; i <= n; i++) {
        gt *= i;
    }
    return gt;
}
// hàm tính sin(x) theo công thức của đề bài 
double sin_x(double x) {
    double sinX = 0.0;
    int n = 0;
    // Khởi tạo một biến tạm để tính kết quả trước khi cập nhật vào kết quả cuối cùng
    double tmp;
    do {
        // Tính theo công thức tổng quát của đề bài 
        tmp = pow(-1, n) * pow(x, 2 * n + 1) / giaithua(2 * n + 1);
        // Cập nhật biến kết quả sau mỗi lần lặp
        sinX += tmp;
        // Tăng biến đếm lên để tiếp tục vòng lặp
        n++;
    } while (abs(tmp) >= 0.00001);
    // Điều kiện vòng lặp là độ chính xác 0.00001
    return sinX;
}
int main() {
    double x;
    cout << "Nhap x: ";
    cin >> x;
    double result = sin_x(x);
    cout << "Gia tri sin(" << x << "): " << result << endl;
    return 0;
}

