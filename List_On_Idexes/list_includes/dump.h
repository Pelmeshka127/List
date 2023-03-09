#ifndef DUMP_H_
#define DUMP_H_

//#define LIST_CONSOLE_DUMP
#define LIST_GRAPH_DUMP

#include "list.h"

/// @brief 
/// @param header 
void List_Console_Dump(list_s * const header);

/// @brief 
/// @param header 
/// @return 
int List_Graph_Dump(list_s * const header);

#endif