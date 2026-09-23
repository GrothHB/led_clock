========================================================================
Bare-Metal STM32 Digital Clock (5461BS)
========================================================================

DESCRIPTION:
	A from-scratch, 100% bare-metal digital clock firmware for the 
	STM32F411xC/E (ARM Cortex-M4) microcontroller. This project drives a 
	5461BS 4-digit 7-segment LED display without any external dependencies, 
	standard C libraries (-nostdlib), or vendor HALs (Hardware Abstraction 
	Layers). 

	It demonstrates low-level memory-mapped register manipulation, custom 
	interrupt handling, hardware-accelerated math, and power-efficient 
	state machine design.

HARDWARE LAYOUT & WIRING:
	Display: 5461BS (Common Anode 4-Digit 7-Segment LED)
	Custom logical-to-physical segment mapping is implemented to optimize 
	wire routing.

	Digit Multiplexing (Power Pins):
	- Digit 1: PA4
	- Digit 2: PA0
	- Digit 3: PA1
	- Digit 4: PB0

	Segment Control Pins (Grounding):
	- Segments: PB9, PB6, PA10, PB3, PB8, PB4, PB10, PA8 (DOT)

	Control Buttons (Active High with internal Pull-Downs):
	- Button 1 (PA9): Wake up / Toggle Power
	- Button 2 (PA7): Set Interval (Hours/Minutes)
	- Button 3 (PA6): Set Side (Left/Right display focus)
	- Button 4 (PA5): Add/Increment Time

FIRMWARE ARCHITECTURE:
	* Zero-Dependency Startup:
	  Custom `linker.ld` and `isr_vector.c` manage memory boundaries, 
	  initialize the .data and .bss sections, and map the interrupt vector 
	  table directly into Flash memory.

	* Interrupt-Driven Multiplexing:
	  The display uses high-frequency multiplexing driven by the SysTick 
	  timer (IRQ 15). The timer refreshes one digit per tick and manages 
	  the 350ms blinking logic during the time-setting mode.

	* Asynchronous UI Control (EXTI):
	  Buttons are mapped to the EXTI9_5 line (IRQ 39). The UI operates as a 
	  state machine (SLEEP, TURN_ON, REAL_TIME). The MCU utilizes the `wfi` 
	  (Wait For Interrupt) assembly instruction to suspend execution and 
	  save power between state changes.

	* Hardware-Accelerated Math:
	  To comply with `-nostdlib`, software division is replaced with direct 
	  ARM assembly optimizations. A custom `__aeabi_uidiv` and modulo 
	  function utilize the Cortex-M4 `udiv` and `mls` (Multiply and Subtract) 
	  instructions for O(1) time complexity during digit extraction.

	* Fast I/O Toggling:
	  GPIO manipulation bypasses ODR (Output Data Register) read-modify-write 
	  cycles by writing directly to the atomic BSRR (Bit Set/Reset Register). 
	  This guarantees zero-latency segment switching, eliminating display 
	  ghosting.

BUILD INSTRUCTIONS:
	Requires: `arm-none-eabi-gcc` toolchain.
	Run `make` to compile the bare-metal firmware.
	The output `firmware.bin` can be flashed directly to the STM32F411 
	memory starting at 0x08000000.
