#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
	int i;

	Verilated::commandArgs(argc, argv);
	Vcounter* top = new Vcounter;
	Verilated::traceEverOn(true);
	VerilatedVcdC* tfp = new VerilatedVcdC;
	top->trace(tfp, 99);
	tfp->open("counter.vcd");

	if (vbdOpen() != 1) return(-1);
	vbdHeader("Lab 1: Counter");
        vbdSetMode(1);
        
	top->clk = 1;
	top->rst = 1;
	top->ld = 0;

	for (i = 0; i < 300; i++) {
		// 1. ALWAYS dump time, toggle the clock, and evaluate the model
		for (int clk = 0; clk < 2; clk++) {
			tfp->dump(2*i + clk);
			top->clk = !top->clk;
			top->eval();
		}

		vbdHex(4, (int(top->count) >> 16) & 0xF);
		vbdHex(3, (int(top->count) >> 8) & 0xF);
		vbdHex(2, (int(top->count) >> 4) & 0xF);
		vbdHex(1, (int(top->count)) & 0xF);
		vbdCycle(i+1);

		// 2. Change the reset stimulus so it doesn't interrupt us at i==15
		top->rst = (i < 2) | (i == 15);
		top->ld = vbdFlag(); // decides where to reset value to what ever is next line. 
		top->v = vbdValue(); // sets new value
		if (Verilated::gotFinish()) exit(0);
	}
	vbdClose();
	tfp->close();
	exit(0);
}
