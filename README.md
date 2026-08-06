# STM32 Bare-Metal UART Echo Driver

A bare-metal UART (USART2) driver for the STM32F446RE that demonstrates full-duplex serial communication using direct register manipulation without relying on the STM32 HAL UART APIs.

The project configures **USART2** for **115200 baud** communication and implements reusable transmit and receive driver functions. Incoming characters received from a host computer are immediately echoed back over the UART interface, demonstrating bidirectional communication.

---

## Features

- Bare-metal USART2 initialization
- Polling-based UART transmission
- Polling-based UART reception
- Character transmit function
- Character receive function
- String transmit function
- Full-duplex UART communication
- Real-time serial echo application
- GPIO Alternate Function configuration
- Direct register manipulation using CMSIS

---

## Hardware

- STM32 Nucleo-F446RE
- ARM Cortex-M4
- ST-LINK Virtual COM Port
- USB connection to host computer

---

## Software

- STM32CubeIDE
- CMSIS
- Embedded C
- macOS Terminal (`screen`) for serial communication

---

## Project Structure

```
Core/
│
├── Inc/
│   ├── uart.h
│   └── main.h
│
├── Src/
│   ├── uart.c
│   └── main.c
```

---

## How It Works

### Initialization

1. Enable the GPIOA peripheral clock.
2. Enable the USART2 peripheral clock.
3. Configure PA2 as USART2_TX.
4. Configure PA3 as USART2_RX.
5. Select Alternate Function 7 (AF7).
6. Configure the baud rate using the BRR register.
7. Enable USART2.
8. Enable the transmitter.
9. Enable the receiver.

---

### Transmitting

The UART driver:

- Waits until the TXE (Transmit Data Register Empty) flag is set.
- Writes one character to the USART Data Register.
- Repeats the process until an entire string has been transmitted.

---

### Receiving

The UART driver:

- Waits until the RXNE (Receive Data Register Not Empty) flag is set.
- Reads one character from the USART Data Register.
- Returns the received character to the application.

---

### Echo Application

The main application continuously:

1. Waits for a character from the PC.
2. Receives the character through USART2.
3. Immediately transmits the same character back.
4. Displays the echoed character in the terminal.

```
Keyboard
    │
    ▼
Mac Terminal
    │
    ▼
USB
    │
    ▼
ST-LINK Virtual COM Port
    │
    ▼
USART2 RX (PA3)
    │
    ▼
STM32
    │
    ▼
USART2 TX (PA2)
    │
    ▼
ST-LINK Virtual COM Port
    │
    ▼
Mac Terminal
```

---

## Registers Used

| Register | Purpose |
|----------|---------|
| RCC->AHB1ENR | Enable GPIOA clock |
| RCC->APB1ENR | Enable USART2 clock |
| GPIOA->MODER | Configure PA2 and PA3 as Alternate Function |
| GPIOA->AFR[0] | Select AF7 for USART2 |
| USART2->BRR | Configure baud rate |
| USART2->CR1 | Enable USART, transmitter, and receiver |
| USART2->SR | Monitor TXE and RXNE status flags |
| USART2->DR | Read and write UART data |

---

## UART Driver API

### Initialize UART

```c
UART2_Init();
```

### Transmit a Character

```c
UART2_WriteChar('A');
```

### Transmit a String

```c
UART2_WriteString("Hello World!\r\n");
```

### Receive a Character

```c
char c = UART2_ReadChar();
```

---

## Example Application

```c
while (1)
{
    char c = UART2_ReadChar();
    UART2_WriteChar(c);
}
```

Typing:

```
Hello STM32
```

Results in:

```
Hello STM32
```

The displayed characters are echoed back by the STM32 after being received over USART2.

---

## macOS Serial Terminal

Locate the Virtual COM Port:

```bash
ls /dev/cu.usb*
```

Example:

```text
/dev/cu.usbmodem143303
```

Connect to the STM32:

```bash
screen /dev/cu.usbmodem143303 115200
```

UART Configuration:

- Baud Rate: **115200**
- Data Bits: **8**
- Parity: **None**
- Stop Bits: **1**
- Flow Control: **None**

---

### Exit `screen`

```
Ctrl-A
Ctrl-\
y
```

---

### If "Sorry, could not find a PTY." Appears

List active sessions:

```bash
screen -ls
```

Terminate a detached session:

```bash
screen -S <session-id> -X quit
```

Reconnect:

```bash
screen /dev/cu.usbmodem143303 115200
```

---

## Concepts Learned

- UART communication fundamentals
- Full-duplex serial communication
- USART peripheral architecture
- GPIO Alternate Function configuration
- Alternate Function Registers (AFR)
- Baud rate calculation using BRR
- Polling-based peripheral communication
- TXE (Transmit Data Register Empty)
- RXNE (Receive Data Register Not Empty)
- Character and string transmission
- Character reception
- Pointer traversal
- Driver modularization
- Embedded serial debugging

---

## Current Limitations

- Polling-based implementation
- No interrupt-driven UART communication
- No DMA support
- Fixed baud rate (115200 bps)
- Configured for a 16 MHz peripheral clock
- No line editing or command parser

---

## Future Improvements

- Interrupt-driven UART communication
- DMA-based UART transfers
- Configurable baud rates
- UART command-line interface (CLI)
- Ring buffer implementation
- `printf()` redirection
- Command interpreter for embedded debugging

---

![Demo](uart_rx.gif)

---

## Author

**Vasanthavel Jeeva Kumararaja**

GitHub: https://github.com/jek327
