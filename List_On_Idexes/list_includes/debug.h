#ifndef DEBUG_H_
#define DEBUG_H_

#include "list.h"

void List_Verificate(list_s * const header, const char * File, const char * Function, const int Line);

void List_Print_Error(list_s * const header, const char * const File, const char * const Function, const int Line, const int Error_Code);

#define LIST_VERIFICATE(header) \
List_Verificate(header, __FILE__, __PRETTY_FUNCTION__, __LINE__);

#endif