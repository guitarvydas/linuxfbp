pipes 1

# tester.c
fork
# write
push 1
# pipe index 0
push 0
# copy pipe into stdout
dup 1
exec tester
krof


