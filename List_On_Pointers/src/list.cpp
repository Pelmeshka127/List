#include "../includes/list.h"
#include "../includes/dump.h"

//---------------------------------------------------------------------------------------------//

list_node * List_Ctor(list_s * const header, elem_t value)
{
    list_node * head = (list_node *)calloc (1, sizeof(list_node));

    if (header == nullptr)
    {
        fprintf(stderr, "Failed initialization of list in function %s\n", __PRETTY_FUNCTION__);
        return nullptr;
    }

    head->data = value;
    head->next = nullptr;
    head->prev = nullptr;

    header->head = header->tail = head;

    header->size++;

    List_Graph_Dump(header);

    return head;
}

//---------------------------------------------------------------------------------------------//

list_node * List_Insert_Back(list_s * const header, elem_t value)
{
    assert(header);

    list_node * cur_node = header->head;
    list_node * adding_node = (list_node *)calloc (1, sizeof(list_node));

    while (cur_node->next != nullptr)
    {
        list_node * old  = cur_node;
        list_node * next = cur_node->next;
        cur_node         = next;
        cur_node->prev   = old;
    }

    cur_node->next    = adding_node;
    adding_node->data = value;
    adding_node->prev = cur_node;
    
    header->tail = adding_node;
    header->size++;

    List_Graph_Dump(header);

    return adding_node;
}

//---------------------------------------------------------------------------------------------//

list_node * List_Insert_Front(list_s * const header, elem_t value)
{
    assert(header);
    
    list_node * adding_node = (list_node *)calloc (1, sizeof(list_node));

    adding_node       = header->head->prev;
    adding_node->next = header->head; 
    adding_node->data = value;

    header->head = adding_node;
    header->size++;

    List_Graph_Dump(header);

    return adding_node;
}

//---------------------------------------------------------------------------------------------//

list_node * List_Insert_After(list_s * const header, elem_t value, list_node * node_index)
{
    assert(header);

    if (node_index == header->head)
        List_Insert_Back(header, value);

    else
    {
        list_node * adding_node = (list_node *)calloc (1, sizeof(list_node));
        if (adding_node == nullptr)
        {
            fprintf(stderr, "Failed allocation of memory in function %s\n", __PRETTY_FUNCTION__);
            return nullptr;
        }

        list_node * cur_node = header->head;
        int index_num = 1;
        while (cur_node != node_index)
        {
            cur_node = cur_node->next;
            index_num++;

            if (index_num > header->size)
            {
                fprintf(stderr, "Incorrect adress of node %p\n", node_index);
                return nullptr;
            }
        }
        
        adding_node->prev    = cur_node;
        adding_node->next    = cur_node->next;
        cur_node->next->prev = adding_node;
        cur_node->next       = adding_node;

        adding_node->data = value;
        header->size++;

        List_Graph_Dump(header);
        
        return adding_node;
    }
}

//---------------------------------------------------------------------------------------------//

list_node * List_Insert_Before(list_s * const header, elem_t value, list_node * node_index)
{
    assert(header);

    if (node_index == header->head)
        List_Insert_Front(header, value);

    else
    {
        list_node * adding_node = (list_node *)calloc (1, sizeof(list_node));
        if (adding_node == nullptr)
        {
            fprintf(stderr, "Failed allocation of memory in function %s\n", __PRETTY_FUNCTION__);
            return nullptr; 
        }

        list_node * cur_node = header->head;
        int index_num = 1;
        while (cur_node != node_index)
        {
            cur_node = cur_node->next;
            index_num++;

            if (index_num > header->size)
            {
                fprintf(stderr, "Incorrect adress of node %p\n", node_index);
                return nullptr;
            }
        }

        adding_node->next    = cur_node;
        adding_node->prev    = cur_node->prev;
        cur_node->prev->next = adding_node;
        cur_node->prev       = adding_node;

        adding_node->data = value;
        header->size++;

        List_Graph_Dump(header);

        return adding_node;
    }
}

//---------------------------------------------------------------------------------------------//

list_node * List_Remove_Node(list_s * const header, list_node * node_index)
{
    assert(header);

    if (node_index == header->head)
        List_Remove_Head(header);

    else if (node_index == header->tail)
        List_Remove_Tail(header);

    else
    {
        int index_num = 0;
        list_node * cur_node = header->head;
        while (cur_node != node_index)
        {
            cur_node = cur_node->next;
            index_num++;

            if (index_num > header->size)
            {
                fprintf(stderr, "Incorrect adress of node %p\n", node_index);
                return nullptr;
            }
        }

        list_node * removing_node = cur_node;
        cur_node->next->prev = cur_node->prev;
        cur_node->prev->next = cur_node->next;

        removing_node->data = 0;
        removing_node->next = nullptr;
        removing_node->prev = nullptr;
        free(removing_node);

        header->size--;

        List_Graph_Dump(header);

        return nullptr;
    }
}

//---------------------------------------------------------------------------------------------//

list_node * List_Remove_Head(list_s * const header)
{
    assert(header);

    if (header->size <= 0)
    {
        fprintf(stderr, "You cannot remove any node because the list is empty\n");
        return nullptr;
    }

    list_node * old_head = header->head;
    header->head = header->head->next;

    old_head->data = 0;
    old_head->next = nullptr;
    free(old_head);

    header->head->prev = nullptr;
    header->size--;

    List_Graph_Dump(header);
    
    return header->head;
}

//---------------------------------------------------------------------------------------------//

list_node * List_Remove_Tail(list_s * const header)
{
    assert(header);

    if (header->size <= 0)
    {
        fprintf(stderr, "You cannot remove any node because the list is empty\n");
        return nullptr;
    }

    list_node * old_tail = header->tail;
    header->tail = header->tail->prev;

    old_tail->data = 0;
    old_tail->next = nullptr;
    free(old_tail);

    header->tail->next = nullptr;
    header->size--;

    List_Graph_Dump(header);

    return header->tail;
}

//---------------------------------------------------------------------------------------------//

list_node * List_Dtor(list_s * const header)
{
    assert(header);

    list_node * cur_node = header->tail;
    while (cur_node != header->head)
    {
        cur_node = cur_node->prev;
        free(cur_node->next);
    }

    free(header->head);

    header->size = 0;
    free(header);

    return nullptr;
}