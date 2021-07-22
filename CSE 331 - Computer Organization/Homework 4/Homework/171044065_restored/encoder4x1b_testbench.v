`define DELAY 20
module encoder4x1b_testbench();
reg in3, in2, in1, in0;
wire [1:0] out;

encoder4x1b encoder (out, in3, in2, in1, in0);

initial begin
in3 = 1'b0; in2 = 1'b0; in1 = 1'b0; in0 = 1'b1;
#`DELAY;
in3 = 1'b0; in2 = 1'b0; in1 = 1'b1; in0 = 1'b0;
#`DELAY;
in3 = 1'b0; in2 = 1'b1; in1 = 1'b0; in0 = 1'b0;
#`DELAY;
in3 = 1'b1; in2 = 1'b0; in1 = 1'b0; in0 = 1'b0;
#`DELAY;
end
 
 
initial
begin
$monitor("time = %2d, in3 =%d, in2=%d, in1 =%d, in0=%d, out=%d", $time, in3, in2, in1, in0, out);
end
 
endmodule
