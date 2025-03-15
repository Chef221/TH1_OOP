#include<bits/stdc++.h>
using namespace std;
// Khởi tạo kiểu dữ liêu học sinh bao gồm: tên, điểm Toán, điểm Văn, điểm Anh
struct HOCSINH {
    string ten;
    double Toan, Van, Anh;
};
// Khởi tạo kiểu dữ liêu mảng học sinh bao gồm: số lượng học sinh và con trỏ mang kiểu học sinh
struct MANGHOCSINH {
    HOCSINH* hs;
    int n;
};
// Hàm kiểm tra tên 
bool checkTen(string ten) {
    // Nếu tên không chứa ký tự thì sẽ trả về false
    for (int i = 0; i < ten.size(); i++) {
        if (!isalpha(ten[i]) && ten[i] != ' ') return false;
    }
    return true;
}
// Hàm chuẩn hóa tên
void ChuanHoaTen(string& ten) {
    // Sử dụng stringstream để tách các từ trong tên ra 
    stringstream ss(ten);
    string res = "", word;
    while (ss >> word) {
        // Chữ cái đầu tiên phải luôn ghi in hoa
        word[0] = toupper(word[0]);
        // Các chữ cái tiếp theo ghi in thường
        for (int i = 1; i < word.size(); i++) {
            word[i] = tolower(word[i]);
        }
        // Cập nhật từng từ vào một biến tạm
        res += word + " ";
    }
    // Xóa dấu cách cuối cùng vì res += word + " " sẽ dư dấu cách cuối
    res.pop_back();
    // gán lại biến tạm vào tên
    ten = res;
}
// Hàm check điểm
bool checkDiem(double diem) {
    // Nếu điểm nhỏ hơn 0 hoặc lớn 10 là sai
    if (diem < 0 || diem > 10) return false;
    return true;
}
// Hàm nhập học sinh
void Nhap(HOCSINH& hs) {
    // Nhập tên cùng với kiểm tra điều kiện
    do {
        cout << "Nhap ten cua hoc sinh: ";
        getline(cin, hs.ten);
        ChuanHoaTen(hs.ten);
    } while (!checkTen(hs.ten));
    // Nhập điểm cùng với kiểm tra điều kiện
    do {
        cout << "Nhap diem Toan, Van, Anh cua hoc sinh: ";
        cin >> hs.Toan >> hs.Van >> hs.Anh;
    } while (!checkDiem(hs.Toan) || !checkDiem(hs.Van) || !checkDiem(hs.Anh));
    // cin.ignore() để tránh bị nhập xót dữ liệu
    cin.ignore();
}
// Hàm nhập danh sách học sinh
void Nhap(MANGHOCSINH& mhs) {
    // Nhập số lượng học sinh và kiểm tra điều kiện phải dương
    do {
        cout << "Nhap so hoc sinh: ";
        cin >> mhs.n;
    } while (mhs.n <= 0);
    cin.ignore();
    // Khởi tạo vùng nhớ cho danh sách học sinh
    mhs.hs = new HOCSINH[mhs.n];
    // Duyệt vòng lặp nhập từng học sinh
    for (int i = 0; i < mhs.n; i++) {
        Nhap(mhs.hs[i]);
    }
}
// Hàm tính điểm trung bình bằng công thức của đề bài 
double DiemTB(HOCSINH& hs) {
    double kq = 0.0;
    kq = ((2 * hs.Toan) + hs.Van + hs.Anh) / 4.0;
    return kq;
}
// Hàm phân loại học sinh theo yêu cầu của đề bài
void PhanLoaiHocSinh(HOCSINH& hs) {
    double result = DiemTB(hs);
    if (result >= 9) cout << "Dat loai Xuat Sac" << endl;
    else if (result >= 8 && result < 9) cout << "Dat loai Gioi" << endl;
    else if (result >= 6.5 && result < 8) cout << "Dat loai Kha" << endl;
    else if (result >= 5 && result < 6.5) cout << "Dat loai Trung Binh" << endl;
    else cout << "Dat loai kem" << endl;
}
// Hàm tìm học sinh có điểm trung bình cao nhất
HOCSINH TimMax(MANGHOCSINH& mhs) {
    // gán học sinh đầu tiên trong danh sách có điểm trung bình cao nhất
    HOCSINH  maxHS = mhs.hs[0];
    // Duyệt qua danh sách học sinh và kiểm tra nếu học sinh nào có điểm trung bình cao hơn điểm trung bình của học sinh cao nhất hiện tại thì cập nhật lại học sinh đó
    for (int i = 1; i < mhs.n; i++) {
        if (DiemTB(mhs.hs[i]) > DiemTB(maxHS)) {
            maxHS = mhs.hs[i];
        }
    }
    return maxHS;
}
// Hàm kiểm tra xem từ khóa có xuất hiện trong tên hay không
bool check(string str, string sub) {
    // Dùng stringstream để tách từng từ trong tên 
    stringstream ss(str);
    string word;
    while (ss >> word) {
        // kiểm tra xem sub có xuất hiện trong từ hiện tại không
        // string ::npos là một hằng số đặc biệt cso giá trị là -1 được sử dụng khi một vị trí không hợp lệ hoặc không tìm thấy được trả về
        if (word.find(sub) != string::npos) return true;
    }
    return false;
}
// hàm tìm kiếm học sinh truyền vào tham số TuKhoa để tìm kiếm
void TimKiem(MANGHOCSINH& mhs, string TuKhoa) {
    cout << "Ket qua tim kiem hoc sinh theo tu khoa \"" << TuKhoa << "\":" << endl;
    // Khởi tạo một biến bool để kiểm tra có tìm thấy hay không
    bool ok = false;
    // Duyệt qua danh sách học sinh và tìm nếu TuKhoa trung voi tên học sinh thì xuất ra thông tin của học sinh đó 
    for (int i = 0; i < mhs.n; i++) {
        if (check(mhs.hs[i].ten, TuKhoa)) {
            cout << "Hoc sinh: " << mhs.hs[i].ten << " | Toan: " << mhs.hs[i].Toan << " | Van: " << mhs.hs[i].Van << " | Anh: " << mhs.hs[i].Anh << endl;
            // Cập nhật đã tìm thấy 
            ok = true;
        }
    }
    // Nếu không tìm thấy xuất ra không tìm thấy học sinh nào
    if (!ok) {
        cout << "Khong tim thay hoc sinh nao!" << endl;
    }
}
// Hàm tìm điểm toán thấp nhất
void TimToanThapNhat(MANGHOCSINH& mhs) {
    // Cho học sinh đầu danh sách có điểm toán thấp nhất
    double minToan = mhs.hs[0].Toan;
    // Duyệt qua danh sách và kiểm tra điều kiện nếu học sinh nào có điểm toán thấp hơn điểm toán học sinh thấp nhất này thì cập nhật lại
    for (int i = 1; i < mhs.n; i++) {
        if (mhs.hs[i].Toan < minToan) {
            minToan = mhs.hs[i].Toan;
        }
    }
    cout << "\nDanh sach hoc sinh co diem Toan thap nhat (" << minToan << "):\n";
    // Duyệt qua danh sách kiểm tra học sinh nào có điểm toán bằng điểm toán thấp nhất trong danh sách thì xuất ra thông tin học sinh đó
    for (int i = 0; i < mhs.n; i++) {
        if (mhs.hs[i].Toan == minToan) {
            cout << "- " << mhs.hs[i].ten << " | Toan: " << mhs.hs[i].Toan << " | Van: " << mhs.hs[i].Van << " | Anh: " << mhs.hs[i].Anh << endl;
        }
    }
}
int main() {
    MANGHOCSINH mhs;
    Nhap(mhs);
    cout << "Danh sach hoc sinh va xep loai:\n";
    for (int i = 0; i < mhs.n; i++) {
        cout << "Hoc sinh: " << mhs.hs[i].ten << ", DTB: " << DiemTB(mhs.hs[i]) << " - ";
        PhanLoaiHocSinh(mhs.hs[i]);
    }
    HOCSINH gioinhat = TimMax(mhs);
    cout << "Hoc sinh co diem cao nhat: " << gioinhat.ten << " (DTB: " << DiemTB(gioinhat) << ")\n";
    string TuKhoa;
    cout << "Nhap tu khoa tim kiem: ";
    getline(cin, TuKhoa);
    TimKiem(mhs, TuKhoa);
    TimToanThapNhat(mhs);
    delete[] mhs.hs;
    return 0;
}
