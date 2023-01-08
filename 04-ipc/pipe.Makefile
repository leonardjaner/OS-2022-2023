PROGRAM_NAME_1 = pipe1
PROGRAM_OBJS_1 = pipe1.o

PROGRAM_NAME_2 = pipe2
PROGRAM_OBJS_2 = pipe2.o

PROGRAM_NAME_3 = pipe3
PROGRAM_OBJS_3 = pipe3.o

PROGRAM_NAME_4 = pipe4
PROGRAM_OBJS_4 = pipe4.o

PROGRAM_NAME_5 = pipe5
PROGRAM_OBJS_5 = pipe5.o

PROGRAM_NAME_6 = pipe6
PROGRAM_OBJS_6 = pipe6.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4) $(PROGRAM_NAME_5) $(PROGRAM_NAME_6)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4) $(PROGRAM_OBJS_5) $(PROGRAM_OBJS_6)

REBUIDABLES = $(PROGRAM_NAME_ALL) $(PROGRAM_OBJS_ALL)

all: $(PROGRAM_NAME_ALL)
	@echo "Finished!"

$(PROGRAM_NAME_1): $(PROGRAM_OBJS_1)
	gcc -o $@ $^ -I ./ -pthread


$(PROGRAM_NAME_2): $(PROGRAM_OBJS_2)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_3): $(PROGRAM_OBJS_3)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_4): $(PROGRAM_OBJS_4)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_5): $(PROGRAM_OBJS_5)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_6): $(PROGRAM_OBJS_6)
	gcc -o $@ $^ -I ./ -pthread

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./ -pthread

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
