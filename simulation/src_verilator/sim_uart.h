#ifndef UARTSIM_H
#define UARTSIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <queue>

#define TXIDLE 0
#define TXDATA 1
#define RXIDLE 0
#define RXDATA 1

class UARTSIM
{
	// Member declarations
	// {{{
	// The file descriptors:
	//	m_skt   is the socket/port we are listening on
	//	m_conrd is the file descriptor to read from
	//	m_conwr is the file descriptor to write to
private:
	int m_skt, m_conrd, m_conwr;
	std::queue <char> uart_fifo,uart_fifo_cp;
	//
	// The m_setup register is the 29'bit control register used within
	// the core.
	unsigned m_setup;
	// And the pieces of the setup register broken out.
	int m_nparity, m_fixdp, m_evenp, m_nbits, m_nstop, m_baud_counts_tx, m_baud_counts_rx;

	// UART state
	int m_rx_baudcounter, m_rx_state, m_rx_busy,
		m_rx_changectr, m_last_tx;
	int m_tx_baudcounter, m_tx_state, m_tx_busy;
	unsigned m_rx_data, m_tx_data;
	// }}}
public:
	bool check_fifo(char *ch);
private:
	// Private methods
	// {{{
	// setup_listener is an attempt to encapsulate all of the network
	// related setup stuff.
	void setup_listener(const int port);

	// Call check_for_new_connections() to see if we can accept a new
	// network socket connection to our device
	int check_for_new_connections(void);

	// nettick() gets called if we are connected to a network, and
	int nettick(const int i_tx);
	int fdtick(const int i_tx);
	int rawtick(const int i_tx, const bool network);

	// We'll use the file descriptor for the listener socket to determine
	// whether we are connected to the network or not.  If not connected
	// to the network, then we assume m_conrd and m_conwr refer to
	// your more traditional file descriptors, and use them as such.
	int tick(const int i_tx)
	{
		return rawtick(i_tx, (m_skt >= 0));
	}
	// }}}
public:
	// Public member functions
	// {{{

	// UARTSIM(port)
	// {{{
	// The UARTSIM constructor takes one argument: the port on the
	// localhost to listen in on.  Once started, connections may be made
	// to this port to get the output from the port.
	UARTSIM(const int port);
	// }}}

	// kill(void)
	// {{{
	// kill() closes any active connection and the socket.  Once killed,
	// no further output will be sent to the port.
	void kill(void);
	// }}}

	// setup(isetup)
	// {{{
	// setup() busts out the bits from isetup to the various internal
	// parameters.  It is ideally only called between bits at appropriate
	// transition intervals.
	void setup(unsigned isetup);
	void setup(unsigned isetup_tx, unsigned isetup_rx);
	// }}}

	// operator()(i_tx)
	// {{{
	// The operator() function is called on every tick.  The input is the
	// the output txuart transmit wire from the device.  The output is to
	// be connected to the the rxuart receive wire into the device.  This
	// makes hookup and operation very simple.
	//
	// This is the most appropriate simulation entry function if the
	// setup register will never change.
	//
	int operator()(int i_tx)
	{
		return tick(i_tx);
	}
	// }}}

	// operator()(i_tx, isetup)
	// {{{
	// If there is a possibility that the core might change the UART setup,
	// then it makes sense to include that current setup when calling the
	// tick operator.
	int operator()(int i_tx, unsigned isetup)
	{
		setup(isetup);
		return tick(i_tx);
	}
	// }}}
	// }}}
};

#endif
