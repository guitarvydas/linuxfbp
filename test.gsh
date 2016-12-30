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

# display.c
fork
# read
push 0
# pipe index 0
push 0
# copy pipe into stdin
dup 0
exec display
krof

