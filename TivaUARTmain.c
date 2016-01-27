//////////////////////////////////////////////////////////////////////////////
//  This program demonstrates the use of the UART feature on the Tiva Stellaris
//  Launchpad.  The micro-controller will respond to buttons in a GUI UART
//  application.   This program is a baseline for many UART features.  The GUI
//  UART application is based on Qt C++ and displays buttons for the LEDs on the
//  micro-controller and will be available on GITHUB.
//  This GUI will become the baseline for many GUI examples.
//  The data sheet for the Tiva C ARM Cortex M4 is lm4f120h5qr.pdf
//////////////////////////////////////////////////////////////////////////////

#include <lm4f120h5qr.h>

char readChar(void);
void printChar(char c);
void printString(char * string);



int main()
{
  char c;
//  To enable and initialize the UART, the following steps are necessary:
//1. Enable the UART module using the RCGCUART register (see page 314).
  SYSCTL->RCGCUART |= 1<<0;  // for UART0

//2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 310).
  SYSCTL->RCGCGPIO |= 1<<0;  // for GPIO Port A


//To find out which GPIO port to enable, refer to Table 21-5 on page 1134.

//3. Set the GPIO AFSEL bits for the appropriate pins (see page 624). To determine which GPIOs to
//configure, see Table 21-4 on page 1130.
  GPIOA->AFSEL = (1<<1)|(1<<0);


//4. Configure the GPIO current level and/or slew rate as specified for the mode selected (see
//page 626 and page 634).
    GPIOA->PCTL = (1<<0)|(1<<4);


    // GPIO Port Digital Enable
    GPIOA->DEN = (1<<0)|(1<<1);

 /////////////////////////////////////////////////////////////////////////

    // This section discusses the steps that are required to use a UART module. For this example, the
    //UART clock is assumed to be 20 MHz, and the desired UART configuration is:
    //¦ 115200 baud rate
    //¦ Data length of 8 bits
    //¦ One stop bit
    //¦ No parity
    //¦ FIFOs disabled
    //¦ No interrupts
    // BDR = 20,000,000 / (16 * 115,2000) = 10.8507

    // For this example, 16 MHz will be used
    // BDR = 16,000,000 / (16 * 9600) = 104.166666
    // UARTFBD(DIVFRAC) = integer(0.1666667 * 64 + 0.5) = 11

    // With the BRD values in hand...UART configuration is as follows:
    // Disable the UART by clearing the UARTEN bit in the UARTCTL register
    UART0->CTL &= (1<<0);

    // Get the integer portion of the BRD in the UARTIBRD register
    UART0->IBRD = 104;

    // Get the fraction portion of the BRD in the UARTFBRD register
    UART0->FBRD = 11;

    // Desired parameters in the UART Line Control register
    UART0->LCRH = (0x3<<5);   // for 8 bits

    // Clock Source for UART in UART Clock configuration register
    UART0->CC = 0x0;

    /////////////////////////////////////////////////////////////////////////

    // Reenable the UART by setting the UARTEN bit in the UARTCTL register
    // Also Enable the transmit and receive bits in the UARTCTL
    UART0->CTL = (1<<0)|(1<<8)|(1<<9);

    ////////////////////////////////////////////////////////////////////////

    // Configure LED Pins
    SYSCTL->RCGCGPIO |= (1<<5);                 // Enable clock on Port F
    GPIOF->DIR = (1<<1)|(1<<2)|(1<<3);          // LED pins are outputs
    GPIOF->DEN = (1<<1)|(1<<2)|(1<<3);          // Enable digital functions on pins
    GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));    // Turn off LEDs

    ///////////////////////////////////////////////////////////////////////
    // Configure LCD Pins
    // GPIO Port D for LCD Command Direction - output


    while(1)
    {
     // The following functions are for use with Tera Term or Putty to be displayed on
     // Tera Term or Putty must be turned on and setup to match the UART Settings above
     // printString("        Connected!");
     // printString("Enter \"r for red\", \"g for green\", or \"b for blue\":\n\r");

     c = readChar();
     // printChar(c);
     // printString("\n\r");
     switch(c)
      {
      case 'r':
        GPIOF->DATA = 1<<1;   // Red LED
        break;
      case 'b':
        GPIOF->DATA = 1<<2;   // Blue LED
        break;
      case 'g':
        GPIOF->DATA = 1<<3;   // Green LED
        break;
      case 'o':
	GPIOF->DATA &= ~((1<<1)|(1<<2)|(1<<3));  // All LEDs are off
	break;
      default:
        break;
      }
    }
}

char readChar(void)
{
  char c;
  while((UART0->FR & (1<<4)) != 0);
  c = UART0->DR;
  return c;
}

void printChar(char c)
{
  while((UART0->FR & (1<<5)) != 0);
  UART0->DR = c;
}

void printString(char * string)
{
  while(*string)
  {
    printChar(*(string++));
  }
}



