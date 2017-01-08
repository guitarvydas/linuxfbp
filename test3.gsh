pipes 3

# readfile master
fork
# write
push 1
# pipe index 0
push 0
# copy pipe into stdout
dup 1
exec readfile master.txt
krof

# readfile detail
fork
# write
push 1
# pipe index 1
push 1
# copy pipe into stdout
dup 1
exec readfile details.txt
krof

# collate
fork
# write port pipe[2][1]->fd[1] (stdout)
#push 1
#push 2
#dup 1
# master port fd=3 connected to stdout of readfile master
# pipe[0][0]->fd[3]
push 0
push 0
dup 3
# details port fd=4 connected to stdout of readfile details
# pipe[1][0]->fd[4]
push 0
push 1
dup 4
exec collate 3 2 5
krof
