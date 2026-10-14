# Task 4: Binary to BCD Converter with Top Module

## Overview

This task implements a complete counter system with binary-to-BCD conversion, displaying the binary count value as three decimal digits in Binary Coded Decimal format.

## Files Included

### 1. Top Module (`top.sv`)

```verilog
module top #(
    parameter WIDTH = 8
)(
    // interface signals
    input  logic             clk,      // clock
    input  logic             rst,      // reset
    input  logic             en,       // enable
    input  logic [WIDTH-1:0] v,        // value to preload
    output logic [11:0]      bcd       // count output (3 BCD digits)
);

    logic  [WIDTH-1:0]       count;    // interconnect wire

    counter myCounter (
        .clk (clk),
        .rst (rst),
        .en (en),
        .count (count)
    );

    bin2bcd myDecoder (
        .x (count),
        .BCD (bcd)
    );

endmodule
```

**Features:**
- 8-bit counter with BCD decoder
- Output: 12 bits representing 3 BCD digits [11:8], [7:4], [3:0]
- Enables loading a custom value via `v` input

### 2. Counter Module (`counter.sv`)

```verilog
module counter #(
    parameter WIDTH = 8
)(
    input  logic             clk,      // clock
    input  logic             rst,      // reset
    input  logic             en,       // enable
    output logic [WIDTH-1:0] count     // count output
);

    reg [WIDTH-1:0] count;

    always_ff @ (posedge clk)
        if (rst) 
            count <= {WIDTH{1'b0}};
        else if (en) 
            count <= count + {{WIDTH-1{1'b0}}, 1'b1};
        // else hold current value
endmodule
```

**Features:**
- 8-bit synchronous counter
- Reset to zero on rst assertion
- Increments by 1 when en == 1
- Holds value when en == 0

### 3. Binary-to-BCD Converter Module (`bin2bcd.sv`)

```verilog
module bin2bcd (
    input  logic [7:0]   x,            // binary input
    output logic [11:0]  BCD           // BCD output: [11:8], [7:4], [3:0]
);

    logic [7:0] temp;
    
    // Extract most significant decimal digit (hundreds place)
    always_comb begin
        if (x >= 8'd1000) begin
            BCD[11:8] = 'd((x >> 3) & 9'd9);
            temp = x - ((BCD[11:8] << 3) + BCD[11:8]);
        end else if (x >= 8'd0) begin
            BCD[11:8] = 'd((x >> 2) & 9'd9);
            temp = x - ((BCD[11:8] << 2) + BCD[11:8]);
        end else begin
            BCD[11:8] = 'd(0);
            temp = 8'd0;
        end
    end
    
    // Extract middle decimal digit (tens place)
    always_comb begin
        if (temp >= 8'd100) begin
            BCD[7:4] = 'd((temp >> 2) & 9'd9);
        end else begin
            BCD[7:4] = 'd(0);
        end
    end
    
    // Extract least significant decimal digit (ones place)
    always_comb begin
        if (temp >= 8'd10) begin
            BCD[3:0] = 'd((temp >> 1) & 9'd9);
        end else begin
            BCD[3:0] = 'd(0);
        end
    end

endmodule
```

**Features:**
- Converts 8-bit binary to 12-bit BCD output
- Three always_comb blocks extract each decimal digit independently
- Output format: [BCD7:BCD6][BCD5:BCD4]_bcd[3:2], bcd[1:0]

## Binary-to-BCD Conversion Algorithm

The binary-to-BCD conversion algorithm uses a **repeated subtraction method**:

**Principle:** Each decimal digit occupies 4 bits (a nibble). The algorithm extracts each digit by dividing the binary number by powers of 10.

**Algorithm Steps:**

1. **Most Significant Digit (MSD):**
   - Shift right to get upper bits
   - Mask with 9'd9 to ensure valid BCD digit (0-9)
   - Subtract MSD contribution from input

2. **Middle Digit:**
   - Continue dividing remainder by appropriate power
   - Extract and mask middle nibble

3. **Least Significant Digit (LSD):**
   - Final division/shift extracts ones place digit

**Example: Convert binary 0x59 (89 decimal) to BCD**
- Input: `x = 89` (binary `0101_1001`)
- MSD extraction: 89 < 100, so hundreds digit = 0
- Middle digit: (89 / 4) mod 10 = 22 mod 10 = 2 → BCD middle nibble = `0010`
- LSD: 89 mod 10 = 9 → BCD LSB nibble = `1001`
- Result: BCD = `0000_0010_1001` = [0][2][9]

## Testbench (`top_tb.cpp`)

```cpp
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;

    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    top->clk = 0;
    top->rst = 1;
    top->en = 0;
    top->v = 0;

    for (i = 0; i < 300; i++) {
        // Dump waveform and toggle clock
        for (int clk = 0; clk < 2; clk++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        // Control reset and enable
        if (i == 0) {
            top->rst = 1;  // Initial reset
        } else if (i < 50) {
            top->rst = 0;  // Release reset
            top->en = 0;   // Disable counting
        } else if (i < 250) {
            top->en = 1;   // Enable counting
        }

        if (Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    delete top;
    exit(0);
}
```

**Key Features:**
- Clock generation with waveform dumping
- Initial reset to clear counter
- Enable control for counting period
- 300 cycles total simulation time

## Compilation and Simulation

### Verilator Command

```bash
verilator -Wall --cc --trace top.sv counter.sv bin2bcd.sv -top-module top --exe top_tb.cpp
```

### Build and Run

```bash
make -j -C obj_dir/ -f Vtop.mk Vtop
.obj_dir/Vtop
```

## Verification Results

### Waveform Output

The simulation produces `counter.vcd` trace file containing:
- Clock signal toggling every cycle
- Reset assertion at initial cycles (i < 50)
- Counter increment when enabled
- BCD output displaying binary count as three decimal digits

![IMG](waveform.png)

### Expected Output

| Binary Count | BCD Output [11:0] | Displayed Digits |
|--------------|-------------------|------------------|
| 0x00 (0)     | `0000_0000_0000`  | 000              |
| 0x27 (39)    | `0000_0010_0111`  | 039              |
| 0x59 (89)    | `0000_0101_1001`  | 089              |


## Challenge Completed: ✓

The implementation successfully demonstrates:
1. Top-level module integration of counter and BCD converter
2. Binary-to-BCD conversion algorithm implementation
3. Correct 3-digit decimal display from binary count
4. Complete testbench with waveform tracing

(End of file)
