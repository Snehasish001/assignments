from typing import Generator

def is_prime(n: int) -> bool:
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

def primes() -> Generator[int]:
    num = 2

    while True:
        if is_prime(num):
            yield num

        num += 1


n = int(input("Enter the no. of primes you want to print: "))

gen = primes()

for _ in range(n):
    print(next(gen), end=" ")