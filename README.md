# pwntools-glibc-buffering

A common issue that people encounter when using Pwntools (or anything else, really) is that the C standard library (glibc, on Ubuntu) performs lots of buffering.  This means that you may not see the results a your `printf` in a challenge binary.

Glibc's buffering has three modes for stdout:

- Fully buffered (stdout is a pipe)
- Line buffered (stdout is a terminal)
- Unbuffered (stdin and stdout are both terminals)

This repository contains an example C program `demo.c` which demonstrates this issue.  Of interest, directly calling `write` avoids any buffering.  This allows us to see that the program has reached a certain state.  Second, it makes use of `printf` which are generally fully-buffered, or line-buffered.  Third, it makes use of one `printf` each which does/does not end with a newline (`"\n"`), which allows us to demonstrate the issues caused by buffering modes.

Included is a sample script, `demo.py`, which demonstrates how the various buffering modes exhibit themselves.  

## Both PTYs

Here is the behavior one would see in an interactive terminal.  Everything is immediately flushed to the screen, since it is expected that the input and output are both interactive.

```
$ python demo.py DEBUG STDIN=PTY STDOUT=PTY
[x] Starting local process './a.out'
[DEBUG] Sent 0x2 bytes:
    'X\n'
[DEBUG] Received 0x20 bytes:
    'AHello\n'
    'BCYou wrote: X\n'
    '\n'
    'DEGoodbye'
[DEBUG] Sent 0x2 bytes:
    'Y\n'
[+] Receiving all data: Done (16B)
[*] Process './a.out' stopped with exit code 1
[DEBUG] Received 0x10 bytes:
    'FYou wrote: Y\n'
    '\n'
    'G'
```

## Stdout is a PTY

Here is the default pwntools behavior.  Notice that "F" precedes "Goodbye", and that the timeout is hit before "Goodbye" arrives.

This is like `less` in the `cat foo | grep bar | less`.  Note that `less` can actually still have input, despite `STDIN` being a pipe.  It does this by accessing `/dev/tty` directly (or some analogue).  However, results do not show up immediately in `less`, since `grep` may buffer them before sending it over the pipe.

```
$ python demo.py DEBUG STDOUT=PTY
[+] Starting local process './a.out': Done
[DEBUG] Sent 0x2 bytes:
    'X\n'
[DEBUG] Received 0x19 bytes:
    'AHello\n'
    'BCYou wrote: X\n'
    '\n'
    'DE'
[DEBUG] Sent 0x2 bytes:
    'Y\n'
[+] Receiving all data: Done (48B)
[*] Process './a.out' stopped with exit code 1
[DEBUG] Received 0x17 bytes:
    'FGoodbyeYou wrote: Y\n'
    '\n'
    'G'
```

## Everything is a pipe

This is how things work with the `subprocess` module by default, and old versions of Pwntools.

It would be like `grep` in the shell command `cat foo | grep bar | less`.

Note that `"Hello"` does not arrive until the buffers are flushed when the binary exits.

```
[+] Starting local process './a.out': Done
[DEBUG] Sent 0x2 bytes:
    'X\n'
[DEBUG] Received 0x5 bytes:
    'ABCDE'
[DEBUG] Sent 0x2 bytes:
    'Y\n'
[+] Receiving all data: Done (48B)
[*] Process './a.out' stopped with exit code 1
[DEBUG] Received 0x2b bytes:
    'FGHello\n'
    'You wrote: X\n'
    '\n'
    'GoodbyeYou wrote: Y\n'
    '\n'
```
