#include "../list_includes/debug.h"

//---------------------------------------------------------------------------------------------//

void List_Verificate(list_s * const header, const char * const File, const char * const Function, const int Line)
{
    if (header->capacity < 1)
        List_Print_Error(header, File, Function, Line, Incorrect_Capacity);

    if (header->size > header->capacity)
        List_Print_Error(header, File, Function, Line, Overflow);

    if (header->size < 0)
        List_Print_Error(header, File, Function, Line, Underflow);

    if (header->node[0].data != 0 || header->node[0].next != 0 || header->node[0].prev != 0)
        List_Print_Error(header, File, Function, Line, Zero_Elem_Error);

    if (header->tail > (int) header->capacity || header->tail < 0)
        List_Print_Error(header, File, Function, Line, Tail_Error);

    if (header->head > (int) header->capacity || header->head < 0)
        List_Print_Error(header, File, Function, Line, Head_Error);

    if (header->free > (int) header->capacity || header->free < 0)
        List_Print_Error(header, File, Function, Line, Free_Error);

    if (header->size >= 2)
    {
        for (int index = 1; header->node[index].next != 0; index++)
        {
            int next = header->node[index].next;
            int prev = header->node[next].prev;

            if (index != prev)
                List_Print_Error(header, File, Function, Line, Ruined_List);
        }

    }
}

//---------------------------------------------------------------------------------------------//


void List_Print_Error(list_s * const header, const char * const File, const char * const Function, const int Line, const int Error_Code)
{
    switch (Error_Code)
    {
        case Incorrect_Capacity:
        fprintf(stderr, "Verification: List has incorrect capacity in file %s; function %s; line %d\n", File, Function, Line);
        break;

        case Overflow:
        fprintf(stderr, "Verification: List is overflow in file %s; function %s; line %d\n", File, Function, Line);
        break;

        case Underflow:
        fprintf(stderr, "Verification: List is underflow in file %s; function %s; line %d\n", File, Function, Line);
        break;

        case Zero_Elem_Error:
        fprintf(stderr, "Verification: Zero node of list was changed in file %s; function %s; line %d\n"
                        "Its data is %d. Its next is %d. Its prev is %d\n", File, Function, Line, header->node[0].data, header->node[0].next,
                        header->node[0].prev);
        break;

        case Tail_Error:
        fprintf(stderr, "Verification: Incorrect tail %d of the list with capacity %u in file %s; in function %s; in line %d\n",
                        header->tail, header->capacity, File, Function, Line);
        break;

        case Head_Error:
        fprintf(stderr, "Verification: Incorrect head %d of the list with capacity %u in file %s; in function %s; in line %d\n",
                        header->head, header->capacity, File, Function, Line);
        break;   

        case Free_Error:
        fprintf(stderr, "Verification: Incorrect free %d of the list with capacity %u in file %s; in function %s; in line %d\n",
                        header->free, header->capacity, File, Function, Line);
        break;

        case Ruined_List:
        fprintf(stderr, "Verification: List was ruined in file %s; function %s; line %d\n", File, Function, Line);
        break;
    }
}

//---------------------------------------------------------------------------------------------//