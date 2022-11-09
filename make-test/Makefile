helloproj: commain.o dizqualquercoisa.o
	cc commain.o dizqualquercoisa.o -o helloproj
commain.o: commain.c definicoes.h
	cc -c commain.c
dizqualquercoisa.o: dizqualquercoisa.c
	cc -c dizqualquercoisa.c
clean:
	rm -f *.o helloproj
	rm -f core core.*
