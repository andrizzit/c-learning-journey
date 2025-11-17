#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_NAME_LEN 50

typedef struct
{
    int parent[MAX_NODES];
    int rank[MAX_NODES];
    char nodes[MAX_NODES][MAX_NAME_LEN];
    int count;
} UnionFind;

void uf_init(UnionFind *uf)
{
    uf->count = 0;
    for (int i = 0; i < MAX_NODES; i++)
    {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

int uf_get_index(UnionFind *uf, const char *node)
{
    for (int i = 0; i < uf->count; i++)
    {
        if (strcmp(uf->nodes[i], node) == 0)
        {
            return i;
        }
    }
    strcpy(uf->nodes[uf->count], node);
    return uf->count++;
}

int uf_find(UnionFind *uf, int x)
{
    if (uf->parent[x] != x)
    {
        uf->parent[x] = uf->parent[uf->parent[x]];
    }
    return uf->parent[x];
}

void uf_union(UnionFind *uf, int x, int y)
{
    int root_x = uf_find(uf, x);
    int root_y = uf_find(uf, y);

    if (root_x == root_y)
        return;

    if (uf->rank[root_x] < uf->rank[root_y])
    {
        uf->parent[root_x] = root_y;
    }
    else if (uf->rank[root_x] > uf->rank[root_y])
    {
        uf->parent[root_y] = root_x;
    }
    else
    {
        uf->parent[root_y] = root_x;
        uf->rank[root_x]++;
    }
}

bool uf_are_connected(UnionFind *uf, const char *node1, const char *node2)
{
    if (strcmp(node1, node2) == 0)
    {
        return true;
    }

    int idx1 = uf_get_index(uf, node1);
    int idx2 = uf_get_index(uf, node2);

    return uf_find(uf, idx1) == uf_find(uf, idx2);
}

bool are_paths_equivalent(
    const char *path1[], int path1_size,
    const char *path2[], int path2_size,
    const char *equivalent_nodes[][2], int equiv_size)
{
    if (path1_size != path2_size)
    {
        return false;
    }

    UnionFind uf;
    uf_init(&uf);

    int i = 0;
    while (i < equiv_size)
    {
        int idx1 = uf_get_index(&uf, equivalent_nodes[i][0]);
        int idx2 = uf_get_index(&uf, equivalent_nodes[i][1]);
        uf_union(&uf, idx1, idx2);
        i++;
    }

    for (int i = 0; i < path1_size; i++)
    {
        if (!uf_are_connected(&uf, path1[i], path2[i]))
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    printf("Test 1: Direct equivalence\n");
    const char *path1[] = {"serverA", "gateway1", "database5"};
    const char *path2[] = {"serverB", "router7", "database3"};
    const char *equivalent_nodes[][2] = {
        {"serverA", "serverB"},
        {"gateway1", "router7"},
        {"database5", "database3"}};
    bool result = are_paths_equivalent(path1, 3, path2, 3, equivalent_nodes, 3);
    printf("Result: %s\n\n", result ? "Equivalent" : "Not equivalent");

    printf("Test 2: Transitive relationship\n");
    const char *path3[] = {"nodeX", "nodeY", "nodeZ"};
    const char *path4[] = {"nodeP", "nodeY", "nodeR"};
    const char *equivalent_nodes2[][2] = {
        {"nodeX", "nodeP"},
        {"nodeP", "nodeQ"},
        {"nodeZ", "nodeR"}};
    result = are_paths_equivalent(path3, 3, path4, 3, equivalent_nodes2, 3);
    printf("Result: %s\n\n", result ? "Equivalent" : "Not equivalent");

    printf("Test 3: Not equivalent\n");
    const char *path5[] = {"serverA", "gateway1", "database5"};
    const char *path6[] = {"serverB", "router7", "database3"};
    const char *equivalent_nodes3[][2] = {
        {"serverA", "serverB"},
        {"database5", "database3"}};
    result = are_paths_equivalent(path5, 3, path6, 3, equivalent_nodes3, 2);
    printf("Result: %s\n\n", result ? "Equivalent" : "Not equivalent");

    printf("Test 4: Transitive chain\n");
    const char *path7[] = {"A"};
    const char *path8[] = {"D"};
    const char *equivalent_nodes4[][2] = {
        {"A", "B"},
        {"B", "C"},
        {"C", "D"} // A ≡ B ≡ C ≡ D (transitive chain)
    };
    result = are_paths_equivalent(path7, 1, path8, 1, equivalent_nodes4, 3);
    printf("Result: %s\n\n", result ? "Equivalent" : "Not equivalent");

    return 0;
}
