#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../list_includes/dump.h"

    static int graph_num = 1;

//---------------------------------------------------------------------------------------------//

void List_Console_Dump(list_s * const header)
{
    #ifdef LIST_CONSOLE_DUMP

    assert(header);
    
    printf("\n//-------------------------------------------------------//\n");\

    if (header->is_sorted == true)
        printf("The list is sorted\n");

    else
        printf("The list is not sorted\n");

    printf("The capacity of the list is %u\n", header->capacity);

    printf("It's size is %u\n", header->size);

    printf("The index of the head is %d; The index of the tail is %d\n", header->head, header->tail);
    
    for (size_t i = 0; i <= header->capacity; i++)
        printf("The index of node is %zu; It's value is %d; The next idx is %d; The previous idx is %d\n",
        i, header->node[i].data, header->node[i].next, header->node[i].prev);

    printf("The free index has number %d\n", header->free);

    printf("//------------------------------------------------------//\n");

    #endif
}

//---------------------------------------------------------------------------------------------//

int List_Dump(list_s * const header, FILE * log_file)
{
    assert(header);

    fprintf(log_file, "<pre>\n");

    fprintf(log_file, "The capacity of the list is %d\n", header->capacity);
    fprintf(log_file, "The size of the list is %d\n", header->size);
    fprintf(log_file, "The index of the head is %d\n", header->head);
    fprintf(log_file, "The index of the tail is %d\n", header->tail);
    fprintf(log_file, "The index of the free node is %d\n", header->free);

    fprintf(log_file, "Index: ");
    for (int index = 0; index <= header->capacity; index++)
        fprintf(log_file, " %d ", index);

    fprintf(log_file, "\nData: ");
    for (int index = 0; index <= header->capacity; index++)
        fprintf(log_file, " %d ", header->node[index].data);
        
    fprintf(log_file, "\nNext: ");
    for (int index = 0; index <= header->capacity; index++)
        fprintf(log_file, " %d ", header->node[index].next);

    fprintf(log_file, "\nPrev: ");
    for (int index = 0; index <= header->capacity; index++)
        fprintf(log_file, " %d ", header->node[index].prev);
        
    List_Graph_Dump(header);
    fprintf(log_file, "\n<image src = \"gpaph%d.png\" /image>\n\n\n", graph_num - 1);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Graph_Dump(list_s * const header)
{
    #ifdef LIST_GRAPH_DUMP

    assert(header);

    FILE * graph_file = fopen("graphics/graph.dot", "w");
    if (graph_file == nullptr)
    {
        fprintf(stderr, "Failed openning graph.dot in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    fprintf(graph_file, "digraph List\n{\n");
    fprintf(graph_file, "  rankdir = LR;\n");
    //fprintf(graph_file, "  splines = polyline;\n");
    //fprintf(graph_file, "  ranksep = 2;\n");
    fprintf(graph_file, "  node[fontsize=14];\n  edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n");
    fprintf(graph_file, "  header[shape = Mrecord, style = filled, fillcolor = \"lightgoldenrod\","
                        "label = \" <head> Head = %d | <tail> Tail = %d | <free> Free = %d | <size> Size = %d | Is_List_Sorted: %s\"];\n",
                        header->head, header->tail, header->free, header->size ,header->is_sorted == true ? "YES" : "NO");

    fprintf(graph_file, "  node0  -> node%d[color = \"webgray\", style = \"dashed\"];\n", header->head);
    fprintf(graph_file, "  node%d -> node0 [color = \"webgray\", style = \"dashed\"];\n", header->tail);

    for (int index = 0; index <= header->capacity; index++)
    {
        fprintf(graph_file, "  node%d[shape = Mrecord, style = filled," 
                            "label = \" <index> index = %d | data = %d | <next_idx> next = %d | <prev_idx> prev = %d\"," 
                            "fillcolor = %s];\n",
                            index, index, header->node[index].data, header->node[index].next, 
                            header->node[index].prev, header->node[index].prev != Poison ? "\"#FFD0D0\"" : "\"skyblue\"");
    }

    for (int index = 1; index < header->capacity; index++)
    {
        if (header->node[index].prev != Poison)
        {
            if (index != header->tail)
                fprintf(graph_file, "  node%d : <next_idx> -> node%d : <next_idx> [color=\"green\"];\n", index, header->node[index].next);
            if (index != header->head)
                fprintf(graph_file, "  node%d : <prev_idx> -> node%d : <prev_idx> [color=\"red\"];\n", index, header->node[index].prev);
        }
    
        else
            fprintf(graph_file, "  node%d : <next_idx> -> node%d : <next_idx> [color = \"blueviolet\"];\n", index, header->node[index].next);
    }

    if (header->node[header->capacity].prev != Poison)
        fprintf(graph_file, "  node%d : <prev_idx> -> node%d : <prev_idx> [color=\"red\"];\n", header->capacity, header->node[header->capacity].prev);

    fprintf(graph_file, "  header : <head> -> node%d : <index> ;\n", header->head);
    fprintf(graph_file, "  header : <tail> -> node%d : <index> ;\n", header->tail);
    fprintf(graph_file, "  header : <free> -> node%d : <index>;\n", header->free);

    fprintf(graph_file, "}");

    if (fclose(graph_file) == EOF)
    {
        fprintf(stderr, "Failed closing graph.dot in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    char call_graph[100] = " ";

    sprintf(call_graph, "dot graphics/graph.dot -Tpng -o graphics/gpaph%d.png", graph_num);
    
    system(call_graph);

    //2 ружима (log and phys)

    graph_num++;

    #endif

    return No_Error;
}

//---------------------------------------------------------------------------------------------//