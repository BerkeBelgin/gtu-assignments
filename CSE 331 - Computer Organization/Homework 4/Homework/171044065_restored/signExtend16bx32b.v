module signExtend16bx32b(out, in);
input [15:0] in;
output [31:0] out;

assign out[15:0] = in;
assign out[31] = in[15];
assign out[30] = in[15];
assign out[29] = in[15];
assign out[28] = in[15];
assign out[27] = in[15];
assign out[26] = in[15];
assign out[25] = in[15];
assign out[24] = in[15];
assign out[23] = in[15];
assign out[22] = in[15];
assign out[21] = in[15];
assign out[20] = in[15];
assign out[19] = in[15];
assign out[18] = in[15];
assign out[17] = in[15];
assign out[16] = in[15];

endmodule
