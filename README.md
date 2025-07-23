<div align="center">

# 🌊 Sistem Klasifikasi Kualitas Air Berbasis AI

### *Implementasi Logika Fuzzy untuk Analisis Kualitas Air*

[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Fuzzy Logic](https://img.shields.io/badge/Fuzzy_Logic-FF6B6B?style=for-the-badge&logo=brain&logoColor=white)]()
[![AI](https://img.shields.io/badge/Artificial_Intelligence-4ECDC4?style=for-the-badge&logo=robot&logoColor=white)]()
[![License](https://img.shields.io/badge/License-Academic-green?style=for-the-badge)]()

[🚀 Demo](#demo) • [📦 Instalasi](#instalasi) • [📖 Dokumentasi](#dokumentasi) • [🤝 Kontribusi](#kontribusi)

</div>

---

## 🎯 Tentang Proyek

Sistem klasifikasi kualitas air berbasis kecerdasan buatan yang menggunakan **Logika Fuzzy** untuk menganalisis dan mengklasifikasikan kualitas air berdasarkan parameter PPM (Parts Per Million) dan suhu. Sistem ini mampu memberikan rekomendasi cerdas dengan tingkat kepercayaan yang akurat.

### ✨ Fitur Unggulan

- 🧠 **Algoritma Fuzzy Logic** - Implementasi sistem inferensi fuzzy Mamdani
- 📊 **Analisis Multi-Parameter** - PPM, Suhu, dan 9 jenis air berbeda
- 🎯 **Klasifikasi Akurat** - 3 kategori: Aman Dikonsumsi, Beracun, Mengandung Kimia
- 💡 **Sistem Rekomendasi** - Saran cerdas berdasarkan hasil analisis
- 🎨 **Interface Interaktif** - Antarmuka pengguna yang user-friendly
- ⚡ **Animasi Skip** - Tekan Enter/Spasi untuk melewati animasi
- 📈 **Tingkat Kepercayaan** - Persentase akurasi untuk setiap klasifikasi

## 🔬 Teknologi yang Digunakan

- **Bahasa**: C++17
- **Algoritma**: Fuzzy Inference System (Mamdani)
- **Platform**: Cross-platform (Windows, Linux, macOS)
- **Compiler**: GCC, MSVC, Clang

## 📦 Instalasi

### 🔧 Prasyarat

- Compiler C++ yang mendukung C++17 atau lebih baru
- Git (untuk cloning repository)
- Terminal/Command Prompt

### 🚀 Langkah Instalasi

#### 1. Clone Repository

```bash
git clone https://github.com/irhamkaraman/klasifikasi-kualitas-air-berbasis-ai.git
cd klasifikasi-kualitas-air-berbasis-ai
```

#### 2. Kompilasi Program

##### Windows (MinGW/MSYS2)
```bash
g++ -std=c++17 -O2 -o fuzzy_water_quality.exe fuzzy_water_quality.cpp
```

##### Linux/macOS
```bash
g++ -std=c++17 -O2 -o fuzzy_water_quality fuzzy_water_quality.cpp
```

##### Visual Studio (Windows)
```bash
cl /EHsc /std:c++17 fuzzy_water_quality.cpp
```

#### 3. Jalankan Program

##### Windows
```bash
.\fuzzy_water_quality.exe
```

##### Linux/macOS
```bash
./fuzzy_water_quality
```

### 🐳 Docker (Opsional)

```bash
# Build image
docker build -t fuzzy-water-quality .

# Run container
docker run -it fuzzy-water-quality
```

## 🎮 Demo

### 📱 Tampilan Program

```
╔══════════════════════════════════════════════════════════════╗
║              🌊 SISTEM KLASIFIKASI KUALITAS AIR 🌊           ║
║                    Berbasis Logika Fuzzy                    ║
╚══════════════════════════════════════════════════════════════╝

📊 Masukkan Data Analisis:
💧 PPM (Parts Per Million): 120
🌡️  Suhu Air (°C): 25
🏷️  Jenis Air: Air Sumur

🔍 Hasil Analisis:
✅ Aman Dikonsumsi    : 85.5% (Tinggi)
☠️  Beracun          : 0.0%  (Rendah)
⚠️  Mengandung Kimia : 14.5% (Rendah)

🎯 KESIMPULAN: AMAN DIKONSUMSI
💡 Rekomendasi: Air dapat dikonsumsi dengan aman. Lakukan pemeriksaan berkala.
```

### 🧪 Contoh Pengujian

| Input PPM | Input Suhu | Jenis Air | Hasil Klasifikasi | Tingkat Kepercayaan |
|-----------|------------|-----------|-------------------|--------------------|
| 80        | 22°C       | Air Mineral | Aman Dikonsumsi | 92.3% |
| 350       | 40°C       | Air Sungai | Beracun | 98.7% |
| 180       | 35°C       | Air Sumur | Mengandung Kimia | 76.4% |

## 📖 Dokumentasi

### 🔬 Algoritma Fuzzy Logic

#### Fungsi Keanggotaan PPM
- **Rendah** (0-150 ppm): Air dengan kontaminan minimal
- **Sedang** (50-300 ppm): Air dengan kontaminan moderat
- **Tinggi** (200+ ppm): Air dengan kontaminan tinggi

#### Fungsi Keanggotaan Suhu
- **Dingin** (0-25°C): Suhu rendah
- **Normal** (15-35°C): Suhu optimal
- **Panas** (30+°C): Suhu tinggi

#### Aturan Inferensi Fuzzy

```
IF PPM = Rendah AND Suhu = Normal THEN Aman Dikonsumsi
IF PPM = Tinggi AND Suhu = Panas THEN Beracun
IF PPM = Sedang AND Suhu = Panas THEN Mengandung Kimia
... (27 aturan total)
```

### 🏗️ Arsitektur Sistem

```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   Input Layer   │───▶│  Fuzzy Engine    │───▶│  Output Layer   │
│                 │    │                  │    │                 │
│ • PPM           │    │ • Fuzzification  │    │ • Klasifikasi   │
│ • Suhu          │    │ • Rule Engine    │    │ • Rekomendasi   │
│ • Jenis Air     │    │ • Defuzzification│    │ • Confidence    │
└─────────────────┘    └──────────────────┘    └─────────────────┘
```

### 📊 Struktur Kode

```cpp
class FuzzyWaterQuality {
public:
    // Fungsi Keanggotaan
    double ppmRendah(double ppm);
    double ppmSedang(double ppm);
    double ppmTinggi(double ppm);
    
    // Operasi Fuzzy
    double fuzzyAND(double a, double b);
    double fuzzyOR(double a, double b);
    
    // Klasifikasi Utama
    HasilKlasifikasi klasifikasiAir(double ppm, double suhu, string jenisAir);
};
```

## 🧪 Pengujian

### Unit Test
```bash
# Compile dengan flag testing
g++ -DTESTING -std=c++17 -o test_fuzzy fuzzy_water_quality.cpp
./test_fuzzy
```

### Benchmark Performance
```bash
# Test dengan 1000 sample
time ./fuzzy_water_quality < test_data.txt
```

## 🚀 Pengembangan Lebih Lanjut

### 🎯 Roadmap

- [ ] **GUI Application** - Interface grafis dengan Qt/GTK
- [ ] **Web API** - REST API untuk integrasi sistem
- [ ] **Mobile App** - Aplikasi Android/iOS
- [ ] **Database Integration** - Penyimpanan hasil analisis
- [ ] **Machine Learning** - Hybrid fuzzy-neural network
- [ ] **IoT Integration** - Sensor real-time

### 🔧 Kontribusi

1. Fork repository ini
2. Buat branch fitur (`git checkout -b fitur-baru`)
3. Commit perubahan (`git commit -am 'Tambah fitur baru'`)
4. Push ke branch (`git push origin fitur-baru`)
5. Buat Pull Request

### 📝 Guidelines Kontribusi

- Ikuti coding style yang ada
- Tambahkan unit test untuk fitur baru
- Update dokumentasi jika diperlukan
- Gunakan commit message yang deskriptif

## 📚 Referensi Akademik

- Zadeh, L.A. (1965). *Fuzzy Sets*. Information and Control, 8, 338-353.
- Mamdani, E.H. (1974). *Application of fuzzy algorithms for control of simple dynamic plant*.
- WHO Guidelines for Drinking-water Quality (2022)
- Ross, T.J. (2010). *Fuzzy Logic with Engineering Applications*

## 👥 Tim Pengembang

<div align="center">

| Role | Name | Contact |
|------|------|----------|
| 🧑‍💻 Developer | Irham Karaman | [@irhamkaraman](https://github.com/irhamkaraman) |
| 📚 Academic Supervisor | Dyah Mustikasari, M. Kom | - |

</div>

## 📄 Lisensi

Proyek ini dilisensikan di bawah [MIT License](LICENSE) - lihat file LICENSE untuk detail lengkap.

## 🙏 Acknowledgments

- Universitas [Nama Universitas]
- Mata Kuliah Kecerdasan Buatan
- Komunitas Open Source C++
- Fuzzy Logic Research Community

---

<div align="center">

**⭐ Jika proyek ini membantu Anda, berikan star pada repository ini! ⭐**

[![GitHub stars](https://img.shields.io/github/stars/irhamkaraman/klasifikasi-kualitas-air-berbasis-ai?style=social)](https://github.com/irhamkaraman/klasifikasi-kualitas-air-berbasis-ai/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/irhamkaraman/klasifikasi-kualitas-air-berbasis-ai?style=social)](https://github.com/irhamkaraman/klasifikasi-kualitas-air-berbasis-ai/network)

**Dibuat dengan ❤️ untuk komunitas AI Indonesia**

</div>
