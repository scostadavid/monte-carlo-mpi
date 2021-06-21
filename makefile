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
LIB := lib

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
LIBS := $(patsubst $(SRC)/%.c, $(LIB)/%.a, $(SRCS))
MPI_BIN := $(BIN)/main
STANDALONE_BIN := $(BIN)/standalone

# ------
# RULES
# ------
.PHONY: all clean

all: $(MPI_BIN) $(STANDALONE_BIN)
	@echo "\n# ====================== #\n# All done.              #\n# ====================== #"

$(MPI_BIN): $(OBJ) $(BIN) $(LIB) $(OBJS) $(LIBS)
	$(CC) $(OBJS) main.c $(CFLAGS) -o $(MPI_BIN)

$(STANDALONE_BIN):
	$(CC) standalone.c $(CFLAGS) -o $(STANDALONE_BIN)

$(OBJ):
	$(MKDIR) $@

$(BIN):
	$(MKDIR) $@

$(LIB):
	$(MKDIR) $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $^ $(CFLAGS) -c -o $@

$(LIB)/%.a: $(OBJ)/%.o
	ar -cvrs $@ $^

clean:
	$(RM) $(BIN)
	$(RM) $(OBJ)
	$(RM) $(LIB)
	@echo "\n# ====================== #\n# All done.              #\n# ====================== #"