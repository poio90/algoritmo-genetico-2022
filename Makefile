# define the C compiler to use
CC=g++
# define any compile-time flags
CFLAGS = -Wall -g -fopenmp

# define any directories containing header files other than /usr/include
INCLUDES = -I./include
# define the C source files
SRCS_DIR=source/
SRCS = ./source/generator.cpp ./source/crossover.cpp ./source/problem.cpp ./source/mutator.cpp \
 ./source/config.cpp ./source/utils.cpp  ./source/selector.cpp ./source/replacer.cpp \
./source/estadistica.cpp ./source/simulate_annealing.cpp ./source/ga.cpp ./source/Servicio_inmigracion.cpp
# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJ_DIR=obj/
# OBJS=$(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.cpp=.o )))
OBJS=$(addprefix $(OBJ_DIR),$(notdir $(SRCS:.cpp=.o )))
#ARCHIVO MAIN
MAIN_FILE = ./main.cpp
MAIN_FILE_SECUENCIAL = ./main_secuencial.cpp

# define the executable file
MAIN = main.exe

# Definicion de los test
TEST_FILES= $(wildcard tests/*.cpp)
#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean info $(MAIN)

all:    $(MAIN)
	@echo  Simple compiler named mycc has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(MAIN_FILE)

mainSecuencial.exe: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o mainSecuencial.exe $(OBJS) $(MAIN_FILE_SECUENCIAL)

# compila los .o que estan en obj, segun lo que haya en source/%.cpp
$(OBJ_DIR)%.o: $(SRCS_DIR)%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


# generar todos los objects
OBJS_GENERATE: $(OBJS)

clean:
	$(RM) $(OBJ_DIR)*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# para ver que contienen las variables
info:
	@echo $()

# DO NOT DELETE THIS LINE -- make depend needs it
