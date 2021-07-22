`define DELAY 20
module mux4x1b_testbench();
reg in3, in2, in1, in0;
reg [1:0] sl;
wire out;

mux4x1b mux (out, in3, in2, in1, in0, sl);

initial begin
in3 = 1'd0; in2 = 1'd0; in1 = 1'd0; in0 = 1'd1; sl = 2'b00;
#`DELAY;
in3 = 1'd0; in2 = 1'd0; in1 = 1'd1; in0 = 1'd0; sl = 2'b01;
#`DELAY;
in3 = 1'd0; in2 = 1'd1; in1 = 1'd0; in0 = 1'd0; sl = 2'b10;
#`DELAY;
in3 = 1'd1; in2 = 1'd0; in1 = 1'd0; in0 = 1'd0; sl = 2'b11;
#`DELAY;
end
 
 
initial
begin
$monitor("time = %2d, in3 =%d, in2=%d, in1 =%d, in0=%d, out=%d, sl=%2b", $time, in3, in2, in1, in0, out, sl);
end
 
endmodule
