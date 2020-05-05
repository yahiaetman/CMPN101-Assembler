#pragma once
const char* GRAMMAR = R"(
code <- line ~eol code / line

line <- instruction / ~empty_line

empty_line <- space* comment?

instruction <- binary_instruction / unary_instruction

binary_instruction <- binary_op ~space+ reg ~space* "," ~space* operand ~space* ~comment?
unary_instruction <- unary_op ~space+ reg ~space* ~comment?


binary_op <- "mov"i / "add"i / "sub"i / "mul"i / "imul"i / "and"i / "or"i / "xor"i / "shl"i / "shr"i
unary_op <- "out"i / "neg"i / "not"i

operand <- num / reg
reg <- [A-D] / [a-d]

num <- neg?(bin / oct / hex / dec)
neg <- "-"
hex <- <([0-9]/[a-f]/[A-F])+>"h"
oct <- <[0-7]+>"o"
bin <- <[0-1]+>"b"
dec <- <[0-9]+>("d"?)


space <- ' ' / '\t'
comment <- ";" (!eol .)*
eol <- '\r\n' / '\n' / '\r'
)";