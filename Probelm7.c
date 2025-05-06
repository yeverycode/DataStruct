#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 버블 정렬
void bubble_sort(int arr[], int n, int* comp, int* swap) {
    *comp = *swap = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swap)++;
            }
        }
    }
}

// 선택 정렬
void selection_sort(int arr[], int n, int* comp, int* swap) {
    *comp = *swap = 0;

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            (*swap)++;
        }
    }
}

// 삽입 정렬
void insertion_sort(int arr[], int n, int* comp, int* swap) {
    *comp = *swap = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            (*comp)++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                (*swap)++;
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// 배열 출력
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int memory[10] = { 42, 17, 8, 99, 3, 67, 21, 14, 88, 5 };
    int arr[10], n = 10;
    int comp, swap;

    printf("====== 버블 정렬 ======\n");
    for (int i = 0; i < n; i++) arr[i] = memory[i];
    printf("정렬 전: ");
    print_array(arr, n);
    bubble_sort(arr, n, &comp, &swap);
    printf("정렬 후: ");
    print_array(arr, n);
    printf("비교 횟수: %d, 교환 횟수: %d\n\n", comp, swap);

    printf("====== 선택 정렬 ======\n");
    for (int i = 0; i < n; i++) arr[i] = memory[i];
    printf("정렬 전: ");
    print_array(arr, n);
    selection_sort(arr, n, &comp, &swap);
    printf("정렬 후: ");
    print_array(arr, n);
    printf("비교 횟수: %d, 교환 횟수: %d\n\n", comp, swap);

    printf("====== 삽입 정렬 ======\n");
    for (int i = 0; i < n; i++) arr[i] = memory[i];
    printf("정렬 전: ");
    print_array(arr, n);
    insertion_sort(arr, n, &comp, &swap);
    printf("정렬 후: ");
    print_array(arr, n);
    printf("비교 횟수: %d, 교환 횟수: %d\n\n", comp, swap);

    return 0;
}
