module SBox(
    input [3:0]in ,
    output [3:0]out
);
wire a , b , c, d;
assign a = in[3];
assign b = in[2];
assign c = in[1];
assign d = in[0];


assign out[0] = (b&(~d)) | (~a & ~c & d) | (a & c &(b | ~d));
assign out[1] = (~b & ~d & ( a | ~c)) | (~c & d) | (~a & b & c & ~d);
assign out[2] = (a & b & ~c) | (~a & ~d & (~c | b)) | (~b & c & ( a | (~a & d)));
assign out[3] = (a & d & (b | c)) | (~a & b & ( c | ~d)) | (~b & ~c &( (~a & d) | (a & ~d)));

// Fill SBox logic here
// 0000 0110
// 0001 1011
// 0010 0000
// 0011 0100
// 0100 1101
// 0101 0011
// 0110 1111
// 0111 1000
// 1000 1010
// 1001 0010
// 1010 0111
// 1011 1100
// 1100 0101
// 1101 1110
// 1110 0001
// 1111 1001
endmodule
