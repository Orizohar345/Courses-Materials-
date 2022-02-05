// 32X32 Multiplier arithmetic unit template
module mult32x32_arith (
    input logic clk,             // Clock
    input logic reset,           // Reset
    input logic [31:0] a,        // Input a
    input logic [31:0] b,        // Input b
    input logic [1:0] a_sel,     // Select one byte from A
    input logic b_sel,           // Select one 2-byte word from B
    input logic [2:0] shift_sel, // Select output from shifters
    input logic upd_prod,        // Update the product register
    input logic clr_prod,        // Clear the product register
    output logic [63:0] product  // Miltiplication product
);
// Put your code here
// ------------------

logic [15:0] mux_2_1_out;
logic[7:0] mux_4_1_out ;
logic [23:0] mult_16x8_out ;
logic [63:0] shifted_mult; 
logic [63:0] bit_adder_out ; 

  always_comb begin
case (a_sel) // mux4->1
            2'd0: mux_4_1_out = a[7:0];
            2'd1: mux_4_1_out = a[15:8];
            2'd2: mux_4_1_out = a[23:16];
			2'd3: mux_4_1_out = a[31:24];
endcase
end
 always_comb begin
case (b_sel) // mux2->1
            1'd0: mux_2_1_out = b[15:0];
            1'd1: mux_2_1_out = b[31:16];

endcase
end

always_comb begin 
mult_16x8_out = mux_4_1_out * mux_2_1_out ;
end

 always_comb begin // Shifting the result of the mux multiply 
 shifted_mult = {64{1'b0}};
case (shift_sel)
3'b000 :  shifted_mult = { {40{1'b0}} ,mult_16x8_out[23:0] }; 
3'b001 :  shifted_mult = { {32{1'b0}} ,mult_16x8_out[23:0],{8{1'b0}} } ;
3'b010 :  shifted_mult = { {24{1'b0} } ,mult_16x8_out[23:0],{16{1'b0}} };
3'b011:  shifted_mult = { {16{1'b0}} ,mult_16x8_out[23:0],{24{1'b0}} } ;
3'b100 :  shifted_mult = { {8{1'b0}} , mult_16x8_out[23:0] , {32{1'b0}} } ;
3'b101 :  shifted_mult = { mult_16x8_out[23:0] ,{40{1'b0}} } ;
endcase
end 


always_comb begin // The add operation 
bit_adder_out = product + shifted_mult ;
end 

    always_ff @(posedge clk, posedge reset) begin // Shifter register 

        if (reset == 1'b1) begin
            product <= {64{1'b0}};
        end
        
        else begin 
        if (clr_prod == 1'b1) begin
            product<= {64{1'b0}};
            end
           
           else if (upd_prod == 1'b1) 
           begin
			product <= bit_adder_out ;
			end
end			
end

// End of your code

endmodule
