module registers(readData1, readData2, writeData1, writeData2, writeAddress1, writeAddress2, readAddress1, readAddress2, writeEnable1, writeEnable2, clk);

output [31:0] readData1, readData2;
input [31:0] writeData1, writeData2;
input [4:0] readAddress1, readAddress2, writeAddress1, writeAddress2;
input writeEnable1, writeEnable2, clk;

reg[31:0] registers[31:0];

assign readData1 = registers[readAddress1];
assign readData2 = registers[readAddress2];

always @(posedge clk) begin
	if(writeEnable1) begin
		registers[writeAddress1] <= writeData1;
	end

	if(writeEnable2) begin
		registers[writeAddress2] <= writeData2;
	end
end
	
endmodule
