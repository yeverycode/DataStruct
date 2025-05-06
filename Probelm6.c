#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // 도시 맵 크기

typedef struct {
    int x, y;
    int time;
} Virus;

typedef struct {
    Virus data[400];
    int front, rear;
} Queue;

// 큐 초기화
void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

// 큐에 추가
void enqueue(Queue* q, Virus v) {
    q->data[q->rear++] = v;
}

// 큐에서 꺼내기
Virus dequeue(Queue* q) {
    return q->data[q->front++];
}

// 큐 비었는지 확인
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

int dx[4] = { -1, 1, 0, 0 }; // 상하좌우
int dy[4] = { 0, 0, -1, 1 };

typedef struct {
    int x, y;
} Point;

int main() {
    Queue q;
    init_queue(&q);

    // 초기 감염 지역 큐에 넣기
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
        int cnt = q.rear - q.front;  // 현재 시간대의 감염 지역 수
        Point infected[400];
        int infected_count = 0;

        for (int i = 0; i < cnt; i++) {
            Virus curr = dequeue(&q);

            // 감염 시간 기록 (처음 감염 제외하고는 시간 기록)
            if (curr.time != 0) {
                map[curr.x][curr.y] = curr.time;
            }

            // 감염 확산
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
            printf("[시간 %d]\n→ 감염된 지역: ", current_time);
            for (int i = 0; i < infected_count; i++) {
                printf("(%d,%d)", infected[i].x, infected[i].y);
                if (i != infected_count - 1) printf(", ");
            }
            printf("\n");
            current_time++;
        }
    }

    // 최종 맵 출력
    printf("\n=== 최종 감염 상태 ===\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == -1) printf(" X ");
            else printf("%2d ", map[i][j]);
        }
        printf("\n");
    }

    printf("\n[종료]\n총 감염 소요 시간: %d시간\n", max_time);

    return 0;
}
