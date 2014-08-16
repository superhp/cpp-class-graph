CFLAGS=-c -Wall
LDFLAGS=
SOURCES= test.cpp antra.cpp dir2/trecia.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=aaa

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
