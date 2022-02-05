// Full Adder/Subtractor template
module fas (
    input logic a,           // Input bit a
    input logic b,           // Input bit b
    input logic cin,         // Carry in
    input logic a_ns,        // A_nS (add/not subtract) control
    output logic s,          // Output S
    output logic cout        // Carry out
);

// Put your code here
// ------------------
logic out1,out2,out3,out4,out5,out6,out7,out8,out9,out10,out11,out12,out13,out14,out15,out16;
NOT #(.Tpdlh(1),.Tpdhl(8) ) not1 (.Z(out1),.A(a));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not2 (.Z(out7),.A(out6));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not3 (.Z(out4),.A(out3));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not4 (.Z(out5),.A(out2));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not5 (.Z(out8),.A(b));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not6 (.Z(out9),.A(cin));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not7 (.Z(out13),.A(out12));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not8 (.Z(out11),.A(out10));
NOT #(.Tpdlh(1),.Tpdhl(8) ) not9 (.Z(out16),.A(out15));

OR2 #(.Tpdlh(2),.Tpdhl(8) ) or1 (.Z(out6),.A(a),.B(out5));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or2 (.Z(s),.A(out4),.B(out7));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or3 (.Z(out3),.A(out1),.B(out2));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or4 (.Z(out10),.A(out8),.B(out9));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or5 (.Z(cout),.A(out11),.B(out16));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or6 (.Z(out15),.A(out14),.B(out13));
OR2 #(.Tpdlh(2),.Tpdhl(8) ) or7 (.Z(out12),.A(cin),.B(b));

XOR2 #(.Tpdlh(3),.Tpdhl(1) ) xor1 (.Z(out2),.A(cin),.B(b));
XOR2 #(.Tpdlh(3),.Tpdhl(1) ) xor2 (.Z(out14),.A(a_ns),.B(a));
// End of your code

endmodule
