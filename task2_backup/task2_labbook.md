# Task 2: Counter Design and Vbuddy Integration

## 1. Vbuddy Information

![Vbuddy Interface](../../images/vbuddy.jpg)

Vbuddy provides a hardware interface for Testbench applications with the following functions:

### Display Functions
- `vbdOpen()` - Opens Vbuddy device (returns 1 on success)
- `vbdClose()` - Closes the opened Vbuddy device
- `vbdClear()` - Clears TFT screen to black
- `vbdHex(digit, v)` - Displays 4-bit binary value on 7-segment display (digit 1-5: right to left)

### Graphical Functions
- `vbdPlot(y, min, max)` - Plots scaled y value at next x coordinate (auto-clears at x=240)
- `vbdHeader(header)` - Writes header text at top of TFT (center justified)
- `vbdCycle(cycle)` - Reports cycle count on bottom right of TFT

### Input/Output Functions
- `vbdFlag()` - Returns current Flag value
- `vbdSetMode(mode)` - Sets Flag mode: 0=toggle, 1=one-shot
- `vbdValue()` - Returns parameter value from rotary encoder
- `vbdInitAnalogOut(Nsamp)` - Initializes DAC output buffer with N samples
- `vbdOutputSample(sample)` - Outputs a sample to Vbuddy DAC buffer
- `vbdAoutON()` / `vbdAoutOFF()` - Turns analog output ON/OFF

### Audio Functions
- `vbdInitMicIn(Nsamp)` - Initializes microphone buffer for N samples
- `vbdMicValue()` - Gets next sample from microphone buffer

### Keyboard Functions
- `vbdGetkey()` - Returns ASCII code of pressed key (0 if none, non-blocking)

### Timing Functions
- `vbdInitWatch()` - Initializes internal stop watch in msec
- `vbdElapsed()` - Returns elapsed time in msec since last vbdInitWatch() call

![Vbuddy Functions](../../images/vbd_function.jpg)

## 2. Counter Module (counter.sv)

```verilog
module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk,     // clock
    input logic rst,     // reset
    input logic en,      // counter enable
    output logic [WIDTH-1:0] count
);

    always_ff @(posedge clk) begin
        if (rst) 
            count <= {WIDTH{1'b0}};
        else begin
            if (en) 
                count <= count + {{WIDTH-1{1'b0}}, 1'b1};
            else 
                count <= count - {{WIDTH-1{1'b0}}, 1'b1};
        end 
    end 

endmodule
```

## 3. Testbench Code (counter_tb.cpp)

```cpp
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

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

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
        top->en = vbdFlag();
        if (Verilated::gotFinish()) exit(0);
    }
    vbdClose();
    tfp->close();
    exit(0);
}
```


**Seven Segment Display Output with Directional Counting**
![[PXL_20261010_214143958.MP.jpg]]

**Graphical Plot**
![[PXL_20261010_214314474.MP.jpg]]

![Challenge Completed](../../images/counter_inners.jpg)

**Graphical Plot Output**
![[PXL_20261010_214314474.MP.jpg]]

**Verilator Simulation Output**
![Verilator Output](../../images/verilator_output.jpg)

## 5. Setting Up Vbuddy to Show Output

### Configure Vbuddy

Edit `vbuddy.cfg` to specify the correct port path for your Vbuddy device, then compile and run:

![Vbuddy Setup](../../images/vbuddy.jpg)
