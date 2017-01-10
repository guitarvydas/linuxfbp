# test two readers sending to dot via 2 pipes, dot send to display

pipes 3

# readfile
fork
# write
push 1
# pipe index 0
push 0
# copy pipe into stdout
dup 1
exec readfile master.txt
krof

# readfile
fork
# write
push 1
# pipe index 1
push 1
# copy pipe into stdout
dup 1
exec readfile details.txt
krof

fork
push 0
push 0
dup 3
push 0
push 1
dup 4
push 1
push 2
dup 1
exec dot 2
krof

# display
fork
push 0
# pipe index 2
push 2
# copy pipe into stdin
dup 0
exec display
krof

