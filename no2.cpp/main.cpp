#include "TebakKata.h"

int main() {
    // inisialisasi seed dari waktu sekarang
    srand(dapat_waktu());

    bersihkan();
    tampil_judul();
    cout << "\nselamat datang di game tebak kata" << endl;
    cout << "tekan enter untuk memulai...";
    cin.get();

    char ulang;
 
    do {
        bersihkan();
        tampil_judul();

        string kesulitan;
        int maks_nyawa = pilih_level(kesulitan);

        main_game(kesulitan, maks_nyawa);

        lb.tampil();

        do {
            cout << "\napakah ingin bermain lagi? (y/n): ";
            cin >> ulang;
            ulang = to_lower(ulang);
            if (ulang != 'y' && ulang != 'n') {
                cout << "  [!] masukkan y atau n saja." << endl;
            }
        } while (ulang != 'y' && ulang != 'n');

    } while (ulang == 'y');

    bersihkan();
    tampil_judul();
    cout << "\nterima kasih sudah bermain, sampai jumpa lagi!" << endl;
    lb.tampil();
    cout << endl;

    return 0;
} 