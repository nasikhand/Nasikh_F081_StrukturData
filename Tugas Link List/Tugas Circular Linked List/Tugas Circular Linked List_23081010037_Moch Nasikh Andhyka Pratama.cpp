#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int nama;
    char jenisKelamin;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void tambahAwal(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        newNode->next = *head;
        temp->next = newNode;
        *head = newNode;
    }
}

void tambahTengah(struct Node** head, int data, int posisi) {
    if (posisi <= 1) {
        tambahAwal(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    for (int i = 1; i < posisi - 1 && temp->next != *head; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void tambahAkhir(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void hapusAwal(struct Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        struct Node* toDelete = *head;
        *head = (*head)->next;
        temp->next = *head;
        free(toDelete);
    }
}

void hapusTengah(struct Node** head, int posisi) {
    if (*head == NULL) return;
    if (posisi <= 1) {
        hapusAwal(head);
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;
    int i;
    for (i = 1; i < posisi && temp->next != *head; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (i == posisi) {
        prev->next = temp->next;
        free(temp);
    }
}

void hapusAkhir(struct Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        struct Node* temp = *head;
        struct Node* prev = NULL;
        while (temp->next != *head) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = *head;
        free(temp);
    }
}

bool cariData(struct Node* head, int target) {
    if (head == NULL) return false;

    struct Node* temp = head;
    do {
        if (temp->data == target) return true;
        temp = temp->next;
    } while (temp != head);

    return false;
}

int hitungJumlahData(struct Node* head) {
    if (head == NULL) return 0;

    int count = 0;
    struct Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

int jumlahkanData(struct Node* head) {
    if (head == NULL) return 0;

    int sum = 0;
    struct Node* temp = head;
    do {
        sum += temp->data;
        temp = temp->next;
    } while (temp != head);

    return sum;
}

void tampilkanList(struct Node* head) {
    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(kembali ke awal)\n");
}

void freeList(struct Node** head) {
    if (*head == NULL) return;

    struct Node* current = *head;
    struct Node* next;

    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != *head);

    *head = NULL;
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
                if (cariData(head, data))
                    printf("Data ditemukan\n");
                else
                    printf("Data tidak ditemukan\n");
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
                freeList(&head);
                return 0;
            default:
                printf("Pilihan tidak valid\n");
        }
    }

    return 0;
}