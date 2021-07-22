module controlUnit(aluOp,branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType,instruction);
output [1:0] aluOp;
output branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType;
input [5:0] instruction;

wire rtype_r,lw_r,sw_r,j_r,jal_r,beq_r,bne_r,ori_r,lui_r;
wire n0,n1,n2,n3,n4,n5;

not not0(n0,instruction[0]);
not not1(n1,instruction[1]);
not not2(n2,instruction[2]);
not not3(n3,instruction[3]);
not not4(n4,instruction[4]);
not not5(n5,instruction[5]);

and a1 (rtype_r,n5,n4,n3,n2,n1,n0);
and a2 (lw_r,instruction[5],n4,n3,n2,instruction[1],instruction[0]);
and a3 (sw_r,instruction[5],n4,instruction[3],n2,instruction[1],instruction[0]);
and a4 (j_r,n5,n4,n3,n2,instruction[1],n0);
and a5 (jal_r,n5,n4,n3,n2,instruction[1],instruction[0]);
and a6 (beq_r,n5,n4,n3,instruction[2],n1,n0);
and a7 (bne_r,n5,n4,n3,instruction[2],n1,instruction[0]);
and a8 (ori_r,n5,n4,instruction[3],instruction[2],n1,instruction[0]);
and a9 (lui_r,n5,n4,instruction[3],instruction[2],instruction[1],instruction[0]);

or f0 (aluOp[1], rtype_r, ori_r);
or f1 (aluOp[0], rtype_r, beq_r, bne_r);
or f2 (branch, beq_r, bne_r);
assign bne = bne_r;
assign j = j_r;
assign jal = jal_r;
assign ori = ori_r;
assign lui = lui_r;
assign memRead = lw_r;
assign memWrite = sw_r;
assign memSlc = lw_r;
assign rType = rtype_r;
or f3 (aluSrc, lw_r, sw_r, ori_r);
or f4 (regWrite1, rtype_r, lw_r, ori_r, lui_r);
or f5 (regWrite2, rtype_r, jal_r);
endmodule
