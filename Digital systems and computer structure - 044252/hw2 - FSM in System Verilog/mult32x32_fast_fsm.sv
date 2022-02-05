// 32X32 Multiplier FSM
module mult32x32_fast_fsm (
    input logic clk,              // Clock
    input logic reset,            // Reset
    input logic start,            // Start signal
    input logic a_msb_is_0,       // Indicates MSB of operand A is 0
    input logic b_msw_is_0,       // Indicates MSW of operand B is 0
    output logic busy,            // Multiplier busy indication
    output logic [1:0] a_sel,     // Select one byte from A
    output logic b_sel,           // Select one 2-byte word from B
    output logic [2:0] shift_sel, // Select output from shifters
    output logic upd_prod,        // Update the product register
    output logic clr_prod         // Clear the product register
);

// Put your code here
// ------------------

typedef enum {idle,mlti1,mlti2,mlti3,mlti4,mlti5,mlti6,mlti7,mlti8}  mlti_sm;
mlti_sm current_state;
mlti_sm next_state ;
always_ff @(posedge clk,posedge reset) begin 
if ( reset == 1'b1 ) begin
current_state <= idle ;
end 
else begin 
current_state <= next_state;
end 
end
always_comb begin 
next_state=current_state; 
 clr_prod = 1'b0;
 busy =1'b1;
 upd_prod= 1'b1;
 a_sel = 2'b00;
 b_sel=1'b0;
 shift_sel= 3'b000;
 case (current_state)
 idle : if (start == 1'b1) begin 
 next_state = mlti1;
 upd_prod = 1'b0;
 busy=1'b0;
 clr_prod=1'b1;
 end
else begin  
busy =1'b0;
upd_prod=1'b0;
end
 mlti1: begin
 next_state = mlti2;
 end 
  mlti2: begin
  next_state = mlti3;
 a_sel = 2'b01;
 shift_sel=3'b001;
 end 
   mlti3: begin
   if ( a_msb_is_0 == 1'b1 && b_msw_is_0 == 1'b1 ) begin 
   next_state = idle ;
   a_sel = 2'b10;
   shift_sel = 3'b010;
   busy = 1'b1 ;
   end 
   else begin 
   next_state = mlti4 ;
 a_sel = 2'b10;
 shift_sel=3'b010;
 end 
 end
    mlti4: begin
  if ( a_msb_is_0 == 1'b0 && b_msw_is_0 == 1'b1 ) begin 
   next_state = idle ;
 a_sel = 2'b11;
 shift_sel=3'b011;
 busy = 1'b1;
 end 
 else if  (a_msb_is_0 == 1'b1 && b_msw_is_0 == 1'b0 ) begin 
 next_state = mlti7 ;
  a_sel = 2'b11;
  b_sel= 1'b1;
 shift_sel=3'b001;
 end
 else begin 
  next_state = mlti5;
 a_sel = 2'b11;
 shift_sel=3'b011;
 end
 end
     mlti5: begin
     next_state = mlti6 ;
     a_sel = 2'b11;
 b_sel=1'b1;
 shift_sel=3'b101;
 end 
      mlti6: begin
       next_state = mlti7 ;
 a_sel = 2'b01;
 b_sel=1'b1;
 shift_sel=3'b011;
 end
       mlti7: begin
        next_state = mlti8 ;
 a_sel = 2'b10;
 b_sel=1'b1;
 shift_sel=3'b100;
 end
        mlti8: begin
         next_state = idle ;
 b_sel=1'b1;
 shift_sel=3'b010;
 busy = 1'b1;
 end
endcase 
end

// End of your code

endmodule
