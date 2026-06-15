def fibonaccci():
    n0 = 0
    n1 = 1
    yield n0
    yield n1

    while True:
        n2 = n0 + n1
        yield n2
        n0 = n1
        n1 = n2

fib = fibonaccci()

n = int(input("Enter the number : "))
for _ in range(n):
    print(next(fib), end=" ")