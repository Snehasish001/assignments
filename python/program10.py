import random as r

l = list(filter(lambda x : x % 2 == 1, map(lambda x : x ** 2, range(r.randint(0, 100)))))

print(l)