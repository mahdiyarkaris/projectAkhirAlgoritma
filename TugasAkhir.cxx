#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;

struct FILM{
    char judul[100];
    char genre[50];
    int durasi;
    char kategori[10];
    float rating;
    int harga;
    int kursi;
};

struct Node{
    FILM data;
    Node* next;
};

Node* head = NULL;

bool loginAdmin(){
    char username[50];
    char password[50];
    
    cout <<"===== Login =====\n";
    cout << "Username : ";
    cin.getline(username, 50);
    cout <<"Password : ";
    cin.getline(password, 50);

    if(strcmp(username, "Admin01") == 0 && strcmp(password, "12345") == 0){
        cout << "\nLogin lerhasil\n";
        return true;
    } else {
        cout <<"Username atau password salah!\n";
        return false;
    }
}
void dataFilm(){
    FILE *data = fopen("film.txt", "r");
    if (data == NULL) return;
    
    while (true){
        Node *baru = new Node;

        if (fscanf(data, "%[^;];%[^;];%d;%[^;];%f;%d;%d\n",
            baru->data.judul,
            baru->data.genre,
            &baru->data.durasi,
            baru->data.kategori,
            &baru->data.rating,
            &baru->data.harga,
            &baru->data.kursi) != 7){

            delete baru;
            break;
        }
        baru->next = head;
        head = baru;
    }
    fclose(data);
}

void simpanData(){
    FILE *data = fopen("film.txt", "w");
    Node *bantu = head;

    while (bantu != NULL){
        fprintf(data, "%s;%s;%d;%s;%.1f;%d;%d\n",
        bantu->data.judul,
        bantu->data.genre,
        bantu->data.durasi,
        bantu->data.kategori,
        bantu->data.rating,
        bantu->data.harga,
        bantu->data.kursi);

    bantu = bantu->next;
    }
    fclose(data);
}
void simpanRiwayat(char nama[], char judul[], int jumlah,int total){
    
    FILE *riwayat = fopen("riwayat.txt", "a");
    fprintf(riwayat, "Nama : %s\nFilm : %s\nJumlah tiket : %d\nTotal bayar : Rp %d\n-----\n",
     nama,judul,jumlah,total);

     fclose(riwayat);
}

void tampilRiwayat(){
    FILE *riwayat = fopen("riwayat.txt", "r");
    if(riwayat == NULL){
        cout << "Belum ada riwayat booking\n";
        return;
    }
    char tampil[175];
    cout << "\n+======================+";
    cout << "\n|   Riwayat Booking    |";
    cout << "\n+======================+\n";

    while (fgets(tampil, sizeof(tampil), riwayat) != NULL){
        cout << tampil;
    }
    fclose(riwayat);
}

void cetakStruk(char nama[], char judul[], int jumlah, int harga){
    int total = jumlah * harga;

    cout << "\n+=================================+\n";
    cout << "|          STRUK PEMBELIAN        |\n";
    cout << "+=================================+\n";
    cout << "Nama         : " << nama << endl;
    cout << "Film         : " << judul << endl;
    cout << "Jumlah Tiket : " << jumlah << endl;
    cout << "Harga Tiket  : Rp " << harga << endl;
    cout << "Total Bayar  : Rp " << total << endl;
    cout << "===================================\n";
}

void tambahFilm(){
    int n;
    cout << "Berapa film yang akan ditambahkan: ";
    cin >> n;
    cin.ignore();

    for (int i = 1; i <= n; i++){
        Node* tambah = new Node;

        cout << "\n Data Film ke- " << i << endl;

        cout << "Judul : ";
        cin.getline(tambah->data.judul, 100);
        cout << "Genre : ";
        cin.getline(tambah->data.genre, 50);
        cout << "Durasi (menit) : ";
        cin >> tambah->data.durasi;
        cout << "Kategori (SU/13+/17+) : ";
        cin >> tambah->data.kategori;
        cout << "Rating : ";
        cin >> tambah->data.rating;
        cout << "Harga Tiket : ";
        cin >> tambah->data.harga;
        cout << "Jumlah Kursi : ";
        cin >> tambah->data.kursi;
        cin.ignore();

        tambah->next = head;
        head = tambah;

        FILE *data = fopen("film.txt", "a");
        if (data == NULL){
            cout << "Gagal membuka File" << endl;
            return;
        }

        fprintf(data, "%s;%s;%d;%s;%.1f;%d;%d\n",
            tambah->data.judul,
            tambah->data.genre,
            tambah->data.durasi,
            tambah->data.kategori,
            tambah->data.rating,
            tambah->data.harga,
            tambah->data.kursi);

        fclose(data);
    }
    cout << "\nData film berhasil ditambahkan!\n";
}
void ubahDataFilm(){
    if(head == NULL){
        cout << " Data film kosong\n";
        return;
    }
    char judul[100];

    cout << " Masukkan Judul Film yang akan diubah: ";
    cin.getline(judul, 100);

    Node* bantu = head;
    bool ketemu = false;

    while (bantu != NULL){
        if(strcmp(bantu->data.judul, judul) == 0){
            ketemu = true;
            cout << "\n=== UBAH DATA FILM ===\n";

            cout << " Judul Baru : ";
            cin.getline(bantu->data.judul, 100);
            cout << " Genre Baru : ";
            cin.getline(bantu->data.genre, 50);
            cout << " Durasi Baru : ";
            cin >> bantu->data.durasi;
            cout << " Kategori Baru : ";
            cin >> bantu->data.kategori;
            cout << " Rating Baru : ";
            cin >> bantu->data.rating;
            cout << " Harga Baru : ";
            cin >> bantu->data.harga;
            cout << " Jumlah Kursi baru : ";
            cin >> bantu->data.kursi;

            cin.ignore();
            simpanData();
                cout << "\nData film berhasil diperbarui !\n";
            break;
        }
        bantu = bantu->next;
    }
    if(!ketemu){
        cout << " Film tidak ditemukan\n";
    }
}

void hapusfilm(){
    if(head == NULL){
        cout << "Data film kosong\n";
        return;
    }

    char judul[100];
    cout << " Masukkan judul film: ";
    cin.getline(judul, 100);

    Node *hapus = head, *prev = NULL;

    while(hapus !=NULL && strcmp(hapus->data.judul, judul) != 0){
        prev = hapus;
        hapus = hapus->next;
    }
    
    if(hapus== NULL){
        cout << "Film tidak ditemukan\n";
        return;
    }

    if (prev == NULL){
        head = head->next;
    } else {
        prev->next = hapus->next;
    }
    delete hapus;
    simpanData();

    cout << "Film berhasil dihapus\n";
}
void tampilFilm(){
    if(head == NULL){
        cout <<"Belum ada film\n";
        return;
    }

    Node* bantu = head;
    int i = 1;

    cout << "\n+====================================================================+\n";
    cout << "|                            NOW SHOWING                             |\n";
    cout << "+====================================================================+\n";
    cout << "| No | Judul                | Genre     | Durasi | Harga | Status    |\n";
    cout << "+--------------------------------------------------------------------+\n";

    while (bantu != NULL){
        cout << "| " << setw(2) << i << " | ";
        cout << left << setw(20) << bantu->data.judul << " | ";
        cout << setw(9) << bantu->data.genre << " | ";
        cout << setw(6) << bantu->data.durasi << " | ";
        cout << setw(5) << bantu->data.harga << " | ";

        if (bantu->data.kursi > 0){
            cout << "Tersedia  |\n";
        } else {
            cout << "Penuh     |\n";
        }

        bantu = bantu->next;
        i++;
    }

    cout << "+====================================================================+\n";

    int pilih;
    cout <<"\n[0] Untuk kembali ke menu";
    cout <<"\n Pilih nomor film: ";
    cin >> pilih;
    cin.ignore();

    if (pilih == 0){
        return;
    }

    bantu = head;
    i = 1;

    while (bantu != NULL && i < pilih){
        bantu = bantu->next;
        i++;
    }
    if (bantu == NULL){
        cout <<"Pilihan tidak valid\n";
        return;
    }

    cout << "\n+=====================================+\n";
    cout << "|            DETAIL FILM	      |\n";
    cout << "+=====================================+\n";
    cout << " Judul    : " << bantu->data.judul << endl;
    cout << " Genre    : " << bantu->data.genre << endl;
    cout << " Durasi   : " << bantu->data.durasi << " menit\n";
    cout << " Kategori : " << bantu->data.kategori << endl;
    cout << " Rating   : " << bantu->data.rating << " / 10\n";
    cout << " Harga    : " << bantu->data.harga << endl;
    cout << " Kursi    : " << bantu->data.kursi << endl;
    cout << "+=====================================+\n";

    int pilihBooking;
    cout <<"\n[1] Booking";
    cout <<"\n[0] Kembali";
    cout <<"\nPilih: ";
    cin >> pilihBooking;
    cin.ignore();

    if( pilihBooking == 1){

        char nama[100];
        cout << "Nama Pemesan : ";
        cin.getline(nama, 100);

        int jumlah;
        cout <<"Jumlah tiket: ";
        cin >> jumlah;
        cin.ignore();

        if(jumlah > 0 && jumlah <= bantu->data.kursi){
			bantu->data.kursi = bantu->data.kursi - jumlah;
			simpanData();

            int total = jumlah * bantu->data.harga;
			
			cout <<"Booking berhasil\n";
			cout <<"Sisa kursi : " << bantu->data.kursi << endl;

            cetakStruk(nama, bantu->data.judul, jumlah, bantu->data.harga);
            simpanRiwayat(nama, bantu->data.judul, jumlah, total);
        }else{
            cout <<"Jumlah tiket tidak valid\n";
		}
	}
}
void sortingHarga(){

    if (head == NULL) {
        cout << " Belum ada data film\n";
        return;
    }
    bool tukar;
    Node *bantu;
    Node *akhir = NULL;

    do {
        tukar = false;
        bantu = head;

        while (bantu->next != akhir){
            if (bantu->data.harga > bantu->next->data.harga){
                FILM temp = bantu->data;
                bantu->data = bantu->next->data;
                bantu->next->data = temp;

                tukar = true;
            }
            bantu = bantu->next;
        }
        akhir = bantu;
    } while (tukar);

    FILE *data = fopen("film.txt", "w");

    if (data == NULL){
        cout << " Gagal membuka file\n";
        return;
    }
    bantu = head;

    while (bantu != NULL){
        fprintf(data, "%s;%s;%d;%s;%.1f;%d;%d\n",
            bantu->data.judul,
            bantu->data.genre,
            bantu->data.durasi,
            bantu->data.kategori,
            bantu->data.rating,
            bantu->data.harga,
            bantu->data.kursi);

            bantu = bantu->next;
    }
    fclose(data);

    cout << "\n+=======================================================+\n";
    cout << "|         FILM DIURUTKAN BERDASARKAN HARGA               |\n";
    cout << "+=======================================================+\n";
    bantu = head;
    int no = 1;
    cout << "| No | Judul                | Genre     | Harga         |\n";
    cout << "+-------------------------------------------------------+\n";
    while (bantu != NULL)
    {
        cout << "| "
             << setw(2) << no << " | "
             << left << setw(20) << bantu->data.judul << " | "
             << setw(9) << bantu->data.genre << " | Rp "
             << setw(10) << bantu->data.harga << " |\n";
        bantu = bantu->next;
        no++;
    }
    cout << "+=======================================================+\n";
}

void booking(){
    char judul[100];
    cout << "Masukkan judul film : ";
    cin.getline(judul, 100);

    Node *bantu = head;
    bool ketemu = false;

    while(bantu != NULL){
        if(strcmp(bantu->data.judul, judul) == 0){
            ketemu = true;

            char nama[100];

            cout << "Nama Pemesan : ";
            cin.getline(nama, 100);

            int jumlah;

            cout <<"Jumlah tiket : ";
            cin >> jumlah;
            cin.ignore();

            if(jumlah > 0 && jumlah <= bantu->data.kursi) {
                bantu->data.kursi = bantu->data.kursi -jumlah;
                simpanData();
                
                int total = jumlah * bantu->data.harga;
                cout << "Booking berhasil\n";
                cout <<"Sisa kursi : "<< bantu->data.kursi << endl;
                
                cetakStruk(nama,bantu->data.judul,jumlah,bantu->data.harga);
                simpanRiwayat(nama,bantu->data.judul,jumlah,total);
            }else{
                cout <<"Jumlah tiket tidak valid\n";
            }
        }
        bantu = bantu->next;
    }
    if(ketemu == false){
        cout <<"Film tidak ditemukan\n";
    }
}

void cariFilm(){
    if(head == NULL){
        cout <<"Belum ada film\n";
        return;
    }

    char cari[50];
    cout << "Masukkan genre film : ";
    cin.getline(cari, 50);

    Node *bantu = head;
    bool ketemu = false;
    int no = 1;

    while(bantu != NULL){
        if(strcmp(bantu->data.genre, cari) == 0) {
            if (ketemu == false){
                cout <<"\n+=========================================================+\n";
                cout <<"|                    HASIL PENCARIAN                      |\n";
                cout <<"+=========================================================+\n";
                cout <<"| No | Judul                | Durasi  | Harga | Status    |\n";
                cout <<"+---------------------------------------------------------+\n";
            }
            ketemu = true;
            
            cout <<"| " << setw(2) << no << " | ";
			cout << left << setw(20) << bantu->data.judul <<" | ";
			cout << setw(7) << bantu->data.durasi <<" | ";
			cout << setw(5) << bantu->data.harga << " | ";
            if(bantu->data.kursi > 0){
                cout <<"Tersedia  |\n";
            }else {
                cout << "Penuh     |\n";
            }
            no++;
        }
        bantu = bantu->next;
    }
    if(ketemu == false){
        cout <<"Film tidak ditemukan\n";
        return;
    }
    cout << "+=========================================================+\n";
    
    char pilih;
    cout << "\nIngin booking? (y/t) : ";
    cin >> pilih;
    cin.ignore();

    if(pilih == 'y'){
        booking();
    }
}

int main(){
    dataFilm();
    if(loginAdmin() == false){
        return 0;
    }
    int menu;

    do{
        cout << "\n+=====================================+\n";
        cout << "|     SISTEM MANAJEMEN BIOSKOP	      |\n";
        cout << "+=====================================+\n";
        cout << "| [ 1 ] Now Showing		      |\n";
        cout << "| [ 2 ] Tambah Film Baru              |\n";
        cout << "| [ 3 ] Ubah Data Film                |\n";
        cout << "| [ 4 ] Urutkan Harga Tiket	      |\n";
        cout << "| [ 5 ] Cari Genre Film 	      |\n";
        cout << "| [ 6 ] Hapus Film	              |\n";
        cout << "| [ 7 ] Riwayat Booking               |\n";
        cout << "| [ 0 ] Keluar                        |\n";
        cout << "+=====================================+\n";

        cout << "Pilih Menu => ";
        cin >> menu;
        cin.ignore();

        if (menu == 1){
            tampilFilm();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
        } else if (menu == 2){
            tambahFilm();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
        } else if(menu == 3){
			ubahDataFilm();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();    
        } else if(menu == 4){
			sortingHarga();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		} else if(menu == 5){
			cariFilm();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
		} else if (menu == 6){
            hapusfilm();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
        } else if(menu== 7){
            tampilRiwayat();
            cout <<"\nTekan Enter untuk melanjutkan...";
			cin.get();
        }
    } while (menu != 0);
}
