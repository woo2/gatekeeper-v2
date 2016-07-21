The following is everything you need to know about settin up UART0 on the ATSAM4E16.

The Xplained Pro uses UART0, so that will be the focus of this page.

Memory Mapping:
- UART0: 0x400E0740 - 0x400E0740 (part of the System Controller)
- UART1: 0x40060600 - 0x40060800

UART generates event triggers directly connected to Peripheral DMA Controller (PDC) for data transfer w/o processor

UART0 is Instance ID 7 of the Peripheral Identifiers found in table 10-1, UART1 is 45
Both UARTs have an NVIC Interrupt and PMC Clock Control
UART0 uses URXD0 and UTXD0 (PA9 and PA10, respectively)

Section 36 focuses on the UART peripheral

36.4.3: Interrupt Sources
The UART interrupt line is connected to one of the interrupt sources of the Interrupt Controller.
Interrupt handling requires programming of the Interrupt Controller before configuring the UART.

36.5.1: Baudrate Generator
The Baudrate generator provides the bit period clock named baud rate clock to both the reveiver and the transmitter.

The baudrate clock is the peripheral clock divided by 16 times the clock divisor (CD) value written in the Baud
Rate Generator register (UART_BRGR). If UART_BRGR is set to 0, the baud rate clock is disabled and the UART remains
inactive. The maximum allowable baud rate is peripheral clock divided by 16.
The minimum allowable baud rate is peripheral clock divided by (16 * 65536).

36.5.2.3: Rx Ready
When a complete character is received, it is transferred to the Receive Holding Register (UART_RHR) and the
RXRDY status bit in the Status Register (UART_SR) is set. The bit RXRDY is automatically cleared when UART_RHR is read.



