#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Stack {
    int count;
    Node* top;
};

void createStack(Stack& stack) {
    stack.count = 0;
    stack.top = nullptr;
}

bool isEmpty(Stack& stack) {
    return stack.count == 0;
}

bool isFull() {
    return false;
}

bool push(Stack& stack, int data) {
    if (isFull()) {
        return false;
    } else {
        Node* newPtr = new Node;
        newPtr->data = data;
        newPtr->next = stack.top;
        stack.top = newPtr;
        stack.count++;
        return true;
    }
}

bool pop(Stack& stack, int& dataOut) {
    if (isEmpty(stack)) {
        return false;
    } else {
        Node* dltPtr = stack.top;
        dataOut = stack.top->data;
        stack.top = stack.top->next;
        stack.count--;
        delete dltPtr;
        return true;
    }
}

bool stackTop(Stack& stack, int& dataOut) {
    if (isEmpty(stack)) {
        return false;
    } else {
        dataOut = stack.top->data;
        return true;
    }
}

void destroyStack(Stack& stack) {
    while (stack.top != nullptr) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
    stack.count = 0;
}

int stackCount(Stack& stack) {
    return stack.count;
}

int main() {
    Stack stack;
    createStack(stack);

    int choice, value;

    do {
        cout << "\nMenu Operasi Stack:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Lihat Elemen Teratas\n";
        cout << "4. Jumlah Elemen\n";
        cout << "5. Hancurkan Stack\n";
        cout << "6. Keluar\n";
        cout << "Pilih operasi (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan nilai untuk ditambahkan ke stack: ";
                cin >> value;
                if (push(stack, value)) {
                    cout << "Nilai " << value << " berhasil ditambahkan ke stack.\n";
                } else {
                    cout << "Stack penuh, tidak dapat menambahkan nilai.\n";
                }
                break;

            case 2:
                if (pop(stack, value)) {
                    cout << "Nilai " << value << " berhasil dihapus dari stack.\n";
                } else {
                    cout << "Stack kosong, tidak ada nilai yang dapat dihapus.\n";
                }
                break;

            case 3:
                if (stackTop(stack, value)) {
                    cout << "Elemen teratas: " << value << endl;
                } else {
                    cout << "Stack kosong, tidak ada elemen teratas.\n";
                }
                break;

            case 4:
                cout << "Jumlah elemen dalam stack: " << stackCount(stack) << endl;
                break;

            case 5:
                destroyStack(stack);
                cout << "Stack telah dihancurkan.\n";
                break;

            case 6:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid. Silakan pilih antara 1-6.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}