n = int(input("Enter the range: "))


even = iter([i for i in range(n + 1) if i % 2 == 0])
odd = iter([i for i in range(n + 1) if i % 2 != 0])

print("\nUsing iter()")
print("Even | Odd")

while True:
    try:
        print(next(even), "   ", next(odd))
    except StopIteration:
        print("End")
        break



class Even:
    def __init__(self, limit):
        self.item = 0
        self.limit = limit

    def __iter__(self):
        return self

    def __next__(self):
        if self.item > self.limit:
            raise StopIteration

        value = self.item
        self.item += 2
        return value
    


class Odd:
    def __init__(self, limit):
        self.item = 1
        self.limit = limit

    def __iter__(self):
        return self

    def __next__(self):
        if self.item > self.limit:
            raise StopIteration

        value = self.item
        self.item += 2
        return value
    


print("\nUsing Custom Iterators")
print("Even | Odd")

e = Even(n)
o = Odd(n)

for i, j in zip(e, o):
    print(i, j)