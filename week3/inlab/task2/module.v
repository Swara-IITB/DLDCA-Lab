module ShiftRows(
    input  [63:0] currentState ,
    output [63:0] nextState    
);
    // Fill shift row logic here
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