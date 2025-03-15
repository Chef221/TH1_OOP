#include <iostream>
using namespace std;

// Khởi tạo kiểu dữ liệu phân số bao gồm 2 thành phần là tử số và mẫu số
struct PHANSO {
    int ts, ms;
};

// Hàm tìm ước chung lớn nhất của 2 số nguyên bằng thuật toán Euclid
int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Hàm khởi tạo phân số đầu tiên với tử số bằng 0 và mẫu số bằng 1 để tránh lấy giá trị rác 
void KhoiTao(PHANSO& ps) {
    ps.ts = 0;
    ps.ms = 1;
}

// Hàm rút gọn 1 phân số
void RutGon(PHANSO& ps) {
    // tìm ước chung lớn nhất của tử số và mẫu số
    int uscln = gcd(abs(ps.ts), abs(ps.ms));
    // Chia cả tử và mẫu cho ước chung lớn nhất để có được phân số rút gọn
    if (uscln > 0) {
        ps.ts /= uscln;
        ps.ms /= uscln;
    }
    // Nếu mẫu số âm thì dấu trừ sẽ chuyển lên tử 
    if (ps.ms < 0) {
        ps.ts = -ps.ts;
        ps.ms = -ps.ms;
    }
}
// Hàm nhập 1 phân số với tham số truyền vô là kiểu dữ liệu phân số ta mới tạo
void Nhap(PHANSO& ps) {
    cout << "Nhap tu so: ";
    cin >> ps.ts;
    // người dùng phải nhập mẫu số tới khi nào khác 0 mới cho thoát vòng lặp
    do {
        cout << "Nhap mau so khac 0: ";
        cin >> ps.ms;
    } while (ps.ms == 0);
    RutGon(ps);
}

// hàm xuất 1 phân số 
void Xuat(PHANSO ps) {
    // Nếu mẫu số bằng 1 thì chỉ xuất ra tử số
    if (ps.ms == 1) {
        cout << ps.ts;
    }
    else {
        cout << ps.ts << "/" << ps.ms;
    }
}
int main() {
    PHANSO ps;
    KhoiTao(ps);
    Nhap(ps);
    Xuat(ps);
    return 0;
}


