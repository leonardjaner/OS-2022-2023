PROGRAM_NAME_1 = sem_1a
PROGRAM_OBJS_1 = sem_1a.o

PROGRAM_NAME_2 = sem_2a
PROGRAM_OBJS_2 = sem_2a.o

PROGRAM_NAME_3 = sem_3a
PROGRAM_OBJS_3 = sem_3a.o

PROGRAM_NAME_4 = sem_4a
PROGRAM_OBJS_4 = sem_4a.o

PROGRAM_NAME_5 = sem_4b
PROGRAM_OBJS_5 = sem_4b.o

PROGRAM_NAME_6 = sem_5a
PROGRAM_OBJS_6 = sem_5a.o

PROGRAM_NAME_7 = sem_5b
PROGRAM_OBJS_7 = sem_5b.o

PROGRAM_NAME_8 = sem_5c
PROGRAM_OBJS_8 = sem_5c.o

PROGRAM_NAME_9 = sem_6a
PROGRAM_OBJS_9 = sem_6a.o

PROGRAM_NAME_10 = sem_6b
PROGRAM_OBJS_10 = sem_6b.o

PROGRAM_NAME_11 = sem_6c
PROGRAM_OBJS_11 = sem_6c.o

PROGRAM_NAME_12 = sem_cleaning
PROGRAM_OBJS_12 = sem_cleaning.o

PROGRAM_NAME_13 = sem_cleaning_name
PROGRAM_OBJS_13 = sem_cleaning_name.o

PROGRAM_NAME_ALL = $(PROGRAM_NAME_1) $(PROGRAM_NAME_2) $(PROGRAM_NAME_3) $(PROGRAM_NAME_4) $(PROGRAM_NAME_5) $(PROGRAM_NAME_6) $(PROGRAM_NAME_7) $(PROGRAM_NAME_8) $(PROGRAM_NAME_9) $(PROGRAM_NAME_10) $(PROGRAM_NAME_11) $(PROGRAM_NAME_12) $(PROGRAM_NAME_13)
PROGRAM_OBJS_ALL = $(PROGRAM_OBJS_1) $(PROGRAM_OBJS_2) $(PROGRAM_OBJS_3) $(PROGRAM_OBJS_4) $(PROGRAM_OBJS_5) $(PROGRAM_OBJS_6) $(PROGRAM_OBJS_7) $(PROGRAM_OBJS_8) $(PROGRAM_OBJS_9) $(PROGRAM_OBJS_10) $(PROGRAM_OBJS_11) $(PROGRAM_OBJS_12) $(PROGRAM_OBJS_13)

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

$(PROGRAM_NAME_11): $(PROGRAM_OBJS_11)
	gcc -o $@ $^ -I ./ -pthread 

$(PROGRAM_NAME_12): $(PROGRAM_OBJS_12)
	gcc -o $@ $^ -I ./ -pthread 

$(PROGRAM_NAME_13): $(PROGRAM_OBJS_13)
	gcc -o $@ $^ -I ./ -pthread 

%.o: %.c
	gcc -c $< -Wall -Wno-unused-variable -I ./ -pthread 

clean:
	rm -f $(REBUIDABLES)
	@echo "Clean done"
