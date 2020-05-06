mov C, -4
mov B, -5

mov A, B
iMul A, C ; -4*-5 = 20 = 14h (out = 14h)
out A

neg C

mov A, B
iMul A, C  ; 4*-5 = -20 = -14h (out = ech)
out A

neg B

mov A, B
iMul A, C ; 4*5 = 20 = 14h (out = 14h)
out A

neg C

mov A, B
iMul A, C ; -4*5 = -20 = -14h (out = ech)
out A