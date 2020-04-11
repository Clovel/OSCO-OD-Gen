# OSCO-OD-Gen - CANOpen Object Dictionary Generator for [OSCO](https://github.com/Clovel/OSCO)

This project's is a cross-platform and modern code generator for the CANOpen Object Dictionary of the [OSCO](https://github.com/Clovel/OSCO) stack.

#### Project status
![Electron project build plan](https://github.com/Clovel/OSCO-OD-Gen/workflows/Electron%20project%20build%20plan/badge.svg?branch=master)
![Generator back-end](https://github.com/Clovel/OSCO-OD-Gen/workflows/Generator%20back-end/badge.svg)

#### License
![GitHub](https://img.shields.io/github/license/Clovel/OSCO-OD-Gen)

## Program goals
This program aims to implement the following features :
- [ ] C Code generator
- [ ] EDS Generator
- [ ] DCF Generator
- [ ] EDS Checker
- [ ] DCF Checker

## Library goals
This project will also build a library to dynamically load EDS/DCF files into the OSCO stack.

## Linked repositories
- [initools](https://github.com/Clovel/initools)
- [RESTServer](https://github.com/Clovel/RESTServer)

## Dependencies
- [initools](https://github.com/Clovel/initools) (Submodule)
- [RESTServer](https://github.com/Clovel/RESTServer) (Submodule)
- [electron](https://github.com/electron/electron)
- [nodejs](https://github.com/nodejs/node)
- [npm](https://github.com/npm/cli)

## Build instructions
### Generator library and utilities
To build the C/C++ generator library and utilities, follow these steps :
```bash
mkdir build
cd build/
cmake ../generator/
make
```

## Contributing
Contributions are welcome !
Please refer to the [CONTRIBUTING.md](https://github.com/Clovel/OSCO/blob/master/CONTRIBUTING.md) for more information.

## Code of Conduct
A [code of conduct](https://github.com/Clovel/OSCO/blob/master/CODE_OF_CONDUCT.md) has been established. Please do your best to comply to it.
By following the rules, we ensure that our interractions will be as civil and enjoyable as possible.
