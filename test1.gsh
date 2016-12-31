pipes 1

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

# display
fork
push 0
# pipe index 0
push 0
# copy pipe into stdin
dup 0
exec display
krof

