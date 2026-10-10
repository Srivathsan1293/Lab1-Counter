#include <string>
#include "vbuddy.cpp"
#include <iostream>


int main() {
    std::cout << "Attempting to open Vbuddy..." << std::endl;
    std::cout << "(If it hangs here, the serial connection is the issue)" << std::endl;

    // Attempt to open the connection using the port in vbuddy.cfg
    if (vbdOpen() != 1) { // Returns 1 on success
        std::cout << "Failed to connect to Vbuddy. Check vbuddy.cfg and permissions." << std::endl;
        return -1;
    }

    std::cout << "Successfully connected! Sending test sequence..." << std::endl;

    // Send a header to the TFT screen[cite: 4]
    vbdHeader("Hardware Test");

    // Send a static number (1234) to the 7-segment display[cite: 4]
    vbdHex(4, 1);
    vbdHex(3, 2);
    vbdHex(2, 3);
    vbdHex(1, 4);

    std::cout << "Test data sent. Check the Vbuddy screen." << std::endl;
    std::cout << "Press ENTER to close the connection..." << std::endl;
    std::cin.get();

    // Clean up and close[cite: 4]
    vbdClose();
    std::cout << "Connection closed." << std::endl;

    return 0;
}
