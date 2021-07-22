`define DELAY 20
module mux2x1b_testbench();
reg  in1, in0;
reg sl;
wire out;

mux2x1b mux(out, in1, in0, sl);

initial begin
in1 = 1'd1; in0 = 1'd0; sl = 1'b0;
#`DELAY;
in1 = 1'd1; in0 = 1'd0; sl = 1'b1;
end
 
 
initial
begin
$monitor("time = %2d, in1 =%d, in0=%d, out=%d, select=%1b", $time, in1, in0, out, sl);
end
 
endmodule
