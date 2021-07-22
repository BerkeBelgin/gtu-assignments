module adder1b(s, cout, a, b, cin);
output s, cout;
input a, b, cin;

wire a1, a0, x0;

xor xor0 (x0, a, b);
xor xor1 (s, x0, cin);

and and0 (a0, x0, cin);
and and1 (a1, a, b);

or or0 (cout, a0, a1);

endmodule
