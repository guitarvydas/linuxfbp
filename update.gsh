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


# read master - output pipe is #0
fork
push 1 ; write
push 0 ; pipe index 0
dup 1  ; copy pipe into stdout
exec readfile master.txt
krof

# read details - output pipe is #0
fork
push 1 ; write
push 1 ; pipe index 1
dup 1  ; copy pipe into stdout
exec readfile detail.txt
krof

fork
push 0 ; read
push 2 ; pipe index 2
dup 0  ; copy pipe into stdin
exec
krof

