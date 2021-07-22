module encoder4x1b(out, in3, in2, in1, in0);

output [1:0] out;
input in3, in2, in1, in0;

or o1 (out[1], in3, in2);
or o0 (out[0], in3, in1);

endmodule
