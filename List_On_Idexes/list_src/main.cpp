#include "../list_includes/list.h"
#include "../list_includes/dump.h"

int main(void)
{
    list_s header = { }; //* ->

    Open_File();

    List_Ctor(&header, Def_Capacity);

    List_Insert_Front(&header, 12);

    List_Insert_Front(&header, 24);

    List_Insert_After(&header, header.head, 10);

    List_Insert_After(&header, 2, 32);

    printf("%d\n", List_Get_Log_By_Data(&header, 12));

    List_Dtor(&header);

    Close_File();
}