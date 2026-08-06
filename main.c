/**
 ******************************************************************************
 * Project : STM32 Bare-Metal UART Transmit Driver
 * File    : main.c
 * Author  : Vasanthavel Jeeva Kumararaja
 * Date    : August 5, 2026
 *
 * Description:
 * Demonstrates bare-metal serial communication on the STM32F446RE using
 * USART2 in transmit mode. The UART peripheral is configured through
 * direct register manipulation without using the STM32 HAL UART APIs.
 *
 * GPIOA Pin 2 is configured for Alternate Function 7 (USART2_TX) to
 * transmit serial data through the on-board ST-LINK Virtual COM Port.
 * Characters and strings are transmitted to a host computer using custom
 * UART driver functions implemented with polling.
 *
 * Learning Objectives:
 * - Configure USART2 using bare-metal programming
 * - Enable GPIOA and USART2 peripheral clocks through the RCC
 * - Configure GPIOA Pin 2 for Alternate Function mode
 * - Select Alternate Function 7 (AF7) for USART2 transmission
 * - Configure the UART baud rate using the Baud Rate Register (BRR)
 * - Enable the USART and transmitter through Control Register 1 (CR1)
 * - Transmit individual characters using the Data Register (DR)
 * - Poll the TXE status flag before transmitting data
 * - Build reusable UART driver functions for character and string output
 * - Send serial data to a host computer through the ST-LINK Virtual COM Port
 *
 * Current Limitations:
 * - Supports transmit-only communication (TX)
 * - UART reception (RX) is not implemented
 * - Uses polling rather than transmit interrupts or DMA
 * - Baud rate is configured for a 16 MHz peripheral clock and 115200 bps
 * - Supports ASCII character transmission only
 *
 * GitHub:
 * github.com/jek327
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "uart.h"

int main(void)
{
	// initialize USART2
	UART2_Init();

	/* Infinite loop */
	while (1)
	{
		// Reads in a char value to C
		char c = UART2_ReadChar();

		/* '\r' is a carriage return which will move the cursor
		 	 to the beginning of the line **/
		if (c == '\r')
		{
			/* both of these brings cursor to the beginning and
			 to the next line */
			UART2_WriteChar('\r');
			UART2_WriteChar('\n');
		}
		else
		{
			// otherwise we transmit the char
			UART2_WriteChar(c);
		}

	}
}

/******************************************************************************
 * UART Serial Terminal (macOS)
 * ----------------------------------------------------------------------------
 * 1. Find the Virtual COM Port
 *
 *    ls /dev/cu.usb*
 *
 *    Example Output:
 *    /dev/cu.usbmodem143303
 *
 * ----------------------------------------------------------------------------
 * 2. Connect to the STM32 UART
 *
 *    screen /dev/cu.usbmodem143303 115200
 *
 *    UART Configuration:
 *      - Baud Rate : 115200
 *      - Data Bits : 8
 *      - Parity    : None
 *      - Stop Bits : 1
 *      - Flow Ctrl : None
 *
 * ----------------------------------------------------------------------------
 * 3. Exit Screen
 *
 *    Press:
 *
 *      Ctrl-A
 *      Ctrl-\
 *
 *    Then press:
 *
 *      y
 *
 * ----------------------------------------------------------------------------
 * 4. If "Sorry, could not find a PTY." Appears
 *
 *    List active screen sessions:
 *
 *      screen -ls
 *
 *    Terminate the old session:
 *
 *      screen -S <session-id> -X quit
 *
 *    Example:
 *
 *      screen -S 31395.ttys001.Jeevas-MBP -X quit
 *
 *    Reconnect:
 *
 *      screen /dev/cu.usbmodem143303 115200
 *
 * ----------------------------------------------------------------------------
 * UART Data Path
 *
 *      STM32 USART2
 *            │
 *            ▼
 *         PA2 (TX)
 *            │
 *            ▼
 *      ST-LINK Virtual COM Port
 *            │
 *            ▼
 *           USB
 *            │
 *            ▼
 *   macOS (/dev/cu.usbmodemXXXXX)
 *            │
 *            ▼
 *      Terminal (screen)
 *
 ******************************************************************************/
