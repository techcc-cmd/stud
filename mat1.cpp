#include <lpc214x.h>

#define ROW_PORT IO1PIN   // Row control (connected to P1.16 - P1.23)
#define COL_PORT IO0PIN   // Column control (connected to P0.0 - P0.7)

// Simple delay function
void delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1000; j++);
}

// Function to display a pattern on the 8x8 LED matrix
void display_pattern(unsigned char pattern[8]) {
    unsigned char row;
    for (row = 0; row < 8; row++) {
        ROW_PORT = (1 << (row + 16));  // Set row HIGH (P1.16 - P1.23)
        COL_PORT = ~pattern[row];      // Set column LOW to turn ON LEDs
        delay(10);                     // Delay for persistence of vision
        COL_PORT = 0xFF;               // Turn OFF all columns
    }
}

int main() {
    // Pattern for the number "2" on an 8×8 common cathode LED matrix
    unsigned char pattern[8] = {
        0x7E, // Row 0:  ******
        0xC3, // Row 1: **    **
        0x03, // Row 2:       **
        0x06, // Row 3:      **
        0x0C, // Row 4:     **
        0x18, // Row 5:    **
        0x30, // Row 6:   **
        0xFF  // Row 7: ********
    };
    
    // Configure GPIO Pins
    PINSEL0 = 0x00000000;  // Set P0.0 to P0.7 as GPIO
    PINSEL1 = 0x00000000;  // Set P1.16 to P1.23 as GPIO
    IO0DIR = 0xFF;         // Set P0.0 to P0.7 as output (columns)
    IO1DIR |= (0xFF << 16); // Set P1.16 to P1.23 as output (rows)

    // Infinite loop to continuously display the pattern
    while (1) {
        display_pattern(pattern);
    }

    return 0;
}
