
heading: counter.sv with asyncronous reset

insert code from counter.sv here

heading: counter_tb.cpp with counter pausing

insert code for counter_tb.cpp

write a quick template that can used to set up a C++ testbench following the template of counter_tb.cpp

also list the following commands used to generate simulation

verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

make -j -C obj_dir/ -f Vcounter.mk Vcounter

obj_dir/Vcounter

paste image showing the counter working on gtkwave images found directory both intial_waves.png and end_of_counter.png directly in md file. 

