module processor_testbench();

reg clock;
wire [31:0] instrOP;
wire [31:0] PC;

processor cpu (instrOP,PC,clock);

initial begin
$readmemb("instructionMemory.mem", cpu.instructionMemory.instructions);
$readmemb("registers.mem",cpu.registers.registers);
$readmemb("dataMemory.txt",cpu.dataMemory.memory);
end

initial clock = 0;
always
	#50 clock=~clock;
initial begin 
	#500 $finish;
end

initial begin
$monitor("instr : %32b\nPC : %32b\n-----------------------\n",instrOP,PC);
end

always @ (*) begin
	$writememb("registers.mem", cpu.registers.registers);
	$writememb("dataMemory.txt",cpu.dataMemory.memory);
end

endmodule