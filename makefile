### Variables
CC=gcc
CFLAGS=-c

### Dirs
SRC_DIR=src
OBJ_DIR=obj
HEAD_DIR=headers

### Executable name
EXEC=cparticle

### Sources (in src directory)
SOURCES=$(addprefix $(SRC_DIR)/, \
	main.c io.c memory.c motion.c)
#	setup.c interpolate.c poisson.c \
#	fields.c mover.c wrappers.c)

### Objects (in obj directory)
OBJECTS=$(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)


### Rules: #######################################

### General target (executable):
all: $(EXEC)

### How to make the executable:
$(EXEC): $(OBJECTS) 
	$(CC) $^ -o $@ -lm

### How to make every object:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

### How to clean up:
clean: 
	rm $(OBJECTS) $(EXEC)
