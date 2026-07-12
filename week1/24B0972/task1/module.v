module adder (
    input a,
    input b,
    input cin,
    output sum,
    output cout
);
    // Fill in the logic for the adder
    assign sum = a ^ b ^ cin;
    assign cout = (a & b) | (b & cin) | (cin & a);
endmodule
