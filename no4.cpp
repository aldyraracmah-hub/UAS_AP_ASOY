#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class Utama untuk mengelola semua logika permainan
class Minesweeper {
private:
    // Constraints: Array 2D statis maks 10x10
    int boardSize;
    int totalMines;
    int markedMinesCount; // Jumlah kotak yang ditandai pemain
    
    // Representasi papan menggunakan array statis
    // Kita gunakan char/int terpisah untuk menjaga state tanpa struct tambahan
    char realBoard[10][10];       // Menyimpan posisi bom ('X') dan angka sekitar ('0'-'8')
    char playerBoard[10][10];     // Papan yang dilihat pemain ('-', 'F', atau angka)
    
    bool isGameOver;
    bool isGameWon;
    time_t startTime;             // Pencatat waktu mulai

    // Menghitung jumlah bom di 8 tetangga sekitar kotak (r, c)
    int countAdjacentMines(int r, int c) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nr = r + i;
                int nc = c + j;
                // Validasi batas papan
                if (nr >= 0 && nr < boardSize && nc >= 0 && nc < boardSize) {
                    if (realBoard[nr][nc] == 'X') {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    // Efek Flood Fill menggunakan Rekursi untuk membuka area kosong (angka 0)
    void floodFill(int r, int c) {
        // Base case: jika di luar batas atau kotak sudah dibuka/ditandai
        if (r < 0 || r >= boardSize || c < 0 || c >= boardSize) return;
        if (playerBoard[r][c] != '-') return;

        // Buka kotak untuk pemain
        playerBoard[r][c] = realBoard[r][c];

        // Jika kotaknya berangka 0, rekursi ke 8 tetangganya
        if (realBoard[r][c] == '0') {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i != 0 || j != 0) {
                        floodFill(r + i, c + j);
                    }
                }
            }
        }
    }

public:
    // Inisialisasi game baru
    void setupGame() {
        // Validasi input ukuran papan (4-10)
        do {
            cout << "Masukkan ukuran papan (4 - 10): ";
            cin >> boardSize;
            if (boardSize < 4 || boardSize > 10) {
                cout << "Ukuran tidak valid! Harus antara 4 sampai 10.\n";
            }
        } while (boardSize < 4 || boardSize > 10);

        // Validasi input jumlah bom (Maksimal setengah dari total kotak agar masuk akal)
        int maxMines = (boardSize * boardSize) / 2;
        do {
            cout << "Masukkan jumlah bom (1 - " << maxMines << "): ";
            cin >> totalMines;
            if (totalMines < 1 || totalMines > maxMines) {
                cout << "Jumlah bom tidak valid! Maksimal untuk papan ini adalah " << maxMines << ".\n";
            }
        } while (totalMines < 1 || totalMines > maxMines);

        // Reset state papan
        isGameOver = false;
        isGameWon = false;
        markedMinesCount = 0;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                realBoard[i][j] = '0';
                playerBoard[i][j] = '-';
            }
        }

        // Tanam bom secara acak
        int minesPlanted = 0;
        while (minesPlanted < totalMines) {
            int r = rand() % boardSize;
            int c = rand() % boardSize;

            if (realBoard[r][c] != 'X') {
                realBoard[r][c] = 'X';
                minesPlanted++;
            }
        }

        // Hitung angka petunjuk di sekitar bom
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (realBoard[i][j] != 'X') {
                    int adjMines = countAdjacentMines(i, j);
                    realBoard[i][j] = '0' + adjMines; // Konversi int ke char
                }
            }
        }

        // Catat waktu mulai setelah setup selesai
        startTime = time(0);
    }

    // Tampilan papan ke layar console
    void displayBoard() {
        // Hitung durasi waktu berjalan saat ini
        int currentDuration = time(0) - startTime;

        cout << "\n==============================\n";
        cout << "        MINESWEEPER++         \n";
        cout << "==============================\n";
        cout << "Bom Tersisa: " << (totalMines - markedMinesCount) << " | Waktu: " << currentDuration << " detik\n\n";

        // Cetak nomor kolom atas (1..N)
        cout << "    ";
        for (int j = 1; j <= boardSize; j++) {
            cout << j << " ";
        }
        cout << "\n   " << "---------------------\n";

        // Cetak isi papan beserta nomor baris (1..N)
        for (int i = 0; i < boardSize; i++) {
            if (i + 1 < 10) cout << " "; // Alignment spasi rapi
            cout << (i + 1) << " | ";
            for (int j = 0; j < boardSize; j++) {
                cout << playerBoard[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "==============================\n";
    }

    // Logika ketika pemain membuka kotak
    void openCell(int r, int c) {
        // Jika kotak sudah diberi bendera (Flag), tidak bisa dibuka langsung
        if (playerBoard[r][c] == 'F') {
            cout << "Kotak ditandai bendera! Hapus tanda terlebih dahulu untuk membuka.\n";
            return;
        }

        // Jika kena bom -> Game Over
        if (realBoard[r][c] == 'X') {
            isGameOver = true;
            // Tampilkan semua bom ke pemain
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (realBoard[i][j] == 'X') playerBoard[i][j] = 'X';
                }
            }
        } else {
            // Lakukan efek flood fill jika aman
            floodFill(r, c);
        }
    }

    // Logika memberi atau menghapus tanda bendera (Flag)
    void toggleFlag(int r, int c) {
        if (playerBoard[r][c] == '-') {
            playerBoard[r][c] = 'F';
            markedMinesCount++;
        } else if (playerBoard[r][c] == 'F') {
            playerBoard[r][c] = '-';
            markedMinesCount--;
        } else {
            cout << "Kotak sudah terbuka, tidak bisa ditandai!\n";
        }
    }

    // Cek Kondisi Menang berdasarkan kecocokan tanda bendera
    void checkWinCondition() {
        int correctFlags = 0;
        int wrongFlags = 0;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (playerBoard[i][j] == 'F') {
                    if (realBoard[i][j] == 'X') {
                        correctFlags++;
                    } else {
                        wrongFlags++;
                    }
                }
            }
        }

        // Menang jika semua bom ditandai dengan tepat, dan tidak ada bendera salah tempat
        if (correctFlags == totalMines && wrongFlags == 0) {
            isGameWon = true;
        }
    }

    bool getIsGameOver() { return isGameOver; }
    bool getIsGameWon() { return isGameWon; }
    
    // Mengembalikan total waktu akhir permainan
    int getFinalTime() {
        return time(0) - startTime;
    }
};

// Fungsi Utama: Driver Menu & Loop Program
int main() {
    srand(time(0)); // Seed acak berdasarkan waktu lokal komputer
    Minesweeper game;
    int choice;

    do {
        cout << "\n====== MENU UTAMA ======\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;

        if (choice == 1) {
            game.setupGame();

            // Loop Ronde Permainan berjalan
            while (!game.getIsGameOver() && !game.getIsGameWon()) {
                game.displayBoard();

                int action, row, col;
                cout << "Pilih aksi:\n1. Buka Kotak\n2. Tandai/Hapus Bendera (Flag)\nPilihan: ";
                cin >> action;

                if (action != 1 && action != 2) {
                    cout << "Aksi tidak valid!\n";
                    continue;
                }

                cout << "Masukkan koordinat (Baris Kolom) contoh '3 4': ";
                cin >> row >> col;

                // Konversi koordinat user (1..N) ke indeks array C++ (0..N-1)
                int r = row - 1;
                int c = col - 1;

                // Validasi input koordinat
                if (r < 0 || r >= 10 || c < 0 || c >= 10) {
                    cout << "Koordinat di luar jangkauan papan permainan!\n";
                    continue;
                }

                // Eksekusi aksi pemain
                if (action == 1) {
                    game.openCell(r, c);
                } else {
                    game.toggleFlag(r, c);
                }

                // Periksa apakah pemain sudah menang setelah aksi dilakukan
                game.checkWinCondition();
            }

            // Tampilan akhir setelah game selesai (Menang/Kalah)
            game.displayBoard();
            int totalWaktu = game.getFinalTime();

            if (game.getIsGameWon()) {
                cout << "\n SELAMAT! Kamu berhasil menjinakkan semua bom dengan tepat! \n";
                cout << "Total Waktu Bermain: " << totalWaktu << " detik.\n";
            } else {
                cout << "\n BOOM! Kamu menginjak bom. Game Over! \n";
                cout << "Total Waktu Bermain: " << totalWaktu << " detik.\n";
            }

        } else if (choice != 2) {
            cout << "Pilihan menu tidak valid!\n";
        }

    } while (choice != 2);

    cout << "\nTerima kasih telah bermain Minesweeper++!\n";
    return 0;
}