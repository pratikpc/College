import math
import random

def isPrime(n):
  if n == 2 or n == 3: return True
  if n < 2 or n%2 == 0: return False
  if n < 9: return True
  if n%3 == 0: return False
  r = int(n**0.5)
  f = 5
  while f <= r:
    if n%f == 0: return False
    if n%(f+2) == 0: return False
    f +=6
  return True
  
minPrime = 0
maxPrime = 9999
cached_primes = [i for i in range(minPrime,maxPrime) if isPrime(i)]
 
def GetPrime(p,q,limit=maxPrime):
        max_val = max(p,q)
        return random.choice([i for i in cached_primes if max_val<i<limit])
def PublicKeyFind(p,q, phin):
	return GetPrime(p,q, phin)
def PrivateKeyFind(e, phin, count):
	for x in range(0, count):
		d = (1 + x * phin) / e
		if d.is_integer():
			return int(d)
	raise Exception("Private Key Not Found in Range")
def RSAKeyFind(p, q):
	n = p * q
	phin = (p-1)*(q-1)
	e = PublicKeyFind(p,q,phin)
	d = PrivateKeyFind(e, phin, 900000)
	return ((e,n),(d,n))

def EncryptRSA(m, pub):
	(e,n) = pub
	if (m >= n):
		raise Exception("Unable to Encrypt")
	c = pow(m,e,n)
	return c

def DecryptRSA(c, priv):
	(d,n) = priv
	p = pow(c,d,n)
	return p
