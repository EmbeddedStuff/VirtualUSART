INCLUDE_DIRS:=include 
COMPILE_DIRS:=source
LIB_DIRS:= 

EXEC_TARGET:=main

##FILES THAT NEED TO BE COMPILED
CFILES:= main.c virtualUSART.c
##LIBRARIES THAT NEED TO BE CREATED
LIBFILES:=
##EXISTING LIBNAMES THAT NEED TO BE LINKED lib<name>
LIBS_TO_LINK:=

LIBNAMES:= $(patsubst lib%.a,%,$(LIBFILES)) $(patsubst lib%,%,$(LIBS_TO_LINK)) 
#LIBFLAGS:= -static $(patsubst %,-L%,$(LIB_DIRS)) $(patsubst %,-l%,$(LIBNAMES))

DIRS:= objects
VPATH:= $(INCLUDE_DIRS) $(COMPILE_DIRS) $(LIB_DIRS) $(DIRS)

INCLUDEFLAGS:=$(patsubst %,-I%,$(INCLUDE_DIRS))
CPPFLAGS:= $(INCLUDEFLAGS)
CFLAGS:= -g -Wall -std=c99
CFILENAMES:=$(notdir $(CFILES))
COBJECTS:=$(patsubst %.c,%.o,$(CFILENAMES))
CC:=gcc

.PHONY: clean run

all: $(EXEC_TARGET) 

$(EXEC_TARGET): $(DIRS) $(COBJECTS) $(LIBFILES)
	gcc $(CFLAGS) $(patsubst %,objects/%,$(COBJECTS)) $(LIBFLAGS) -o $@
$(COBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o objects/$@

$(DIRS): %:
	mkdir -p $@

clean:
	rm -fr $(DIRS)
	rm -f $(EXEC_TARGET)
run: $(EXEC_TARGET)
	./$(EXEC_TARGET)
