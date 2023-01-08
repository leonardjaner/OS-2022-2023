PROGRAM_NAME_1 = udp_client1
PROGRAM_OBJS_1 = udp_client1.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1)

REBUIDABLES = $(PROGRAM_NAME_ALL) $(PROGRAM_OBJS_ALL)

all: $(PROGRAM_NAME_ALL)
	@echo "Finished!"

$(PROGRAM_NAME_1): $(PROGRAM_OBJS_1)
	gcc -o $@ $^ -I ./

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
