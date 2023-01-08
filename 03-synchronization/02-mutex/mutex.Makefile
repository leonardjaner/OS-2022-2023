PROGRAM_NAME_1 = mutex1
PROGRAM_OBJS_1 = mutex1.o

PROGRAM_NAME_2 = mutex2
PROGRAM_OBJS_2 = mutex2.o

PROGRAM_NAME_3 = mutex3
PROGRAM_OBJS_3 = mutex3.o

PROGRAM_NAME_4 = mutex4
PROGRAM_OBJS_4 = mutex4.o

PROGRAM_NAME_5 = mutex5
PROGRAM_OBJS_5 = mutex5.o

PROGRAM_NAME_6 = mutex6
PROGRAM_OBJS_6 = mutex6.o

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
