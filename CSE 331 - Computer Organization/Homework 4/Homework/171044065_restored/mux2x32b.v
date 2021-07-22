module mux2x32b(out, in1, in0, sl);

output [31:0] out;
input [31:0] in1,in0;
input sl;

mux2x1b m0(out[0],in1[0],in0[0],sl);
mux2x1b m1(out[1],in1[1],in0[1],sl);
mux2x1b m2(out[2],in1[2],in0[2],sl);
mux2x1b m3(out[3],in1[3],in0[3],sl);
mux2x1b m4(out[4],in1[4],in0[4],sl);
mux2x1b m5(out[5],in1[5],in0[5],sl);
mux2x1b m6(out[6],in1[6],in0[6],sl);
mux2x1b m7(out[7],in1[7],in0[7],sl);
mux2x1b m8(out[8],in1[8],in0[8],sl);
mux2x1b m9(out[9],in1[9],in0[9],sl);
mux2x1b m10(out[10],in1[10],in0[10],sl);
mux2x1b m11(out[11],in1[11],in0[11],sl);
mux2x1b m12(out[12],in1[12],in0[12],sl);
mux2x1b m13(out[13],in1[13],in0[13],sl);
mux2x1b m14(out[14],in1[14],in0[14],sl);
mux2x1b m15(out[15],in1[15],in0[15],sl);
mux2x1b m16(out[16],in1[16],in0[16],sl);
mux2x1b m17(out[17],in1[17],in0[17],sl);
mux2x1b m18(out[18],in1[18],in0[18],sl);
mux2x1b m19(out[19],in1[19],in0[19],sl);
mux2x1b m20(out[20],in1[20],in0[20],sl);
mux2x1b m21(out[21],in1[21],in0[21],sl);
mux2x1b m22(out[22],in1[22],in0[22],sl);
mux2x1b m23(out[23],in1[23],in0[23],sl);
mux2x1b m24(out[24],in1[24],in0[24],sl);
mux2x1b m25(out[25],in1[25],in0[25],sl);
mux2x1b m26(out[26],in1[26],in0[26],sl);
mux2x1b m27(out[27],in1[27],in0[27],sl);
mux2x1b m28(out[28],in1[28],in0[28],sl);
mux2x1b m29(out[29],in1[29],in0[29],sl);
mux2x1b m30(out[30],in1[30],in0[30],sl);
mux2x1b m31(out[31],in1[31],in0[31],sl);

endmodule
