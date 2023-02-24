#include "../list_includes/debug.h"

void List_Verificate(list_s * const header, const char * const File, const char * const Function, const int Line)
{
    if (header->size > header->capacity)
        List_Print_Error(header, File, Function, Line, Overflow);

    if (header->node[0].data != 0 || header->node[0].next != 0 || header->node[0].prev != 0)
        List_Print_Error(header, File, Function, Line, Zero_Elem_Error);
}
void List_Print_Error(list_s * const header, const char * const File, const char * const Function, const int Line, const int Error_Code)
{
    switch (Error_Code)
    {
        case Overflow:
        fprintf(stderr, "Verification: List is overflow in file %s; function %s; line %d\n", File, Function, Line);
        break;

        case Zero_Elem_Error:
        fprintf(stderr, "Verification: Zero node of list was changed in file %s; function %s; line %d\n"
                        "Its data is %d. Its next is %d. Its prev is %d\n", File, Function, Line, header->node[0].data, header->node[0].next,
                        header->node[0].prev);
        break;
    }
}