#include "../includes/list.h"

int main()
{
    list_s * header = (list_s *)calloc (1, sizeof(list_s));
    if (header == nullptr)
    {
        fprintf(stderr, "Failed allocation of list\n");
        return Alloc_Err;
    }

    List_Ctor(header, 5);
    list_node * node2 = List_Insert_Back(header, 6);
    list_node * node3 = List_Insert_Back(header, 7);
    list_node * node4 = List_Insert_After(header, 8, node2);
    list_node * node5 = List_Insert_Before(header, 9, node4);
    List_Remove_Node(header, node4);

    List_Dtor(header);

    return 0;
}