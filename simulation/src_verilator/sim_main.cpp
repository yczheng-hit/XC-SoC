#include <verilated.h>
#include <iostream>
#include <fstream>
#include "VXC_SoC.h"
#include "testbench.h"
#include "sim_uart.h"
#include "cxxopts.hpp"
#include "vgasim.h"
using namespace std;

// Global Variable
unsigned long sim_cycle = 15000; // 仿真周期数
bool trace = false;
bool VGA_enable = false;
int port = 2333;
#define MAX_CYCLE 9999999999
int uart0 = 1;
UARTSIM *uart;

class TB_VGA : public TESTBENCH<VXC_SoC>
{
private:
public:
	VGAWIN m_vga;

private:
	void init(void)
	{
		Glib::signal_idle().connect(sigc::mem_fun((*this), &TB_VGA::on_tick));
	}

public:
	TB_VGA(bool enable, unsigned long count, bool wave) : m_vga(800, 600), TESTBENCH<VXC_SoC>(count, wave)
	{
		if (enable)
			init();
	}
	void tick(void)
	{
		static int r = 0, g = 0, b = 0;
		r = int(255.0f * ((m_core->vga_data >> 6) / 8.0f));
		g = int(255.0f * (((m_core->vga_data >> 3) & 0x7) / 8.0f));
		b = int(255.0f * ((m_core->vga_data & 0x7) / 8.0f));
		m_vga((m_core->vsync) ? 1 : 0, (m_core->hsync) ? 1 : 0,
			  r,
			  g,
			  b);
		TESTBENCH<VXC_SoC>::tick();
	}

	bool on_tick(void)
	{
		tick();
		uart0 = (*uart)((m_core->TXD));
		m_core->RXD = uart0;
		if (done())
			exit(0);
		return true;
	}
};

int main(int argc, char **argv)
{
	int baud_cnt = 0;
	Gtk::Main main_instance(argc, argv);
	// arguments init
	cxxopts::Options options("sim_main", "Verilator Simulation.");
	options
		.set_width(70)
		.set_tab_expansion()
		.allow_unrecognised_options()
		.add_options()("c,cycle", "Simulation cycles", cxxopts::value<unsigned long>())("p,port", "Uart TCP port, 0 means stdio", cxxopts::value<int>())("t,trace", "Simulation trace", cxxopts::value<bool>())("v,vga", "Enable VGA simulation,800*600", cxxopts::value<bool>())("h,help", "Print help");
	// arguments parse
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
		VGA_enable = result["vga"].as<bool>();
		port = result["port"].as<int>();
		if (port > 65535)
			port = 0;
	}
	catch (const cxxopts::OptionException &e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}

	TB_VGA *top = new TB_VGA(VGA_enable, sim_cycle, trace);
	uart = new UARTSIM(port);
	uart->setup(16);
	top->opentrace("/home/zycccccc/vcd_file/XC-SoC/mcutest.vcd");
	top->reset();

	if (VGA_enable)
	{
		std::cout << "***VGA ENABLED***" << std::endl;
		Gtk::Main::run(top->m_vga);
	}
	else
	{
		std::cout << "***VGA NOT ENABLED***" << std::endl;
		while (!top->done())
		{
			top->tick();
			baud_cnt++;
			uart0 = (*uart)((top->m_core->TXD));
			top->m_core->RXD = uart0;
		}
	}
	top->close();
	delete top;
	exit(0);
	return 0;
}