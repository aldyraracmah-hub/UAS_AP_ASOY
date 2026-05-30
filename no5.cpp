#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

string buatPetunjuk(string negara) {
    string petunjuk(negara.length(), '_');

    int panjang = negara.length();

    // menampilkan minimal 2 huruf dari nama negara
    int pos1 = rand() % panjang;
    int pos2;

    do {
        pos2 = rand() % panjang;
    } while (pos1 == pos2);

    petunjuk[pos1] = negara[pos1];
    petunjuk[pos2] = negara[pos2];

    // menampilkan beberapa huruf tambahan secara acak
    for (int i = 0; i < panjang; i++) {
        if (petunjuk[i] == '_' && rand() % 100 < 30) {
            petunjuk[i] = negara[i];
        }
    }

    return petunjuk;
}

int main() {
    srand(time(0));

    vector<string> negara = {
    "indonesia",
    "malaysia",
    "singapura",
    "brunei",
    "thailand",
    "vietnam",
    "filipina",
    "kamboja",
    "laos",
    "myanmar",
    "jepang",
    "china",
    "india",
    "pakistan",
    "bangladesh",
    "korea",
    "mongolia",
    "rusia",
    "norwegia",
    "swedia",
    "finlandia",
    "denmark",
    "belanda",
    "jerman",
    "prancis",
    "italia",
    "spanyol",
    "portugal",
    "yunani",
    "turki",
    "inggris",
    "irlandia",
    "polandia",
    "ukraina",
    "mesir",
    "aljazair",
    "maroko",
    "tunisia",
    "libya",
    "sudan",
    "kenya",
    "uganda",
    "afrika",
    "kanada",
    "amerika",
    "meksiko",
    "argentina",
    "brasil",
    "chili",
    "peru",
    "kolombia",
    "australia",
    "selandiabaru",
    "oman",
    "qatar",
    "kuwait",
    "bahrain",
    "yaman",
    "suriah",
    "irak",
    "iran",
    "yordania",
    "lebanon"
};

    int skor = 0;
    char lagi = 'y';

    while (lagi == 'y' || lagi == 'Y') {

        int randomIndex = rand() % negara.size();
        string jawabanBenar = negara[randomIndex];

        string petunjuk = buatPetunjuk(jawabanBenar);

        string jawaban;

        cout << "\nTebak negara: " << petunjuk << endl;
        cout << "Negara apakah yang dimaksud? ";
        cin >> jawaban;

        for (char &c : jawaban)
            c = tolower(c);

        if (jawaban == jawabanBenar) {
            cout << "Selamat! Anda benar." << endl;
            skor++;
        }
        else {
            cout << "Maaf, jawaban Anda salah. Coba lagi." << endl;
            cout << "Jawaban yang benar: " << jawabanBenar << endl;
        }

        cout << "Skor Anda: " << skor << endl;
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> lagi;
    }

    cout << "\nGame Selesai :D" << endl;
}