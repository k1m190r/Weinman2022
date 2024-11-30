NAME = main
CFILE = main
# CPP = g++-13 
CPP = clang++-20
GCC_WARNS = -Wall -Wextra -Wpedantic -fsanitize=address -Werror -fexperimental-library
GCC_WARNS2 = -Wcast-align -Wconversion -Wctor-dtor-privacy -Wshadow -Wsign-conversion 
CFLAGS = -stdlib=libc++ -O3 -march=native -mavx2 -std=c++26 -g3 -pthread $(GCC_WARNS) $(GCC_WARNS2) 
LDLIBS = -static-libstdc++ `pkg-config --libs fmt`

# get the top most directory
DIR = $(shell python -c "import os; print(sorted([x for x in os.listdir() if x[0]!='.'])[0])")

$(NAME): $(CFILE).o
	@$(CPP) -o out/$(NAME) out/$(CFILE).o $(CFLAGS) $(LDLIBS) 
	@./out/$(NAME)

$(CFILE).o: $(DIR)/$(CFILE).cpp
	@mkdir -p out
	@$(CPP) -o out/$(CFILE).o -c $(DIR)/$(CFILE).cpp $(CFLAGS)

