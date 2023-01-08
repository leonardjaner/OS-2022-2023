PROGRAM_NAME = hello4
PROGRAM_OBJS = hello4.o

REBUIDABLES = $(PROGRAM_OBJS) $(PROGRAM_NAME)

all: $(PROGRAM_NAME)
	@echo "Finished!"

$(PROGRAM_NAME): $(PROGRAM_OBJS)
	gcc -o $@ $<

%.o: %.c
	gcc -c $<

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
