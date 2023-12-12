#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10000

typedef struct {
    int low;
    int high;
} StackItem;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortIterative(int arr[], int low, int high) {
    StackItem stack[MAX_STACK_SIZE];
    int top = -1;

    stack[++top].low = low;
    stack[top].high = high;

    while (top >= 0) {
        low = stack[top].low;
        high = stack[top--].high;

        int pivotIndex = partition(arr, low, high);

        if (pivotIndex - 1 > low) {
            stack[++top].low = low;
            stack[top].high = pivotIndex - 1;
        }

        if (pivotIndex + 1 < high) {
            stack[++top].low = pivotIndex + 1;
            stack[top].high = high;
        }
    }
}

int main() {
    int tamanhoVetor = 80000000;
    int *arr;
    arr = (int *)malloc(tamanhoVetor * sizeof(int));

    // Preencha o vetor com dados não ordenados (você pode usar sua própria lógica aqui)

    // Exemplo de preenchimento do vetor com dados aleatórios
    for (int i = 0; i < tamanhoVetor; i++) {
        arr[i] = rand() % 10000;
    }

    quickSortIterative(arr, 0, tamanhoVetor - 1);


    free(arr);
    return 0;
}
