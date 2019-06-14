
TARGET = postman.out
LIB = ./fake-mininet/
INC = ./include/
CC = g++ -std=c++11
CFLAGS += -O3 
SRC = $(wildcard ./src/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -L $(LIB) -lfakemn

%.o : %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJ) 

