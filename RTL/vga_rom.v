module vga_rom (input clk,
                input [10:0] addr,
                input [6:0] font_type,
                output reg rdata);
    // 16*16*96
    reg [7:0] mem [24575:0];
    initial begin
        `ifdef SIMULATION
        $readmemh("/mnt/d/hit_sim_soft/arm-term/XC-SoC/RTL/font/font.hex", mem);
        `else
        $readmemh("D:/hit_sim_soft/arm-term/XC-SoC/RTL/font/font.hex",mem);
        `endif
    end
    wire [7:0]font;
    assign font = mem[{font_type,addr[10:3]}];
    always @(posedge clk) begin
        rdata <= font&(1'b1 << addr[2:0])?1'b1:1'b0;
    end
endmodule
