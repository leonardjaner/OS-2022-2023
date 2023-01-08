PROGRAM_NAME = hello5
PROGRAM_OBJS = hello5b.o hello5a.o

REBUIDABLES = $(PROGRAM_OBJS) $(PROGRAM_NAME)

all: $(PROGRAM_NAME)
	@echo "Finished!"

$(PROGRAM_NAME): $(PROGRAM_OBJS)
	gcc -Wall -Werror -o $@ $^ -I ./

%.o: %.c
	gcc -Wall -Werror -c $< -I ./

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
