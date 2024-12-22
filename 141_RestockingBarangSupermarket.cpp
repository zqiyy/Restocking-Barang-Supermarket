#include <iostream>
#include <string>
#include <ctime>    // Untuk menangani waktu

using namespace std;

// Struktur untuk menyimpan informasi barang
struct Barang {
    string nama;
    int jumlah;   // Menggunakan int biasa untuk jumlah barang
    double harga;
};

// Fungsi untuk menampilkan waktu saat restock dilakukan
void tampilkanWaktu() {
    time_t now = time(0);  // Mendapatkan waktu sekarang
    char* dt = ctime(&now);  // Mengubah waktu menjadi format string
    cout << "Waktu Restock: " << dt;
}

// Fungsi untuk menampilkan informasi barang
void tampilkanBarang(Barang barangList[], int jumlahBarang) {
    if (jumlahBarang == 0) {
        cout << "Tidak ada barang di daftar.\n";
        return;
    }
    cout << "\nDaftar Barang yang Tersedia:\n";
    for (int i = 0; i < jumlahBarang; ++i) {
        cout << "Nama Barang: " << barangList[i].nama << endl;
        cout << "Jumlah Stok: " << barangList[i].jumlah << " unit" << endl;
        cout << "Harga: Rp " << barangList[i].harga << endl;
        cout << "--------------------------------\n";
    }
}

// Fungsi untuk menambah jumlah stok barang atau menambah barang baru
void restockBarang(Barang barangList[], int& jumlahBarang, const string& namaBarang, int jumlahRestock, double hargaBarang) {
    if (jumlahRestock < 0) {
        cout << "Jumlah yang di-restock tidak valid!" << endl;
        return;
    }

    // Mencari barang apakah sudah ada dalam daftar
    bool barangDitemukan = false;
    for (int i = 0; i < jumlahBarang; ++i) {
        if (barangList[i].nama == namaBarang) {
            barangList[i].jumlah += jumlahRestock;
            cout << "Barang " << barangList[i].nama << " berhasil di-restock sebanyak " << jumlahRestock << " unit." << endl;
            barangDitemukan = true;
            break;
        }
    }

    // Jika barang tidak ditemukan, tambahkan barang baru
    if (!barangDitemukan) {
        if (jumlahBarang < 10) { // Mengatur batas maksimal barang yang ada dalam daftar
            Barang barangBaru = {namaBarang, jumlahRestock, hargaBarang};
            barangList[jumlahBarang] = barangBaru;
            jumlahBarang++;
            cout << "Barang baru " << barangBaru.nama << " berhasil ditambahkan dengan jumlah " << barangBaru.jumlah << " unit." << endl;
        } else {
            cout << "Daftar barang sudah penuh! Tidak bisa menambah barang baru." << endl;
        }
    }
}

int main() {
    // Daftar barang awal
    Barang barangList[10] = {
        {"Teh Botol", 50, 4000.0},
        {"Indomie", 100, 3000.0}
    };

    int jumlahBarang = 2;  // Jumlah barang yang tersedia di awal
    int pilihan, jumlahRestock;
    double hargaBarang;
    string namaBarang;  // Deklarasi variabel namaBarang di luar switch untuk menghindari error
    bool barangDitemukan; // Deklarasi di luar switch

    do {
        // Menampilkan menu
        cout << "\n=== Restocking Barang Supermarket ===\n";
        cout << "1. Tampilkan Daftar Barang\n";
        cout << "2. Restock Barang\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanBarang(barangList, jumlahBarang);
                break;
            case 2:
                // Input nama barang dan jumlah restock
                cout << "Masukkan nama barang yang ingin di-restock: ";
                cin.ignore();  // Membersihkan buffer input
                getline(cin, namaBarang);

                cout << "Masukkan jumlah barang yang ingin di-restock: ";
                cin >> jumlahRestock;

                // Cek apakah barang ada di daftar
                barangDitemukan = false; // Reset sebelum pengecekan
                for (int i = 0; i < jumlahBarang; ++i) {
                    if (barangList[i].nama == namaBarang) {
                        barangDitemukan = true;
                        break;
                    }
                }

                if (barangDitemukan) {
                    // Jika barang ditemukan, tidak perlu minta harga
                    hargaBarang = 0;  // Set harga ke 0 karena tidak dibutuhkan
                } else {
                    // Jika barang baru, minta harga barang
                    cout << "Masukkan harga barang (jika barang baru): ";
                    cin >> hargaBarang;
                }

                // Melakukan restock barang atau menambah barang baru
                restockBarang(barangList, jumlahBarang, namaBarang, jumlahRestock, hargaBarang);

                // Menampilkan waktu dan daftar barang setelah restock dilakukan
                tampilkanWaktu();
                tampilkanBarang(barangList, jumlahBarang);

                break;
            case 3:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }

    } while (pilihan != 3);  // Program akan terus berjalan sampai user memilih opsi keluar

    return 0;
}