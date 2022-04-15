#include <verilated.h>
#include <iostream>
#include <fstream>
#include "VCortexM0_SoC.h"
#include "testbench.h"
#include "sim_uart.h"
#include "cxxopts.hpp"
using namespace std;
unsigned long sim_cycle = 15000; // 仿真周期数
bool trace=false;
int port=2333;
#define MAX_CYCLE 9999999999
int uart0=1;
int main(int argc, char **argv)
{
	int baud_cnt=0;

	//arguments init
	cxxopts::Options options("sim_main", "Verilator Simulation.");
	options
		.set_width(70)
		.set_tab_expansion()
		.allow_unrecognised_options()
		.add_options()("c,cycle", "Simulation cycles", cxxopts::value<unsigned long>())("p,port", "Uart TCP port, 0 means stdio", cxxopts::value<int>())("t,trace", "Simulation trace", cxxopts::value<bool>())("h,help", "Print help");
	//arguments parse
	auto result = options.parse(argc, argv);
	if (result.count("help"))
	{
		std::cout << options.help({"", "Group"}) << std::endl;
		exit(0);
	}
	// Verilated::commandArgs(argc, argv);
	try
	{

		sim_cycle = result["cycle"].as<unsigned long>();
		if (sim_cycle == 0)
			sim_cycle = MAX_CYCLE;
		trace = result["trace"].as<bool>();
		port = result["port"].as<int>();
		if(port>65535)
			port = 0;
	}
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}

	UARTSIM *uart;
	TESTBENCH<VCortexM0_SoC> *top = new TESTBENCH<VCortexM0_SoC>(sim_cycle,trace);
	uart = new UARTSIM(port);
	uart->setup(16);
	top->opentrace("mcutest.vcd");
	top->reset();
	while (!top->done())
	{
		top->tick();
		baud_cnt++;
		uart0 = (*uart)((top->m_core->TXD));
		top->m_core->RXD = uart0;
		// if(uart0)
		// 	top->m_core->P1 |= 1;
		// else
		// 	top->m_core->P1 &= 0xfffe;
	}

	top->close();
	delete top;
	exit(0);
	return 0;
}