#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ���� Ž�� �Լ�
int linear_search(int arr[], int n, int target, int* comp_count) {
    *comp_count = 0;
    for (int i = 0; i < n; i++) {
        (*comp_count)++;
        if (arr[i] == target) return i;
    }
    return -1;
}

// ���� Ž�� �Լ�
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
    printf("ã���� �ϴ� �峭�� ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &target);

    int index, comp_count;

    // â�� (���� Ž��)
    printf("\n[â�� Ž�� - ���� Ž��]\n");
    index = linear_search(warehouse, 10, target, &comp_count);
    if (index != -1)
        printf("�˻� ����! �ε���: %d, �� Ƚ��: %d\n", index, comp_count);
    else
        printf("�˻� ����. �� Ƚ��: %d\n", comp_count);

    // ���� (���� Ž��)
    printf("\n[���� Ž�� - ���� Ž��]\n");
    index = binary_search(shelf, 10, target, &comp_count);
    if (index != -1)
        printf("�˻� ����! �ε���: %d, �� Ƚ��: %d\n", index, comp_count);
    else
        printf("�˻� ����. �� Ƚ��: %d\n", comp_count);

    // ���
    printf("\n[���]\n");
    printf("������ ���� Ž���� �Ϲ������� �� ȿ�����Դϴ�.\n");
    printf("����: ������ ���ĵǾ� �����Ƿ� ���� Ž���� �� Ƚ���� �ξ� ���� �� �ֱ� �����Դϴ�.\n");

    return 0;
}
