#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int CABANG = 5;
const int HARI = 7;

// ------------------- FUNGSI INPUT DATA -------------------
void inputPenjualan(int data[CABANG][HARI]) {
    cout << "\n=== INPUT DATA PENJUALAN ===\n";
    for (int i = 0; i < CABANG; i++) {
        cout << "\nCabang " << i + 1 << endl;
        for (int j = 0; j < HARI; j++) {
            cout << "  Hari " << j + 1 << ": ";
            cin >> data[i][j];
        }
    }
}

// ------------------- FUNGSI DATA DUMMY (OTOMATIS) -------------------
void generateDummyData(int data[CABANG][HARI]) {
    cout << "\nSedang mengacak data penjualan...\n";
    cout << "Data berhasil diisi otomatis!\n";

    for (int i = 0; i < CABANG; i++) {
        for (int j = 0; j < HARI; j++) {
            data[i][j] = 500000 + (rand() % 4500000); 
        }
    }
}

// ------------------- FUNGSI TAMPILKAN TABEL -------------------
void tampilkanTabel(int data[CABANG][HARI]) {
    cout << "\n=== TABEL PENJUALAN ===\n";
    for (int i = 0; i < CABANG; i++) {
        cout << "Cabang " << i + 1 << " : ";
        for (int j = 0; j < HARI; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// ------------------- TOTAL PER CABANG -------------------
void totalPerCabang(int data[CABANG][HARI], int totalCabang[]) {
    for (int i = 0; i < CABANG; i++) {
        totalCabang[i] = 0;
        for (int j = 0; j < HARI; j++) {
            totalCabang[i] += data[i][j];
        }
    }
}

// ------------------- TOTAL PER HARI -------------------
void totalPerHari(int data[CABANG][HARI], int totalHari[]) {
    for (int j = 0; j < HARI; j++) {
        totalHari[j] = 0;
        for (int i = 0; i < CABANG; i++) {
            totalHari[j] += data[i][j];
        }
    }
}

// ------------------- CABANG TERTINGGI -------------------
int cabangTertinggi(int totalCabang[]) {
    int maxIndex = 0;
    for (int i = 1; i < CABANG; i++) {
        if (totalCabang[i] > totalCabang[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// ------------------- HARI TERBURUK -------------------
int hariTerburuk(int totalHari[]) {
    int minIndex = 0;
    for (int i = 1; i < HARI; i++) {
        if (totalHari[i] < totalHari[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// ------------------- CEK HARI < 1 JUTA -------------------
void cekHariDiBawahTarget(int data[CABANG][HARI]) {
    bool ditemukan = false;

    for (int j = 0; j < HARI; j++) {
        bool semuaDibawah = true;

        for (int i = 0; i < CABANG; i++) {
            if (data[i][j] >= 1000000) {  // jika ada yg tidak di bawah 1 juta
                semuaDibawah = false;
                break;
            }
        }

        if (semuaDibawah) {
            cout << "Hari " << j + 1 << " semua cabang penjualan < 1 juta\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada hari di mana seluruh cabang < 1 juta\n";
    }
}

// ------------------- SORTING TOTAL CABANG -------------------
void urutkanTotalCabang(int totalCabang[]) {
    for (int i = 0; i < CABANG - 1; i++) {
        for (int j = 0; j < CABANG - i - 1; j++) {
            if (totalCabang[j] < totalCabang[j + 1]) {
                swap(totalCabang[j], totalCabang[j + 1]);
            }
        }
    }
}

// =============================================================
//                          MAIN PROGRAM
// =============================================================
int main() {
    srand(time(0));
    int data[CABANG][HARI];
    int totalCabang[CABANG], totalHari[HARI];
    int pilihan, modeInput;

    cout << "=== PILIH MODE INPUT DATA ===\n";
    cout << "1. Input Manual (Ketik satu-satu)\n";
    cout << "2. Input Otomatis (Data Dummy/Acak)\n";
    cout << "Pilihan: ";
    cin >> modeInput;

    if (modeInput == 1) {
        inputPenjualan(data);
    } else {
        generateDummyData(data);
        tampilkanTabel(data); 
    }

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Tampilkan tabel penjualan\n";
        cout << "2. Total penjualan tiap cabang\n";
        cout << "3. Total penjualan per hari\n";
        cout << "4. Cabang dengan total penjualan tertinggi\n";
        cout << "5. Hari dengan performa terburuk\n";
        cout << "6. Cek hari seluruh cabang < 1 juta\n";
        cout << "7. Urutkan total penjualan cabang\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        cout << endl;

        switch (pilihan) {
        case 1:
            tampilkanTabel(data);
            break;

        case 2:
            totalPerCabang(data, totalCabang);
            cout << "\nTotal per cabang:\n";
            for (int i = 0; i < CABANG; i++) {
                cout << "Cabang " << i + 1 << ": " << totalCabang[i] << endl;
            }
            break;

        case 3:
            totalPerHari(data, totalHari);
            cout << "\nTotal per hari:\n";
            for (int i = 0; i < HARI; i++) {
                cout << "Hari " << i + 1 << ": " << totalHari[i] << endl;
            }
            break;

        case 4:
            totalPerCabang(data, totalCabang);
            cout << "Cabang dengan total tertinggi: Cabang " << cabangTertinggi(totalCabang) + 1 << endl;
            break;

        case 5:
            totalPerHari(data, totalHari);
            cout << "Hari dengan performa terburuk: Hari " << hariTerburuk(totalHari) + 1 << endl;
            break;

        case 6:
            cekHariDiBawahTarget(data);
            break;

        case 7:
            totalPerCabang(data, totalCabang);
            urutkanTotalCabang(totalCabang);
            cout << "\nTotal cabang (diurutkan tertinggi → terendah):\n";
            for (int i = 0; i < CABANG; i++) {
                cout << totalCabang[i] << " ";
            }
            cout << endl;
            break;

        case 8:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 8);

    return 0;
}
