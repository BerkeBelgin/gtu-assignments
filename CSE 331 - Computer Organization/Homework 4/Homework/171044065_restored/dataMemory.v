module dataMemory(readData, writeData, address, writeEnable, readEnable, clk);
output reg [31:0] readData;
input [31:0] writeData;
input [17:0] address;
input readEnable, writeEnable, clk;

reg [31:0] memory [255:0];

always @(readEnable or writeEnable or address or writeData or readData) begin
	if(readEnable) begin
		readData <= memory[address[17:2]];
	end
	if(writeEnable) begin
		memory[address[17:2]] <= writeData;
	end
end

endmodule
