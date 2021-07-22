`define DELAY 20
module adder32b_testbench();
reg [31:0] a, b;
reg cin;
wire [31:0] s;
wire cout;

adder32b adder(s, cout, a, b, cin);

initial begin
a = 32'd10; b = 32'd10; cin = 1'b0;
#`DELAY;
a = 32'd10; b = 32'd10; cin = 1'b1;
#`DELAY;
a = 32'd10; b = 32'd20; cin = 1'b0;
#`DELAY;
a = 32'd10; b = 32'd20; cin = 1'b1;
#`DELAY;
a = 32'd20; b = 32'd10; cin = 1'b0;
#`DELAY;
a = 32'd20; b = 32'd10; cin = 1'b1;
#`DELAY;
a = 32'd20; b = 32'd20; cin = 1'b0;
#`DELAY;
a = 32'd20; b = 32'd20; cin = 1'b1;
end
 
 
initial
begin
$monitor("time = %2d, a =%d, b=%d, cin=%1b, s=%d, cout=%1b", $time, a, b, cin, s, cout);
end
 
endmodule
