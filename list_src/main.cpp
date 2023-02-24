#include "../list_includes/list.h"
#include "../list_includes/dump.h"

int main(void)
{
    list_s * header = List_Ctor();

    List_Insert_Front(header, 4);
    List_Insert_Front(header, 10);
    List_Insert_After(header, 1, 20);
    List_Insert_After(header, 3, 58);

    List_Dtor(header);
}