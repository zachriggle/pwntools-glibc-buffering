from pwn import *

if args['STDOUT'] == 'PTY': 
    stdout = process.PTY
else:
    stdout = subprocess.PIPE

if args['STDIN'] == 'PTY': 
    stdin = process.PTY
else: 
    stdin = subprocess.PIPE

p = process('./a.out', stdout=stdout, stdin=stdin)
p.sendline("X")
data = p.recvuntil('Goodbye', timeout=3)
p.sendline("Y")
p.recvall()
