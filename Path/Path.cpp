#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */
int path[MAX_VERTICES];

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g)
{
	static int step = 1; // static ?
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

//
void shortest_path(GraphType* g, int start)
{
	int i, u, w, min;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		path[i] = start;
		found[i] = FALSE;
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	path[start] = -1;
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					path[w] = u;
				}
	}

}

void print_path(int start, int end) {
	int result[MAX_VERTICES];
	int k = end;
	int idx=0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		result[i] = k;
		int tmp = path[k];
		if (tmp == -1)
			break;
		k = tmp;
	}
	for (int i = 0; i < MAX_VERTICES; i++)
		if (result[i] == start)
			idx = i;
	for (int j= idx; j>0;j--) {		
		printf("<%d->%d> ", result[j], result[j - 1]);
	}
}

int main(void)
{
	GraphType g = { 7,
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7, 0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 2, INF, INF, INF },
	{ INF, 10, 2, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 } }
	};
	shortest_path(&g, 0);
	print_path(0, 3);
	
	return 0;
}