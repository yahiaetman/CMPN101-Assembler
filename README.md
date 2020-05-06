# Assembler for a Simplified Processor Module

This is a utility tool made for the project of CMPN101 Course in Spring 2020.

You can download the project as an executable binary for `Win64` from the [Releases Section](./releases/latest).

## Usage
To assemble a file, use the assembler as follows:

`.\assembler.exe code.asm -o binary.hex`

The program will also simulate the code and print the simulation result.

The code has the following syntax rules:

* You can write binary instructions or unary instructions.
* Binary instructions are in the format: `<binary_op> <register>, <operand>`
* `<binary_op>` can be: `mov`, `add`, `sub`, `mul`, `imul`, `and`, `or`, `xor`, `shl`, `shr`.
* `<register>` can be: `A`, `B`, `C`, `D`.
* `<operand>` can be either a `<register>` or a `<value>`.
* `<value>` can be any __signed__ 8-bit number.
* `<value>` can have a postfix to denote its base: `d` for decimal, `b` for binary, `o` for octal, `h` for hexadecimal. If the postfix is omitted, the base will default to decimal.
* Unary instructions are in the format: `<unary_op> <register>`
* `<unary_op>` can be: `out`, `neg`, `not`.
* Any text preceded by `;` is considered a comment till the end of the line.
* `<binary_op>`, `<unary_op>` and `<register>` are case insensitive.

The following is an example of a valid code:
```
; this is a comment
Mov A, 3
Add A, -2h
Mov B, 0100b
Mov C, A
Sub C, B
Mul A, B
Out A
```

The simulation result of the assembler will be:
```
Simulation Result:
01: mov A, 03h          (code: 0103)    =>      A=03,   B=00,   C=00,   D=00,   OUT=00
02: add A, feh          (code: 41fe)    =>      A=01,   B=00,   C=00,   D=00,   OUT=00
03: mov B, 04h          (code: 0304)    =>      A=01,   B=04,   C=00,   D=00,   OUT=00
04: mov C, A            (code: 0400)    =>      A=01,   B=04,   C=01,   D=00,   OUT=00
05: sub C, B            (code: 4c01)    =>      A=01,   B=04,   C=fd,   D=00,   OUT=00
06: mul A, B            (code: 6001)    =>      A=04,   B=04,   C=fd,   D=00,   OUT=00
07: out A               (code: 0800)    =>      A=04,   B=04,   C=fd,   D=00,   OUT=04
```

and the binary file will contain:
```
v2.0 raw
103
41fe
304
400
4c01
6001
800
```

The binary file can loaded into a ROM in [Logisim](http://www.cburch.com/logisim/).

## Build

The project was built under `Windows 10 64-bit` using `cmake 3.17.0-rc2` and `GCC 8.1.0`. It was not tested for any other platform, compiler or version of `cmake`.

## License
The project is available as open source under the terms of the [MIT License](LICENSE).