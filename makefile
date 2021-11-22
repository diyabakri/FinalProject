CC = gcc
EXE = electronSimulation
CFLAGS = -mhard-float
RUN_P = python3 plot.py 
defult:
	$(CC) $(CFLAGS) main.c config/Config.c  util/Reads.c util/strParce.c simulation/simulation.c  calculations/Calc.c -lm -o  $(EXE)
run:
	./$(EXE)
plot:
	$(RUN_P)
clean: 
	rm	*.o