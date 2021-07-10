# ------
# GCC
# ------
CC := mpicc
CFLAGS := -lm

# ------
# UNIX
# ------
MKDIR := mkdir
RM := rm -rf

# ------
# SOURCE
# ------
SRC := src
OBJ := obj
BIN := bin

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
MPI_BIN := $(BIN)/main

# ------
# RULES
# ------
.PHONY: all clean

all: $(MPI_BIN) $(STANDALONE_BIN)
	@echo "\n# ====================== #\n# All done.              #\n# ====================== #"

$(MPI_BIN): $(OBJ) $(BIN) $(OBJS) $(LIBS)
	$(CC) $(OBJS) main.c $(CFLAGS) -o $(MPI_BIN)

run: 
	mpirun --quiet -np $(np) $(MPI_BIN) $(n) 

$(OBJ):
	$(MKDIR) $@

$(BIN):
	$(MKDIR) $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $^ $(CFLAGS) -c -o $@

clean:
	$(RM) $(BIN)
	$(RM) $(OBJ)
	@echo "\n# ====================== #\n# All done.              #\n# ====================== #"
