#ifndef TEBAK_KATA_H
#define TEBAK_KATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int total_kata = 30;
const int max_skor = 5;

string bank_kata[total_kata] = {
    "sabun", "ember", "sikat", "kapal", "pisau", "pulsa",
    "komik", "radio", "surat", "kabel", "bulan", "hujan",
    "bunga", "lampu", "botol", "garis", "gitar", "tikar",
    "kipas", "warna", "dapur", "pagar", "bakso", "sopir",
    "kasur", "gelas", "kunci", "bakar", "belah", "bisik"
};

struct skor_entry {
    string nama;
    int poin;
    string level;
};

class leaderboard {
private:
    skor_entry data[max_skor];
    int jumlah;

public:
    leaderboard() : jumlah(0) {}

    void tambah(string nama, int poin, string level) {
        if (jumlah < max_skor) {
            data[jumlah] = {nama, poin, level};
            jumlah++;
        } else {
            int idx_min = 0;
            for (int i = 1; i < max_skor; i++) {
                if (data[i].poin < data[idx_min].poin) idx_min = i;
            }
            if (poin > data[idx_min].poin) {
                data[idx_min] = {nama, poin, level};
            }
        }
        urutkan();
    }

    void urutkan() {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - i - 1; j++) {
                if (data[j].poin < data[j + 1].poin) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void tampil() {
        cout << "\n**************** leaderboard ****************" << endl;
        if (jumlah == 0) {
            cout << "          (belum ada skor tersimpan)" << endl;
        } else {
            cout << "  no | nama             | poin | kesulitan" << endl;
            cout << "  ---|------------------|------|----------" << endl;
            for (int i = 0; i < jumlah; i++) {
                cout << "  " << i + 1 << "  | ";
                string nm = data[i].nama;
                for (int p = nm.size(); p < 16; p++) nm += ' ';
                cout << nm << " | " << data[i].poin
                     << "  | " << data[i].level << endl;
            }
        }
        cout << "*********************************************" << endl;
    }
};

leaderboard lb;

void bersihkan() {
    system("cls");
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

void tampil_judul() {
    cout << "*********************************************" << endl;
    cout << "              game tebak kata                " << endl;
    cout << "          selamat datang, pemain!            " << endl;
    cout << "*********************************************" << endl;
}

int pilih_level(string &nama_level) {
    int pilih, nyawa = 6;
    bool valid = false;

    while (!valid) {
        cout << "\npilih tingkat kesulitan:" << endl;
        cout << "1. easy   (8 nyawa)" << endl;
        cout << "2. medium (6 nyawa)" << endl;
        cout << "3. hard   (4 nyawa)" << endl;
        cout << "masukkan pilihan (1/2/3): ";
        cin >> pilih;

        if (pilih == 1)      { nama_level = "easy";   nyawa = 8; valid = true; }
        else if (pilih == 2) { nama_level = "medium"; nyawa = 6; valid = true; }
        else if (pilih == 3) { nama_level = "hard";   nyawa = 4; valid = true; }
        else                { cout << "  [!] pilihan tidak valid, coba lagi." << endl; }
    }
    return nyawa;
}

int dapat_waktu() {
    time_t sekarang = time(NULL);
    return (int)sekarang;
}

struct katagame {
    string kata;
    string status;
    int nyawa;
    string salah;
    bool hint_dipakai = false;
};

katagame buat_game(string kata, int nyawa) {
    katagame game;
    game.kata = kata;
    game.nyawa = nyawa;
    game.hint_dipakai = false;
    game.status = "";
    game.salah = "";
    for (int i = 0; i < kata.size(); i++) {
        game.status += '_';
        if (i < kata.size() - 1) game.status += ' ';
    }
    return game;
}

void tampil_status(const katagame *game) {
    cout << "\n******************************" << endl;
    cout << "  kata  : " << game->status << endl;
    cout << "  nyawa : " << game->nyawa << " sisa" << endl;
    cout << "  salah : ";
    if (game->salah.empty()) cout << "(belum ada)";
    else cout << game->salah;
    cout << endl;
    cout << "******************************" << endl;
}

bool sudah_tebak(const katagame *game, char huruf) {
    if (game->salah.find(huruf) != string::npos) return true;
    for (int i = 0; i < game->kata.size(); i++) {
        if (game->status[i * 2] == huruf) return true;
    }
    return false;
}

int proses_tebakan(katagame *game, char huruf) {
    if (sudah_tebak(game, huruf)) return -1;

    bool ada = false;
    for (int i = 0; i < game->kata.size(); i++) {
        if (game->kata[i] == huruf) {
            game->status[i * 2] = huruf;
            ada = true;
        }
    }

    if (ada) {
        return 1;
    } else {
        game->salah += huruf;
        game->salah += " ";
        game->nyawa--;
        return 0;
    }
}

bool menang(const katagame *game) {
    for (int i = 0; i < game->kata.size(); i++) {
        if (game->status[i * 2] == '_') return false;
    }
    return true;
}

int hitung_skor(string kesulitan, int sisa_nyawa, int panjang_kata) {
    int base = panjang_kata * 10;
    int bonus = sisa_nyawa * 5;
    int mult  = 1;
    if      (kesulitan == "medium") mult = 2;
    else if (kesulitan == "hard")   mult = 3;
    return (base + bonus) * mult;
}

int hitung_skor(string kesulitan, int sisa_nyawa, int panjang_kata, bool hint_dipakai) {
    int skor = hitung_skor(kesulitan, sisa_nyawa, panjang_kata);
    if (hint_dipakai) skor = skor * 80 / 100;
    return skor;
}

void pakai_hint(katagame *game) {
    if (game->nyawa <= 1) {
        cout << "  [!] nyawa terlalu sedikit!" << endl;
        return;
    }
    if (game->hint_dipakai) {
        cout << "  [!] hint sudah pernah digunakan!" << endl;
        return;
    }
    if (game->status[0] != '_') {
        cout << "  [!] huruf pertama sudah terbuka!" << endl;
        return;
    }

    char huruf_pertama = game->kata[0];
    for (int i = 0; i < game->kata.size(); i++) {
        if (game->kata[i] == huruf_pertama) {
            game->status[i * 2] = huruf_pertama;
        }
    }
    game->nyawa--;
    game->hint_dipakai = true;
    cout << "  [hint] huruf '" << huruf_pertama << "' terbuka! (-1 nyawa)" << endl;
}

void main_game(string level, int max_nyawa) {
    string kata = bank_kata[rand() % total_kata];

    katagame game = buat_game(kata, max_nyawa);

    string nama;
    cout << "\nmasukkan nama pemain: ";
    cin >> nama;

    bool selesai = false;

    do {
        bersihkan();
        tampil_judul();
        cout << "\n  kesulitan : " << level << endl;
        tampil_status(&game);

        if (game.nyawa <= 0) {
            cout << "\n  game over! nyawa habis." << endl;
            cout << "  kata yang benar: [ " << game.kata << " ]" << endl;
            selesai = true;
        } else if (menang(&game)) {
            int poin = hitung_skor(level, game.nyawa, game.kata.size(), game.hint_dipakai);
            cout << "\n  selamat! kamu berhasil menebak kata!" << endl;
            cout << "  kata  : [ " << game.kata << " ]" << endl;
            cout << "  poin  : " << poin << " poin";
            if (game.hint_dipakai) cout << " (hint -20%)";
            cout << endl;
            lb.tambah(nama, poin, level);
            selesai = true;
        } else {
            cout << "\n  pilih aksi:" << endl;
            cout << "  ketik [H] untuk gunakan hint (-1 nyawa, skor -20%)" << endl;
            cout << "  [huruf a-z] tebak huruf" << endl;
            cout << "  input: ";

            char inp;
            cin >> inp;

            if (inp == 'H') {
                pakai_hint(&game);
                if (menang(&game)) {
                    bersihkan();
                    tampil_judul();
                    tampil_status(&game);
                    int poin = hitung_skor(level, game.nyawa, game.kata.size(), game.hint_dipakai);
                    cout << "\n  selamat! kamu berhasil menebak kata!" << endl;
                    cout << "  kata  : [ " << game.kata << " ]" << endl;
                    cout << "  poin  : " << poin << " poin (hint -20%)" << endl;
                    lb.tambah(nama, poin, level);
                    selesai = true;
                }
            } else if (inp >= 'a' && inp <= 'z') {
                inp = to_lower(inp);
                int hasil = proses_tebakan(&game, inp);
                if (hasil == -1) {
                    cout << "  [!] huruf '" << inp << "' sudah pernah ditebak!" << endl;
                } else if (hasil == 1) {
                    cout << "  [v] benar! huruf '" << inp << "' ada dalam kata." << endl;
                } else {
                    cout << "  [x] salah! huruf '" << inp << "' tidak ada dalam kata." << endl;
                }
            } else {
                cout << "  [!] input tidak valid." << endl;
            }
            cout << "  tekan enter untuk melanjutkan...";
            cin.ignore(); cin.get();
        }
    } while (!selesai);
}

#endif