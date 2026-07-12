module Encrypt(
    input [63:0]  plaintext  ,
    input [63:0]  secretKey  ,
    output [63:0] ciphertext 
);
wire [63:0] r1in;
AddRoundKey u1(
    .currentState(plaintext),
    .roundKey(secretKey),
    .nextState(r1in)
);

wire [63:0] keys[0:10];
wire [63:0] text[0:10];
assign text[0] = r1in;
assign keys[0] = secretKey;
genvar i;
generate
    for (i = 0; i<10; i = i+1) begin 
        NextKey u_roundkey(
            .currentKey(keys[i]),
            .nextKey(keys[i+1])
        );
        Round u_round(
            .currentState(text[i]),
            .roundKey(keys[i+1]),
            .nextState(text[i+1])
        );
    end
endgenerate

assign ciphertext = text[10];

endmodule

module Round(
    input  [63:0] currentState ,
    input  [63:0] roundKey     ,
    output [63:0] nextState    
);
wire [63:0] subo;
wire [63:0] shifto;
SBox u1(
    .in(currentState[3:0]),
    .out(subo[3:0])
);
SBox u2(
    .in(currentState[7:4]),
    .out(subo[7:4])
);
SBox u3(
    .in(currentState[11:8]),
    .out(subo[11:8])
);
SBox u4(
    .in(currentState[15:12]),
    .out(subo[15:12])
);
SBox u5(
    .in(currentState[19:16]),
    .out(subo[19:16])
);
SBox u6(
    .in(currentState[23:20]),
    .out(subo[23:20])
);
SBox u7(
    .in(currentState[27:24]),
    .out(subo[27:24])
);
SBox u8(
    .in(currentState[31:28]),
    .out(subo[31:28])
);
SBox u9(
    .in(currentState[35:32]),
    .out(subo[35:32])
);
SBox u10(
    .in(currentState[39:36]),
    .out(subo[39:36])
);
SBox u11(
    .in(currentState[43:40]),
    .out(subo[43:40])
);
SBox u12(
    .in(currentState[47:44]),
    .out(subo[47:44])
);
SBox u13(
    .in(currentState[51:48]),
    .out(subo[51:48])
);
SBox u14(
    .in(currentState[55:52]),
    .out(subo[55:52])
);
SBox u15(
    .in(currentState[59:56]),
    .out(subo[59:56])
);
SBox u16(
    .in(currentState[63:60]),
    .out(subo[63:60])
);

ShiftRows u17(
    .currentState(subo),
    .nextState(shifto)
);

AddRoundKey u18(
    .currentState(shifto),
    .roundKey(roundKey),
    .nextState(nextState)
);
endmodule

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

endmodule

module NextKey(
    input  [63:0] currentKey,
    output [63:0] nextKey
);
assign nextKey[3:0] = currentKey[63:60];
assign nextKey[7:4] = currentKey[3:0];
assign nextKey[11:8] = currentKey[7:4];
assign nextKey[15:12] = currentKey[11:8];

assign nextKey[19:16] = currentKey[15:12];
assign nextKey[23:20] = currentKey[19:16];
assign nextKey[27:24] = currentKey[23:20];
assign nextKey[31:28] = currentKey[27:24]; 

assign nextKey[35:32] = currentKey[31:28];
assign nextKey[39:36] = currentKey[35:32];
assign nextKey[43:40] = currentKey[39:36];
assign nextKey[47:44] = currentKey[43:40];

assign nextKey[51:48] = currentKey[47:44];
assign nextKey[55:52] = currentKey[51:48];
assign nextKey[59:56] = currentKey[55:52];
assign nextKey[63:60] = currentKey[59:56];
endmodule

module ShiftRows(
    input  [63:0] currentState ,
    output [63:0] nextState    
);
assign nextState[3:0] = currentState[3:0];
assign nextState[7:4] = currentState[7:4];
assign nextState[11:8] = currentState[11:8];
assign nextState[15:12] = currentState[15:12];

assign nextState[19:16] = currentState[31:28];
assign nextState[23:20] = currentState[19:16];
assign nextState[27:24] = currentState[23:20];
assign nextState[31:28] = currentState[27:24]; 

assign nextState[35:32] = currentState[43:40];
assign nextState[39:36] = currentState[47:44];
assign nextState[43:40] = currentState[35:32];
assign nextState[47:44] = currentState[39:36];

assign nextState[51:48] = currentState[55:52];
assign nextState[55:52] = currentState[59:56];
assign nextState[59:56] = currentState[63:60];
assign nextState[63:60] = currentState[51:48];
endmodule

module AddRoundKey(
    input  [63:0] currentState ,
    input  [63:0] roundKey     ,
    output [63:0] nextState    
);
assign nextState = currentState ^ roundKey;
endmodule
