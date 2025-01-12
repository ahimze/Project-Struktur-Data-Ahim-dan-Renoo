#include <iostream>
#include <fstream>
using namespace std;

// Struktur untuk menyimpan data KTP
struct KTP {
    string nama;
    string nik;
    string alamat;
    string tanggalLahir;
};

// Struktur untuk node produk dalam linked list
struct NodeProduk {
    string kodeItem;
    string tanggal;
    NodeProduk* next;
};

// Struktur untuk node pembeli dalam linked list
struct NodePembeli {
    KTP ktp; // Data KTP pembeli
    string waktuKedatangan;
    string kodeItemBarang;
    NodePembeli* next; // Pointer ke node berikutnya
};

// Struktur untuk menyimpan dan mengelola produk
struct Produk {
    NodeProduk* head;
    Produk() : head(NULL) {}  // Konstruktor untuk inisialisasi head
    void pushBarang(string kodeItem, string tanggal);
    void popBarang();
    void displayBarang();
    bool isEmptyBarang();
};

// Struktur untuk menyimpan dan mengelola pembeli
struct Pembeli {
    NodePembeli* front;
    NodePembeli* rear;
    Pembeli() : front(NULL), rear(NULL) {}  // Konstruktor untuk inisialisasi front dan rear
    void enquePembeli(KTP ktp, string waktuKedatangan);
    void dequePembeli();
    void displayPembeli();
    bool isEmptyPembeli();
};

// Implementasi fungsi untuk menambahkan produk ke linked list
void Produk::pushBarang(string kodeItem, string tanggal) {
    NodeProduk* newNode = new NodeProduk;
    newNode->kodeItem = kodeItem;
    newNode->tanggal = tanggal;
    newNode->next = head;  //Menunjuk node baru ke node teratas saat ini

    head = newNode;  //Mengatur node baru sebagai node
}

//Implementasi fungsi untuk menghapus produk dari linked list
void Produk::popBarang() {
    if (isEmptyBarang()) {
        cout << "Gudang kosong, tidak ada barang yang bisa dihapus.\n";
        return;
    }
    NodeProduk* temp = head;
    head = head->next;
    cout<<temp->kodeItem;
    delete temp;
}

// Implementasi fungsi untuk menampilkan produk dalam linked list
void Produk::displayBarang() {
    if (isEmptyBarang()) {
        cout << "Gudang kosong, tidak ada barang untuk ditampilkan.\n";
        return;
    }
    NodeProduk* temp = head;
    while (temp != NULL) {
        cout << "| " << temp->kodeItem << " | " << temp->tanggal << " |\n";
        temp = temp->next;
    }
}

// Implementasi fungsi untuk memeriksa apakah produk kosong
bool Produk::isEmptyBarang() {
    return head == NULL;
}

// Implementasi fungsi untuk menambahkan pembeli ke linked list
void Pembeli::enquePembeli(KTP ktp, string waktuKedatangan) {
    NodePembeli* newNode = new NodePembeli;
    newNode->ktp = ktp;
    newNode->waktuKedatangan = waktuKedatangan;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Implementasi fungsi untuk menghapus pembeli dari linked list
void Pembeli::dequePembeli() {
    if (isEmptyPembeli()) {
        cout << "Antrian pembeli kosong.\n";
        return;
    }
    NodePembeli* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    cout<<temp->ktp.nik<<" | "<<temp->waktuKedatangan<<" | "; // Menampilkan data pembeli yang dihapus
    delete temp; // Menghapus node depan lama
}

// Implementasi fungsi untuk menampilkan pembeli dalam linked list
void Pembeli::displayPembeli() {
    if (isEmptyPembeli()) {
        cout << "Antrian pembeli kosong.\n";
        return;
    }
    NodePembeli* temp = front;
    while (temp != NULL) {
        cout << "| " << temp->ktp.nik << " | " << temp->waktuKedatangan << " | " << temp->kodeItemBarang << " |\n";
        temp = temp->next;
    }
}

// Implementasi fungsi untuk memeriksa apakah pembeli kosong
bool Pembeli::isEmptyPembeli() {
    return front == NULL;
}

// Implementasi fungsi untuk memasukkan data KTP
void inputKTP(KTP &ktp,string status) {
    cout << "Masukkan Nama: ";
    getline(cin, ktp.nama);
    cout << "Masukkan NIK: ";
    getline(cin, ktp.nik);
    cout << "Masukkan Alamat: ";
    getline(cin, ktp.alamat);
    cout << "Masukkan Tanggal Lahir (dd-mm-yyyy): ";
    getline(cin, ktp.tanggalLahir);

    if(status == "admin"){
        // Menyimpan data admin ke dalam file data_ktp_admin.txt
        ofstream file("data_ktp_admin.txt", ios::app);
        if (file.is_open()) {
            file << "Nama: " << ktp.nama << "\n";
            file << "NIK: " << ktp.nik << "\n";
            file << "Alamat: " << ktp.alamat << "\n";
            file << "Tanggal Lahir: " << ktp.tanggalLahir << "\n";
            file << "-------------------------\n";
            file.close();
        } else {
            cerr << "Gagal membuka file data_ktp_pembeli.txt untuk menulis data.\n";
        }
    }else{
        // Menyimpan data pembeli ke dalam file data_ktp_pembeli.txt
    ofstream file("data_ktp_pembeli.txt", ios::app);
    if (file.is_open()) {
        file << "Nama: " << ktp.nama << "\n";
        file << "NIK: " << ktp.nik << "\n";
        file << "Alamat: " << ktp.alamat << "\n";
        file << "Tanggal Lahir: " << ktp.tanggalLahir << "\n";
        file << "-------------------------\n";
        file.close();
    } else {
        cerr << "Gagal membuka file data_ktp_pembeli.txt untuk menulis data.\n";
    }
    }


}

// Implementasi fungsi untuk memeriksa apakah username admin ada
bool checkAdminUsername(const string& username) {
    ifstream file("data_ktp_admin.txt");
    if (!file.is_open()) {
        cerr << "File admin tidak ditemukan" << endl;
        return false;
    }

    string line;
    bool foundUsername = false;

    while (getline(file, line)) {
        if (line.find("Nama: ") == 0) {
            string name = line.substr(6);  // Mengambil nama setelah "Nama: "
            if (name == username) {
                foundUsername = true;
                break;
            }
        }
    }

    file.close();
    return foundUsername;
}

// Implementasi fungsi untuk mencetak data KTP
void cetakKTP() {
    ifstream file("data_ktp_admin.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file data_ktp_pembeli.txt untuk membaca data.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line == "-------------------------") {
            cout << line << endl;
        } else {
            cout << line << endl;
        }
    }

    file.close();
}

// Fungsi utama
int main() {
    Produk produk;
    Pembeli pembeli;
    KTP adminKTP;
    bool isAdminSignedIn = false;
    bool isLogin = false;
    string username;
    char registrasi;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Admin Sign In\n";
        cout << "2. Entri Item Barang\n";
        cout << "3. Catat Pembeli\n";
        cout << "4. Jual Item Barang\n";
        cout << "5. Cetak Daftar Barang dan Pembeli\n";
        cout << "6. Keluar\n";
        cout << "Pilih opsi: ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(); // Mengabaikan karakter newline setelah input angka

        switch (pilihan) {
            case 1:
                do {
                    cout << "Masukkan UserName Admin : ";
                    getline(cin, username);
                    if (checkAdminUsername(username)) {
                        isLogin = true;
                        isAdminSignedIn = true;
                    } else {
                        cout << "Username Tidak Ditemukan, Silakan Registrasi!\n";
                        cout << "Registrasi (y/t) : ";
                        cin >> registrasi;
                        cin.ignore();
                        if (registrasi == 'y' or registrasi == 'Y') {
                            inputKTP(adminKTP,"admin");
                            cout << "Admin berhasil sign in.\n";
                        }
                    }
                } while (!isLogin);
                cout << "\nData Admin Sign In:\n";
                cetakKTP();
                break;
            case 2:
                if (!isAdminSignedIn) {
                    cout << "Admin harus sign in terlebih dahulu.\n";
                    break;
                }
                {
                    string kodeItem, tanggal;
                    cout << "Entri Item Barang:\n";
                    cout << "Masukkan Kode Item: ";
                    getline(cin, kodeItem);
                    cout << "Masukkan Tanggal (dd-mm-yyyy): ";
                    getline(cin, tanggal);
                    produk.pushBarang(kodeItem, tanggal);
                    cout << "Item barang berhasil ditambahkan ke gudang.\n";
                }
                break;
            case 3:
                if (!isAdminSignedIn) {
                    cout << "Admin harus sign in terlebih dahulu.\n";
                    break;
                }
                {
                    KTP pembeliKTP;
                    string waktuKedatangan, kodeItemBarang;
                    cout << "Catat Pembeli:\n";
                    inputKTP(pembeliKTP,"pembeli");
                    cout << "Masukkan Waktu Kedatangan (hh:mm): ";
                    getline(cin, waktuKedatangan);
                    pembeli.enquePembeli(pembeliKTP, waktuKedatangan);
                    cout << "Pembeli berhasil dicatat.\n";
                }
                break;
            case 4:
                if (!isAdminSignedIn) {
                    cout << "Admin harus sign in terlebih dahulu.\n";
                    break;
                }

                {
                    cout<<"------------------------------------------"<<endl;
                    cout<<"KTP    | Waktu Kedatangan | Kode Item BRG "<<endl;
                    pembeli.dequePembeli();
                    produk.popBarang();

                }
                break;

            case 5:
                if (!isAdminSignedIn) {
                    cout << "Admin harus sign in terlebih dahulu.\n";
                    break;
                }
                cout << "Daftar Barang di Gudang:\n";
                produk.displayBarang();
                cout << "Daftar Pembeli:\n";
                pembeli.displayPembeli();
                break;

            case 6:
                cout << "Terima kasih telah menggunakan sistem.\n";
                return 0;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}

