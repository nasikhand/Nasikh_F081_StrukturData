#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struktur node untuk linked list
struct Node {
    int data;
    struct Node* next;
};

// Fungsi untuk membuat node baru
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Tambah data di awal daftar tertaut
void tambahAwal(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Tambah data di tengah daftar tertaut
void tambahTengah(struct Node** head, int data, int posisi) {
    if (posisi <= 0) {
        printf("Posisi tidak valid.\n");
        return;
    }
    
    if (posisi == 1 || *head == NULL) {
        tambahAwal(head, data);
        return;
    }
    
    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    int count = 1;
    
    while (count < posisi - 1 && temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
}

// Tambah data di akhir daftar tertaut
void tambahAkhir(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Hapus data di awal daftar tertaut
void hapusAwal(struct Node** head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Hapus data di tengah daftar tertaut
void hapusTengah(struct Node** head, int posisi) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }
    struct Node* temp = *head;
    struct Node* prev = NULL;
    int count = 1;

    if (posisi == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && count < posisi) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Posisi melebihi panjang list.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Hapus data di akhir daftar tertaut
void hapusAkhir(struct Node** head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    struct Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Pencarian data dalam daftar tertaut
bool cariData(struct Node* head, int target) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == target) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Menampilkan informasi jumlah data di daftar tertaut
int hitungJumlahData(struct Node* head) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Menampilkan hasil penjumlahan dari semua data di linked list
int jumlahkanData(struct Node* head) {
    int sum = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

// Fungsi untuk menampilkan linked list
void tampilkanList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int pilihan, data, posisi;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Cari data\n");
        printf("8. Tampilkan jumlah data\n");
        printf("9. Tampilkan jumlah semua data\n");
        printf("10. Tampilkan list\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukkan data: ");
                scanf("%d", &data);
                tambahAwal(&head, data);
                break;
            case 2:
                printf("Masukkan data: ");
                scanf("%d", &data);
                printf("Masukkan posisi: ");
                scanf("%d", &posisi);
                tambahTengah(&head, data, posisi);
                break;
            case 3:
                printf("Masukkan data: ");
                scanf("%d", &data);
                tambahAkhir(&head, data);
                break;
            case 4:
                hapusAwal(&head);
                break;
            case 5:
                printf("Masukkan posisi: ");
                scanf("%d", &posisi);
                hapusTengah(&head, posisi);
                break;
            case 6:
                hapusAkhir(&head);
                break;
            case 7:
                printf("Masukkan data yang dicari: ");
                scanf("%d", &data);
                if (cariData(head, data)) {
                    printf("Data %d ditemukan.\n", data);
                } else {
                    printf("Data %d tidak ditemukan.\n", data);
                }
                break;
            case 8:
                printf("Jumlah data: %d\n", hitungJumlahData(head));
                break;
            case 9:
                printf("Jumlah semua data: %d\n", jumlahkanData(head));
                break;
            case 10:
                tampilkanList(head);
                break;
            case 0:
                // Membersihkan memori sebelum keluar
                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                printf("Terima kasih, program selesai.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}