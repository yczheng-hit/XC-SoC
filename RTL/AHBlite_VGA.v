module AHBlite_VGA(input wire HCLK,
                   input wire HRESETn,
                   input wire HSEL,
                   input wire [31:0] HADDR,
                   input wire [1:0] HTRANS,
                   input wire [2:0] HSIZE,
                   input wire [3:0] HPROT,
                   input wire HWRITE,
                   input wire [31:0] HWDATA,
                   input wire HREADY,
                   output wire HREADYOUT,
                   output reg [31:0] HRDATA,
                   output wire HRESP,
                   output wire [3:0] vga_addr_v,
                   output wire [4:0] vga_addr_h,
                   output wire [31:0] vga_ctrl,
                   output wire vga_ctrl_en);
    
    assign HRESP     = 1'b0;
    assign HREADYOUT = 1'b1;
    
    wire read_en;
    assign read_en = HSEL&HTRANS[1]&(~HWRITE)&HREADY;
    
    wire write_en;
    assign write_en = HSEL&HTRANS[1]&(HWRITE)&HREADY;
    
    reg [15:0] addr_reg;
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) addr_reg                 <= 4'h0;
        else if (read_en || write_en) addr_reg <= HADDR[15:0];
    end
    
    reg rd_en_reg;
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) rd_en_reg     <= 1'b0;
        else if (read_en) rd_en_reg <= 1'b1;
        else rd_en_reg              <= 1'b0;
    end
    
    reg wr_en_reg;
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) wr_en_reg      <= 1'b0;
        else if (write_en) wr_en_reg <= 1'b1;
        else  wr_en_reg              <= 1'b0;
    end
    
    always@(*) begin
        HRDATA <= 32'b0;
    end
    
    assign vga_ctrl_en = wr_en_reg ? 1'b1 : 1'b0;
    assign vga_ctrl    = wr_en_reg ? HWDATA[31:0] : 32'd0;
    assign vga_addr_h  = addr_reg[6:2];
    assign vga_addr_v  = addr_reg[10:7];
    
endmodule
    
    
