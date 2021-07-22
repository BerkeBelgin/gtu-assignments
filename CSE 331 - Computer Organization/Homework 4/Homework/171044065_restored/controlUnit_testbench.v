`define DELAY 20
module controlUnit_testbench();
wire [1:0] aluOp;
wire branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType;
reg [5:0] instruction;

controlUnit cu (aluOp,branch,bne,j,jal,ori,lui,memRead,memWrite,memSlc,aluSrc,regWrite1,regWrite2,rType,instruction);

initial begin
instruction = 6'd8;
#`DELAY;
instruction = 6'd0;
#`DELAY;
instruction = 6'h23;
#`DELAY;
instruction = 6'h2b;
#`DELAY;
instruction = 6'h2;
#`DELAY;
instruction = 6'h3;
#`DELAY;
instruction = 6'h4;
#`DELAY;
instruction = 6'h5;
#`DELAY;
instruction = 6'hd;
#`DELAY;
instruction = 6'hf;
#`DELAY;
instruction = 6'd10;
#`DELAY;
end
 
 
initial
begin
$monitor(
	"time = %2d, instruction =%2h, rType=%1b, branch=%1b, bne=%1b, j=%1b, jal=%1b, ori=%1b, lui=%1b, memSlc=%1b, memRead=%1b, memWrite=%1b, aluSrc=%1b, aluOp=%2b, regWrite1=%1b, regWrite2=%1b", 
	$time, instruction,rType,branch,bne,j,jal,ori,lui,memSlc,memRead,memWrite,aluSrc,aluOp,regWrite1,regWrite2
);
end
 
endmodule
