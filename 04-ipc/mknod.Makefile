PROGRAM_NAME_1 = mknod1
PROGRAM_OBJS_1 = mknod1.o

PROGRAM_NAME_2 = mknod2a
PROGRAM_OBJS_2 = mknod2a.o

PROGRAM_NAME_3 = mknod2b
PROGRAM_OBJS_3 = mknod2b.o

PROGRAM_NAME_4 = mknod3a
PROGRAM_OBJS_4 = mknod3a.o

PROGRAM_NAME_5 = mknod3b
PROGRAM_OBJS_5 = mknod3b.o

PROGRAM_NAME_6 = mknod3c
PROGRAM_OBJS_6 = mknod3c.o

PROGRAM_NAME_7 = mknod4a
PROGRAM_OBJS_7 = mknod4a.o

PROGRAM_NAME_8 = mknod4b
PROGRAM_OBJS_8 = mknod4b.o

PROGRAM_NAME_9 = mknod4c
PROGRAM_OBJS_9 = mknod4c.o

PROGRAM_NAME_10 = mknod_cleaning
PROGRAM_OBJS_10 = mknod_cleaning.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4) $(PROGRAM_NAME_5) $(PROGRAM_NAME_6) $(PROGRAM_NAME_7) $(PROGRAM_NAME_8) $(PROGRAM_NAME_9) $(PROGRAM_NAME_10) 
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4) $(PROGRAM_OBJS_5) $(PROGRAM_OBJS_6) $(PROGRAM_OBJS_7) $(PROGRAM_OBJS_8) $(PROGRAM_OBJS_9) $(PROGRAM_OBJS_10) 

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

$(PROGRAM_NAME_7): $(PROGRAM_OBJS_7)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_8): $(PROGRAM_OBJS_8)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_9): $(PROGRAM_OBJS_9)
	gcc -o $@ $^ -I ./ -pthread

$(PROGRAM_NAME_10): $(PROGRAM_OBJS_10)
	gcc -o $@ $^ -I ./ -pthread


%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./ -pthread

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
