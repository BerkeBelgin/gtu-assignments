module mux2x5b (out, in1, in0, sl);

output [4:0] out;
input [4:0] in1,in0;
input sl;

mux2x1b m0(out[0],in1[0],in0[0],sl);
mux2x1b m1(out[1],in1[1],in0[1],sl);
mux2x1b m2(out[2],in1[2],in0[2],sl);
mux2x1b m3(out[3],in1[3],in0[3],sl);
mux2x1b m4(out[4],in1[4],in0[4],sl);

endmodule
