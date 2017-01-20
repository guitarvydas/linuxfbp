#
# Simple collate example from com.jpmorrsn.fbp.examples.networks
#
# 4 components - readfile to read the master, readfile to read the details,
# collate and display to show the collate recrods on the concole
#
# a total of 3 pipes and two "initializer ports" which we will simulate using
# the command line (exec1st)
#

pipes 3

fork
# write==1
push 1
# pipe index 0
push 0
# copy pipe into stdout (1)
dup 1
exec readfile master.txt
krof

fork
push 1
# pipe index 1
push 1
# copy pipe into stdout
dup 1
exec readfile details.txt
krof

fork
# write is pipe[2][1]->fd[1] (stdout)
push 1
push 2
dup 1
# master is pipe[0][0]->fd[3]
push 0
push 0
dup 3
# details is pipe[1][0]->fd[4]
push 0
push 1
dup 4
exec collate 3 2 5
krof

fork
push 0
push 2
dup 0
exec display
krof



