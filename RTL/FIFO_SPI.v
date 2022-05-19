// synopsys translate_off
// `include "timescale.v"
// synopsys translate_on


// 4 entry deep fast fifo
module FIFO_SPI(clk, rst, clr,  din, we, dout, re, full, empty);

parameter dw = 8;

input		clk, rst;
input		clr;
input   [dw:1]	din;
input		we;
output  [dw:1]	dout;
input		re;
output		full, empty;


////////////////////////////////////////////////////////////////////
//
// Local Wires
//

reg     [dw:1]	mem[0:7];
reg     [2:0]   wp;
reg     [2:0]   rp;
wire    [2:0]   wp_p1;
wire    [2:0]   rp_p1;
wire		full, empty;
reg		gb;

////////////////////////////////////////////////////////////////////
//
// Misc Logic
//

always @(posedge clk or negedge rst)
        if(!rst)	wp <= #1 3'h0;
        else
        if(clr)		wp <= #1 3'h0;
        else
        if(we)		wp <= #1 wp_p1;

assign wp_p1 = wp + 3'h1;

always @(posedge clk or negedge rst)
        if(!rst)	rp <= #1 3'h0;
        else
        if(clr)		rp <= #1 3'h0;
        else
        if(re)		rp <= #1 rp_p1;

assign rp_p1 = rp + 3'h1;

// Fifo Output
assign  dout = mem[ rp ];

// Fifo Input
always @(posedge clk)
        if(we)	mem[ wp ] <= #1 din;

// Status
assign empty = (wp == rp) & !gb;
assign full  = (wp == rp) &  gb;

// Guard Bit ...
always @(posedge clk)
	if(!rst)			gb <= #1 1'b0;
	else
	if(clr)				gb <= #1 1'b0;
	else
	if((wp_p1 == rp) & we)		gb <= #1 1'b1;
	else
	if(re)				gb <= #1 1'b0;

endmodule
