# XC-SoC

A simple SoC Based on Cortex-m0.

## configuration
Install [verilator](https://veripool.org/guide/latest/)
```
cd simulation
make sim
./sim_main -h
```
For more detail, read the source code please.

#### Files

- [Files in this Repository](#files-in-this-repository)
  - [FPGA/](#FPGA)
  - [RTL/](#RTL)
  - [software/](#software)
  - [simulation/](#simulation)
  - [README.md](#readmemd)

## Files in this Repository

#### FPGA

This Verilog file contains the following Verilog modules:

| File           | Description                         |
| -------------- | ----------------------------------- |
| `XC-SoC.xpr`   | Vivado Project                      |
| `ebaz4205.xdc` | Constraints File for EBAZ4205 Board |

#### RTL

RTL Source, core_m0 included.
| File | Description |
| -------------- | ----------------------------------- |
| `cortexm0ds_logic.v` | Cortex-m0 Core |
| `CortexM0_SoC.v` | Top File of The Project |
| `……` | …… |

#### simulation

Source file for simulation. Current simulation is finished by verilator. VCS(or more) will be supported soon.
| File/Folder | Description |
| -------------- | ----------------------------------- |
| `makefile` | Makefile for Simulation |
| `src_verilator` | Folder of CPP Source for Simulation |
| `verilator.vc` | Simulation Script for Verilator |

#### software

Software source for XC-SoC.
| File/Folder | Description |
| -------------- | ----------------------------------- |
| `gcc` | Startup File and Makefile Based on GNU GCC |
| `keil` | Startup File and Keil Project |
| `main.c` | main.c |
| `XC-SoC.h` | Core Config for XC-SoC |
| `include` | M0 Core Headfile |
| `uart_api.h/c` | API for Uart |

#### README.md

\\\^\_^
