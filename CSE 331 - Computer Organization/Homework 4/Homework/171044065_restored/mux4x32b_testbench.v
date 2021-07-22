`define DELAY 20
module mux4x32b_testbench();
reg [31:0] in3, in2, in1, in0;
reg [1:0] sl;
wire [31:0] out;

mux4x32b mux (out, in3, in2, in1, in0, sl);

initial begin
in3 = 32'd17; in2 = 32'd16; in1 = 32'd15; in0 = 32'd14; sl = 2'b00;
#`DELAY;
in3 = 32'd13; in2 = 32'd12; in1 = 32'd11; in0 = 32'd10; sl = 2'b01;
#`DELAY;
in3 = 32'd9; in2 = 32'd8; in1 = 32'd7; in0 = 32'd6; sl = 2'b10;
#`DELAY;
in3 = 32'd5; in2 = 32'd4; in1 = 32'd3; in0 = 32'd2; sl = 2'b11;
#`DELAY;
end
 
 
initial
begin
$monitor("time = %2d, in3 =%d, in2=%d, in1 =%d, in0=%d, out=%d, sl=%2b", $time, in3, in2, in1, in0, out, sl);
end
 
endmodule
