all: listtask

FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++\
 -Wc++14-compat -Wmissing-declarations\
  -Wcast-align -Wcast-qual -Wchar-subscripts\
   -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal\
    -Wformat-nonliteral -Wformat-security -Wformat=2\
	 -Winline -Wlong-long -Wnon-virtual-dtor -Wopenmp\
	 -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow\
	   -Wsign-conversion -Wsign-promo -Wstrict-overflow=2\
		 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef\
		  -Wunreachable-code -Wunused -Wvariadic-macros\
		   -Wno-literal-range -Wno-missing-field-initializers -Wno-narrowing\
		    -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new\
			 -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer\
			  -Wlarger-than=8192 -fPIE\
			   -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,\
			   -fsanitize=float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,\
			   -fsanitize=address,signed-integer-overflow,undefined,unreachable,vla-bound,vptr,

listtask: main.o list.o dump.o debug.o
	g++ list_obj/main.o list_obj/list.o list_obj/dump.o list_obj/debug.o $(FLAGS) -o list

main.o: ./list_src/main.cpp
	g++ -c ./list_src/main.cpp $(FLAGS) -o list_obj/main.o

list.o: ./list_src/list.cpp
	g++ -c ./list_src/list.cpp $(FLAGS) -o list_obj/list.o

dump.o: ./list_src/dump.cpp
	g++ -c ./list_src/dump.cpp $(FLAGS) -o list_obj/dump.o

debug.o: ./list_src/debug.cpp
	g++ -c ./list_src/debug.cpp $(FLAGS) -o list_obj/debug.o

.PHONY: clean

clean:
	rm *.o list


