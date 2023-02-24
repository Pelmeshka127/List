#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../list_includes/dump.h"

void List_Console_Dump(list_s * const header)
{
    assert(header);
    
    printf("\n//-------------------------------------------------------//\n");\

    printf("The capacity of the list is %zu\n", header->capacity);

    printf("It's size is %zu\n", header->size);

    printf("The index of the head is %zu; The index of the tail is %zu\n", header->head, header->tail);
    
    for (size_t i = 0; i <= header->capacity; i++)
        printf("The index of node is %zu; It's value is %d; The next idx is %d; The previous idx is %d\n",
        i, header->node[i].data, header->node[i].next, header->node[i].prev);

    printf("The free index has number %zu\n", header->free);

    printf("//------------------------------------------------------//\n");
}