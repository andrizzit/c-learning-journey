#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool are_nodes_equivalent(
    const char *node1, const char *node2,
    const char *equivalent_nodes[][2], int equiv_size)
{

    if (strcmp(node1, node2) == 0)
    {
        return true;
    }

    for (int i = 0; i < equiv_size; i++)
    {
        if ((strcmp(node1, equivalent_nodes[i][0]) == 0 &&
             strcmp(node2, equivalent_nodes[i][1]) == 0) ||
            (strcmp(node1, equivalent_nodes[i][1]) == 0 &&
             strcmp(node2, equivalent_nodes[i][0]) == 0))
        {
            return true;
        }
    }

    return false;
}
bool are_paths_equivalent(
    const char *path1[], int path1_size,
    const char *path2[], int path2_size,
    const char *equivalent_nodes[][2], int equiv_size)
{

    if (path1_size != path2_size)
        return false;

    for (int i = 0; i < path1_size; i++)
    {
        if (!are_nodes_equivalent(path1[i], path2[i], equivalent_nodes, equiv_size))
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

    return 0;
}
