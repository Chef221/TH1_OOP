#include <bits/stdc++.h>
using namespace std;
/* Khởi tạo kiểu dữ liệu ChuyenBay với các thành phần:
- Mã chuyến bay
- Ngày, tháng, năm, giờ, phút khởi hành
- Nơi đi, nơi đến
*/
struct ChuyenBay {
    string maCB;
    int ngay, thang, nam, gio, phut;
    string noiDi, noiDen;
};
// Kiểu dữ liệu danh sách chuyến bay với số lượng chuyến bay và con trỏ kiểu dứ liệu ChuyenBay
struct DANHSACHCHUYENBAY {
    int n;
    ChuyenBay* cb;
};

// Kiểm tra mã chuyến bay hợp lệ (mã có nhiều nhất 5 ký tự và không chứa ký tự đặc biệt)
bool checkmaCB(string& maCB) {
    if (maCB.size() > 5) return false;
    for (char c : maCB) {
        if (!isalnum(c)) return false;
    }
    return true;
}

// Kiểm tra ngày hợp lệ 
bool checkNgayThangNam(int ngay, int thang, int nam) {
    // kiểm tra ngày và tháng không hợp lệ
    if (thang < 1 || thang > 12 || ngay < 1) return false;
    // Đếm số ngày trong từng tháng
    int DemSoNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // Kiểm tra năm nhuận (năm nhuận nếu năm đó chia hết cho 400 hoặc chia hết cho 4 và không chia hết cho 100)
    bool NamNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
    // Nếu năm nhuận thì cập nhật lại tháng 2 có 29 ngày
    if (NamNhuan) DemSoNgayTrongThang[1] = 29;
    return ngay <= DemSoNgayTrongThang[thang - 1];
}

// Kiểm tra giờ hợp lệ
bool checkGioPhut(string time, int& gio, int& phut) {
    // Chuỗi ngày giờ có định dạng hh:mm nến có hơn 5 ký tự và ký tự thứ 3 không phải là ":" là sai
    if (time.size() != 5 || time[2] != ':') return false;
    // Tách giờ bằng hàm substr cắt từ vị trí đầu tiên đến vị trí trước dấu chấm
    string gioStr = time.substr(0, 2);
    // Tách phút bằng hàm substr cắt từ vị trí sau dấu chấm đến cuối chuỗi
    string phutStr = time.substr(3, 2);
    // Nếu chuỗi giờ và phút không phải ký số thì trả về false
    if (!isdigit(gioStr[0]) || !isdigit(gioStr[1]) || !isdigit(phutStr[0]) || !isdigit(phutStr[1])) return false;
    // đưa chuỗi giờ và phút về kiểu dữ liệu int bằng hàm stoi (string to interger)
    gio = stoi(gioStr);
    phut = stoi(phutStr);
    // giờ phải nằm trong (0,24) và phút phải nằm trong khoảng (0,60)
    return (gio >= 0 && gio < 24) && (phut >= 0 && phut < 60);
}

// Kiểm tra nơi đi/nơi đến hợp lệ
bool checkPlace(string& place) {
    // Nếu nơi đi và nơi đến không phải ký tự thì trả về false
    for (char c : place) {
        if (!isalpha(c) && c != ' ') return false;
    }
    // Độ dài chuỗi tối đa là 20
    return place.size() <= 20;
}

// Chuẩn hóa tên (nơi đi, nơi đến)
void ChuanHoa(string& s) {
    // Dùng stringstream để tách các từ trong chuỗi
    stringstream ss(s);
    string res = "", word;
    while (ss >> word) {
        // Chữ cái đầu in hoa
        word[0] = toupper(word[0]);
        // Các chữ cái còn lại in thường
        for (int i = 1; i < word.size(); i++) {
            word[i] = tolower(word[i]);
        }
        res += word + " ";
    }
    // xóa dấu cách cuối cùng (do res += word + " " dư 1 dấu cách cuối chuỗi) 
    s = res.substr(0, res.size() - 1);
}

// Hàm chuẩn hóa mã (mã phải ghi in hoa)
string ChuanHoaMa(string& s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}
// Nhập thông tin một chuyến bay
void NhapChuyenBay(ChuyenBay& cb) {
    // Nhập mã chuyến bay và kiểm tra điều kiện
    do {
        cout << "Nhap ma chuyen bay: ";
        cin >> cb.maCB;
        ChuanHoaMa(cb.maCB);
    } while (!checkmaCB(cb.maCB));
    // Nhập thời gian khởi hành và kiểm tra điều kiện
    do {
        cout << "Nhap ngay bay (dd/mm/yyyy): ";
        string date;
        cin >> date;
        stringstream ss(date);
        string word;
        getline(ss, word, '/'); cb.ngay = stoi(word);
        getline(ss, word, '/'); cb.thang = stoi(word);
        getline(ss, word); cb.nam = stoi(word);
    } while (!checkNgayThangNam(cb.ngay, cb.thang, cb.nam));
    string time;
    // Nhập ngày giờ bay và kiểm tra điều kiện
    do {
        cout << "Nhap gio bay (hh:mm): ";
        cin >> time;
    } while (!checkGioPhut(time, cb.gio, cb.phut));
    // cin.ignore() để tránh nhập xót dữ liệu
    cin.ignore();
    // Nhập nơi đi, nơi đến và kiểm tra điều kiện
    do {
        cout << "Nhap noi di: ";
        getline(cin, cb.noiDi);
        ChuanHoa(cb.noiDi);
    } while (!checkPlace(cb.noiDi));

    do {
        cout << "Nhap noi den: ";
        getline(cin, cb.noiDen);
        ChuanHoa(cb.noiDen);
    } while (!checkPlace(cb.noiDen));
}

// Nhập danh sách chuyến bay
void NhapDanhSachChuyenBay(DANHSACHCHUYENBAY& dscb) {
    // Nhập số lượng chuyến bay
    do {
        cout << "Nhap so luong chuyen bay: ";
        cin >> dscb.n;
    } while (dscb.n <= 0);
    // Khởi tạo vùng nhớ cho danh sách chuyến bay
    dscb.cb = new ChuyenBay[dscb.n];
    // Duyệt vòng lặp để nhập thông tin từng chuyến bay
    for (int i = 0; i < dscb.n; i++) {
        cout << "\n=== Nhap thong tin chuyen bay thu " << i + 1 << " ===\n";
        NhapChuyenBay(dscb.cb[i]);
    }
}

// Xuất thông tin một chuyến bay
void XuatChuyenBay(ChuyenBay cb) {
    cout << "Ma chuyen bay: " << cb.maCB << endl;
    cout << "Ngay bay: " << cb.ngay << "/" << cb.thang << "/" << cb.nam << endl;
    cout << "Gio bay: " << setw(2) << setfill('0') << cb.gio << ":" << setw(2) << setfill('0') << cb.phut << endl;
    cout << "Noi di: " << cb.noiDi << endl;
    cout << "Noi den: " << cb.noiDen << endl;
}

// Xuất danh sách chuyến bay
void XuatDanhSachChuyenBay(DANHSACHCHUYENBAY& dscb) {
    cout << "\n===== DANH SACH CHUYEN BAY =====\n";
    for (int i = 0; i < dscb.n; i++) {
        cout << "\n--- Chuyen bay thu " << i + 1 << " ---\n";
        XuatChuyenBay(dscb.cb[i]);
    }
}
// Hàm comparator để sắp xếp chuyến bay theo thời gian từ sớm đến muộn
bool cmp(ChuyenBay& a, ChuyenBay& b) {
    // Nếu năm khác nhau thì sắp xếp năm sớm đến năm muộn
    if (a.nam != b.nam) return a.nam < b.nam;
    // Tương tự như năm, ta làm cho tháng, ngày, giờ và phút
    else if (a.thang != b.thang) return a.thang < b.thang;
    else if (a.ngay != b.ngay) return a.ngay < b.ngay;
    else if (a.gio != b.gio) return a.gio < b.gio;
    return a.phut < b.phut;
}
// Hàm sắp xếp chuyến bay theo thời gian từ sớm đến muộn
void SapXepDanhSachChuyenBay(DANHSACHCHUYENBAY& dscb) {
    // Sử dụng hàm sort và truyền vào comparator để ta sắp xếp
    sort(dscb.cb, dscb.cb + dscb.n, cmp);
}
// Hàm kiểm tra mã chuyến bay bằng mã chuyến bay hoặc nơi đi và nơi đến
void KiemTraMaChuyenBay(DANHSACHCHUYENBAY& dscb, string ma) {
    // Duyệt qua vòng lặp để kiểm tra xem chuyến bay nào thỏa điều kiện thì xuất ra thông tin của chuyến bay đó
    for (int i = 0; i < dscb.n; i++) {
        if (dscb.cb[i].maCB == ma || dscb.cb[i].noiDi == ma || dscb.cb[i].noiDen == ma) {
            cout << "Chuyen bay co ma " << ma << " ton tai:\n";
            XuatChuyenBay(dscb.cb[i]);
            return;
        }
    }
    // Nếu không thấy thì xuất ra không tìm thấy chuyến bay nào
    cout << "Khong tim thay chuyen bay co ma " << ma << ".\n";
}
// Hàm tìm chuyến bay theo nơi đi vào một ngày nhất định
void TimChuyenBayTheoNoiDi(DANHSACHCHUYENBAY& dscb, string noidi, int& day, int& month, int& year) {
    // Kiểu dữ liệu bool để kiêm tra xem có tìm thấy chuyến bay nào hay không
    bool ok = false;
    cout << "Danh sach cac chuyen bay tu " << noidi << " trong ngay " << day << "/" << month << "/" << year << ":\n";
    for (int i = 0; i < dscb.n; i++) {
        // Kiểm tra chuyến bay nào có nơi đi và thời gian trùng với dữ liệu ta nhập vào thì ta xuất ra thông tin chuyến bay đó
        if (dscb.cb[i].noiDi == noidi && dscb.cb[i].ngay == day && dscb.cb[i].thang == month && dscb.cb[i].nam == year) {
            XuatChuyenBay(dscb.cb[i]);
            cout << "----------------------\n";
            // Đã tìm thấy 
            ok = true;
        }
    }
    // Nếu không tìm thấy thì xuất ra không tìm thấy
    if (!ok) {
        cout << "Khong tim thay chuyen bay nao tu \"" << noidi << "\".\n";
    }
}
// hàm đếm số chuyến bay từ một nơi đi đến một nơi đến cụ thể
void DemSoChuyenBay(DANHSACHCHUYENBAY& dscb, string noidi, string noiden) {
    // khởi tạo biến đếm bằng 0
    int cnt = 0;
    cout << "So chuyen bay khoi hanh tu " << noidi << " den " << noiden << " la: ";
    for (int i = 0; i < dscb.n; i++) {
        // kiểm tra chuyến bay nào có nơi đi và nơi đến trùng với dữ liệu ta nhập vào cập nhật lại biến đếm
        if (dscb.cb[i].noiDi == noidi && dscb.cb[i].noiDen == noiden) cnt++;
    }
    cout << cnt;
}
int main() {
    DANHSACHCHUYENBAY dscb;
    NhapDanhSachChuyenBay(dscb);
    SapXepDanhSachChuyenBay(dscb);
    XuatDanhSachChuyenBay(dscb);
    // Tim chuyen bay theo ma, noi di hoac noi den
    string ma;
    cout << "Nhap ma chuyen bay can tim: ";
    getline(cin, ma);
    if (ma.size() > 5) ChuanHoa(ma);
    else ChuanHoaMa(ma);
    KiemTraMaChuyenBay(dscb, ma);

    string noidi;
    cout << "Nhap noi di can tim: ";
    getline(cin, noidi);
    ChuanHoa(noidi);
    int ngay, thang, nam;
    cout << "Nhap ngay thang nam can tim (dd mm yyyy): ";
    cin >> ngay >> thang >> nam;
    if (checkNgayThangNam(ngay, thang, nam)) {
        TimChuyenBayTheoNoiDi(dscb, noidi, ngay, thang, nam);
    }

    string NoiDi, NoiDen;
    cout << "Nhap noi di: ";
    cin.ignore();
    getline(cin, NoiDi);
    ChuanHoa(NoiDi);
    cout << "Nhap noi den: ";
    getline(cin, NoiDen);
    ChuanHoa(NoiDen);
    DemSoChuyenBay(dscb, NoiDi, NoiDen);

    delete[] dscb.cb;
    return 0;
}

