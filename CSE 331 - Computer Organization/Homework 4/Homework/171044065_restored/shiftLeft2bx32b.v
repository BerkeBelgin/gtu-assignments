module shiftLeft2bx32b(out,in);
output [31:0] out;
input [31:0] in;

assign out[31:2] = in[29:0];
assign out[1] = 0;
assign out[0] = 0;

endmodule
