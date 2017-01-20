This code is an experiment to see if FBP can be implemented using Linux as the FBP runtime.

Networks as grash shell scripts:

test.gsh
- usage: grash test.gsh
- Simple test of tester.c.
- "grash test0.gsh" runs tester.c and the 3 lines of output should appear on the console (or stdout).

test1.gsh
- usage: grash test1.gsh
- Joins output of readfile (master.txt) to input so display.

testcollate.gsh
- usage: grash testcollate.gsh
- Joins output of readfile (master.txt) to input 3 of collate.
- Joins output of readfile (details.txt) to input 4 of collate.
- Joins output 1 of collate to input 0 of display.
- Should result in a collated dump of master+details.
- When run from linux bash, the next bash prompt appears before the output from display, making it look like the program has not finished.  Just hit ENTER to get another prompt.

testdot.gsh
- usage: grash testdot.gsh
- Joins output of readfile (master.txt) to input 3 of dot.
- Joins output of readfile (details.txt) to input 4 of dot.
- Joins output 1 of dot to input 0 of display.
- Should result in one line from master.txt, one line from details.txt and so on until master.txt runs out, then all of the rest of the lines from details.txt.
- When run from linux bash, the next bash prompt appears before the output from display, making it look like the program has not finished.  Just hit ENTER to get another prompt.


Details:

Components run as separate Linux commands.  At present, all components are written in C, but this does not preclude the use of any other language.

Flows (wires) are implemented as Linux pipes.  In the future, they could be implemented as unnamed pipes, sockets, etc.

FBP networks are represented in "grash" - a very simple, stunted shell (graph shell), which replaces bash.

Bash (and sh) do not have syntax that allows for multiple inputs and outputs, hence, they cannot represent full-blown FBP networks.

Grash has only 8 commands, very assembler-like and only marginally human readable.  It has been shown (see "vsh") that networks can be compiled from a more readable format to grash commands.

Grash simply duplicates the action of bash when pipe syntax "|" is used, i.e. fork(), dup2() and exec().  See https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/pipe.html for examples of how shells fork (create) processes and link them together with pipes.

Roughly, a parent process (in this case grash itself) spawns a process for each command that is piped.  The parent creates an array of pipes.

A single pipe is a vector of 2 integers (FD's).

Pipe[0] is the source.  A process reads from pipe[0].

Pipe[1] is the sink.  A process writes to pipe[1].

In Linux, a parent "forks" its children, after setting up the pipes.  A forked child is a complete clone of the parent, including the pipe array.  The parent is distinguished from the cloned child only by the return value from the fork() call.  The parent receives a non-zero PID, whereas the child receives a return value of 0.

A child, upon being forked, proceeds to copy its pipes into corresponding FD's using the dup2() command.  It closes unused pipes and then repurposes itself by calling exec() to run a given program, with the correctly copied FD's.

Linux has a limited number of FD's per process (by default, 1024, I believe).

By convention, fd[0] is stdin, fd[1] is stdout and fd[2] is stderr.

The code herein tries to obey this convention.

Any component that has only one input and two outputs can use FD's 0-2.

A component, such as collate.c, that needs 2 inputs and one output begins mapping its inputs from FD #3 onwards.

The code for collate.c maps its first input to fd #3, its second output to fd #4 and its output to fd #1 (stdout).

This experiment shows that Linux pipes do not work exactly like FBP flows.  In FBP it is possible to send outputs from two different components to the same input on a third component.  This is not possible with pipes (at least in this implementation), since, once one writer closes a pipe, the reader considers the pipe closed, regardless of wheter the other writer is finished or not.

The simplistic solution adopted here is to use "dot.c" to fan-in a number of different pipes and send all inputs to a single output.  When all inputs are closed, dot.c closes its output pipe.

This means that an FBP network compiler needs to be "smart" and implicitly emit instances of dot when it detects multiple writers on a single flow.

The Linux convention is the "IP's" are lines, terminated by '\n' or EOF.

Components:

display.c
- One input FD 0 (stdin).  No outputs.
- Fprintf's each line to stdout (usually the console).

readfile.c
- One output, 1, no inputs.
- A filename is specified on the command line.
- Opens the given filename and sends its contents, line by line to FD #1 (stdout).

tester.c
- Very simple early test.
- No inputs, one output stdout (1).
- Prints 3 lines containing "hello" to stdout, then exits.

collate.c
 - Two inputs #3, #4, one output #1.
 - Fashioned closely after Collate.java.

dot.c
 - Up to 10 inputs 3-12 (can be changed, hard-wired as a #define presently), one output #1.
 - Outputs one line from each open input, until all inputs are closed.


