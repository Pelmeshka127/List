#include "../includes/dump.h"

int List_Graph_Dump(list_s * header)
{
    #ifdef LIST_DUMP

    static int graph_num = 1;
    FILE * graph_file = fopen("graphics/graph.dot", "w");
    if (graph_file == nullptr)
    {
        fprintf(stderr, "Failed openning file %s in function\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    fprintf(graph_file, "digraph G {\n");
    fprintf(graph_file, "  rankdir = LR;\n");
    fprintf(graph_file, "  splines = polyline;\n");
    fprintf(graph_file, "  node[fontsize=14];\n  edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n");

    list_node * cur_node = header->head;
    for (int index = 1; index <= header->size; index++)
    {
        fprintf(graph_file, "  node%d[shape = Mrecord, style = filled," 
                "label = \" <index> adress = %p | data = %d | <next_idx> next = %p | <prev_idx> prev = %p\"," 
                "fillcolor = \"#FFD0D0\"];\n",
                index, cur_node, cur_node->data, cur_node->next == nullptr ? nullptr : cur_node->next, 
                cur_node->prev == nullptr ? nullptr : cur_node->prev);
        cur_node = cur_node->next;
    }

    for (int index = 2; index <= header->size - 1; index++)
    {
        fprintf(graph_file, "  node%d : <next_idx> -> node%d : <next_idx> [color=\"green\"];\n", index, index + 1);
        fprintf(graph_file, "  node%d : <prev_idx> -> node%d : <prev_idx> [color=\"red\"];\n", index, index - 1);
    }

    if (header->size >= 2)
    {
        fprintf(graph_file, "  node%d : <next_idx> -> node%d : <next_idx> [color=\"green\"];\n", 1, 2);
        fprintf(graph_file, "  node%zu : <prev_idx> -> node%zu : <prev_idx> [color=\"red\"];\n", header->size, header->size - 1);
    }

    fprintf(graph_file, "  head[shape = Mrecord, style = filled, fillcolor = lightgoldenrod, label = \" Head adress = %p \"];\n", header->head);
    fprintf(graph_file, "  head -> node%d : <index> ;\n", 1);

    fprintf(graph_file, "  tail[shape = Mrecord, style = filled, fillcolor = lightskyblue, label = \" Tail adress = %p \"];\n", header->tail);
    fprintf(graph_file, "  tail -> node%d : <index> ;\n", header->size);

    fprintf(graph_file, "}");

    if (fclose(graph_file) == EOF)
    {
        fprintf(stderr, "Failed closing file %s in function\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    char cmd[100] = " ";
    sprintf(cmd, "dot graphics/graph.dot -Tpng -o graphics/gpaph%d.png", graph_num);
    graph_num++;
    system(cmd);

    #endif

    return No_Error;
}