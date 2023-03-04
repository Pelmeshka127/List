#include "../list_includes/list.h"
#include "../list_includes/dump.h"

int main(void)
{
    list_s * header = { };

    header = (list_s *) calloc(1, sizeof(list_s));
    if (header == nullptr)
    {
        fprintf(stderr, "Allocation of the list failed\n");
        return Alloc_Err;
    }

    List_Ctor(header, Def_Capacity);

    List_Insert_Front(header, 12);
    List_Insert_After(header, header->head, 10);
    List_Insert_After(header, header->tail, 20);
    List_Insert_After(header, header->head, 30);
    List_Insert_Before(header, header->tail, 40);

    List_Linearize(header);
    List_Console_Dump(header);

    List_Dtor(header);
}