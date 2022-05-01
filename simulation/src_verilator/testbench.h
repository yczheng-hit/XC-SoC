#ifndef _TESTBENCH_H_
#define _TESTBENCH_H_
#include <verilated_vcd_c.h>
template <class MODULE>
class TESTBENCH
{
	unsigned long m_tickcount;
	unsigned long sim_time;

public:
	bool trace;
	VerilatedVcdC *m_trace;
	MODULE *m_core;
	TESTBENCH(unsigned long count, bool wave)
	{
		m_core = new MODULE;
		m_tickcount = 0l;
		sim_time = count;
		trace = wave;
		m_trace = NULL;
		Verilated::traceEverOn(true);
	}

	~TESTBENCH(void)
	{
		delete m_core;
		m_core = NULL;
	}

	void reset(void)
	{
		m_core->clk = 0;
		m_core->RSTn = 0;
		m_core->eval();
		if (m_trace)
			m_trace->dump(m_tickcount);
		for (int i = 0; i < 5; i++)
			this->tick();
		m_core->RSTn = 1;
	}

	void tick(void)
	{
		m_tickcount++;
		// Repeat for the positive edge of the clock
		// m_core->P1 &= 0xfffe;
		m_core->clk = 1;
		m_core->eval();
		if (m_trace)
			m_trace->dump(2 * m_tickcount - 1);

		// m_core->P1 &= 0xfffe;
		// negative edge
		m_core->clk = 0;
		m_core->eval();
		if (m_trace)
		{
			m_trace->dump(2 * m_tickcount);
			// m_trace->flush();
		}
	}
	void opentrace(const char *vcdname)
	{
		if (trace)
		{
			if (!m_trace)
			{
				m_trace = new VerilatedVcdC;
				m_core->trace(m_trace, 99);
				m_trace->open(vcdname);
			}
		}
		else
			m_trace = NULL;
	}
	void close(void)
	{
		if (m_trace)
		{
			m_trace->close();
			m_trace = NULL;
		}
	}

	bool done(void) { return (Verilated::gotFinish() || m_tickcount >= sim_time); }
};

#endif