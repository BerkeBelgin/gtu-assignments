module mux2x1b(out, in1, in0, sl);

output out;
input in1, in0, sl;
wire t1, t0, slnot;

not n0 (slnot, sl);

and a1 ( t1,    sl, in1);
and a0 ( t0, slnot, in0);
or o0 (out, t1, t0);

endmodule
