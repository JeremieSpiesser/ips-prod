# IPS-PROD 

Local density of a nuclear system : calculations and plotting using C++11, [Armadillo](http://arma.sourceforge.net/) and PovRay 


## Structure
```
.
├── AUTHORS
├── bin
├── doc
├── Doxyfile
├── headers
├── Makefile
├── obj
├── pres
| └── visu
├── README.md
├── rho.arma
├── src
└── tests
```

* doc : documentation (generated using doxygen)
* bin : binary files 
* headers : headers (.h files)
* src : source files (.cpp files)
* obj : obj (.o files)
* pres : presentation (launch using `firefox pres/index.html` or `make pres`)

>** Attention **
>The pictures in the presentation are generated when you run the `bin/main` file and run the povray target.
>If you don't see any pictures in the presentation, run `make && ./bin/main && make povray`



## Compilation

### Requirements

Required libs in order to compile the main executable : 

- `armadillo` : Check that you have the Armadillo lib installed with support for g++ and c++11. 

Required libs in order to render the 3D ray tracing model :

- `povray`

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

Rendering povray :

```Bash
make povray
```

## Settings

The `Makefile` first lines are options you can edit to customize your compilation flow

## Where are the executables, tests and documentation ?

**All executables must be executed from the base project folder**
(because code is using relative paths)

- To run the main executable, run `./bin/main`
- To view the results, run `make povray`
- To run the tests, run `./bin/tests`
- To view the documentation, look at `./doc/html/index.html`


