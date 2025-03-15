#include <bits/stdc++.h>
using namespace std;

/* kiểu dữ liệu sổ tiết kiệm bao gồm:
- Mã sổ
- Loại tiết kiệm
- Họ tên
- CCCD
- Ngày mở sổ
- Số tiền gửi
*/
struct SoTietKiem {
    string MaSo, LoaiTietKiem, HoTen, CCCD;
    double Money;
    int ngay, thang, nam;
};
// kiểu dữ liệu danh sách sổ tiết kiệm gồm số lượng sổ tiết kiệm và con trỏ kiểu SoTietKiem
struct DANHSACHSOTIETKIEM {
    int n;
    SoTietKiem* STK;
};
// Hàm kiểm tra mã số (không được quá 5 ký tự và chứa ký tự đặc biệt)
bool checkMaSo(string& ma) {
    if (ma.size() > 5) return false;
    for (char c : ma) {
        if (c == ' ' || !isalnum(c)) return false;
    }
    return true;
}
// Hàm chuẩn hóa mã số (Phải in hoa)
string ChuanHoaMaSo(string& ma) {
    for (char& c : ma) {
        c = toupper(c);
    }
    return ma;
}

// Hàm kiểm tra họ tên (tên không quá 30 ký tự và chứa số hoặc ký tự đặc biệt)
bool checkHoTen(string& ten) {
    if (ten.size() > 30) return false;
    for (char c : ten) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Hàm chuẩn hóa họ tên 
void ChuanHoaHoTen(string& ten) {
    // Sử dụng stringstream để tách các từ trong chuỗi 
    stringstream ss(ten);
    string res = "", word;
    while (ss >> word) {
        // Chữ cái đầu tiên phải viết in hoa
        word[0] = toupper(word[0]);
        for (int i = 1; i < word.size(); i++) {
            // Các chữ cái sau đó in thường
            word[i] = tolower(word[i]);
        }
        res += word + " ";
    }
    // Xóa dấu cách cuối cùng (do res += word + " " dư dấu cách cuối chuỗi)
    res.pop_back();
    ten = res;
}

// Hàm kiểm tra CCCD (phải có đúng 9 hoặc 12 số)
bool checkCCCD(string& CCCD) {
    for (int i = 0; i < CCCD.size(); i++) if (!isdigit(CCCD[i])) return false;
    return (CCCD.size() == 9 || CCCD.size() == 12);
}

// Hàm kiểm tra số tiền (số thực và không âm)
bool checkMoney(double& money) {
    return money > 0;
}

// Hàm kiểm tra ngày hợp lệ
bool checkDate(int ngay, int thang, int nam) {
    // Kiểm tra ngày tháng hợp lệ
    if (thang < 1 || thang > 12 || ngay < 1) return false;
    // Tính số ngày của mỗi tháng
    int DemSoNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // Kiểm tra năm nhuận và cập nhật lại giá trị của tháng 2 nếu năm nhập vào là năm nhuận
    bool NamNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
    if (NamNhuan) DemSoNgayTrongThang[1] = 29;
    return ngay <= DemSoNgayTrongThang[thang - 1];
}

// Hàm nhập thông tin sổ tiết kiệm
void Nhap(SoTietKiem& STK) {
    cout << "========== QUAN LY SO TIET KIEM ==========" << endl;
    // Nhập mã sổ và kiểm tra điều kiện
    do {
        cout << "Nhap ma so: ";
        cin >> STK.MaSo;
        ChuanHoaMaSo(STK.MaSo);
    } while (!checkMaSo(STK.MaSo));
    cin.ignore();
    // Nhâp loại tiết kiệm và kiểm tra điều kiện
    do {
        cout << "Nhap loai tiet kiem (ngan han/dai han): ";
        getline(cin, STK.LoaiTietKiem);
        ChuanHoaHoTen(STK.LoaiTietKiem);
    } while (STK.LoaiTietKiem != "Ngan Han" && STK.LoaiTietKiem != "Dai Han");
    // Nhập họ tên khách hàng, kiểm tra điều kiện và chuẩn hóa họ tên cho đúng định dạng
    do {
        cout << "Nhap ho ten khach hang: ";
        getline(cin, STK.HoTen);
        ChuanHoaHoTen(STK.HoTen);
    } while (!checkHoTen(STK.HoTen));
    // Nhập CCCD và kiểm tra điều kiện
    do {
        cout << "Nhap CCCD (9 hoac 12 so): ";
        cin >> STK.CCCD;
    } while (!checkCCCD(STK.CCCD));
    // Nhập ngày mở sổ và kiểm tra điều kiện
    do {
        cout << "Nhap ngay mo so (dd/mm/yyyy): ";
        string date;
        cin >> date;
        // Dùng stringstream để tách các từ trong chuỗi theo dấu / (do ngày tháng năm có định dạng dd/mm/yyyy)
        stringstream ss(date);
        string word;
        // tách ra và gán lại cho ngày, tháng, năm để kiểm tra
        getline(ss, word, '/'); STK.ngay = stoi(word);
        getline(ss, word, '/'); STK.thang = stoi(word);
        getline(ss, word, '/'); STK.nam = stoi(word);
    } while (!checkDate(STK.ngay, STK.thang, STK.nam));
    // Nhập số tiền gửi và kiểm tra điều kiện
    do {
        cout << "Nhap so tien gui: ";
        cin >> STK.Money;
    } while (!checkMoney(STK.Money));
    cout << endl;
}

// Hàm xuất thông tin sổ tiết kiệm
void Xuat(SoTietKiem STK) {
    cout << "========== THONG TIN SO TIET KIEM ==========" << endl;
    cout << "Ma so: " << STK.MaSo << endl;
    cout << "Loai tiet kiem: " << STK.LoaiTietKiem << endl;
    cout << "Ho ten khach hang: " << STK.HoTen << endl;
    cout << "CCCD: " << STK.CCCD << endl;
    // setw(2) và setfill('0') để nếu ngày hoặc tháng nhập vào có 1 ký số thì tự động thêm số 0 đằng trước ngày và tháng
    cout << "Ngay mo so: " << setw(2) << setfill('0') << STK.ngay << "/"
        << setw(2) << setfill('0') << STK.thang << "/" << STK.nam << endl;
    // fixed << setprecision(0) để xuất ra đúng dạng của số tiền gửi
    cout << "So tien gui: " << fixed << setprecision(0) << STK.Money << endl;
    cout << "============================================" << endl;
}

// Chuyển ngày thành time_t
time_t ConvertToTime(int ngay, int thang, int nam) {
    tm time_in = {}; // khởi tạo một cấu trúc tm với tất cả các giá trị ban đầu là 0
    time_in.tm_mday = ngay; // Gán ngày vào tm_mday
    time_in.tm_mon = thang - 1; // Gán tháng vào tm_mon (tháng trong tm bắt đầu từ 0 nên ta phải trừ đi 1)
    time_in.tm_year = nam - 1900; // Gán năm vào tm_year (năm trong tm bắt đầu từ 1900 nên ta phải trừ đi 1900)
    return mktime(&time_in); // chuyển đổi struct thành kiểu time_t và trả về
}

// Tính số ngày gửi
int TinhSoNgayGui(SoTietKiem& STK) {
    time_t ngayMoSo = ConvertToTime(STK.ngay, STK.thang, STK.nam); // chuyển ngày mở sổ thành time_t
    time_t ngayHienTai = time(0); // Lấy thời gian hiện tại (số ngày tính từ 01/01/1970)
    return difftime(ngayHienTai, ngayMoSo) / (60 * 60 * 24); // Tính số ngày bằng cách lấy hiệu của 2 giá trị time_t, rồi chia cho số giây trong 1 ngày 
}

// Tính tiền lãi
double TinhTienLai(SoTietKiem& STK, double LaiSuat) {
    int day = TinhSoNgayGui(STK); // Tinh số ngày gửi tiền 
    double soNamGui = day / 365.0; // Chuyển đổi số ngày thành số năm
    double LaiSuatNam = LaiSuat / 100.0; // Chuyển lãi suất từ phần trăm thành số thập phân

    if (STK.LoaiTietKiem == "Ngan Han") {
        // Tính lãi đơn : Số tiền * lãi suất * số năm gửi 
        return STK.Money * LaiSuatNam * soNamGui;
    }
    else {
        // Tính lãi kép: (số tiền gửi * (1 + lãi suất) ^ năm gửi - Số tiền gửi)
        return STK.Money * pow(1 + LaiSuatNam, soNamGui) - STK.Money;
    }
}

// Hàm rút tiền 
void RutTien(SoTietKiem& STK, double LaiSuat) {
    int SoNgayGui = TinhSoNgayGui(STK); // Tính số ngày đã gửi (nếu chưa được 1 năm thì cảnh báo và giảm lãi còn 0.5 %/năm)
    if (SoNgayGui < 365) {
        cout << "Ban dang rut truoc han, lai suat chi con 0.5 %/nam." << endl;
        LaiSuat = 0.5;
    }
    double TienLai = TinhTienLai(STK, LaiSuat);
    double TongTien = STK.Money + TienLai;
    double SoTienRut;
    // Nhập số tiền muốn rút và tính số tiền còn lại trong sổ
    do {
        cout << "Nhap so tien muon rut: ";
        cin >> SoTienRut;
    } while (SoTienRut > TongTien || SoTienRut <= 0);
    STK.Money = TongTien - SoTienRut;
    cout << "Rut tien thanh cong! So du con lai: " << fixed << setprecision(0) << STK.Money << " VND" << endl;
}
// Hàm nhập một danh sách sổ tiết kiệm
void Nhap(DANHSACHSOTIETKIEM& dsSTK) {
    cout << "===================================" << endl;
    // Nhập số lượng sổ tiết kiệm
    do {
        cout << "Nhap so luong so tiet kiem can tao: ";
        cin >> dsSTK.n;
    } while (dsSTK.n <= 0);
    // Nhập thông tin của từng sổ tiết kiệm
    dsSTK.STK = new SoTietKiem[dsSTK.n];
    for (int i = 0; i < dsSTK.n; i++) {
        Nhap(dsSTK.STK[i]);
    }
}
// hàm xuất danh sách sổ tiết kiệm
void Xuat(DANHSACHSOTIETKIEM dsSTK) {
    cout << "========== DANH SACH SO TIET KIEM ==========" << endl;
    for (int i = 0; i < dsSTK.n; i++) {
        Xuat(dsSTK.STK[i]);
    }
}
// Hàm tìm kiếm sổ tiết kiệm
void TimKiemSoTietKiem(DANHSACHSOTIETKIEM dsSTK, string key) {
    // biến bool để kiểm tra có tìm thấy hay không
    bool ok = false;
    for (int i = 0; i < dsSTK.n; i++) {
        // Kiểm tra và xuất ra thông tin của sổ nếu thỏa điều kiện
        if (dsSTK.STK[i].CCCD == key || dsSTK.STK[i].MaSo == key) {
            Xuat(dsSTK.STK[i]);
            // Cập nhật đã tìm thấy
            ok = true;
        }
    }
    // Không tìm thấy thì xuất không tìm thấy
    if (!ok) cout << "Khong tim thay so tiet kiem voi CCCD hoac ma so: " << key << endl;
}
// Hàm liệt kê sổ tiết kiệm trong 1 khoảng thời gian xác định
void LietKeSoTietKiem(DANHSACHSOTIETKIEM dsSTK, int ngayBD, int thangBD, int namBD, int ngayKT, int thangKT, int namKT) {
    time_t start = ConvertToTime(ngayBD, thangBD, namBD); // Chuyển thời gian bắt đầu thành kiểu time_t
    time_t end = ConvertToTime(ngayKT, thangKT, namKT); // Chuyển thời gian kết thúc thành kiểu time_t
    bool ok = false;
    cout << "========== DANH SACH SO TIET KIEM TRONG KHOANG THOI GIAN ==========" << endl;
    for (int i = 0; i < dsSTK.n; i++) {
        // kiểm tra xem sổ nào có ngày mở nằm trong khoảng trên thì xuất ra thông tin sổ đó
        time_t NgayMo = ConvertToTime(dsSTK.STK[i].ngay, dsSTK.STK[i].thang, dsSTK.STK[i].nam);
        if (NgayMo >= start && NgayMo <= end) {
            Xuat(dsSTK.STK[i]);
            ok = true;
        }
    }
    if (!ok) cout << "Khong co so tiet kiem nao trong khoang thoi gian nay." << endl;
}
// Hàm comparator sắp xếp theo số tiền giảm dần 
bool SoSanhTheoSoTienGiamDan(const SoTietKiem& a, const SoTietKiem& b) {
    return a.Money > b.Money;
}
// Hàm sắp xếp danh sách sổ theo số tiền gửi giảm dần
void SapXepTheoSoTien(DANHSACHSOTIETKIEM& dsSTK) {
    sort(dsSTK.STK, dsSTK.STK + dsSTK.n, SoSanhTheoSoTienGiamDan);
    cout << "Danh sach so tiet kiem da duoc sap xep theo so tien gui giam dan: " << endl;
}
// hàm comparator sắp xếp theo thời gian từ sớm đến muộn
bool cmp(SoTietKiem a, SoTietKiem b) {
    // so sánh lần lượt năm, tháng, ngày
    if (a.nam != b.nam) return a.nam < b.nam;
    if (a.thang != b.thang) return a.thang < b.thang;
    return a.ngay < b.ngay;
}
// Hàm sắp xếp danh sách sổ theo ngày mở từ sớm đến muộn
void SapXepTheoNgayMo(DANHSACHSOTIETKIEM& dsSTK) {
    sort(dsSTK.STK, dsSTK.STK + dsSTK.n, cmp);
    cout << "Danh sach so tiet kiem sau khi sap xep theo ngay mo so tang dan: " << endl;
}
int main() {
    SoTietKiem STK;
    Nhap(STK);
    Xuat(STK);
    cout << endl;
    cout << "========== TINH TIEN LAI ===================" << endl;
    double LaiSuat;
    cout << "Nhap lai suat (%/nam): ";
    cin >> LaiSuat;
    double TienLai = TinhTienLai(STK, LaiSuat);
    cout << "Tien lai: " << fixed << setprecision(0) << TienLai << " VND" << endl;
    cout << endl;
    cout << "========== RUT TIEN ========================" << endl;
    RutTien(STK, LaiSuat);
    DANHSACHSOTIETKIEM dsSTK;
    Nhap(dsSTK);
    Xuat(dsSTK);
    cout << endl;
    cout << "========== TIM KIEM SO TIET KIEM ===========" << endl;
    string key;
    cout << "Nhap CMND hoac ma so can tim: ";
    cin >> key;
    TimKiemSoTietKiem(dsSTK, key);
    cout << endl;
    cout << "========== LIET KE SO TIET KIEM ==========" << endl;
    int ngayBD, thangBD, namBD, ngayKT, thangKT, namKT;
    do {
        cout << "Nhap ngay bat dau (dd mm yyyy): ";
        cin >> ngayBD >> thangBD >> namBD;
    } while (!checkDate(ngayBD, thangBD, namBD));
    do {
        cout << "Nhap ngay ket thuc (dd mm yyyy): ";
        cin >> ngayKT >> thangKT >> namKT;
    } while (!checkDate(ngayKT, thangKT, namKT));
    LietKeSoTietKiem(dsSTK, ngayBD, thangBD, namBD, ngayKT, thangKT, namKT);
    cout << endl;
    cout << "============ SAP XEP ===========" << endl;
    SapXepTheoSoTien(dsSTK);
    Xuat(dsSTK);
    SapXepTheoNgayMo(dsSTK);
    Xuat(dsSTK);
    return 0;
}


