module instructionMemory(instruction,address);
output [31:0] instruction;
input [13:0] address;

reg [31:0] instructions [255:0];

assign instruction = instructions[address[13:2]];

endmodule
