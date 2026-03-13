#!/usr/bin/env pypy3

from sys import stdin, stdout
from array import array

input, print = stdin.readline, stdout.write

N = 10**6 + 1
MOD = 10 ** 9 + 7
BASE = 8383838383

factor = array('l', [-1] * N)
primes = []
cnt = array('l', [0] * N)
pw = array('l', [0] * N)

for p in range(2, N):
	if factor[p] == -1:
		factor[p] = p
		primes.append(p)
	for k in primes:
		if p * k >= N:
			break
		factor[p * k] = k
		if p % k == 0:
			break

pw[0] = 1
for i in range(1, N):
	pw[i] = BASE * pw[i - 1] % MOD

n, q = map(int, input().split())
a = list(map(int, input().split()))
h = array('l', [0] * (n + 1))

for i in range(1, n + 1):
	h[i] = h[i - 1]

	x = a[i - 1]

	while x > 1:
		p, k = factor[x], 0

		while x % p == 0:
			x //= p
			k += 1

		exp = (cnt[p] + k) % 3
		h[i] = (h[i] + (exp - cnt[p]) * pw[p]) % MOD
		cnt[p] = exp

while q > 0:
	q -= 1

	l, r = map(int, input().split())

	if (h[r] - h[l - 1]) % MOD == 0:
		print('Yes\n')
	else:
		print('No\n')
	
