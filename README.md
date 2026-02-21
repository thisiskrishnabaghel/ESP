# Calculator Using Memory-Mapped I/O (ATmega2560):----

## Overview
This project implements a **3-digit calculator** using the **ATmega2560 microcontroller**,
developed entirely with **register-level programming**. No Arduino libraries were used 
— all peripherals are controlled via **memory-mapped I/O registers**.

## Features
* Bare-metal register-level implementation
* GPIO configured through direct register access
* Matrix keypad scanning with software debouncing
* Basic arithmetic operations
* Multiplexed 4-digit 7-segment display
* Minimal pin usage via time-division multiplexing

## Working Principle
Keypad inputs are detected using row-column scanning and debouncing.
A simple processing logic interprets operands and operators.
Results are displayed using **fast time-division multiplexing**, leveraging persistence of vision.

## Key Concepts Demonstrated
Memory-Mapped I/O, Register-Level GPIO Control, Keypad Scanning, 
Debouncing, Embedded Timing, Display Multiplexing, Low-Level Firmware Design.

## Learning Outcomes
Hands-on experience with microcontroller internals,
low-level firmware development, and efficient hardware interfacing.
