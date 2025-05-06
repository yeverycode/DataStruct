#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // ���� �� ũ��

typedef struct {
    int x, y;
    int time;
} Virus;

typedef struct {
    Virus data[400];
    int front, rear;
} Queue;

// ť �ʱ�ȭ
void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

// ť�� �߰�
void enqueue(Queue* q, Virus v) {
    q->data[q->rear++] = v;
}

// ť���� ������
Virus dequeue(Queue* q) {
    return q->data[q->front++];
}

// ť ������� Ȯ��
int is_empty(Queue* q) {
    return q->front == q->rear;
}

int map[SIZE][SIZE] = {
    {1, 0, 0, 0, -1},
    {0, 0, -1, 0, 0},
    {0, -1, 0, 0, 0},
    {0, 0, 0, -1, 0},
    {0, 0, 0, 0, 0}
};

int visited[SIZE][SIZE] = { 0 };

int dx[4] = { -1, 1, 0, 0 }; // �����¿�
int dy[4] = { 0, 0, -1, 1 };

typedef struct {
    int x, y;
} Point;

int main() {
    Queue q;
    init_queue(&q);

    // �ʱ� ���� ���� ť�� �ֱ�
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 1) {
                Virus v = { i, j, 0 };
                enqueue(&q, v);
                visited[i][j] = 1;
            }
        }
    }

    int max_time = 0;
    int current_time = 1;

    while (!is_empty(&q)) {
        int cnt = q.rear - q.front;  // ���� �ð����� ���� ���� ��
        Point infected[400];
        int infected_count = 0;

        for (int i = 0; i < cnt; i++) {
            Virus curr = dequeue(&q);

            // ���� �ð� ��� (ó�� ���� �����ϰ�� �ð� ���)
            if (curr.time != 0) {
                map[curr.x][curr.y] = curr.time;
            }

            // ���� Ȯ��
            for (int d = 0; d < 4; d++) {
                int nx = curr.x + dx[d];
                int ny = curr.y + dy[d];

                if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE) {
                    if (map[nx][ny] == 0 && visited[nx][ny] == 0) {
                        visited[nx][ny] = 1;

                        Virus next = { nx, ny, curr.time + 1 };
                        enqueue(&q, next);

                        infected[infected_count].x = nx;
                        infected[infected_count].y = ny;
                        infected_count++;
                        max_time = next.time;
                    }
                }
            }
        }

        if (infected_count > 0) {
            printf("[�ð� %d]\n�� ������ ����: ", current_time);
            for (int i = 0; i < infected_count; i++) {
                printf("(%d,%d)", infected[i].x, infected[i].y);
                if (i != infected_count - 1) printf(", ");
            }
            printf("\n");
            current_time++;
        }
    }

    // ���� �� ���
    printf("\n=== ���� ���� ���� ===\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == -1) printf(" X ");
            else printf("%2d ", map[i][j]);
        }
        printf("\n");
    }

    printf("\n[����]\n�� ���� �ҿ� �ð�: %d�ð�\n", max_time);

    return 0;
}
