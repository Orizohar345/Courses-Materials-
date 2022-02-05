// 2->1 multiplexer template
module mux2 (
    input logic d0,          // Data input 0
    input logic d1,          // Data input 1
    input logic sel,         // Select input
    output logic z           // Output
);

// Put your code here
// ------------------
logic out1,out2,out3,out4,out5,out6,out7;
NOT #(.Tpdlh(1),.Tpdhl(8) ) not1 (.Z(out1),.A(d0));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not2 (.Z(out7),.A(out6));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not3 (.Z(out5),.A(out3));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not4 (.Z(out2),.A(d1));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not5 (.Z(out4),.A(sel));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or1 (.Z(out6),.A(out1),.B(sel));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or2 (.Z(z),.A(out5),.B(out7));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or3 (.Z(out3),.A(out4),.B(out2));
// End of your code

endmodule
