module zeroExtend16bx32b(out, in);
input [15:0] in;
output [31:0] out;

assign out[15:0] = in;
assign out[31] = 0;
assign out[30] = 0;
assign out[29] = 0;
assign out[28] = 0;
assign out[27] = 0;
assign out[26] = 0;
assign out[25] = 0;
assign out[24] = 0;
assign out[23] = 0;
assign out[22] = 0;
assign out[21] = 0;
assign out[20] = 0;
assign out[19] = 0;
assign out[18] = 0;
assign out[17] = 0;
assign out[16] = 0;

endmodule
