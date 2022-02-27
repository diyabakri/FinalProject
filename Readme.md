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
charge =4.803E-10
# used as the value of the mass of the electron in every equation
mass =9.109383E-28
# used as the time interval for between each itration
t =1E-21
# the base value of l to be used in the equations
Hbar =1.05435246E-27
# the number of orbits to simulate
N =2
# the spific orbit to simulate if set to 0 all orbits will be simulated note: this value also effects the ploting of the results
K_LIST =1,2,3
# the spific angle to simulate if set to 0 all orbits will be simulated note: this value also effects the ploting of the results
M_LIST =1,2,3
# flag for which equations to use 0 regular equations 1 relativity equations 
reltive =0
# flag for which equations to use 0 2d polar projection 1 3d Spherical projection 
Spherical =0
# the logging for how many itrations to actually store in the results files
logPerod =10000
# path and sub path for all result files must be in c format
results_path ="results/result_n%d/result_k%d/result_m%d.txt"

```

## Run

Run the python script to plot the results through the terminal 

```bash
make plot
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
note for each change in any of the .c files there is a need to recompile the code before the changes are applied
compile using the [gcc](https://gcc.gnu.org/) compiler with the use of makefile any added files need to be also added 
to the makefile


```bash
1.make
2.make run
3.make plot
```
