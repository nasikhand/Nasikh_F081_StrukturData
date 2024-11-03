#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAMA 50

typedef struct Mahasiswa {
    char nama[MAX_NAMA];
    char jenisKelamin;
    struct Mahasiswa* next;
} Mahasiswa;

typedef struct {
    Mahasiswa* head;
    int jumlah;
} Lingkaran;

Mahasiswa* buatMahasiswa(char nama[], char jenisKelamin) {
    Mahasiswa* baru = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenisKelamin = jenisKelamin;
    baru->next = NULL;
    return baru;
}

void tambahMahasiswa(Lingkaran* l, char nama[], char jenisKelamin) {
    if (l->jumlah >= 20) {
        printf("Lingkaran sudah penuh, tidak bisa menambah %s.\n", nama);
        return;
    }

    Mahasiswa* baru = buatMahasiswa(nama, jenisKelamin);

    if (l->head == NULL) {
        l->head = baru;
        baru->next = baru;  // Circular linked list
    } else {
        Mahasiswa* temp = l->head;
        while (temp->next != l->head) {
            temp = temp->next;
        }
        temp->next = baru;
        baru->next = l->head;
    }

    l->jumlah++;
    printf("%s ditambahkan ke lingkaran.\n", nama);
}

void hapusMahasiswa(Lingkaran* l, char nama[]) {
    if (l->head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    Mahasiswa* current = l->head;
    Mahasiswa* prev = NULL;

    do {
        if (strcmp(current->nama, nama) == 0) {
            if (prev == NULL) {
                if (l->head->next == l->head) {
                    free(l->head);
                    l->head = NULL;
                } else {
                    Mahasiswa* last = l->head;
                    while (last->next != l->head) {
                        last = last->next;
                    }
                    l->head = l->head->next;
                    last->next = l->head;
                    free(current);
                }
            } else {
                prev->next = current->next;
                if (current == l->head) {
                    l->head = prev->next;
                }
                free(current);
            }
            l->jumlah--;
            printf("%s dihapus dari lingkaran.\n", nama);
            return;
        }
        prev = current;
        current = current->next;
    } while (current != l->head);

    printf("%s tidak ditemukan dalam lingkaran.\n", nama);
}

bool cekCindy(Lingkaran* l) {
    if (l->head == NULL) return true;

    Mahasiswa* current = l->head;
    do {
        if (strcmp(current->nama, "Cindy") == 0) {
            if (current->next->jenisKelamin == 'L' || 
                current->next == l->head && l->head->jenisKelamin == 'L') {
                return false;
            }
        }
        current = current->next;
    } while (current != l->head);

    return true;
}

void pisahLingkaran(Lingkaran* l, Lingkaran* lL, Lingkaran* lP) {
    if (l->head == NULL) return;

    Mahasiswa* current = l->head;
    do {
        if (current->jenisKelamin == 'L') {
            tambahMahasiswa(lL, current->nama, 'L');
        } else {
            tambahMahasiswa(lP, current->nama, 'P');
        }
        current = current->next;
    } while (current != l->head);
}

void tampilkanLingkaran(Lingkaran* l) {
    if (l->head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    printf(" --- Anggota Lingkaran : ");
    Mahasiswa* current = l->head;
    do {
        printf("%s(%c) ", current->nama, current->jenisKelamin);
        current = current->next;
    } while (current != l->head);
    printf("\n");
}

int main() {
    Lingkaran lingkaran = {NULL, 0};
    Lingkaran lingkaranL = {NULL, 0};
    Lingkaran lingkaranP = {NULL, 0};
    char pilihan;
    char nama[MAX_NAMA];
    char jenisKelamin;

    do {
        printf("\n1. Tambah mahasiswa\n");
        printf("2. Hapus mahasiswa\n");
        printf("3. Tampilkan lingkaran\n");
        printf("4. Pisahkan lingkaran\n");
        printf("5. Keluar\n");
        printf("Pilihan Anda: ");
        scanf(" %c", &pilihan);

        switch(pilihan) {
            case '1':
                printf("Masukkan nama: ");
                scanf("%s", nama);
                printf("Masukkan jenis kelamin (L/P): ");
                scanf(" %c", &jenisKelamin);
                tambahMahasiswa(&lingkaran, nama, jenisKelamin);
                if (!cekCindy(&lingkaran)) {
                    printf("Cindy tidak bisa bergabung karena posisinya.\n");
                    hapusMahasiswa(&lingkaran, "Cindy");
                }
                break;
            case '2':
                printf("Masukkan nama yang akan dihapus: ");
                scanf("%s", nama);
                if (strcmp(nama, "Irsyad") == 0 || strcmp(nama, "Arsyad") == 0) {
                    hapusMahasiswa(&lingkaran, "Irsyad");
                    hapusMahasiswa(&lingkaran, "Arsyad");
                } else {
                    hapusMahasiswa(&lingkaran, nama);
                }
                break;
            case '3':
                tampilkanLingkaran(&lingkaran);
                break;
            case '4':
                pisahLingkaran(&lingkaran, &lingkaranL, &lingkaranP);
                printf("-----------------------------------------\n");
                printf("|--------| Lingkaran Laki - Laki |------|\n");
                printf("-----------------------------------------\n\n");
                tampilkanLingkaran(&lingkaranL);
                printf("\n-----------------------------------------\n");
                printf("|--------| Lingkaran Perempuan   |------|\n");
                printf("-----------------------------------------\n\n");
                tampilkanLingkaran(&lingkaranP);
                break;
            case '5':
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != '5');

    return 0;
}