module vga_controler (input rst_n,
                      input clk,
                      input vga_data_en,
                      input rdata,
                      input [3:0]  vga_addr_v, 
                      input [4:0]  vga_addr_h,
                      input [31:0]  vga_ctrl,
                      input vga_ctrl_en,
                      output [11:0] addr,
                      output [8:0] color,
                      output [6:0] font_type);
    
    /*
    block control reg 
    12 * 32 * 32
    v  * h  * bits
    8-0:    color
    17-9:   background (not implemented)
    21-18:  board(white only) (not implemented)
    ...:    reserved
    31-24:  font_type
    */
    reg [31:0] block_ctrl[11:0][31:0];
    reg [4:0] hblock_cnt;
    wire [4:0] hblock_cnt_n;
    reg [3:0] vblock_cnt;
    wire [3:0] vblock_cnt_n;
    reg [4:0] hsyn_cnt;
    wire [4:0] hsyn_cnt_n;
    reg [5:0] vsyn_cnt;
    wire [5:0] vsyn_cnt_n;
    wire board;
    wire [9:0] tmp1;
    wire [9:0] tmp2;
    assign tmp1 = {vga_addr_v,vga_addr_h};
    assign tmp2 = (vblock_cnt<<5)+hblock_cnt;
    always @(posedge clk) begin
        if(vga_ctrl_en)
            block_ctrl[vga_addr_v][vga_addr_h] <= vga_ctrl;
    end

    assign font_type = block_ctrl[vblock_cnt][hblock_cnt][31:24];
    // assign font_type = (hblock_cnt + vblock_cnt * 6'd32)&7'h7f;
    
    assign board = ((vsyn_cnt == 6'd49)||(hsyn_cnt == 5'd0)||(vsyn_cnt == 6'd0))?1'b1:1'd0;

    assign addr = (board)?12'd0:hsyn_cnt - 12'd1 + 12'd24* (vsyn_cnt-12'd1);
    
    assign color = rdata?block_ctrl[vblock_cnt][hblock_cnt][8:0]:9'h0;

    assign hblock_cnt_n = (hsyn_cnt == 5'd24)?hblock_cnt+1'b1:hblock_cnt;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            hblock_cnt <= 5'd0;
        else
            hblock_cnt <= hblock_cnt_n;
    end

    assign hsyn_cnt_n = (~vga_data_en)?hsyn_cnt:
    (hsyn_cnt == 5'd24)?5'd0:hsyn_cnt + 1'b1;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            hsyn_cnt <= 5'd0;
        else
            hsyn_cnt <= hsyn_cnt_n;
    end

    assign vblock_cnt_n = !((vsyn_cnt == 6'd49)&&(hsyn_cnt == 5'd24)&&(hblock_cnt==5'd31))?vblock_cnt:
                                        (vblock_cnt==4'd11)?4'd0:vblock_cnt+1'b1;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            vblock_cnt <= 4'd0;
        else
            vblock_cnt <= vblock_cnt_n;
    end

    assign vsyn_cnt_n = ~((hsyn_cnt == 5'd24)&&(hblock_cnt==5'd31))?vsyn_cnt:
                        (vsyn_cnt==6'd49)?6'd0:vsyn_cnt + 1'b1;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            vsyn_cnt <= 6'd0;
        else
            vsyn_cnt <= vsyn_cnt_n;
    end
endmodule
    
