module ALUControlUnit (operation, func, aluOp);
input [5:0] func;
input [1:0] aluOp;
output [2:0] operation;

wire nop0,nop1,nf0,nf1,nf2,f0,f1,f100,f101,f110, a00, a01, a10, a11, w1,w2,w3,w4,w5;

not n1 (nop0,aluOp[0]);
not n2 (nop1,aluOp[1]);

not n3(nf0,func[0]);
not n4(nf1,func[1]);
not n5(nf2,func[2]);

and and1 (f0,nf2,nf1,nf0);
and and2 (f1,nf2,func[1],nf0);
and and3 (f100,func[2],nf1,nf0);
and and4 (f101,func[2],nf1,func[0]);
and and5 (f110,func[2],func[1],nf0);
and and6 (a00,nop1,nop0);
and and7 (a01,nop1,aluOp[0]);
and and8 (a10,aluOp[1],nop0);
and and9 (a11,aluOp[1],aluOp[0]);

or o1 (w1,f101,f110);
and and10 (w2,a11,w1);
or o2 (operation[0],a10,w2);

or o3 (w3,f0,f1,f110);
and and11 (w4,a11,w3);
or o4 (operation[1],a00,a01,w4);

and and12 (w5,a11,f1);
or o5 (operation[2],a01,w5);

endmodule
