module mux4x1b(out, in3, in2, in1, in0, sl);

output out;
input in3, in2, in1, in0;
input [1:0] sl;
wire t3, t2, t1, t0, snot1, snot0;

not n1 (snot1, sl[1]);
not n0 (snot0, sl[0]);

and a3 (t3,  sl[1], sl[0], in3);
and a2 (t2,  sl[1], snot0, in2);
and a1 (t1,  snot1, sl[0], in1);
and a0 (t0,  snot0, snot1, in0);
or  o0 (out,t0,t1,t2,t3);

endmodule
