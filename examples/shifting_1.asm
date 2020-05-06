mov A, a3h

mov B, A
add B, B
out B; (out = 46h)

mov C, A
mul C, 2
out C; (out = 46h)

mov D, A
shl D, 1
out D; (out = 46h)

mov A, 24h
mov B, A
shr B, 1
out B; (out = 12h)
mov C, A
sub C, B
out C; (out = 12h)