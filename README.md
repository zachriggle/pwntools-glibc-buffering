# pwntools-glibc-buffering

Glibc's buffering has three modes for stdout:

- Fully buffered (stdout is a pipe)
- Line buffered (stdout is a terminal)
- Unbuffered (stdin and stdout are both terminals)




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
