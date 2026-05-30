#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

void tambahBarang(vector<Barang>& daftarBarang) {
    Barang baru;
    cout << "\n--- Tambah Barang ---\n";
    cout << "Masukkan Kode Barang : ";
    getline(cin, baru.kodeBarang);
    cout << "Masukkan Nama Barang : ";
    getline(cin, baru.namaBarang);
    
    do {
        cout << "Masukkan harga : ";
        cin >> baru.harga;

        if (baru.harga < 0) {
            cout << "Error! Harga tidak boleh negatif.\n";
        }

    } while (baru.harga < 0);

    do {
        cout << "Masukkan stok : ";
        cin >> baru.stok;

        if (baru.stok < 0) {
            cout << "Error! Stok tidak boleh negatif.\n";
        }

    } while (baru.stok < 0);

    daftarBarang.push_back(baru);
    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanSemuaBarang(const vector<Barang>& daftarBarang) {
    cout << "\n--- Daftar Inventaris Toko ---\n";

    if (daftarBarang.empty()) {
        cout << "Inventaris masih kosong.\n";
        return;
    }

    cout << "\n===== DAFTAR BARANG =====\n";

    for (const auto& b : daftarBarang) {
        cout << "Kode  : " << b.kodeBarang << endl;
        cout << "Nama  : " << b.namaBarang << endl;
        cout << "Harga : " << b.harga << endl;
        cout << "Stok  : " << b.stok << endl;
        cout << "------------------------\n";
    }

}

void cariBarangTermahal(const vector<Barang>& daftarBarang) {
    cout << "\n--- Cari Barang Termahal ---\n";
    if (daftarBarang.empty()) {
        cout << " Inventaris masih kosong.\n";
        return;
    }

    const Barang* termahal = &daftarBarang[0];
    for (size_t i = 1; i < daftarBarang.size(); ++i) {
        if (daftarBarang[i].harga > termahal->harga) {
            termahal = &daftarBarang[i];
        }
    }

    cout << " Barang Termahal Saat Ini:\n";
    cout << "   Kode Barang : " << termahal->kodeBarang << endl;
    cout << "   Nama Barang : " << termahal->namaBarang << endl;
    cout << "   Harga       : Rp " << termahal->harga << endl;
    cout << "   Stok        : " << termahal->stok << " pcs\n";
}

void hitungTotalAset(const vector<Barang>& daftarBarang) {
    cout << "\n--- Total Nilai Inventaris ---\n";
    double total = 0;
    for (const auto& b : daftarBarang) {
        total += b.harga * b.stok;
    }
    cout << "Total nilai aset seluruh barang di gudang: Rp " << (long long) total << endl;
}

void cekRestock(const vector<Barang>& daftarBarang) {
    cout << "\n--- Cek Stok Kritis (< 5) ---\n";

    bool adaKritis = false;

    for (const auto& b : daftarBarang) {

        if (b.stok < 5) {
            cout << "Kode : " << b.kodeBarang
                << " | Nama : " << b.namaBarang
                << " | Stok : " << b.stok << endl;

            adaKritis = true;
        }
    }

    if (!adaKritis) {
        cout << "Aman! Semua barang memiliki stok yang cukup (>= 5).\n";
    }
}


void updateStok(vector<Barang>& daftarBarang) {
    cout << "\n--- Update Stok Barang ---\n";
    if (daftarBarang.empty()) {
        cout << " Inventaris masih kosong.\n";
        return;
    }

    string targetKode;
    cout << "Masukkan Kode Barang yang ingin diupdate: ";
    getline(cin, targetKode);

    int* pointerStok = nullptr;
    string namaTarget = "";

    for (size_t i = 0; i < daftarBarang.size(); ++i) {
        if (daftarBarang[i].kodeBarang == targetKode) {
            pointerStok = &daftarBarang[i].stok;
            namaTarget = daftarBarang[i].namaBarang;
            break;
        }
    }

    if (pointerStok != nullptr) {
    cout << "Barang ditemukan: " << namaTarget
         << " (Stok saat ini: " << *pointerStok << ")\n";

    int stokBaru;

    do {
        cout << "Masukkan jumlah stok baru: ";
        cin >> stokBaru;

        if (stokBaru < 0) {
            cout << "Error! Stok tidak boleh negatif.\n";
        }

    } while (stokBaru < 0);

    *pointerStok = stokBaru;

    cout << "Stok berhasil diperbarui menjadi: "
         << *pointerStok << " pcs\n";
    }
}

int main() {
    vector<Barang> inventaris;
    int pilihanMenu;

    do {
        cout << "\n=========================================\n";
        cout << "     SISTEM MANAJEMEN INVENTARIS TOKO    \n";
        cout << "=========================================\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock (Stok < 5)\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "-----------------------------------------\n";
        cout << "Pilih menu (1-7): ";
        
        cin >> pilihanMenu;

        if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan tidak valid! Masukkan angka antara 1 sampai 7.\n";
        continue;
    }

cin.ignore();

        switch (pilihanMenu) {
            case 1:
                tambahBarang(inventaris);
                break;
            case 2:
                tampilkanSemuaBarang(inventaris);
                break;
            case 3:
                cariBarangTermahal(inventaris);
                break;
            case 4:
                hitungTotalAset(inventaris);
                break;
            case 5:
                cekRestock(inventaris);
                break;
            case 6:
                updateStok(inventaris);
                break;
            case 7:
                cout << "\n Keluar dari program. Terima kasih!\n";
                break;
            default:
                cout << " Pilihan menu tidak tersedia. Silakan coba lagi.\n";
        }
    } while (pilihanMenu != 7);

    return 0;
}
