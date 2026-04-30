#include <iostream>
#include <stdio.h>
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

void tambahFilm(){
    Node* tambah = new Node;
    cin.ignore();

    cout <<"Judul : ";
    cin.getline(tambah->data.judul, 100);
    cout << "Genre : ";
    cin.getline(tambah-> data.genre, 50);
    cout <<"Durasi (menit) : ";
    cin >> tambah->data.durasi;
    cout <<"Kategori (SU/13+/17+) : ";
    cin >> tambah->data.kategori;
    cout<<"Rating : ";
    cin >> tambah->data.rating;
    cout <<"Harga Tiket : ";
    cin >> tambah->data.harga;
    cout <<"Jumlah Kursi : ";
    cin >>tambah->data.kursi;
    cin.ignore();

    tambah->next = head;
    head = tambah;

    FILE *data = fopen("film.txt", "a");
    if (data == NULL){
        cout <<"Gagal membuka file" << endl;
        return;
    }

    fprintf(data, "%s;%s;%d;%s;%.1f;%d;%d\n",
    tambah->data.judul,
    tambah->data.genre,
    tambah-> data.durasi,
    tambah-> data.kategori,
    tambah-> data.rating,
    tambah->data.harga,
    tambah->data.kursi);

    fclose(data);
    cout <<"Film berhasil ditambah!\n";
}

void tampilFilm(){
    if(head == NULL){
        cout <<"Belum ada film\n";
        return;
    }

    Node* bantu = head;
    int i = 1;

    cout <<"\n=====================================================================\n";
    cout <<"\n                            NOW SHOWING                              \n";
    cout <<"\n---------------------------------------------------------------------\n";
    cout <<"No   Judul                Genre        Durasi     Harga       Status   \n";
    cout <<"\n---------------------------------------------------------------------\n";

    while(bantu != NULL){
        cout << "[" << i << "] ";
        cout << left << setw(25) << bantu-> data.judul;
        cout << setw(12) << bantu-> data.genre;
        cout << setw(8) << bantu->data.durasi;
        cout << setw(8) << bantu->data.harga;

        if(bantu-> data.kursi > 0){
            cout <<"Tersedia";
        } else {
            cout <<"Penuh";
        }
        cout << endl;
        bantu = bantu-> next;
        i++;
    }
    cout <<"\n---------------------------------------------------------------------\n";

    int pilih;
    cout <<"\nPilih nomor film (0 kembali) : ";
    cin >> pilih;
    cin.ignore();

    if (pilih == 0)
    return;

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

    //DETAIL
    cout <<"\n=====================================================================\n";
    cout <<"\n                      DETAIL FILM                                    \n";
    cout <<"\n=====================================================================\n";
    cout <<"Judul : " << bantu->data.judul << endl;
    cout <<"Genre : " << bantu->data.genre << endl;
    cout <<"Durasi : " << bantu->data.durasi << " menit\n";
    cout <<"Kategori : " << bantu->data.kategori << endl;
    cout <<"Rating : " << bantu->data.rating << "/ 10\n";
    cout <<"Harga: " << bantu->data.harga << endl;
    cout <<"Kursi : " << bantu->data.kursi<< endl;
    cout <<"\n=====================================================================\n";
    int pilihBooking;
    cout <<"[1] Booking Tiket\n";
    cout <<"[0] Kembali\n";
    cout <<"Pilih : ";
    cin >> pilihBooking;
    cin.ignore();
}

int main(){
    int menu;

    do{
        cout<<"\n=====================================================================\n";
        cout<<"                           BIOSKOP SYSTEM                              \n";
        cout<<"\n=====================================================================\n";
        cout<<"[1] Now Showing\n";
        cout<<"[2] Tambah Film\n";
        cout<<"[3] Urutkan Harga Tiket\n";
        cout<<"[4] Cari Film (Genre)\n";
        cout<<"[5] Hapus Film\n";
        cout<<"[0] Keluar\n";
        cout <<"\n=====================================================================\n";
        cout <<"Pilih : ";
        cin >> menu;
        cin.ignore();

        if (menu == 1){
            tampilFilm();
        }
        else if (menu == 2){
            tambahFilm();
            tampilFilm();
        }
    } while (menu != 0);
}