CC = gcc
EXE = electronSimulation
CFLAGS = -mhard-float -O3 -lm 

ifeq ($(OS),Windows_NT)
RUN_P = python plot.py
else
RUN_P = python3 plot.py
endif

SOURCE_P = source/C/

config_path = $(SOURCE_P)config/
util_path = $(SOURCE_P)util/
simulation_path = $(SOURCE_P)simulation/
calculations_path = $(SOURCE_P)calculations/

calculations_files = $(calculations_path)Calc.c $(calculations_path)SphericalCalc.c $(calculations_path)CalcRel.c
simulation_files = $(simulation_path)simulation.c
util_files = $(util_path)Reads.c $(util_path)strParce.c
config_files = $(config_path)Config.c
main_file = $(SOURCE_P)main.c

source_files = $(calculations_files) $(config_files) $(main_file) $(simulation_files) $(util_files)


defult: 
	$(CC) $(CFLAGS) $(source_files) -lm -o $(EXE)
run:
	./$(EXE)
plot:
	$(RUN_P)
clean: 
	rm	*.o
	