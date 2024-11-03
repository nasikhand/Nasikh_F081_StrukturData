#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void tambahAwal(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
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
    for (int i = 1; i < posisi - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Posisi melebihi panjang list.\n");
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void tambahAkhir(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void hapusAwal(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void hapusTengah(struct Node** head, int posisi) {
    if (*head == NULL) return;
    if (posisi <= 1) {
        hapusAwal(head);
        return;
    }

    struct Node* temp = *head;
    for (int i = 1; i < posisi && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Posisi melebihi panjang list.\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void hapusAkhir(struct Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    free(temp);
}

bool cariData(struct Node* head, int target) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == target) return true;
        temp = temp->next;
    }
    return false;
}

int hitungJumlahData(struct Node* head) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int jumlahkanData(struct Node* head) {
    int sum = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

void tampilkanList(struct Node* head) {
    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    struct Node* temp = head;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

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