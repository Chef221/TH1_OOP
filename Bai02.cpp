#include<iostream>
using namespace std;

struct PHANSO {
    int ts, ms;
};
// Hàm khởi tạo phân số 
void KhoiTao(PHANSO& ps) {
    ps.ts = 0;
    ps.ms = 1;
}
// Hàm nhập 1 phân số
void Nhap(PHANSO& ps) {
    cout << "Nhap tu so: ";
    cin >> ps.ts;
    // nhập đến khi nào mẫu số khác 0 mới thoát vòng lặp
    do {
        cout << "Nhap mau so khac 0: ";
        cin >> ps.ms;
    } while (ps.ms == 0);
}
// Hàm xuất phân số
void Xuat(PHANSO ps) {
    // Nếu mâu số âm thì chuyển dấu trừ lên tử số
    if (ps.ms < -1) {
        cout << -ps.ts << "/" << -ps.ms;
    }
    // Nếu mẫu số bằng -1 thì xuất ra số đối của tử số
    else if (ps.ms == -1) {
        cout << -ps.ts;
    }
    // Nếu tử số bằng 1 thì chỉ xuất ra tử số
    else if (ps.ms == 1) {
        cout << ps.ts;
    }
    else cout << ps.ts << "/" << ps.ms << endl;
}
// Hàm so sánh 2 phân số 
void SoSanh(PHANSO ps1, PHANSO ps2) {
    // Tìm mẫu số chung của 2 phân số
    int msc = ps1.ms * ps2.ms;
    // Ta nhân chéo tử số và mẫu số của 2 phân số để dùng cho việc so sánh
    int ts1 = ps1.ts * ps2.ms;
    int ts2 = ps2.ts * ps1.ms;
    if (ts1 > ts2) {
        cout << "Phan so lon hon la phan so thu nhat: ";
        Xuat(ps1);
    }
    else if (ts1 < ts2) {
        cout << "Phan so lon hon la phan so thu hai: ";
        Xuat(ps2);
    }
    else {
        cout << "Hai phan so nay bang nhau: ";
        Xuat(ps1);
    }
}

int main() {
    PHANSO ps1, ps2;
    KhoiTao(ps1);
    KhoiTao(ps2);
    Nhap(ps1);
    Nhap(ps2);
    SoSanh(ps1, ps2);
    return 0;
}
