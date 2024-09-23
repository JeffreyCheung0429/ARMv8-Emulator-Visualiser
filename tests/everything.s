add x0, x0, #0
sub x0, x0, #0
adds x0, x0, #0
subs x0, x0, #0
movn x0, #0
movz x0, #0
movk x0, #0

logical:
add x0, x0, x0
sub x0, x0, x0
adds x0, x0, x0
subs x0, x0, x0
and x1, x1, x1
bic x0, x0, x0
orr x0, x0, x0
orn x0, x0, x0
eor x0, x0, x0
eon x0, x0, x0
ands x0, x0, x0
bics x0, x0, x0
madd x0, x0, x0, x0
msub x0, x0, x0, x0

str x0, [x0], #0
str x0, [x0, #0]!
str x0, [x0, #0]
str x0, [x0, x0]

ldr x0, [x0], #0
ldr x0, [x0, #0]!
ldr x0, [x0, #0]
ldr x0, [x0, x0]

b.eq logical
br x0
b logical

and x0, x0, x0