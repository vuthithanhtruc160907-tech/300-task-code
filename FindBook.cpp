#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;
// ============================================================================
// YÊU CẦU 1: Định nghĩa struct Sach và các hàm nhập xuất cơ bản
// ============================================================================
struct Sach {
    char maSach[50];       // c-string
    string tenSach;        // string
    char tenTacGia[100];   // c-string
    double giaBan;         // số thực
    int giamGia;           // số nguyên (%)
};

// Hàm nhập thông tin 1 quyển sách từ bàn phím (Nếu cần dùng sau này)
void nhap1Sach(Sach& s) {
    cout << "Nhap ma sach: ";
    cin.getline(s.maSach, 50);
    cout << "Nhap ten sach: ";
    getline(cin, s.tenSach);
    cout << "Nhap ten tac gia: ";
    cin.getline(s.tenTacGia, 100);
    cout << "Nhap gia ban: ";
    cin >> s.giaBan;
    cout << "Nhap giam gia (%): ";
    cin >> s.giamGia;
    cin.ignore(); // Xóa bộ nhớ đệm
}

// Hàm xuất thông tin 1 quyển sách ra màn hình (Đã canh lề chuẩn)
void xuat1Sach(const Sach& s) {
    cout << left << setw(10) << s.maSach
        << setw(35) << s.tenSach
        << setw(25) << s.tenTacGia
        << setw(12) << fixed << setprecision(0) << s.giaBan
        << s.giamGia << "%" << endl;
}

// ============================================================================
// YÊU CẦU 2: Định nghĩa struct DSQS, đọc file Sach.txt và xuất danh sách
// ============================================================================
struct DSQS {
    Sach* danhSach = nullptr; // Con trỏ trỏ đến mảng động các quyển sách
    int soLuong = 0;          // Số lượng sách hiện có
};

// Hàm đọc tập tin Sach.txt (Phiên bản xử lý dấu '#' và tự đếm số dòng)
void docFileSach(const string& filename, DSQS& ds) {
    ifstream fileIn(filename);
    if (!fileIn.is_open()) {
        cout << "Khong the mo file " << filename << " de doc!" << endl;
        return;
    }

    // --- BƯỚC 1: Đếm số lượng sách (số dòng có dữ liệu) trong file ---
    string dummyLine;
    int count = 0;
    while (getline(fileIn, dummyLine)) {
        if (!dummyLine.empty()) {
            count++;
        }
    }

    if (count == 0) {
        cout << "File trong hoac khong co du lieu!" << endl;
        fileIn.close();
        return;
    }

    // Nếu danh sách đã có dữ liệu từ trước, giải phóng bộ nhớ để tránh rò rỉ
    if (ds.danhSach != nullptr) {
        delete[] ds.danhSach;
    }

    // Cấp phát mảng động mới
    ds.soLuong = count;
    ds.danhSach = new Sach[ds.soLuong];

    // --- BƯỚC 2: Tua con trỏ về đầu file để đọc thật ---
    fileIn.clear();
    fileIn.seekg(0, ios::beg);

    for (int i = 0; i < ds.soLuong; i++) {
        string line;
        getline(fileIn, line);
        if (line.empty()) {
            i--;
            continue;
        }

        stringstream ss(line);
        string s_ma, s_tacGia, s_gia, s_giam;

        // Cắt dữ liệu bằng dấu '#'
        getline(ss, s_ma, '#');
        getline(ss, ds.danhSach[i].tenSach, '#');
        getline(ss, s_tacGia, '#');
        getline(ss, s_gia, '#');
        getline(ss, s_giam);

        // Gán vào struct
        strcpy(ds.danhSach[i].maSach, s_ma.c_str());
        strcpy(ds.danhSach[i].tenTacGia, s_tacGia.c_str());

        try {
            ds.danhSach[i].giaBan = stod(s_gia);
            ds.danhSach[i].giamGia = stoi(s_giam);
        }
        catch (...) {
            ds.danhSach[i].giaBan = 0;
            ds.danhSach[i].giamGia = 0;
        }
    }

    cout << "=> Doc file thanh cong! Da tai " << ds.soLuong << " quyen sach vao he thong." << endl;
    fileIn.close();
}

// Hàm xuất danh sách sách ra màn hình
void xuatDanhSach(const DSQS& ds) {
    if (ds.soLuong == 0 || ds.danhSach == nullptr) {
        cout << "Danh sach hien tai dang trong!" << endl;
        return;
    }

    cout << "\n------------------------------------------------ KHO SACH ------------------------------------------------\n";
    cout << left << setw(10) << "Ma sach" << setw(35) << "Ten sach" << setw(25) << "Ten tac gia" << setw(12) << "Gia ban" << "Giam gia" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < ds.soLuong; i++) {
        xuat1Sach(ds.danhSach[i]);
    }
    cout << "----------------------------------------------------------------------------------------------------------\n";
}

// ============================================================================
// YÊU CẦU 3: Hàm tìm kiếm theo mã sách hoặc tên sách
// ============================================================================
int timKiemSach(const DSQS& ds) {
    if (ds.soLuong == 0) {
        cout << "Danh sach trong, khong the tim kiem!" << endl;
        return -1;
    }

    cout << "\nChon phuong thuc tim kiem:\n";
    cout << "1. Tim theo ma sach\n";
    cout << "2. Tim theo ten sach\n";
    cout << "Lua chon cua ban: ";
    int luaChon;
    cin >> luaChon;
    cin.ignore();

    if (luaChon == 1) {
        char maTim[50];
        cout << "Nhap ma sach can tim: ";
        cin.getline(maTim, 50);
        for (int i = 0; i < ds.soLuong; i++) {
            if (strcmp(ds.danhSach[i].maSach, maTim) == 0) {
                return i;
            }
        }
    }
    else if (luaChon == 2) {
        string tenTim;
        cout << "Nhap ten sach can tim: ";
        getline(cin, tenTim);
        for (int i = 0; i < ds.soLuong; i++) {
            if (ds.danhSach[i].tenSach == tenTim) {
                return i;
            }
        }
    }
    else {
        cout << "Lua chon khong hop le!" << endl;
    }
    return -1;
}

// ============================================================================
// YÊU CẦU 4: Chọn mua sách vào giỏ hàng và xuất hóa đơn ra HoaDon.txt
// ============================================================================
void muaSachVaXuatHoaDon(const DSQS& ds) {
    if (ds.soLuong == 0) {
        cout << "Kho khong co sach de mua! Vui long tai file truoc." << endl;
        return;
    }

    int* gioHang = new int[ds.soLuong];
    int soLuongMua = 0;
    char tiepTuc = 'y';

    do {
        cout << "\n--- CHON SACH MUON MUA ---" << endl;
        int index = timKiemSach(ds);

        if (index != -1) {
            gioHang[soLuongMua] = index;
            soLuongMua++;
            cout << "=> Da them sach \"" << ds.danhSach[index].tenSach << "\" vao gio hang." << endl;
        }
        else {
            cout << "=> Khong tim thay sach nay trong kho!" << endl;
        }

        cout << "Ban co muon mua them sach khong? (y/n): ";
        cin >> tiepTuc;
        cin.ignore();
    } while ((tiepTuc == 'y' || tiepTuc == 'Y') && soLuongMua < ds.soLuong);

    if (soLuongMua == 0) {
        cout << "Gio hang trong. Khong xuat hoa don." << endl;
        delete[] gioHang;
        return;
    }

    // Tính tổng hóa đơn: Thành tiền mỗi quyển = giá bán * (100 - giảm giá) / 100
    // Tính tổng hóa đơn
    double tongHoaDon = 0;
    for (int i = 0; i < soLuongMua; i++) {
        int idx = gioHang[i];
        // Lưu ý: Đề bài ghi "thành tiền = giá bán * giảm giá". 
        // Ở đây mình chia 100 để tính ra số tiền được giảm theo % cho hợp lý nhé.
        double thanhTien = (ds.danhSach[idx].giaBan * ds.danhSach[idx].giamGia) / 100.0;
        tongHoaDon += thanhTien;
    }

    // --- THÊM PHẦN IN RA MÀN HÌNH Ở ĐÂY ---
    cout << "\n================ HOÁ ĐƠN CỦA BẠN ================\n";
    cout << "=> Tong tien phai thanh toan: " << fixed << setprecision(0) << tongHoaDon << " VND\n";
    cout << "=================================================\n";

    // Xuất hóa đơn ra file
    ofstream fileOut("HoaDon.txt");
    if (!fileOut.is_open()) {
        cout << "Khong the mo file HoaDon.txt de ghi!" << endl;
        delete[] gioHang;
        return;
    }

    // Ghi dòng 1: Tổng tiền
    fileOut << fixed << setprecision(0) << tongHoaDon << endl;

    // Ghi các dòng tiếp theo: Thông tin sách
    for (int i = 0; i < soLuongMua; i++) {
        int idx = gioHang[i];
        fileOut << ds.danhSach[idx].maSach << "#"
            << ds.danhSach[idx].tenSach << "#"
            << ds.danhSach[idx].tenTacGia << "#"
            << fixed << setprecision(0) << ds.danhSach[idx].giaBan << "#"
            << ds.danhSach[idx].giamGia << endl;
    }

    cout << "=> Chi tiet hoa don da duoc luu vao file 'HoaDon.txt'!" << endl;
    fileOut.close();
    delete[] gioHang;
}

// ============================================================================
// YÊU CẦU 5: Xây dựng hàm main với menu lựa chọn
// ============================================================================
int main() {
    DSQS dsNhaBe;
    int luaChon;

    do {
        cout << "\n==================== MENU QUAN LY SACH ====================\n";
        cout << "1. Doc du lieu tu tap tin Sach.txt\n";
        cout << "2. Hien thi danh sach sach hien co\n";
        cout << "3. Tim kiem thong tin sach\n";
        cout << "4. Chon mua sach va xuat hoa don (HoaDon.txt)\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "===========================================================\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;
        cin.ignore();

        switch (luaChon) {
        case 1:
            docFileSach("Sach.txt", dsNhaBe);
            break;
        case 2:
            xuatDanhSach(dsNhaBe);
            break;
        case 3: {
            // ---> THÊM DÒNG NÀY VÀO: Hiện danh sách ra trước khi tìm kiếm
            xuatDanhSach(dsNhaBe);

            int idx = timKiemSach(dsNhaBe);
            if (idx != -1) {
                cout << "\n--- THONG TIN SACH TIM THAY ---\n";
                xuat1Sach(dsNhaBe.danhSach[idx]);
            }
            else {
                cout << "=> Khong tim thay ket qua phu hop." << endl;
            }
            break;
        }
        case 4:
            // ---> THÊM DÒNG NÀY VÀO: Hiện danh sách ra để khách dễ nhìn mã sách mà mua
            xuatDanhSach(dsNhaBe);

            muaSachVaXuatHoaDon(dsNhaBe);
            break;
        case 0:
            cout << "Tam biet va chuc ban thi tot!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (luaChon != 0);

    // Dọn dẹp bộ nhớ trước khi thoát
    if (dsNhaBe.danhSach != nullptr) {
        delete[] dsNhaBe.danhSach;
    }

    return 0;
}