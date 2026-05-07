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
            cout << "Penuh |\n";
        }

        bantu = bantu->next;
        i++;
    }

    cout << "+====================================================================+\n";

    int pilih;
    cout <<"\n[0] Untuk kembali ke menu \n Pilih nomor film: ";
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
    cout << "\n[1] Booking\n[0] Kembali\nPilih: ";
    cin >> pilihBooking;
    cin.ignore();

    if( pilihBooking == 1){
        int jumlah;
        cout << "Jumlah tiket: ";
        cin >> jumlah;
        cin.ignore();

        if(jumlah <= bantu->data.kursi){
            bantu->data.kursi -= jumlah;
            simpanData();
            cout << "Booking berhasil!\n";
        } else {
            cout << "Kursi Tidak cukup\n";
        }
    }
}

void cariFilm(){
	if(head == NULL){
		cout <<"Belum ada film\n";
		return;
	}
	
	char cari[50];
	cout<<"Masukkan genre yang dicari: ";
	cin.getline(cari, 50);
	
	Node* bantu = head;
	bool ketemu = false;
	
	cout <<"\nHASIL PENCARIAN   : \n";
	cout <<"-----------------------\n";
	while (bantu != NULL){
		if(strcmp(bantu->data.genre, cari) == 0){
			cout <<"Judul : " << bantu->data.judul << endl;
			cout <<"Genre : " << bantu->data.genre << endl;
            cout <<"Durasi : " << bantu->data.durasi << endl;
			cout <<"Harga : Rp " << bantu->data.harga << endl;
            cout <<"Kursi : " << bantu->data.kursi << endl;
			cout <<"-----------------------\n";

			ketemu = true;
		}
		bantu = bantu-> next;
	}
	
	if(ketemu == false){
		cout <<"Film tidak ditemukan\n";
	}
}

int main(){
    dataFilm();
    int menu;

    do{
        cout << "\n+=====================================+\n";
        cout << "|     SISTEM MANAJEMEN BIOSKOP	      |\n";
        cout << "+=====================================+\n";
        cout << "| [ 1 ] Now Showing		      |\n";
        cout << "| [ 2 ] Tambah Film Baru              |\n";
        cout << "| [ 3 ] Urutkan Harga Tiket	      |\n";
        cout << "| [ 4 ] Cari Genre Film 	      |\n";
        cout << "| [ 5 ] Hapus Film	              |\n";
        cout << "| [ 0 ] Keluar                        |\n";
        cout << "+=====================================+\n";

        cout << "Pilih Menu => ";
        cin >> menu;
        cin.ignore();

        if (menu == 1){
            tampilFilm();
        } else if (menu == 2){
            tambahFilm();
        } else if(menu == 4){
			cariFilm();
		} else if (menu == 5){
            hapusfilm();
        }
    } while (menu != 0);
}