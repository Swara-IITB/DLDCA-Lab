module getNextState (
    input [2:0] currentState,
    output [2:0] nextState
);
wire t1 = 1'b1;
wire t2 = currentState[0];
wire t3 = currentState[0] & currentState[1];

assign nextState[0] = currentState[0] ^ t1;
assign nextState[1] = currentState[1] ^ t2;
assign nextState[2] = currentState[2] ^ t3;
    
endmodule

module threeBitCounter (
    input clk,
    input reset,
    output reg [2:0] count  
);
wire [2:0] tmp;
getNextState gu(
            .currentState(count),
            .nextState(tmp)
        );
always @(posedge clk) begin
    if (reset) begin
        count <= 3'b000;
    end else begin   
        count <= tmp;
    end
end

endmodule

module counterToLights (
    input [2:0] count,
    output [2:0] rgb
);

assign rgb[0] = count[0] ^ ((~count[2]) | count[1]);
assign rgb[1] = ((~(count[0] & count[1])) & (~count[2])) | ((~count[1]) & (~count[0]));
assign rgb[2] = count[1] ^ ((~count[0]) | count[2]);
endmodule

module rgbLighter (
    input clk,
    input reset,
    output reg [2:0] rgb
);
wire [2:0] count;
wire [2:0] tmp;
threeBitCounter tu(
    .clk(clk),
    .reset(reset),
    .count(count)
);
counterToLights cu(
    .count(count),
    .rgb(tmp)
);

always @(*) begin
    
      rgb <= tmp;
    
end
endmodule
