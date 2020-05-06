mov A, 0
mov B, 1

out B ; fib(1) = 1 (out = 01h)

add A, B

xor A, B
xor B, A
xor A, B

out B  ; fib(2) = 1 (out = 01h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(3) = 2 (out = 02h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(4) = 3 (out = 03h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(5) = 5 (out = 05h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(6) = 8 (out = 08h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(7) = 13 (out = 0Dh)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(8) = 21 (out = 15h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(9) = 34 (out = 22h)

add A, B

xor A, B
xor B, A
xor A, B

out B ; fib(10) = 55 (out = 37h)