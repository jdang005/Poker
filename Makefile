CC = gcc
OBJS = studPokerMain.o PokerTable.o

StudPokerMain: studPokerMain.o PokerTable.o PokerTable.h
	$(CC) -o StudPokerMain $(OBJS)
studPokerMain.o: studPokerMain.c
	$(CC) -c studPokerMain.c
PokerTable.o: PokerTable.c
	$(CC) -c PokerTable.c
clean:
	rm -f $(OBJS)
