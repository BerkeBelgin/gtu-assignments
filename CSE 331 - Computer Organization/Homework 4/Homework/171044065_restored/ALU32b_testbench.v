`define DELAY 20
module ALU32b_testbench();
reg [31:0] a, b;
reg [2:0] op;
wire [31:0]result;
wire lt, eq, gt;

ALU32b alu(result, lt, eq, gt, a, b, op);

initial begin
a = 32'd7; b = 32'd2; op = 3'b000; //and
#`DELAY;
a = 32'd23; b = 32'd11; op = 3'b010; //add
#`DELAY;
a = 32'd4; b = 32'd5; op = 3'b110; //sub
#`DELAY;
a = 32'd4; b = 32'd4; op = 3'b110; //sub
#`DELAY;
a = 32'd4; b = 32'd3; op = 3'b110; //sub
#`DELAY;
a = 32'd2; b = 32'd3; op = 3'b001; // or
#`DELAY;
a = 32'd2; b = 32'd3; op = 3'b011; // xor 
end
 
 
initial
begin
$monitor("time = %2d, a =%d, b=%d, op=%3b, result=%32b, lt=%1b, eq=%1b, gt=%1b", $time, a, b, op, result, lt, eq, gt);
end
 
endmodule
