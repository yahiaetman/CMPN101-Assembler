mov a, 9ah
mov b, a
mov c, b
mov d, a

out d ; (out = 9ah)

mov d, c7h
mov c, d
mov b, c
mov a, b

out a ; (out = c7h)