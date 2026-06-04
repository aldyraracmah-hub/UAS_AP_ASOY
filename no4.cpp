#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Minesweeper {
private:
    int boardSize;
    int totalMines;
    int markedMinesCount; 
    
    char realBoard[10][10];       
    char playerBoard[10][10];     
    
    bool isGameOver;
    bool isGameWon;
    time_t startTime;             

    int countAdjacentMines(int r, int c) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nr = r + i;
                int nc = c + j;
                if (nr >= 0 && nr < boardSize && nc >= 0 && nc < boardSize) {
                    if (realBoard[nr][nc] == 'X') {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    void floodFill(int r, int c) {
        if (r < 0 || r >= boardSize || c < 0 || c >= boardSize) return;
        if (playerBoard[r][c] != '-') return;

        playerBoard[r][c] = realBoard[r][c];

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
int getBoardSize() {
    return boardSize;
}
    void setupGame() {
        do {
            cout << "Masukkan ukuran papan (4 - 10): ";
            cin >> boardSize;
            if (boardSize < 4 || boardSize > 10) {
                cout << "Ukuran tidak valid! Harus antara 4 sampai 10.\n";
            }
        } while (boardSize < 4 || boardSize > 10);

        int maxMines = (boardSize * boardSize) / 2;
        do {
            cout << "Masukkan jumlah bom (1 - " << maxMines << "): ";
            cin >> totalMines;
            if (totalMines < 1 || totalMines > maxMines) {
                cout << "Jumlah bom tidak valid! Maksimal untuk papan ini adalah " << maxMines << ".\n";
            }
        } while (totalMines < 1 || totalMines > maxMines);

        isGameOver = false;
        isGameWon = false;
        markedMinesCount = 0;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                realBoard[i][j] = '0';
                playerBoard[i][j] = '-';
            }
        }

        int minesPlanted = 0;
        while (minesPlanted < totalMines) {
            int r = rand() % boardSize;
            int c = rand() % boardSize;

            if (realBoard[r][c] != 'X') {
                realBoard[r][c] = 'X';
                minesPlanted++;
            }
        }

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (realBoard[i][j] != 'X') {
                    int adjMines = countAdjacentMines(i, j);
                    realBoard[i][j] = '0' + adjMines; 
                }
            }
        }

        startTime = time(0);
    }

    void displayBoard() {
        int currentDuration = time(0) - startTime;
        int correctFlags = 0;

        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (playerBoard[i][j] == 'F' &&
                    realBoard[i][j] == 'X') {
                    correctFlags++;
                }
            }
        }

        cout << "\n==============================\n";
        cout << "        MINESWEEPER++         \n";
        cout << "==============================\n";
        
        cout << "Bom Tersisa: " << (totalMines - correctFlags)<< " | Waktu: "<< currentDuration<< " detik\n\n";

        cout << "    ";
        for (int j = 1; j <= boardSize; j++) {
            cout << j << " ";
        }
        cout << "\n   " << "---------------------\n";

        for (int i = 0; i < boardSize; i++) {
            if (i + 1 < 10) cout << " "; 
            cout << (i + 1) << " | ";
            for (int j = 0; j < boardSize; j++) {
                cout << playerBoard[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "==============================\n";
    }

    void openCell(int r, int c) {
        if (playerBoard[r][c] != '-' && playerBoard[r][c] != 'F') {
            cout << "Kotak sudah terbuka!\n";
            return;
        }
        if (playerBoard[r][c] == 'F') {
            cout << "Kotak ditandai bendera! Hapus tanda terlebih dahulu untuk membuka.\n";
            return;
        }

        if (realBoard[r][c] == 'X') {
            isGameOver = true;
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (realBoard[i][j] == 'X') playerBoard[i][j] = 'X';
                }
            }
        } else {
            floodFill(r, c);
        }
    }

    void toggleFlag(int r, int c) {

    if (playerBoard[r][c] == '-') {

        if (markedMinesCount >= totalMines) {
            cout << "Jumlah flag sudah mencapai jumlah bom!\n";
            return;
        }

        playerBoard[r][c] = 'F';
        markedMinesCount++;

    } else if (playerBoard[r][c] == 'F') {

        playerBoard[r][c] = '-';
        markedMinesCount--;

    } else {

        cout << "Kotak sudah terbuka, tidak bisa ditandai!\n";

    }
}

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

        if (correctFlags == totalMines && wrongFlags == 0) {
            isGameWon = true;
        }
    }

    bool getIsGameOver() { return isGameOver; }
    bool getIsGameWon() { return isGameWon; }
    
    int getFinalTime() {
        return time(0) - startTime;
    }
};

int main() {
    srand(time(0)); 
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

                int r = row - 1;
                int c = col - 1;

                if (r < 0 || r >= game.getBoardSize() ||
                    c < 0 || c >= game.getBoardSize()) {

                    cout << "Koordinat di luar jangkauan papan permainan!\n";
                    continue;
                }

                if (action == 1) {
                    game.openCell(r, c);
                } else {
                    game.toggleFlag(r, c);
                }

                game.checkWinCondition();
            }

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