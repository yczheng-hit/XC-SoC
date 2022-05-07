module fpga_top (input wire clk,
                 input wire RSTn,
                 inout wire SWDIO,
                 input wire SWCLK,
                 output wire TXD,
                 input wire RXD,
                 output wire vsync,
                 output wire hsync,
                 output wire [8:0] vga_data);
    
    wire 	clk_50M;
    wire 	clk_100M;
    wire 	clk_40M;
    
    clk_wiz_0  clk_wiz_0 (
    .clk_out1          (clk_50M),
    .clk_out2          (clk_100M),
    .clk_out3          (clk_40M),
    .clk_in1           (clk)
    );
    XC_SoC u_XC_SoC(
    .clk      (clk_40M),
    .RSTn     (RSTn),
    .SWDIO    (SWDIO),
    .SWCLK    (SWCLK),
    .TXD      (TXD),
    .RXD      (RXD),
    .vsync    (vsync),
    .hsync    (hsync),
    .vga_data (vga_data)
    );
    
    
endmodule
