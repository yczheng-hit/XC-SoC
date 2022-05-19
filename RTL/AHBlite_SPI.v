module AHBlite_SPI(input wire HCLK,
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
                    output [31:0] HRDATA,
                    output wire HRESP,
                    output wire scs,
                    output wire sck,
                    output wire mosi,
                    input wire miso
                    );
    assign HRESP     = 1'b0;
    //AHB to wishbone
    reg sel_reg;
    wire [1:0]addr_reg_n;
    reg [1:0]addr_reg;
    wire write_en;
    reg wr_en_reg;
    
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) sel_reg     <= 1'b0;
        else sel_reg        <= HSEL&HTRANS[1];
    end

    assign addr_reg_n = ~(HSEL&HTRANS[1])?2'b00:HADDR[3:2];
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) addr_reg     <= 2'd0;
        else addr_reg        <= addr_reg_n;
    end

    assign write_en = HSEL&HTRANS[1]&(HWRITE)&HREADY;
    always@(posedge HCLK or negedge HRESETn) begin
        if (~HRESETn) wr_en_reg      <= 1'b0;
        else if (write_en) wr_en_reg <= 1'b1;
        else  wr_en_reg              <= 1'b0;
    end
    
    spi u_spi(
    	.clk_i  (HCLK  ),
        .rst_i  (HRESETn  ),
        .cyc_i  (sel_reg  ),
        .stb_i  (sel_reg  ),
        .adr_i  (addr_reg),
        .we_i   (wr_en_reg   ),
        .dat_i  (HWDATA  ),
        .dat_o  (HRDATA  ),
        .ack_o  (HREADYOUT  ),
        .inta_o (),
        .scs_o  (scs),
        .sck_o  (sck),
        .mosi_o (mosi),
        .miso_i (miso)
    );
    

endmodule
        
        
