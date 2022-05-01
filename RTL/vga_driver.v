module vga_driver (input clk,
                   input rst_n,
                   input [8:0]color,
                   output reg vsync,
                   output reg hsync,
                   output reg [8:0] vga_data,
                   output vga_data_en);
    
    //-- Horizonal timing information
    parameter  HSYNC_A = 16'd128 ; // 128
    parameter  HSYNC_B = 16'd216 ; // 128 + 88
    parameter  HSYNC_C = 16'd1016; // 128 + 88 + 800
    parameter  HSYNC_D = 16'd1056; // 128 + 88 + 800 + 40
    //-- Vertical  timing information
    parameter VSYNC_O = 16'd4  ;  // 4
    parameter VSYNC_P = 16'd27 ;  // 4 + 23
    parameter VSYNC_Q = 16'd627;  // 4 + 23 + 600
    parameter VSYNC_R = 16'd628;  // 4 + 23 + 600 + 1
    
    reg [15:0] 	hsync_cnt;
    wire [15:0]	hsync_cnt_n;
    reg [15:0] 	vsync_cnt;
    wire [15:0] vsync_cnt_n;
    wire vsync_n;
    wire hsync_n;
    reg [8:0] 	vga_data_n;
    
    assign hsync_cnt_n = (hsync_cnt == HSYNC_D-1)? 16'd0:hsync_cnt + 1'b1;
    always @ (posedge clk or negedge rst_n)
    begin
        if (!rst_n)
            hsync_cnt <= 16'b0;
        else
            hsync_cnt <= hsync_cnt_n;
    end
    
    assign vsync_cnt_n = ((vsync_cnt == VSYNC_R-1) && (hsync_cnt == HSYNC_D-1))? 16'b0:
    (hsync_cnt == HSYNC_D-1)?vsync_cnt + 1'b1:vsync_cnt;
    always @ (posedge clk or negedge rst_n)
    begin
        if (!rst_n)
            vsync_cnt <= 16'b0;
        else
            vsync_cnt <= vsync_cnt_n;
    end
    
    assign hsync_n = (hsync_cnt < HSYNC_A)?1'b0:1'b1;
    always @ (posedge clk or negedge rst_n)
    begin
        if (!rst_n)
            hsync <= 1'b0;
        else
            hsync <= hsync_n;
    end
    
    assign vsync_n = (vsync_cnt < VSYNC_O)?1'b0:1'b1;
    always @ (posedge clk or negedge rst_n)
    begin
        if (!rst_n)
            vsync <= 1'b0;
        else
            vsync <= vsync_n;
    end
    
    assign vga_data_en = (hsync_cnt > HSYNC_B - 1 && hsync_cnt <HSYNC_C)&&(vsync_cnt > VSYNC_P - 1 && vsync_cnt < VSYNC_Q);
    
    always @ (*)
    begin
        vga_data_n = color;
    end
    
    always @ (posedge clk or negedge rst_n)
    begin
        if (!rst_n)
            vga_data <= 9'h0;
        else
            vga_data <= vga_data_n;
    end
    
endmodule
