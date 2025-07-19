#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"


void enableColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}


void loadingAnimation(const string& text, int duration = 3) {
    cout << CYAN << text << RESET;
    for (int i = 0; i < duration; i++) {
        for (int j = 0; j < 3; j++) {
            cout << YELLOW << "." << RESET;
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        cout << "\b\b\b   \b\b\b";
    }
    cout << GREEN << " SELESAI!" << RESET << endl;
}


void typeText(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}


void clearScreen() {
    system("cls");
}


void showAnimatedHeader() {
    clearScreen();
    cout << BOLD << CYAN;
    typeText("\n");
    typeText("  #######  #     #  #######  #######  #     #\n", 30);
    typeText("  #        #     #        #        #   #   # \n", 30);
    typeText("  #####    #     #    ####     ####     # #  \n", 30);
    typeText("  #        #     #       #        #      #   \n", 30);
    typeText("  #        #######  #######  #######      #   \n", 30);
    typeText("                                              \n", 30);
    cout << RESET;
    
    cout << BOLD << MAGENTA;
    typeText("\n     SISTEM KLASIFIKASI KUALITAS AIR\n", 40);
    typeText("        MENGGUNAKAN LOGIKA FUZZY\n", 40);
    cout << RESET;
    
    cout << YELLOW;
    typeText("\n  ==========================================\n", 20);
    cout << RESET;
    
    this_thread::sleep_for(chrono::milliseconds(1000));
}

class FuzzyWaterQuality {
private:

    double ppmRendah(double ppm) {
        if (ppm <= 50) return 1.0;
        else if (ppm <= 150) return (150 - ppm) / 100.0;
        else return 0.0;
    }
    
    double ppmSedang(double ppm) {
        if (ppm <= 50 || ppm >= 300) return 0.0;
        else if (ppm <= 150) return (ppm - 50) / 100.0;
        else if (ppm <= 200) return 1.0;
        else return (300 - ppm) / 100.0;
    }
    
    double ppmTinggi(double ppm) {
        if (ppm <= 200) return 0.0;
        else if (ppm <= 300) return (ppm - 200) / 100.0;
        else return 1.0;
    }
    

    double suhuDingin(double suhu) {
        if (suhu <= 15) return 1.0;
        else if (suhu <= 25) return (25 - suhu) / 10.0;
        else return 0.0;
    }
    
    double suhuNormal(double suhu) {
        if (suhu <= 15 || suhu >= 35) return 0.0;
        else if (suhu <= 25) return (suhu - 15) / 10.0;
        else if (suhu <= 30) return 1.0;
        else return (35 - suhu) / 5.0;
    }
    
    double suhuPanas(double suhu) {
        if (suhu <= 30) return 0.0;
        else if (suhu <= 35) return (suhu - 30) / 5.0;
        else return 1.0;
    }
    

    double fuzzyAND(double a, double b) {
        return min(a, b);
    }
    

    double fuzzyOR(double a, double b) {
        return max(a, b);
    }
    
public:
    struct HasilKlasifikasi {
        double ppm, suhu;
        double amanDikonsumsi;
        double beracun;
        double mengandungKimia;
        string kategoriUtama;
        string deskripsi;
        string jenisAir;
        string rekomendasi;
    };
    
    HasilKlasifikasi klasifikasiAir(double ppm, double suhu, string jenisAir) {
        HasilKlasifikasi hasil;
        

        hasil.ppm = ppm;
        hasil.suhu = suhu;
        hasil.jenisAir = jenisAir;
        

        double ppm_rendah = ppmRendah(ppm);
        double ppm_sedang = ppmSedang(ppm);
        double ppm_tinggi = ppmTinggi(ppm);
        
        double suhu_dingin = suhuDingin(suhu);
        double suhu_normal = suhuNormal(suhu);
        double suhu_panas = suhuPanas(suhu);
        

        

        double aman1 = fuzzyAND(ppm_rendah, suhu_normal);
        double aman2 = fuzzyAND(ppm_sedang, suhu_normal);
        double aman3 = fuzzyAND(ppm_rendah, suhu_dingin);
        hasil.amanDikonsumsi = fuzzyOR(fuzzyOR(aman1, aman2), aman3);
        

        double beracun1 = fuzzyAND(ppm_tinggi, suhu_panas);
        double beracun2 = fuzzyAND(ppm_tinggi, suhu_normal);
        double beracun3 = ppm_tinggi;
        hasil.beracun = fuzzyOR(fuzzyOR(beracun1, beracun2), beracun3);
        

        double kimia1 = fuzzyAND(ppm_sedang, suhu_panas);
        double kimia2 = fuzzyAND(ppm_tinggi, suhu_dingin);
        double kimia3 = fuzzyAND(ppm_sedang, suhu_dingin);
        hasil.mengandungKimia = fuzzyOR(fuzzyOR(kimia1, kimia2), kimia3);
        

        if (hasil.amanDikonsumsi >= hasil.beracun && hasil.amanDikonsumsi >= hasil.mengandungKimia) {
            hasil.kategoriUtama = "AMAN DIKONSUMSI";
            hasil.deskripsi = "Air ini aman untuk dikonsumsi sehari-hari";
        }
        else if (hasil.beracun >= hasil.mengandungKimia) {
            hasil.kategoriUtama = "BERACUN";
            hasil.deskripsi = "Air ini mengandung zat berbahaya dan tidak aman dikonsumsi";
        }
        else {
            hasil.kategoriUtama = "MENGANDUNG KIMIA";
            hasil.deskripsi = "Air ini mengandung bahan kimia yang perlu diwaspadai";
        }
        

        hasil.rekomendasi = generateRekomendasi(jenisAir, hasil.kategoriUtama, ppm, suhu);
        
        return hasil;
    }
    
    void tampilkanHasil(HasilKlasifikasi hasil) {
        cout << "\n" << BOLD << CYAN << "+===============================================+" << RESET << endl;
        cout << BOLD << CYAN << "|" << RESET << BOLD << WHITE << "     HASIL KLASIFIKASI KUALITAS AIR        " << RESET << BOLD << CYAN << "|" << RESET << endl;
        cout << BOLD << CYAN << "+===============================================+" << RESET << endl;
        
        cout << "\n" << BOLD << YELLOW << "[DATA] Input Data:" << RESET << endl;
        cout << BLUE << "   - Jenis Air: " << WHITE << hasil.jenisAir << RESET << endl;
        cout << BLUE << "   - PPM (Parts Per Million): " << WHITE << hasil.ppm << RESET << endl;
        cout << BLUE << "   - Suhu Air: " << WHITE << hasil.suhu << " derajat C" << RESET << endl;
        
        loadingAnimation("\n[ANALISIS] Menganalisis data", 2);
        
        cout << "\n" << BOLD << MAGENTA << "[HASIL] Hasil Analisis Fuzzy:" << RESET << endl;
        cout << fixed << setprecision(3);
        

        showProgressBar("Aman Dikonsumsi", hasil.amanDikonsumsi, GREEN);
        showProgressBar("Beracun", hasil.beracun, RED);
        showProgressBar("Mengandung Kimia", hasil.mengandungKimia, YELLOW);
        
        cout << "\n" << BOLD << WHITE << "[KESIMPULAN]: ";
        if (hasil.kategoriUtama == "AMAN DIKONSUMSI") {
            cout << GREEN << hasil.kategoriUtama << RESET << endl;
        } else if (hasil.kategoriUtama == "BERACUN") {
            cout << RED << hasil.kategoriUtama << RESET << endl;
        } else {
            cout << YELLOW << hasil.kategoriUtama << RESET << endl;
        }
        
        cout << CYAN << "[INFO] Deskripsi: " << WHITE << hasil.deskripsi << RESET << endl;
        
        cout << "\n" << BOLD << GREEN << "[REKOMENDASI]:" << RESET << endl;
        cout << WHITE << hasil.rekomendasi << RESET << endl;
        
        cout << "\n" << BOLD << CYAN << "===============================================" << RESET << endl;
    }
    
    void showProgressBar(const string& label, double value, const string& color) {
        cout << "   " << BOLD << WHITE << label << ": " << RESET;
        cout << color << "[";
        
        int barLength = 20;
        int filledLength = (int)(value * barLength);
        
        for (int i = 0; i < barLength; i++) {
            if (i < filledLength) {
                cout << "#";
            } else {
                cout << "-";
            }
        }
        
        cout << "] " << RESET << BOLD << WHITE << (value * 100) << "%" << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    string generateRekomendasi(string jenisAir, string kategori, double ppm, double suhu) {
        string rekomendasi = "";
        
        if (kategori == "AMAN DIKONSUMSI") {
            if (jenisAir == "Air Mineral" || jenisAir == "Air Minum Kemasan") {
                rekomendasi = "Air ini layak dikonsumsi langsung. Pastikan kemasan tidak rusak.";
            } else if (jenisAir == "Air Kran") {
                rekomendasi = "Air kran aman dikonsumsi. Disarankan direbus terlebih dahulu untuk sterilisasi.";
            } else if (jenisAir == "Air Sumur") {
                rekomendasi = "Air sumur dalam kondisi baik. Lakukan tes berkala dan rebus sebelum diminum.";
            } else if (jenisAir == "Air Hujan") {
                rekomendasi = "Air hujan dapat digunakan untuk keperluan non-konsumsi. Jika ingin diminum, saring dan rebus terlebih dahulu.";
            } else {
                rekomendasi = "Air dalam kondisi baik untuk penggunaan sesuai jenisnya.";
            }
        } else if (kategori == "BERACUN") {
            if (jenisAir == "Air Kran" || jenisAir == "Air Sumur") {
                rekomendasi = "BAHAYA! Jangan konsumsi air ini. Periksa sistem pipa atau sumber air. Hubungi ahli kualitas air.";
            } else if (jenisAir == "Air Hujan") {
                rekomendasi = "Air hujan terkontaminasi berat. Jangan gunakan untuk konsumsi atau memasak.";
            } else if (jenisAir == "Parfum" || jenisAir == "Sabun Cair") {
                rekomendasi = "Produk ini BUKAN untuk dikonsumsi! Jauhkan dari jangkauan anak-anak.";
            } else {
                rekomendasi = "Air sangat berbahaya! Jangan dikonsumsi dalam kondisi apapun. Cari sumber air alternatif.";
            }
        } else { // MENGANDUNG KIMIA
            if (jenisAir == "Air Kran") {
                rekomendasi = "Air mengandung bahan kimia. Gunakan filter air atau rebus lebih lama sebelum dikonsumsi.";
            } else if (jenisAir == "Air Kolam Renang") {
                rekomendasi = "Air kolam mengandung klorin tinggi. Hanya untuk berenang, jangan dikonsumsi.";
            } else if (jenisAir == "Air Hujan") {
                rekomendasi = "Air hujan mengandung polutan. Saring dengan karbon aktif sebelum digunakan.";
            } else {
                rekomendasi = "Air mengandung bahan kimia. Hindari konsumsi langsung, gunakan metode penyaringan.";
            }
        }
        
        return rekomendasi;
    }
    
    void tampilkanJenisAir() {
        cout << "\n" << BOLD << MAGENTA << "+===============================================+" << RESET << endl;
        cout << BOLD << MAGENTA << "|" << RESET << BOLD << WHITE << "            PILIHAN JENIS AIR              " << RESET << BOLD << MAGENTA << "|" << RESET << endl;
        cout << BOLD << MAGENTA << "+===============================================+" << RESET << endl;
        
        cout << "\n" << BOLD << CYAN << "[1]" << WHITE << " Air Mineral" << RESET << endl;
        cout << BOLD << CYAN << "[2]" << WHITE << " Air Minum Kemasan" << RESET << endl;
        cout << BOLD << CYAN << "[3]" << WHITE << " Air Kran" << RESET << endl;
        cout << BOLD << CYAN << "[4]" << WHITE << " Air Sumur" << RESET << endl;
        cout << BOLD << CYAN << "[5]" << WHITE << " Air Hujan" << RESET << endl;
        cout << BOLD << CYAN << "[6]" << WHITE << " Air Kolam Renang" << RESET << endl;
        cout << BOLD << CYAN << "[7]" << WHITE << " Parfum" << RESET << endl;
        cout << BOLD << CYAN << "[8]" << WHITE << " Sabun Cair" << RESET << endl;
        cout << BOLD << CYAN << "[9]" << WHITE << " Lainnya" << RESET << endl;
        
        cout << "\n" << BOLD << MAGENTA << "===============================================" << RESET << endl;
    }
    
    string pilihJenisAir() {
        int pilihan;
        string jenisAir;
        
        tampilkanJenisAir();
        
        bool validInput = false;
        while (!validInput) {
            cout << "\n" << CYAN << "[PILIH] Masukkan nomor jenis air (1-9): " << WHITE;
            if (cin >> pilihan && pilihan >= 1 && pilihan <= 9) {
                validInput = true;
                switch (pilihan) {
                    case 1: jenisAir = "Air Mineral"; break;
                    case 2: jenisAir = "Air Minum Kemasan"; break;
                    case 3: jenisAir = "Air Kran"; break;
                    case 4: jenisAir = "Air Sumur"; break;
                    case 5: jenisAir = "Air Hujan"; break;
                    case 6: jenisAir = "Air Kolam Renang"; break;
                    case 7: jenisAir = "Parfum"; break;
                    case 8: jenisAir = "Sabun Cair"; break;
                    case 9: 
                        cout << CYAN << "[INPUT] Masukkan jenis air lainnya: " << WHITE;
                        cin.ignore();
                        getline(cin, jenisAir);
                        break;
                }
            } else {
                cout << RED << "\n[ERROR] Pilihan tidak valid! Masukkan angka 1-9.\n" << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        
        return jenisAir;
    }
    
    void tampilkanPanduan() {
        cout << "\n" << BOLD << YELLOW << "+===============================================+" << RESET << endl;
        cout << BOLD << YELLOW << "|" << RESET << BOLD << WHITE << "          PANDUAN PARAMETER AIR            " << RESET << BOLD << YELLOW << "|" << RESET << endl;
        cout << BOLD << YELLOW << "+===============================================+" << RESET << endl;
        
        cout << "\n" << BOLD << CYAN << "[PPM] Parts Per Million:" << RESET << endl;
        cout << GREEN << "   - Rendah: " << WHITE << "0-150 ppm" << GREEN << " (air bersih)" << RESET << endl;
        cout << YELLOW << "   - Sedang: " << WHITE << "50-300 ppm" << YELLOW << " (air biasa)" << RESET << endl;
        cout << RED << "   - Tinggi: " << WHITE << "200+ ppm" << RED << " (air tercemar)" << RESET << endl;
        
        cout << "\n" << BOLD << CYAN << "[SUHU] Suhu Air:" << RESET << endl;
        cout << BLUE << "   - Dingin: " << WHITE << "0-25 derajat C" << RESET << endl;
        cout << GREEN << "   - Normal: " << WHITE << "15-35 derajat C" << RESET << endl;
        cout << RED << "   - Panas: " << WHITE << "30+ derajat C" << RESET << endl;
        
        cout << "\n" << BOLD << YELLOW << "===============================================" << RESET << endl;
    }
};

int main() {

    enableColors();
    
    FuzzyWaterQuality fuzzySystem;
    double ppm, suhu;
    char lanjut;
    

    showAnimatedHeader();
    
    cout << "\n" << BOLD << WHITE << "Sistem ini akan menganalisis kualitas air berdasarkan PPM dan Suhu" << RESET << endl;
    cout << CYAN << "Tekan ENTER untuk melanjutkan..." << RESET;
    cin.get();
    
    do {
        clearScreen();
        fuzzySystem.tampilkanPanduan();
        
        cout << "\n" << BOLD << MAGENTA << "[INPUT] Masukkan data untuk analisis:" << RESET << endl;
        

        bool validInput = false;
        while (!validInput) {
            cout << CYAN << "[PPM] Parts Per Million: " << WHITE;
            if (cin >> ppm && ppm >= 0) {
                validInput = true;
            } else {
                cout << RED << "\n[ERROR] Masukkan nilai PPM yang valid (angka positif)!\n" << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        

        validInput = false;
        while (!validInput) {
            cout << CYAN << "[SUHU] Suhu Air (derajat Celsius): " << WHITE;
            if (cin >> suhu && suhu >= 0) {
                validInput = true;
            } else {
                cout << RED << "\n[ERROR] Masukkan nilai suhu yang valid (angka positif)!\n" << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        

        string jenisAir = fuzzySystem.pilihJenisAir();
        

        loadingAnimation("\n[PROSES] Memproses data dengan algoritma fuzzy", 2);
        FuzzyWaterQuality::HasilKlasifikasi hasil = fuzzySystem.klasifikasiAir(ppm, suhu, jenisAir);
        

        fuzzySystem.tampilkanHasil(hasil);
        

        cout << "\n" << BOLD << YELLOW << "[MENU] Apakah Anda ingin melakukan analisis lagi?" << RESET << endl;
        cout << GREEN << "   [Y] Ya, analisis lagi" << RESET << endl;
        cout << RED << "   [N] Tidak, keluar program" << RESET << endl;
        cout << CYAN << "Pilihan Anda (y/n): " << WHITE;
        cin >> lanjut;
        
    } while (lanjut == 'y' || lanjut == 'Y');
    

    clearScreen();
    cout << "\n" << BOLD << CYAN;
    typeText("  +===============================================+\n", 30);
    typeText("  |                                               |\n", 30);
    typeText("  |        TERIMA KASIH TELAH MENGGUNAKAN         |\n", 30);
    typeText("  |      SISTEM KLASIFIKASI KUALITAS AIR!         |\n", 30);
    typeText("  |                                               |\n", 30);
    typeText("  +===============================================+\n", 30);
    cout << RESET;
    
    cout << "\n" << GREEN;
    typeText("           Program selesai dengan sukses!\n", 50);
    cout << RESET;
    
    cout << "\n" << BOLD << YELLOW;
    typeText("  +===============================================+\n", 20);
    typeText("  |              INFORMASI PROYEK                |\n", 20);
    typeText("  +===============================================+\n", 20);
    cout << RESET;
    
    cout << "\n" << BOLD << WHITE;
    typeText("    Tugas Akhir UAS Kecerdasan Buatan\n", 30);
    cout << RESET;
    
    cout << CYAN;
    typeText("    Dibuat oleh: ", 30);
    cout << WHITE;
    typeText("Lazuardi Irham Karaman\n", 30);
    cout << CYAN;
    typeText("    NIM        : ", 30);
    cout << WHITE;
    typeText("23533740\n", 30);
    cout << RESET;
    
    cout << "\n" << YELLOW << "Tekan ENTER untuk keluar..." << RESET;
    cin.ignore();
    cin.get();
    
    return 0;
}