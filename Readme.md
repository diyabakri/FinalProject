# Bohr's Model Electron Simulation

Bohr's Model Electron Simulation is program for simulationg the movment of an electron
in a given orbit path that is determinant by Bohr constant aka "H bar"

## Installation
Use the terminal to install [Python](https://www.python.org/ftp/python/3.10.0/python-3.10.0-amd64.exe)

```bash
sudo apt-get install python
```
## Extrnal libraries

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install matplotlib.

```bash
pip install matplotlib
```
## Configuration

To change the settings of the simulation you need to edit the "config.ini" file

```python
# number of itrations to run for each orbit
itrs =10000000
# bohrs radios this line is only needed to determine the unit of  distance
r =5.29E-9
# used as the value of the charge of the electron in every equation
ch =4.803E-10
# used as the value of the mass of the electron in every equation
mass =9.109383E-28
# used as the time interval for between each itration
t =1E-21
# the base value of l to be used in the equations
l =1.05435246E-27
# the number of orbits to simulate
n = 3
# the logging for how many itrations to actually store in the results files
logPerod =10000
# what to name the result files
results_path ="result"

```

## Run

Run the python script "plot.py" through the terminal 

```bash
python3 plot.py
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
note for each change in any of the .c files there is a need to recompile the code before the changes are applied
compile using the [gcc](https://gcc.gnu.org/) compiler with the command 


```bash
gcc Calc.c Config.c Ellipse.c  strParce.c Reads.c simulation.c <any other added files to be compiled> -o electronSimulation -lm
```
