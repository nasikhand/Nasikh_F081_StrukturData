#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    int count;
    struct Node* top;
};

void createStack(struct Stack* stack) {
    stack->count = 0;
    stack->top = NULL;
}

int isEmpty(struct Stack* stack) {
    return stack->count == 0;
}

int isFull(struct Stack* stack) {
    return stack->count >= MAX_SIZE;
}

int push(struct Stack* stack, int data) {
    if (isFull(stack)) {
        return 0;
    } else {
        struct Node* newPtr = (struct Node*)malloc(sizeof(struct Node));
        newPtr->data = data;
        newPtr->next = stack->top;
        stack->top = newPtr;
        stack->count++;
        return 1;
    }
}

int pop(struct Stack* stack, int* dataOut) {
    if (isEmpty(stack)) {
        return 0;
    } else {
        struct Node* dltPtr = stack->top;
        *dataOut = stack->top->data;
        stack->top = stack->top->next;
        stack->count--;
        free(dltPtr);
        return 1;
    }
}

int stackTop(struct Stack* stack, int* dataOut) {
    if (isEmpty(stack)) {
        return 0;
    } else {
        *dataOut = stack->top->data;
        return 1;
    }
}

void destroyStack(struct Stack* stack) {
    while (stack->top != NULL) {
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    stack->count = 0;
}

int stackCount(struct Stack* stack) {
    return stack->count;
}

int main() {
    struct Stack stack;
    createStack(&stack);

    int choice, value;

    do {
        printf("\nMenu Operasi Stack:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Lihat Elemen Teratas\n");
        printf("4. Jumlah Elemen\n");
        printf("5. Hancurkan Stack\n");
        printf("6. Cek Apakah Stack Kosong\n");
        printf("7. Cek Apakah Stack Penuh\n");
        printf("8. Keluar\n");
        printf("Pilih operasi (1-8): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nilai untuk ditambahkan ke stack: ");
                scanf("%d", &value);
                if (push(&stack, value)) {
                    printf("Nilai %d berhasil ditambahkan ke stack.\n", value);
                } else {
                    printf("Stack penuh, tidak dapat menambahkan nilai.\n");
                }
                break;

            case 2:
                if (pop(&stack, &value)) {
                    printf("Nilai %d berhasil dihapus dari stack.\n", value);
                } else {
                    printf("Stack kosong, tidak ada nilai yang dapat dihapus.\n");
                }
                break;

            case 3:
                if (stackTop(&stack, &value)) {
                    printf("Elemen teratas: %d\n", value);
                } else {
                    printf("Stack kosong, tidak ada elemen teratas.\n");
                }
                break;

            case 4:
                printf("Jumlah elemen dalam stack: %d\n", stackCount(&stack));
                break;

            case 5:
                destroyStack(&stack);
                printf("Stack telah dihancurkan.\n");
                break;

            case 6:
            	 if (isEmpty(&stack)) {
                    printf("Stack kosong.\n");
                } else {
                    printf("Stack tidak kosong.\n");
                }
                break;
                
            case 7:
                if (isFull(&stack)) {
                    printf("Stack penuh.\n");
                } else {
                    printf("Stack tidak penuh.\n");
                }
                break;

            case 8:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan pilih antara 1-6.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}