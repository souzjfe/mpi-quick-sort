#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_STACK_SIZE 10000

typedef struct
{
    int low;
    int high;
} StackItem;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortIterative(int arr[], int low, int high)
{
    StackItem stack[MAX_STACK_SIZE];
    int top = -1;

    stack[++top].low = low;
    stack[top].high = high;

    while (top >= 0)
    {
        low = stack[top].low;
        high = stack[top--].high;

        int pivotIndex = partition(arr, low, high);

        if (pivotIndex - 1 > low)
        {
            stack[++top].low = low;
            stack[top].high = pivotIndex - 1;
        }

        if (pivotIndex + 1 < high)
        {
            stack[++top].low = pivotIndex + 1;
            stack[top].high = high;
        }
    }
}

int main(int argc, char **argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tamanhoVetor = 10000;
    int *arr = NULL;
    int *subArr = NULL;
    int subArrSize = tamanhoVetor / size;

    arr = (int *)malloc(tamanhoVetor * sizeof(int));
    subArr = (int *)malloc(subArrSize * sizeof(int));

    // Preencher o vetor com dados não ordenados (você pode usar sua própria lógica aqui)
    if (rank == 0)
    {
        for (int i = 0; i < tamanhoVetor; i++)
        {
            arr[i] = rand() % 10000;
        }
    }

    // Distribuir o vetor para os processos
    MPI_Scatter(arr, subArrSize, MPI_INT, subArr, subArrSize, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo classifica sua parte do vetor
    quickSortIterative(subArr, 0, subArrSize - 1);

    // Juntar os resultados
    MPI_Gather(subArr, subArrSize, MPI_INT, arr, subArrSize, MPI_INT, 0, MPI_COMM_WORLD);

    // O processo raiz imprime o vetor ordenado
    if (rank == 0)
    {
        printf("Vetor original:\n");
        for (int i = 0; i < tamanhoVetor; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    free(arr);
    free(subArr);

    MPI_Finalize();
    return 0;
}
