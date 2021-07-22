`define DELAY 20
module mux2x32b_testbench();
reg [31:0] in1, in0;
reg sl;
wire [31:0] out;

mux2x32b mux(out, in1, in0, sl);

initial begin
in1 = 32'd23; in0 = 32'd20; sl = 1'b0;
#`DELAY;
in1 = 32'd40; in0 = 32'd45; sl = 1'b1;
end
 
 
initial
begin
$monitor("time = %2d, in1=%d, in0=%d, out=%d, sl=%1b", $time, in1, in0, out, sl);
end
 
endmodule