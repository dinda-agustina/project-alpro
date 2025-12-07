/*
 * Program Analisis Penjualan Multi-Cabang
 * Program ini mengelola dan menganalisis data penjualan dari 5 cabang selama 7 hari
 */

#include <iostream>   // Library untuk input/output (cout, cin)
#include <iomanip>    // Library untuk manipulasi format output (setw, left, right)
#include <cstdlib>    // Library untuk fungsi random (rand)
#include <ctime>      // Library untuk fungsi waktu (time) - digunakan untuk seed random

using namespace std;

// Konstanta global untuk jumlah cabang dan hari
const int CABANG = 5;  // Jumlah cabang toko
const int HARI = 7;    // Jumlah hari dalam satu minggu

// Struktur data untuk menyimpan informasi cabang (tidak digunakan dalam program ini)
struct DataCabang {
    int id;      // ID cabang
    int total;   // Total penjualan cabang
};

// ===============================================================
// FUNGSI: inputPenjualan
// Deskripsi: Menerima input data penjualan secara manual dari user
// Parameter: 
//   - data[][]: array 2D untuk menyimpan data penjualan
// ===============================================================
void inputPenjualan(int data[CABANG][HARI]) {
    cout << "\n=== INPUT DATA PENJUALAN ===\n";
    
    // Loop untuk setiap cabang (5 cabang)
    for (int i = 0; i < CABANG; i++) {
        cout << "\nCabang " << i + 1 << endl;  // Tampilkan nomor cabang (dimulai dari 1)
        
        // Loop untuk setiap hari (7 hari)
        for (int j = 0; j < HARI; j++) {
            cout << "  Hari " << j + 1 << ": ";  // Minta input untuk hari ke-j
            cin >> data[i][j];  // Simpan input ke array data[cabang][hari]
        }
    }
}

// ===============================================================
// FUNGSI: generateDummyData
// Deskripsi: Mengisi data penjualan secara otomatis dengan angka acak
// Parameter: 
//   - data[][]: array 2D untuk menyimpan data penjualan
// Range data: 500.000 - 5.000.000
// ===============================================================
void generateDummyData(int data[CABANG][HARI]) {
    cout << "\nSedang mengacak data penjualan...\n";
    cout << "Data berhasil diisi otomatis!\n";

    // Loop untuk setiap cabang
    for (int i = 0; i < CABANG; i++) {
        // Loop untuk setiap hari
        for (int j = 0; j < HARI; j++) {
            // Generate angka random antara 500.000 - 5.000.000
            // Formula: 500000 + (angka random 0-4499999)
            data[i][j] = 500000 + (rand() % 4500000); 
        }
    }
}

// ===============================================================
// FUNGSI: tampilkanTabel
// Deskripsi: Menampilkan data penjualan dalam format tabel yang rapi
// Parameter: 
//   - data[][]: array 2D yang berisi data penjualan
// ===============================================================
void tampilkanTabel(int data[CABANG][HARI]) {
    cout << "\n=== TABEL PENJUALAN ===\n";
    
    // Cetak header tabel (kolom untuk hari)
    cout << left << setw(12) << " ";  // Spasi kosong untuk kolom pertama (label cabang)

    // Loop untuk header hari (H-1, H-2, ..., H-7)
    for (int j = 0; j < HARI; j++) {
        cout << right << setw(9) << ("H-" + to_string(j + 1));  // Cetak H-1, H-2, dst dengan lebar 9 karakter
    }
    cout << endl;

    // Cetak garis pemisah header
    cout << left << setw(12) << "-----------";  // Garis untuk kolom pertama
    for (int j = 0; j < HARI; j++) {
        cout << right << setw(9) << "--------";  // Garis untuk setiap kolom hari
    }
    cout << endl;

    // Loop untuk setiap cabang (baris tabel)
    for (int i = 0; i < CABANG; i++) {
        // Buat label untuk baris (contoh: "Cabang 1 :")
        string label = "Cabang " + to_string(i + 1) + " :";
        cout << left << setw(12) << label;  // Cetak label cabang dengan rata kiri
        
        // Loop untuk setiap hari (kolom tabel)
        for (int j = 0; j < HARI; j++) {
            cout << right << setw(9) << data[i][j];  // Cetak data penjualan dengan rata kanan
        }
        cout << endl;  // Pindah ke baris berikutnya
    }
}

// ===============================================================
// FUNGSI: totalPerCabang
// Deskripsi: Menghitung total penjualan untuk setiap cabang
// Parameter: 
//   - data[][]: array 2D yang berisi data penjualan
//   - totalCabang[]: array untuk menyimpan hasil total per cabang
// ===============================================================
void totalPerCabang(int data[CABANG][HARI], int totalCabang[]) {
    // Loop untuk setiap cabang
    for (int i = 0; i < CABANG; i++) {
        totalCabang[i] = 0;  // Inisialisasi total cabang ke-i dengan 0
        
        // Loop untuk setiap hari, jumlahkan semua penjualan
        for (int j = 0; j < HARI; j++) {
            totalCabang[i] += data[i][j];  // Akumulasi penjualan hari ke-j ke total cabang
        }
    }
}

// ===============================================================
// FUNGSI: totalPerHari
// Deskripsi: Menghitung total penjualan untuk setiap hari (semua cabang)
// Parameter: 
//   - data[][]: array 2D yang berisi data penjualan
//   - totalHari[]: array untuk menyimpan hasil total per hari
// ===============================================================
void totalPerHari(int data[CABANG][HARI], int totalHari[]) {
    // Loop untuk setiap hari
    for (int j = 0; j < HARI; j++) {
        totalHari[j] = 0;  // Inisialisasi total hari ke-j dengan 0
        
        // Loop untuk setiap cabang, jumlahkan semua penjualan di hari yang sama
        for (int i = 0; i < CABANG; i++) {
            totalHari[j] += data[i][j];  // Akumulasi penjualan cabang ke-i ke total hari
        }
    }
}

// ===============================================================
// FUNGSI: cabangTertinggi
// Deskripsi: Mencari cabang dengan total penjualan tertinggi
// Parameter: 
//   - totalCabang[]: array yang berisi total penjualan per cabang
// Return: index cabang dengan penjualan tertinggi (0-4)
// ===============================================================
int cabangTertinggi(int totalCabang[]) {
    int maxIndex = 0;  // Asumsikan cabang pertama (index 0) adalah yang tertinggi
    
    // Loop mulai dari cabang kedua (index 1) hingga terakhir
    for (int i = 1; i < CABANG; i++) {
        // Jika total cabang ke-i lebih besar dari cabang tertinggi saat ini
        if (totalCabang[i] > totalCabang[maxIndex]) {
            maxIndex = i;  // Update index cabang tertinggi
        }
    }
    return maxIndex;  // Kembalikan index cabang tertinggi
}

// ===============================================================
// FUNGSI: hariTerburuk
// Deskripsi: Mencari hari dengan total penjualan terendah
// Parameter: 
//   - totalHari[]: array yang berisi total penjualan per hari
// Return: index hari dengan penjualan terendah (0-6)
// ===============================================================
int hariTerburuk(int totalHari[]) {
    int minIndex = 0;  // Asumsikan hari pertama (index 0) adalah yang terendah
    
    // Loop mulai dari hari kedua (index 1) hingga terakhir
    for (int i = 1; i < HARI; i++) {
        // Jika total hari ke-i lebih kecil dari hari terendah saat ini
        if (totalHari[i] < totalHari[minIndex]) {
            minIndex = i;  // Update index hari terendah
        }
    }
    return minIndex;  // Kembalikan index hari terendah
}

// ===============================================================
// FUNGSI: cekHariDiBawahTarget
// Deskripsi: Mencari hari dimana SEMUA cabang memiliki penjualan < 1 juta
// Parameter: 
//   - data[][]: array 2D yang berisi data penjualan
// ===============================================================
void cekHariDiBawahTarget(int data[CABANG][HARI]) {
    bool ditemukan = false;  // Flag untuk menandai apakah ada hari yang memenuhi kriteria

    // Loop untuk setiap hari
    for (int j = 0; j < HARI; j++) {
        bool semuaDibawah = true;  // Asumsikan semua cabang di bawah 1 juta

        // Loop untuk setiap cabang di hari tersebut
        for (int i = 0; i < CABANG; i++) {
            // Jika ada cabang yang penjualannya >= 1 juta
            if (data[i][j] >= 1000000) {
                semuaDibawah = false;  // Tandai bahwa tidak semua cabang di bawah 1 juta
                break;  // Keluar dari loop cabang (tidak perlu cek cabang lainnya)
            }
        }

        // Jika semua cabang di hari ini < 1 juta
        if (semuaDibawah) {
            cout << "Hari " << j + 1 << " semua cabang penjualan < 1 juta\n";
            ditemukan = true;  // Tandai bahwa ada hari yang ditemukan
        }
    }

    // Jika tidak ada hari yang memenuhi kriteria
    if (!ditemukan) {
        cout << "Tidak ada hari di mana seluruh cabang < 1 juta\n";
    }
}

// ===============================================================
// FUNGSI: urutkanTotalCabang
// Deskripsi: Mengurutkan dan menampilkan cabang berdasarkan total penjualan
//            (dari tertinggi ke terendah) menggunakan Bubble Sort
// Parameter: 
//   - totalCabang[]: array yang berisi total penjualan per cabang
// ===============================================================
void urutkanTotalCabang(int totalCabang[]) {
    // Buat array sementara untuk menyimpan data yang akan diurutkan
    int tempTotal[CABANG];   // Array untuk menyimpan total penjualan
    int idCabang[CABANG];    // Array untuk menyimpan ID/nomor cabang

    // Salin data ke array sementara
    for (int i = 0; i < CABANG; i++) {
        tempTotal[i] = totalCabang[i];  // Salin total penjualan
        idCabang[i] = i + 1;            // Salin nomor cabang (1-5, bukan 0-4)
    }

    // Algoritma Bubble Sort (pengurutan gelembung)
    // Loop luar: jumlah pass yang diperlukan (CABANG-1 kali)
    for (int i = 0; i < CABANG - 1; i++) {
        // Loop dalam: bandingkan elemen yang bersebelahan
        // Setiap iterasi, elemen terbesar akan "menggelembung" ke akhir
        for (int j = 0; j < CABANG - i - 1; j++) {
            // Jika elemen saat ini lebih kecil dari elemen berikutnya
            // (urutkan dari besar ke kecil)
            if (tempTotal[j] < tempTotal[j + 1]) {
                // Tukar posisi total penjualan
                int t = tempTotal[j];
                tempTotal[j] = tempTotal[j + 1];
                tempTotal[j + 1] = t;

                // Tukar posisi ID cabang agar tetap sesuai dengan totalnya
                int tID = idCabang[j];
                idCabang[j] = idCabang[j + 1];
                idCabang[j + 1] = tID;
            }
        }
    }

    // Tampilkan hasil pengurutan
    cout << "\n=== PERINGKAT PENJUALAN (Tertinggi ke Terendah) ===\n";
    for (int i = 0; i < CABANG; i++) {
        // Cetak peringkat, nomor cabang, dan total penjualan
        cout << "Peringkat " << i + 1 << " : Cabang " << idCabang[i] 
             << " (Total: " << tempTotal[i] << ")\n";
    }
}

// ===============================================================
//                      FUNGSI UTAMA (MAIN)
// ===============================================================
int main() {
    // Inisialisasi seed untuk random number generator
    // menggunakan waktu saat ini agar angka random berbeda setiap run
    srand(time(0));
    
    // Deklarasi variabel
    int data[CABANG][HARI];        // Array 2D untuk menyimpan data penjualan (5x7)
    int totalCabang[CABANG];       // Array untuk menyimpan total per cabang (5 elemen)
    int totalHari[HARI];           // Array untuk menyimpan total per hari (7 elemen)
    int pilihan, modeInput;        // Variabel untuk menyimpan pilihan menu user

    // Menu pemilihan mode input data
    cout << "=== PILIH MODE INPUT DATA ===\n";
    cout << "1. Input Manual (Ketik satu-satu)\n";
    cout << "2. Input Otomatis (Data Dummy/Acak)\n";
    cout << "Pilihan: ";
    cin >> modeInput;  // Terima input dari user

    // Proses input data berdasarkan pilihan user
    if (modeInput == 1) {
        inputPenjualan(data);  // Jika pilih 1, input manual
    } else {
        generateDummyData(data);  // Jika pilih 2 (atau lainnya), generate otomatis
        tampilkanTabel(data);     // Langsung tampilkan tabel setelah generate
    }

    // Loop menu utama program (do-while agar minimal dijalankan 1 kali)
    do {
        // Tampilkan menu utama
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
        cin >> pilihan;  // Terima pilihan menu dari user

        cout << endl;  // Baris kosong untuk pemisah

        // Switch-case untuk menjalankan fungsi sesuai pilihan user
        switch (pilihan) {
        case 1:
            // Menu 1: Tampilkan tabel penjualan
            tampilkanTabel(data);
            break;

        case 2:
            // Menu 2: Hitung dan tampilkan total penjualan per cabang
            totalPerCabang(data, totalCabang);  // Hitung total
            cout << "\nTotal per cabang:\n";
            // Loop untuk menampilkan total setiap cabang
            for (int i = 0; i < CABANG; i++) {
                cout << "Cabang " << i + 1 << ": " << totalCabang[i] << endl;
            }
            break;

        case 3:
            // Menu 3: Hitung dan tampilkan total penjualan per hari
            totalPerHari(data, totalHari);  // Hitung total
            cout << "\nTotal per hari:\n";
            // Loop untuk menampilkan total setiap hari
            for (int i = 0; i < HARI; i++) {
                cout << "Hari " << i + 1 << ": " << totalHari[i] << endl;
            }
            break;

        case 4:
            // Menu 4: Cari dan tampilkan cabang dengan total tertinggi
            totalPerCabang(data, totalCabang);  // Hitung total dulu
            // Tampilkan hasil (+1 karena index dimulai dari 0)
            cout << "Cabang dengan total tertinggi: Cabang " << cabangTertinggi(totalCabang) + 1 << endl;
            break;

        case 5:
            // Menu 5: Cari dan tampilkan hari dengan performa terburuk
            totalPerHari(data, totalHari);  // Hitung total dulu
            // Tampilkan hasil (+1 karena index dimulai dari 0)
            cout << "Hari dengan performa terburuk: Hari " << hariTerburuk(totalHari) + 1 << endl;
            break;

        case 6:
            // Menu 6: Cek hari dimana semua cabang penjualannya < 1 juta
            cekHariDiBawahTarget(data);
            break;

        case 7:
            // Menu 7: Urutkan dan tampilkan peringkat cabang
            totalPerCabang(data, totalCabang);  // Hitung total dulu
            urutkanTotalCabang(totalCabang);    // Urutkan dan tampilkan
            break;

        case 8:
            // Menu 8: Keluar dari program
            cout << "Program selesai.\n";
            break;

        default:
            // Jika user input pilihan yang tidak valid (bukan 1-8)
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 8);  // Ulangi selama user belum pilih 8 (Keluar)

    return 0;  // Program selesai dengan sukses
}