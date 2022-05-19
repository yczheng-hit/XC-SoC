# XC-SoC

A simple SoC Based on Cortex-m0.

## Configuration

Install [Verilator](https://veripool.org/guide/latest/).
Install [arm-none-elf-gcc](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)(if used) or

```
sudo apt install gcc-arm-none-eabi
```

You can also use keil to compile C source.

## First Start

Follow these steps to build the simulation environment.

```
cd simulation
make sim
make image.hex # GNU gcc only
./sim_main -h
```

For more detail, read the source code please.

#### Files

- [XC-SoC](#xc-soc)
  - [Configuration](#configuration)
  - [First Start](#first-start)
      - [Files](#files)
      - [Memory Map](#memory-map)
  - [Files in this Repository](#files-in-this-repository)
      - [FPGA](#fpga)
      - [RTL](#rtl)
      - [simulation](#simulation)
      - [software](#software)
      - [README.md](#readmemd)
  - [Troubleshooting Build Problems](#troubleshooting-build-problems)
  - [TODO](#todo)

#### Memory Map
| Address Range            | Description |
| ------------------------ | ----------- |
| 0x00000000 .. 0x0000ffff | ROMCODE     |
| 0X20000000 .. 0X2000FFFF | RAMDATA     |
| 0X40000010 .. 0X4000001B | UART        |
| 0X40000020 .. 0X4000002B | SPI         |
| 0X40010000 .. 0X4001ffff | VGA         |

## Files in this Repository

#### FPGA

This Verilog file contains the following Verilog modules:

| File           | Description                         |
| -------------- | ----------------------------------- |
| `XC-SoC.xpr`   | Vivado Project                      |
| `ebaz4205.xdc` | Constraints File for EBAZ4205 Board |

The IP core clk_wiz is not included currently.

#### RTL

RTL Source, core_m0 included.
| File                 | Description             |
| -------------------- | ----------------------- |
| `cortexm0ds_logic.v` | Cortex-m0 Core          |
| `XC_SoC.v`           | Top File of The Project |
| `……`                 | ……                      |

#### simulation

Source file for simulation. Current simulation is finished by verilator. VCS(or more) will be supported soon.
| File/Folder     | Description                         |
| --------------- | ----------------------------------- |
| `makefile`      | Makefile for Simulation             |
| `src_verilator` | Folder of CPP Source for Simulation |
| `verilator.vc`  | Simulation Script for Verilator     |

#### software

Software source for XC-SoC.
| File/Folder    | Description                                |
| -------------- | ------------------------------------------ |
| `gcc`          | Startup File and Makefile Based on GNU GCC |
| `keil`         | Startup File and Keil Project              |
| `main.c`       | main.c                                     |
| `XC-SoC.h`     | Core Config for XC-SoC                     |
| `include`      | M0 Core Headfile                           |
| `uart_api.h/c` | API for UART                               |
| `spi_api.h/c`  | API for SPI                                |

#### README.md

\\\^\_^

## Troubleshooting Build Problems

```
src_verilator/sim_main.cpp:1:10: fatal error: verilated.h: No such file or directory
```

Check whether verilator is installed correctly and `make clean`.

## TODO

1. IIC (Waiting for board T_T)
2. FM  (Waiting for board T_T)
