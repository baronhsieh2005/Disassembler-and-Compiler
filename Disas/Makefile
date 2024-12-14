.PHONY = all clean

CC15 = clang-15
CFLAGS = -g3 -Wall -gdwarf-4 

disas: disas.o loader.o decoder.o
	$(CC15) $(CFLAGS) -o $@ $^

disas.o: disas.c loader.h decoder.h
	$(CC15) $(CFLAGS) -c $<

loader.o: loader.c loader.h
	$(CC15) $(CFLAGS) -c $<

decoder.o: decoder.c decoder.h
	clang-15 -g3 -gdwarf-4 -Wall -c decoder.c

clean:
	rm -f *.o disas *~


