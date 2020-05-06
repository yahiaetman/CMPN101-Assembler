mov A, a3h

mov B, 2
mov C, A
shl C, B
out C ; (out = 8ch)
mov D, A
shr D, B
out D ; (out = 28h)

mov B, 4
mov C, A
shl C, B
out C ; (out = 30h)
mov D, A
shr D, B
out D ; (out = 0ah)

mov B, 8
mov C, A
shl C, B
out C ; (out = 00h)
mov D, A
shr D, B
out D ; (out = 00h)

mov B, 10
mov C, A
shl C, B
out C ; (out = 00h)
mov D, A
shr D, B
out D ; (out = 00h)