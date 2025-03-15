#include<iostream>
using namespace std;
// Hàm kiểm tra năm nhuận
bool KiemTraNamNhuan(int year) {
    // Năm là năm nhuận nếu năm đó chia hết cho 400 hoặc chia hết cho 4 và đồng thời không chia hết cho 100
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
// Hàm đếm số ngày của mỗi tháng trong năm
int DemSoNgayTrongThang(int month, int year) {
    // Tạo một mảng để lưu số ngày của từng tháng trong năm
    int day[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    // Kiểm tra nếu năm nhuận thì tháng 2 có 29 ngày và cập nhất lại giá trị
    if (month == 2 && KiemTraNamNhuan(year)) {
        return 29;
    }
    return day[month];
}
// Hàm tính ngày kế tiếp ngày đã nhập
void NextDay(int& day, int& month, int& year) {
    // Nếu ngày ta đã nhập nhỏ hơn số ngày trong tháng ta nhập thì cộng thêm 1 ngày
    if (day < DemSoNgayTrongThang(month, year)) {
        day++;
    }
    // Nếu ngày ta đã nhập lớn hơn số ngày trong tháng ta đã nhập thì ngày tiếp theo là ngày đầu tháng 
    else {
        day = 1;
        // Nếu tháng ta nhập không phải tháng 12 thì cộng thêm 1 tháng
        if (month < 12) month++;
        // Nếu tháng ta nhập là tháng 12 thì cập nhật sang năm sau
        else {
            month = 1;
            year++;
        }
    }
}
// Hàm tính ngày trước ngày ta đã nhập
void PreviousDay(int& day, int& month, int& year) {
    // Nếu ngày lớn hơn 1 thì ta trừ bớt đi 1 ngày
    if (day > 1) {
        day--;
    }
    // Nếu ngày = 1 tức là ngày đầu tháng thì ta phải lùi lại tháng trước
    else {
        if (month > 1) {
            month--;
            day = DemSoNgayTrongThang(month, year);
        }
        // Nếu tháng là tháng 1 thì ta phải lùi lại năm trước
        else {
            month = 12;
            year--;
            day = 31;
        }
    }
}
// Hàm tính số thứ tự của ngày ta đã nhập trong năm
int SoNgayTrongNam(int day, int month, int year) {
    // Khởi tạo kết quả bằng 0
    int sum = 0;
    // Duyệt vòng lặp từ tháng 1 đến tháng ta đã nhập - 1 và cập nhật kết quả
    for (int i = 1; i < month; i++) {
        sum += DemSoNgayTrongThang(i, year);
    }
    // Cộng nốt số ngày ta đã nhập để ra được kết quả
    sum += day;
    return sum;
}

int main() {
    int day, month, year;
    do {
        cout << "Nhap ngay, thang, nam: ";
        cin >> day >> month >> year;
    } while (month < 1 || month > 12 || day < 1 || day > DemSoNgayTrongThang(month, year));
    int day_tmp = day, month_tmp = month, year_tmp = year;
    NextDay(day_tmp, month_tmp, year_tmp);
    cout << "Ngay ke tiep: " << day_tmp << "/" << month_tmp << "/" << year_tmp << endl;
    int day_tmp1 = day, month_tmp1 = month, year_tmp1 = year;
    PreviousDay(day_tmp1, month_tmp1, year_tmp1);
    cout << "Ngay truoc do: " << day_tmp1 << "/" << month_tmp1 << "/" << year_tmp1 << endl;
    cout << "Ngay thu " << SoNgayTrongNam(day, month, year) << " trong nam" << endl;
    return 0;
}


