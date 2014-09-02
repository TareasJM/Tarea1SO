SRC    = Tarea1SO.c
OBJ    = $(SRC:.c=.o)

CC      = gcc
CFLAGS  = -Wall
RM      = rm -f

%.o: %.c
	$(CC) $(CFLAGS) $*.c

clean:
	$(RM) $(OBJ)