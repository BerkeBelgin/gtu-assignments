module processor(test_ins, test_pc, clk);
input clk;
output [31:0] test_ins, test_pc;

reg [31:0] pc;
wire [31:0] instruction;
wire [31:0] final_PC;

initial begin
	pc = 32'b00000000000000000000000000000000;
end

always @(posedge clk) begin
	pc = final_PC;
end

assign test_ins = instruction;
assign test_pc = pc;

instructionMemory f0(instruction,pc[13:0]);

wire rtypeOrlui;
or or2(rtypeOrlui,rType,lui);
mux2x32b mux53(writeData1,temp2,temp1,rtypeOrlui);

wire n5,n4,n2,n1,n0;
not not5 (n5,instruction[5]);
not not4 (n4,instruction[4]);
not not2 (n2,instruction[2]);
not not1 (n1,instruction[1]);
not not0 (n0,instruction[0]);
and and1(jr,n5,n4,instruction[3],n2,n1,n0);

assign luiOut = {instruction[15:0],16'd0};

wire notZero, finalZero, selectBranch;
not not6(notZero,aluEq);
mux2x1b mux6(finalZero,notZero,aluEq,bne);
and and2(selectBranch,branch,finalZero);

wire [31:0] pc_branch, shifted_imm;
shiftLeft2bx32b shift(shifted_imm,immediate);
adder32b add2(pc_branch,C,PC_4,shifted_imm,1'b0);

mux2x32b mux9(nextPC,pc_branch,PC_4,selectBranch);


wire jalorj;
wire [31:0] temp;
wire [31:0] targetAdd;
assign targetAdd = {pc[31:28],instruction[25:0],2'b00};
or or1 (jalorj,jal,j);
mux2x32b mux10 (temp,targetAdd,nextPC,jalorj);
mux2x32b mux11 (final_PC,readData1,temp,jr);

wire C;
wire [31:0] PC_4, nextPC;
adder32b f1 (PC_4,C,pc,32'd4,1'b0);


wire branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType;
wire [1:0] aluOp;
controlUnit cU(aluOp,branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType,instruction[31:26]);

wire jr, notjr, newReg1, newReg2;
not n11(notjr,jr);
and and11 (newReg1,regWrite1,notjr);
and and12 (newReg2,regWrite2,notjr);

wire [31:0] writeData1, writeData2;
wire [4:0] writeReg1, writeReg2;
mux2x5b mux1(writeReg1,instruction[15:11],instruction[20:16],rType);

mux2x5b mux2(writeReg2,5'b11111,instruction[25:21],jal);

wire [31:0] readData1, readData2;

registers registers(readData1,readData2,writeData1,writeData2,instruction[25:21],instruction[20:16],writeReg1,writeReg2,newReg1,newReg2,clk);

wire [31:0] zeroEx, signEx, immediate;
signExtend16bx32b se(signEx,instruction[15:0]);
zeroExtend16bx32b ze(zeroEx,instruction[15:0]);

mux2x32b mux8 (immediate,zeroEx,signEx,ori);

wire [2:0] operation;
ALUControlUnit acu(operation, instruction[5:0], aluOp);

wire [31:0] data2;
mux2x32b mux3(data2,immediate,readData2,aluSrc);
wire aluLt, aluEq, aluGt;
wire [31:0] aluResult;
ALU32b alu(aluResult,aluLt,aluEq,aluGt,readData1,data2,operation);

wire [31:0] memData;
dataMemory datamem(memData,memWrite,memRead,aluResult,readData2,clk);

mux2x32b mux4(writeData2,PC_4,aluResult,jal);

wire [31:0] temp1,temp2,luiOut,compRes;
wire [1:0] slcBt;

encoder4x1b enc (slcBt, 1'b0, aluGt, aluLt, aluEq);
mux4x32b mux61(compRes, 32'd0, 32'd3, 32'd2, 32'd1, slcBt);

mux2x32b mux51(temp1,memData,aluResult,memSlc);
mux2x32b mux52(temp2,luiOut,compRes,lui);

endmodule
