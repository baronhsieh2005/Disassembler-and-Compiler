.PHONY = all clean

CC15 = clang-15
CFLAGS = -g3 -Wall -gdwarf-4 

jc: jc.o token.o asm_gen.o Deque.o
	$(CC15) $(CFLAGS) -o $@ $^

jc.o: jc.c token.h asm_gen.h
	$(CC15) $(CFLAGS) -c $<

asm_gen.o: asm_gen.c asm_gen.h rat_num.h token.h Deque.h
	$(CC15) $(CFLAGS) -c $<

token.o: token.c token.h
	$(CC15) $(CFLAGS) -c $<

Deque.o: Deque.c Deque.h rat_num.h

clean:
	rm -f jc *.o