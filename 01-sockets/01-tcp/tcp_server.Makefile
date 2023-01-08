PROGRAM_NAME_1 = tcp_server1
PROGRAM_OBJS_1 = tcp_server1.o

PROGRAM_NAME_2 = tcp_server2
PROGRAM_OBJS_2 = tcp_server2.o

PROGRAM_NAME_3 = tcp_server3
PROGRAM_OBJS_3 = tcp_server3.o

PROGRAM_NAME_4 = tcp_server4
PROGRAM_OBJS_4 = tcp_server4.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4)

REBUIDABLES = $(PROGRAM_NAME_ALL) $(PROGRAM_OBJS_ALL)

all: $(PROGRAM_NAME_ALL)
	@echo "Finished!"

$(PROGRAM_NAME_1): $(PROGRAM_OBJS_1)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_2): $(PROGRAM_OBJS_2)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_3): $(PROGRAM_OBJS_3)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_4): $(PROGRAM_OBJS_4)
	gcc -o $@ $^ -I ./

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
