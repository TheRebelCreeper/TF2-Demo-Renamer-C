CC = gcc
CFLAGS = -Wall -Ofast

LIBS += -lrt

SOURCES  = $(wildcard *.c)
INCLUDES = $(wildcard *.h)
OBJECTS  = $(SOURCES:.c=.o)

DEFINES =
DEFINES = -DIS_64BIT
# TODO: Check if CPU supports AVX2 and enable if it does
DEFINES += -DUSE_AVX2 -mavx2
DEFINES += -DUSE_SSE41 -msse4.1
DEFINES += -DUSE_SSE3 -msse3
DEFINES += -DUSE_SSE2 -msse2
DEFINES += -DUSE_SSE -msse

NAME = Saxton

all: clean $(NAME)

$(NAME):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) $(DEFINES)

$(OBJECTS):$(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) -c $(SOURCES) $(DEFINES)



.PHONY: clean
clean:
	-rm *.o 2>> /dev/null;
	-rm *.so 2>> /dev/null;
	-rm core.* 2>> /dev/null;
