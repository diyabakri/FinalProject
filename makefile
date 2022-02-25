CC = gcc
EXE = electronSimulation
CFLAGS = -mhard-float -O3
RUN_P = python3 plot.py 
defult:
	$(CC) $(CFLAGS) main.c config/Config.c  util/Reads.c util/strParce.c simulation/simulation.c  calculations/Calc.c calculations/SphericalCalc.c calculations/CalcRel.c -lm -o  $(EXE)
run:
	./$(EXE)
plot:
	$(RUN_P)
clean: 
	rm	*.o