#include<bits/stdc++.h>
using namespace std;
// Hàm tính ước chung lớn nhất bằng giải thuật Euclid
int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
// Kiểu dữ liệu phân số gồm tử số và mẫu số
struct PHANSO {
    int ts, ms;
};
// hàm khởi tạo phân số
void KhoiTao(PHANSO& ps) {
    ps.ts = 0;
    ps.ms = 1;
}
// Hàm rút gọn phân số 
PHANSO rutgon(PHANSO ps) {
    int ucln = gcd(abs(ps.ts), abs(ps.ms));
    // chia cả tử và mẫu cho ước chung lớn nhất của tử số và mẫu số
    ps.ts /= ucln;
    ps.ms /= ucln;
    // Nếu tử số âm và mẫu số âm thì sẽ cả tử số và mẫu số sẽ dương
    if (ps.ts < 0 && ps.ms < 0) {
        ps.ts = -ps.ts;
        ps.ms = -ps.ms;
    }
    // Nếu mẫu số âm thì chuyển dấu trừ lên tử số
    else if (ps.ms < 0) {
        ps.ts = -ps.ts;
        ps.ms = -ps.ms;
    }
    return ps;
}
// Hàm tính tổng phân số
PHANSO tong(PHANSO ps1, PHANSO ps2) {
    PHANSO tong;
    // Lấy tử số phân số 1 nhân với mẫu số phân số 2 cộng với tử số phân số 2 nhân với mẫu số phân số 1 ta được tử số
    tong.ts = ps1.ts * ps2.ms + ps2.ts * ps1.ms;
    // Lấy 2 mẫu số 2 phân số nhân với nhau ta được mẫu số 
    tong.ms = ps1.ms * ps2.ms;
    // Rút gọn phân số trước khi xuất ra 
    return rutgon(tong);
}
// Hàm tính hiệu 2 phân số 
PHANSO hieu(PHANSO ps1, PHANSO ps2) {
    PHANSO hieu;
    // Lấy tử số phân số 1 nhân với mẫu số phân số 2 trừ cho tử số phân số 2 nhân với mẫu số phân số 1 ta được tử số
    hieu.ts = ps1.ts * ps2.ms - ps2.ts * ps1.ms;
    // Lấy mẫu số 2 phân số nhân với nhau ta được mẫu số
    hieu.ms = ps1.ms * ps2.ms;
    // Rút gọn phân số trước khi xuất ra
    return rutgon(hieu);
}
// Hàm tính tích 2 phân số
PHANSO tich(PHANSO ps1, PHANSO ps2) {
    PHANSO tich;
    // Lấy tử số của 2 phân số nhân với nhau ta được tử số 
    tich.ts = ps1.ts * ps2.ts;
    // Lấy mẫu số của 2 phân số nhân với nhau ta được mẫu số
    tich.ms = ps1.ms * ps2.ms;
    // Rút gọn phân số trước khi xuất ra 
    return rutgon(tich);
}
// Hàm tính thương 2 phân số
PHANSO thuong(PHANSO ps1, PHANSO ps2) {
    // Kiểm tra nếu tử số phân số 2 = 0 thì phân số sẽ vô nghĩa
    if (ps2.ts == 0) {
        cout << "Khong the chia cho so 0." << endl;
        return { 0,1 };
    }
    PHANSO thuong;
    // Lấy tử số của phân số 1 nhân với mẫu số phân số 2 được tử số
    thuong.ts = ps1.ts * ps2.ms;
    // Lấy tử số phân số 2 nhân với mẫu số phân số 1 được mẫu số
    thuong.ms = ps1.ms * ps2.ts;
    // Rút gọn trước khi xuất ra 
    return rutgon(thuong);
}
// Hàm nhập 1 phân số 
void Nhap(PHANSO& ps) {
    cout << "Nhap tu so: ";
    cin >> ps.ts;
    // Kiểm tra điều kiện của mẫu số
    do {
        cout << "Nhap mau so khac 0: ";
        cin >> ps.ms;
    } while (ps.ms == 0);
}
// Hàm xuất 1 phân số 
void xuat(PHANSO& ps) {
    // Nếu mẫu số bằng 1 chỉ xuất ra tử số
    if (ps.ms == 1) cout << ps.ts << endl;
    // Nếu tử số bằng 0 thì xuất ra 0
    else if (ps.ts == 0) cout << 0 << endl;
    else cout << ps.ts << "/" << ps.ms << endl;
}
int main() {
    PHANSO ps1, ps2;
    KhoiTao(ps1);
    KhoiTao(ps2);
    cout << "Nhap phan so thu nhat" << endl;
    Nhap(ps1);
    cout << "Nhap phan so thu hai" << endl;
    Nhap(ps2);
    PHANSO val1 = tong(ps1, ps2);
    PHANSO val2 = hieu(ps1, ps2);
    PHANSO val3 = tich(ps1, ps2);
    cout << "Tong: "; xuat(val1);
    cout << "Hieu: "; xuat(val2);
    cout << "Tich: "; xuat(val3);
    if (ps2.ts != 0) {
        PHANSO val4 = thuong(ps1, ps2);
        cout << "Thuong: "; xuat(val4);
    }
    else cout << "Khong the chia cho 0.";
    return 0;
}

