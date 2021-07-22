`define DELAY 20
module shiftLeft2bx32b_testbench();
reg [31:0] in;
wire [31:0] out;

shiftLeft2bx32b sl (out,in);

initial begin
in = 32'd4;
#`DELAY;
in = 32'd5;
#`DELAY;
in = 32'd100000;
#`DELAY;
in = 32'd18;
#`DELAY;
in = 32'd19;
#`DELAY;
in = 32'd20;
end
 
 
initial
begin
$monitor("time = %2d, in =%32b, out=%32b", $time, in, out);
end
 
endmodule
