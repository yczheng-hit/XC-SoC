module vga_top (input clk,
                input rst_n,
                input wire [3:0] vga_addr_v,
                input wire [4:0] vga_addr_h,
                input wire [31:0] vga_ctrl,
                input wire vga_ctrl_en,
                output vsync,
                output hsync,
                output [8:0] vga_data);
    
    wire vga_data_en;
    wire [8:0]color;
    wire [6:0] font_type;
    wire [11:0] addr;
    wire rdata;
    vga_driver u_vga_driver(
    .clk     (clk),
    .rst_n       (rst_n),
    //from control
    .color       (color),
    
    //output
    .vsync       (vsync),
    .hsync       (hsync),
    .vga_data    (vga_data),
    //to control
    .vga_data_en (vga_data_en)
    );
    
    vga_rom u_vga_rom(
    .clk       (clk),
    //from control
    .addr      (addr),
    .font_type (font_type),
    //output to control
    .rdata     (rdata)
    );
    
    vga_controler u_vga_controler(
    .rst_n       (rst_n),
    .clk         (clk),
    .vga_addr_v      (vga_addr_v),
    .vga_addr_h      (vga_addr_h),
    .vga_ctrl    (vga_ctrl),
    .vga_ctrl_en (vga_ctrl_en),
    .vga_data_en (vga_data_en),
    .rdata       (rdata),
    .addr        (addr),
    .color       (color),
    .font_type   (font_type)
    );
    
    
    
endmodule
