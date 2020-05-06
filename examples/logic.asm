mov A, 00110101b
out A ; (out = 35h)

mov B, A
and B, f0h
shr B, 4
mov C, A
and C, 0fh
shl c, 4
or B, C
out B ; (out = 53h)

mov D, A
and D, B
out D ; (out = 11h)

mov D, A
or D, B
out D ; (out = 77h)

mov D, A
xor D, B
out D ; (out = 66h)

mov D, A
not D
out D ; (out = cah)

mov D, B
not D
out D ; (out = ach)