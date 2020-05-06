mov A, 1
mov B, 1
out A ; 1! = 1 = 01h

add B, 1
mul A, B
out A ; 2! = 2 = 02h

add B, 1
mul A, B
out A ; 3! = 6 = 06h

add B, 1
mul A, B
out A ; 4! = 24 = 18h

add B, 1
mul A, B
out A ; 5! = 120 = 78h