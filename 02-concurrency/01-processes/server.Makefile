PROGRAM_NAME_1 = server1
PROGRAM_OBJS_1 = server1.o

PROGRAM_NAME_2 = server2
PROGRAM_OBJS_2 = server2.o

PROGRAM_NAME_3 = server3
PROGRAM_OBJS_3 = server3.o

PROGRAM_NAME_4 = server_iteration
PROGRAM_OBJS_4 = server_iteration.o

PROGRAM_NAME_5 = server_iterationdefunct
PROGRAM_OBJS_5 = server_iterationdefunct.o

PROGRAM_NAME_6 = server_iterationgood
PROGRAM_OBJS_6 = server_iterationgood.o

PROGRAM_NAME_7 = server_iterationdefunct_waitpid
PROGRAM_OBJS_7 = server_iterationdefunct_waitpid.o

PROGRAM_NAME_8 = server_iterationdefunct_wait_thread
PROGRAM_OBJS_8 = server_iterationdefunct_wait_thread.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4) $(PROGRAM_NAME_5) $(PROGRAM_NAME_6) $(PROGRAM_NAME_7) $(PROGRAM_NAME_8)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4) $(PROGRAM_OBJS_5) $(PROGRAM_OBJS_6) $(PROGRAM_OBJS_7) $(PROGRAM_OBJS_8)

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

$(PROGRAM_NAME_5): $(PROGRAM_OBJS_5)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_6): $(PROGRAM_OBJS_6)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_7): $(PROGRAM_OBJS_7)
	gcc -o $@ $^ -I ./

$(PROGRAM_NAME_8): $(PROGRAM_OBJS_8)
	gcc -o $@ $^ -pthread -I ./

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -pthread -I ./

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
