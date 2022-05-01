module vga_rom (input clk,
                input [11:0] addr,
                input [6:0] font_type,
                output reg rdata);
    reg [7:0] memory [0:127][0:143];
    initial begin
        `ifdef SIMULATION
        $readmemh("./font/font.hex", memory);
        `else
        $readmemh("D:/hit_sim_soft/arm-term/XC-SoC/simulation/font/font.hex",mem);
        `endif
    end
    
    always @(posedge clk) begin
        rdata <= memory[font_type][addr[11:3]]&(1'b1 << addr[2:0])?1'b1:1'b0;
    end
endmodule
