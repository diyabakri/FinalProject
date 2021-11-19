electronSimulation: main.o config.o Reads.o strParce.o simulation.o calculations.o
			gcc main.o config.o Reads.o strParce.o simulation.o  calculations.o -lm -o electronSimulation 
main.o:
			gcc -c main.c -lm
config.o:
			gcc -c config/Config.c -lm -o config.o
Reads.o:
			gcc -c util/Reads.c -lm
strParce.o:
			gcc -c util/strParce.c -lm
simulation.o:
			gcc -c simulation/simulation.c -lm -o simulation.o
calculations.o:
			gcc -c calculations/Calc.c -lm -o calculations.o
clean: 
	rm	*.o