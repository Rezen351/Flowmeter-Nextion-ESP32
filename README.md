# 🌊 Flowmeter Dashboard HMI

Sebuah dasbor HMI (Human-Machine Interface) canggih dan modern untuk pemantauan *flowmeter* (alat ukur aliran) secara *real-time*. Proyek ini dirancang untuk berjalan pada mikrokontroler (seperti ESP32 atau Arduino) yang terhubung ke layar HMI, kemungkinan besar Nextion Display, untuk memberikan visualisasi data yang intuitif dan menarik.

## 🖼️ Tampilan Dasbor (Screenshots)

Berikut adalah beberapa contoh tampilan dari antarmuka dasbor:

| Tampilan Utama | Tampilan Grafik |
| :---: | :---: |
| ![Display 1](Display%201.png) | ![Display 2](Display%202.png) |
| **Tampilan Pengaturan** | **Tampilan Peringatan** |
| ![Display 3](Display%203.png) | ![Display 4](Display%204.png) |

## ✨ Fitur Utama (Key Features)

- 📊 **Visualisasi Real-Time:** Menampilkan data laju aliran (*flow rate*) dan total volume cairan yang telah melewati sensor secara langsung.
- 🔄 **Animasi Gauge Dinamis:** Menggunakan lebih dari 200 gambar gauge untuk menciptakan animasi yang halus dan responsif terhadap perubahan data.
- 🎨 **Antarmuka Kustom:** Desain UI yang modern dengan ikon dan font kustom (Pirata One, Quantico) untuk keterbacaan maksimal.
- 💡 **Dasbor Cerdas:** Proyek `flowmeter_intelligent.HMI` mengindikasikan adanya logika tambahan seperti pengecekan status, kalibrasi, atau sistem peringatan.
- 📄 **Beberapa Layar:** Navigasi yang mudah antara beberapa layar untuk fungsi yang berbeda (utama, pengaturan, data, dll).

## 🛠️ Teknologi & Komponen (Tech & Components)

- **Hardware:**
  - Mikrokontroler (Arduino, ESP32, atau sejenisnya)
  - Layar HMI (Sangat mungkin **Nextion Display** berdasarkan ekstensi file `.HMI` dan `.zi`)
  - Sensor Flowmeter
- **Firmware:**
  - Bahasa: **C++**
  - Framework: **Arduino** (terlihat dari file `.ino` dan struktur folder `main`)
- **Desain HMI:**
  - Software: **Nextion Editor**
  - Aset Grafis: PNG untuk ikon dan sekuens animasi gauge.
  - Font: **Quantico** dan **Pirata One** (file `.zip` dan `.zi`).

## 📂 Struktur Proyek (Project Structure)

```
.
├── 📄 *.HMI                  # File proyek untuk Nextion Editor
├── 🖼️ Display *.png            # Screenshot antarmuka dasbor
├── 📁 main/                    # Kode sumber firmware (C++/Arduino) untuk mikrokontroler
│   ├── main.ino              # File utama sketch Arduino
│   ├── sensor.cpp            # Logika untuk membaca data dari sensor
│   ├── checks.cpp            # Logika untuk pengecekan status atau validasi
│   └── *.h, *.cpp            # File header dan implementasi lainnya
├── 📁 gauge_images-20250922T143959Z-1-001/ # Aset gambar untuk animasi gauge
├── 📁 zi/                     # File font yang sudah dikompilasi untuk Nextion
└── 📄 README.md               # Anda sedang membacanya
```

## 🚀 Panduan Instalasi (Installation Guide)

1.  **HMI (Layar Tampilan):**
    - Buka file `flowmeter_intelligent.HMI` menggunakan [Nextion Editor](https://nextion.tech/nextion-editor/).
    - Kompilasi proyek HMI untuk menghasilkan file `.tft`.
    - Upload file `.tft` tersebut ke layar Nextion Anda melalui kartu SD atau koneksi serial.

2.  **Firmware (Mikrokontroler):**
    - Buka folder `main/` menggunakan **Arduino IDE** atau **PlatformIO**.
    - Pastikan semua library yang dibutuhkan sudah terinstal.
    - Sesuaikan konfigurasi pin untuk sensor dan koneksi ke layar HMI di dalam file `config.h` atau `main.ino`.
    - Upload kode ke board mikrokontroler Anda.

3.  **Koneksi Fisik:**
    - Hubungkan pin `TX` dan `RX` dari mikrokontroler ke layar Nextion.
    - Sambungkan sensor flowmeter ke pin digital yang telah dikonfigurasi pada mikrokontroler.
    - Pastikan semua komponen mendapatkan catu daya yang sesuai.

---

Dibuat dengan ❤️ untuk visualisasi data yang lebih baik.