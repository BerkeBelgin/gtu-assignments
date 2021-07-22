`define DELAY 20
module adder1b_testbench();
reg a, b, cin;
wire s, cout;

adder1b adder(s, cout, a, b, cin);

initial begin
a = 1'b0; b = 1'b0; cin = 1'b0;
#`DELAY;
a = 1'b0; b = 1'b0; cin = 1'b1;
#`DELAY;
a = 1'b0; b = 1'b1; cin = 1'b0;
#`DELAY;
a = 1'b0; b = 1'b1; cin = 1'b1;
#`DELAY;
a = 1'b1; b = 1'b0; cin = 1'b0;
#`DELAY;
a = 1'b1; b = 1'b0; cin = 1'b1;
#`DELAY;
a = 1'b1; b = 1'b1; cin = 1'b0;
#`DELAY;
a = 1'b1; b = 1'b1; cin = 1'b1;
end
 
 
initial
begin
$monitor("time = %2d, a =%1b, b=%1b, cin=%1b, s=%1b, cout=%1b", $time, a, b, cin, s, cout);
end
 
endmodule
