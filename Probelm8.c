#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 선형 탐색 함수
int linear_search(int arr[], int n, int target, int* comp_count) {
    *comp_count = 0;
    for (int i = 0; i < n; i++) {
        (*comp_count)++;
        if (arr[i] == target) return i;
    }
    return -1;
}

// 이진 탐색 함수
int binary_search(int arr[], int n, int target, int* comp_count) {
    *comp_count = 0;
    int left = 0, right = n - 1;

    while (left <= right) {
        (*comp_count)++;
        int mid = (left + right) / 2;

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    int warehouse[10] = { 13, 5, 27, 8, 2, 11, 19, 3, 9, 15 };
    int shelf[10] = { 2, 3, 5, 8, 9, 11, 13, 15, 19, 27 };

    int target;
    printf("찾고자 하는 장난감 번호를 입력하세요: ");
    scanf("%d", &target);

    int index, comp_count;

    // 창고 (선형 탐색)
    printf("\n[창고 탐색 - 선형 탐색]\n");
    index = linear_search(warehouse, 10, target, &comp_count);
    if (index != -1)
        printf("검색 성공! 인덱스: %d, 비교 횟수: %d\n", index, comp_count);
    else
        printf("검색 실패. 비교 횟수: %d\n", comp_count);

    // 선반 (이진 탐색)
    printf("\n[선반 탐색 - 이진 탐색]\n");
    index = binary_search(shelf, 10, target, &comp_count);
    if (index != -1)
        printf("검색 성공! 인덱스: %d, 비교 횟수: %d\n", index, comp_count);
    else
        printf("검색 실패. 비교 횟수: %d\n", comp_count);

    // 결론
    printf("\n[결론]\n");
    printf("선반의 이진 탐색이 일반적으로 더 효율적입니다.\n");
    printf("이유: 선반은 정렬되어 있으므로 이진 탐색이 비교 횟수를 훨씬 줄일 수 있기 때문입니다.\n");

    return 0;
}
