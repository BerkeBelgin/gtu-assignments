module upperExtend16bx32b(out, in);
input [15:0] in;
output [31:0] out;

assign out = {in, 16'd0};

endmodule
