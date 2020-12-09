# IPS-PROD 

Local density of a nuclear system : calculations and plotting using C++11 and [Armadillo](http://arma.sourceforge.net/)


## Structure
```
.
├── astyle.sh
├── AUTHORS
├── bin
├── Doxyfile
├── headers
├── Makefile
├── obj
├── pres
├── README.md
├── src
├── visu
└── tests
```

* doc : documentation (generated using doxygen)
* bin : binary files 
* headers : headers (.h files)
* src : source files (.cpp files)
* obj : obj (.o files)
* pres : presentation (launch using `firefox pres/index.html`)

## Compilation

### Requirements

Required libs in order to compile the main executable : 

- `armadillo` : Check that you have the Armadillo lib installed with support for g++ and c++11. 
  
  
Required libs in order to compile the tests : 

- `cxxtests` 


Required libs in ordre to compile the documentation : 

- `doxygen` 
- `graphviz`


### How to compile

Compiling the main executable : 

```Bash
make
```

Compiling the tests : 

```Bash
make tests
```

Compiling the documentation : 

```Bash
make docs
```


## Where are the executables, tests and documentation ?

- To run the main executable, run `./bin/main`
- To view the results, run `python3 ./visualize.py`
- To run the tests, run `./bin/tests`
- To view the documentation, look at `./doc/html/index.html`


