PROGRAM_NAME_1 = shm_1a
PROGRAM_OBJS_1 = shm_1a.o

PROGRAM_NAME_2 = shm_1b
PROGRAM_OBJS_2 = shm_1b.o

PROGRAM_NAME_3 = shm_1c
PROGRAM_OBJS_3 = shm_1c.o

PROGRAM_NAME_4 = shm_1cleaning
PROGRAM_OBJS_4 = shm_1cleaning.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4)

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

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./ -pthread

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
