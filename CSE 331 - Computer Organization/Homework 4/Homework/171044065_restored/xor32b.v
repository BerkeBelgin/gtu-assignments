module xor32b(out,i1,i0);
input [31:0] i1, i0;
output [31:0] out;

xor x0(out[0],i1[0],i0[0]);
xor x1(out[1],i1[1],i0[1]);
xor x2(out[2],i1[2],i0[2]);
xor x3(out[3],i1[3],i0[3]);
xor x4(out[4],i1[4],i0[4]);
xor x5(out[5],i1[5],i0[5]);
xor x6(out[6],i1[6],i0[6]);
xor x7(out[7],i1[7],i0[7]);
xor x8(out[8],i1[8],i0[8]);
xor x9(out[9],i1[9],i0[9]);
xor x10(out[10],i1[10],i0[10]);
xor x11(out[11],i1[11],i0[11]);
xor x12(out[12],i1[12],i0[12]);
xor x13(out[13],i1[13],i0[13]);
xor x14(out[14],i1[14],i0[14]);
xor x15(out[15],i1[15],i0[15]);
xor x16(out[16],i1[16],i0[16]);
xor x17(out[17],i1[17],i0[17]);
xor x18(out[18],i1[18],i0[18]);
xor x19(out[19],i1[19],i0[19]);
xor x20(out[20],i1[20],i0[20]);
xor x21(out[21],i1[21],i0[21]);
xor x22(out[22],i1[22],i0[22]);
xor x23(out[23],i1[23],i0[23]);
xor x24(out[24],i1[24],i0[24]);
xor x25(out[25],i1[25],i0[25]);
xor x26(out[26],i1[26],i0[26]);
xor x27(out[27],i1[27],i0[27]);
xor x28(out[28],i1[28],i0[28]);
xor x29(out[29],i1[29],i0[29]);
xor x30(out[30],i1[30],i0[30]);
xor x31(out[31],i1[31],i0[31]);

endmodule
