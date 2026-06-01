#include <iostream>
#include <vector>
#include <string>
#include <ctime> // library untuk fungsi waktu
#include <limits> // Library untuk batas nilai

using namespace std;

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk; // Menyimpan waktu masuk
};

class ParkirMall {
private:
    vector<Mobil*> daftarMobil;
    int kapasitas;

public:
    ParkirMall(int maxMobil) {
        kapasitas = maxMobil;
    }

    ~ParkirMall() {
        for (int i = 0; i < daftarMobil.size(); i++) {
            delete daftarMobil[i];
        }
    }

    void tambahMobil() {
        if (daftarMobil.size() >= kapasitas) {
            cout << "Maaf parkiran hanya dapat memuat " << kapasitas << " mobil !\n";
            system("pause");
            return;
        }

        int jumlahMobil;
        cout << "\nMasukkan jumlah mobil yang akan diparkirkan : ";
        cin >> jumlahMobil;

        if (daftarMobil.size() + jumlahMobil > kapasitas) {
            cout << "Maaf parkiran hanya dapat memuat " << kapasitas << " mobil !\n";
            system("pause");
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer input

        for (int i = 0; i < jumlahMobil; i++) {
            Mobil* mobilBaru = new Mobil;

            cout << "\nMobil ke " << daftarMobil.size() + 1 << endl;

            cout << "Masukkan plat mobil  : ";
            getline(cin, mobilBaru->plat);
            cout << "Masukkan merk mobil  : ";
            getline(cin, mobilBaru->merk);
            cout << "Masukkan warna mobil : ";
            getline(cin, mobilBaru->warna);

            mobilBaru->waktuMasuk = time(0); // Menyimpan waktu saat mobil masuk

            daftarMobil.push_back(mobilBaru);
        }
    }

    void tampilkanMobil() {
        if (daftarMobil.empty()) {
            cout << "\nBelum ada mobil yang parkir.\n";
            return;
        }

        cout << "\nDAFTAR MOBIL YANG SUDAH TERPARKIR :\n";
        cout << "====================================================\n";

        for (int i = 0; i < daftarMobil.size(); i++) {
            time_t sekarang = time(0); // Menyimpan waktu sekarang
            int durasi = difftime(sekarang, daftarMobil[i]->waktuMasuk); // Menghitung lama parkir dengan selisih waktu masuk

            int jam = durasi / 3600;
            int menit = (durasi % 3600) / 60;
            int detik = durasi % 60;

            cout << "\nMobil ke-" << i + 1 << endl;
            cout << "Plat mobil   : " << daftarMobil[i]->plat << endl;
            cout << "Merk mobil   : " << daftarMobil[i]->merk << endl;
            cout << "Warna mobil  : " << daftarMobil[i]->warna << endl;
            cout << "Waktu parkir : " << jam << " jam "
                 << menit << " menit "
                 << detik << " detik" << endl;
            cout << "\n====================================================\n";
        }
    }

    void pembayaran() {
        if (daftarMobil.empty()) {
            cout << "\nTidak ada mobil di parkiran.\n";
            return;
        }

        tampilkanMobil();

        string cariPlat;
        bool ditemukan = false;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (!ditemukan) {
            cout << "\nMasukkan plat mobil yang ingin dibayar : ";
            getline(cin, cariPlat);

            for (int i = 0; i < daftarMobil.size(); i++) {
                if (daftarMobil[i]->plat == cariPlat) {
                    ditemukan = true;

                    time_t sekarang = time(0);
                    int durasiDetik = difftime(sekarang, daftarMobil[i]->waktuMasuk);

                    int biaya = durasiDetik * 2;

                    cout << "\nB I A Y A   P A R K I R : Rp" << biaya << endl;
                    cout << "====================================================\n";

                    delete daftarMobil[i];
                    daftarMobil.erase(daftarMobil.begin() + i);

                    break;
                }
            }

            if (!ditemukan) {
                cout << "\nPLAT TIDAK DITEMUKAN! Silakan coba lagi.\n";
            }
        }
    }
};

int main() {
    string namaPetugas, idPetugas;

    system("cls");

    cout << "=====================================================================\n";
    cout << "-------------------- S E L A M A T   D A T A N G --------------------\n";
    cout << "                    DI PORTAL PARKIR KHUSUS MOBIL\n";
    cout << "                           MALL PRIENAL\n";
    cout << "=====================================================================\n";

    cout << "\nKami senang Anda telah hadir.\n";
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n";

    cout << "\nMasukkan nama : ";
    getline(cin, namaPetugas);
    cout << "Masukkan ID   : ";
    getline(cin, idPetugas);

    ParkirMall parkir(20);

    int opsi;

    do {
        system("cls");

        cout << "\n====================================================\n";
        cout << "Nama Petugas : " << namaPetugas << endl;
        cout << "ID Petugas   : " << idPetugas << endl;
        cout << "\n          TERIMA KASIH ATAS KERJASAMANYA !\n";
        cout << "---------- S E L A M A T  B E R T U G A S ----------\n";
        cout << "====================================================\n";

        cout << "\nSilahkan input opsi berikut dalam bentuk angka.\n";
        cout << "1. Tambahkan Daftar Kendaraan\n";
        cout << "2. Tampilkan Daftar Kendaraan\n";
        cout << "3. Pembayaran\n";
        cout << "4. Keluar Program\n";

        cout << "\nMasukkan opsi : ";
        cin >> opsi;

        switch (opsi) {
        case 1:
            parkir.tambahMobil();
            break;

        case 2:
            parkir.tampilkanMobil();
            system("pause");
            break;

        case 3:
            parkir.pembayaran();
            system("pause");
            break;

        case 4:
            cout << "\nPROGRAM SELESAI. TERIMA KASIH\n";
            break;

        default:
            cout << "\nOpsi tidak tersedia!\n";
            system("pause");
        }
    } while (opsi != 4);
}