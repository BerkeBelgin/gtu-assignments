module ALU32b(result,lt,eq,gt,a,b,op);
input [31:0] a,b;
input [2:0] op;
output [31:0] result;
output lt, eq, gt;

wire [31:0] bnot, m0out, out3, out2, out1, out0;
wire tmp;

not32b f0 (bnot, b);
mux2x32b m0 (m0out,bnot,b,op[2]);

and32b f1 (out0, a, b);
or32b f2 (out1, a, b);
adder32b f3 (out2, tmp, a, m0out, op[2]);
xor32b f4 (out3, a, b);

mux4x32b m1(result, out3, out2, out1, out0, op[1:0]);

comparator0x32b f5 (lt, eq, gt, result);

endmodule
