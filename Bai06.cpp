#include<iostream>
#include<vector>
using namespace std;
// hàm kiểm tra dãy A có xuất hiện trong mảng B, bắt đầu từ vị trí x hay không
bool check(vector<int>& B, vector<int>& A, int x) {
    int n = A.size();
    // Duyệt qua từng phần tử trong A và so sánh với phần tử tương ứng trong B từ vị trí x trở đi
    for (int i = 0; i < n; i++) {
        // Nếu có bất kỳ phân tử nào không khớp thì trả về false
        if (B[x + i] != A[i]) return false;
    }
    return true;
}
// Hàm tìm tất cả các vị trí mà dãy A xuất hiện trong B
vector<int> solve(vector<int>& B, vector<int>& A) {
    int n = A.size();
    int m = B.size();
    // Tạo một vector để lưu các vị trí xuất hiện của A trong B
    vector<int> kq;
    // Duyệt qua B từ vị trí 0 đến vị trí m - n (vì m - n chính là vị trí cuối cùng mà phần tử đầu tiên của dãy A có thể xuất hiện)
    for (int i = 0; i <= m - n; i++) {
        // Nếu kiểm tra đúng thì ta lưu vào vector kq
        if (check(B, A, i)) {
            kq.push_back(i);
        }
    }
    return kq;
}

int main() {
    int n, m;
    cout << "Nhap so luong phan tu cua A: ";
    cin >> n;
    cout << "Nhap so luong phan tu cua B: ";
    cin >> m;
    vector<int> A(n), B(m);
    cout << "Nhap cac phan tu cua A: ";
    for (int i = 0; i < n; i++) cin >> A[i];
    cout << "Nhap cac phan tu cua B: ";
    for (int i = 0; i < m; i++) cin >> B[i];
    vector<int> result = solve(B, A);
    cout << "So lan A xuat hien trong B: " << result.size() << endl;
    cout << "Cac vi tri bat dau A xuat hien trong B: ";
    if (result.empty()) cout << "khong co";
    else for (auto it : result) {
        cout << it << " ";
    }
    return 0;
}


