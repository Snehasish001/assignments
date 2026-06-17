import random as r

def geometric_progress(a, q):
    yield a
    i = 1
    while i < 100000:
        yield a * q ** i
        
        i += 1
    return None

gp = geometric_progress(r.randint(1, 10), r.randint(1, 10))

for _ in range(r.randint(1, 100)):
    print(next(gp))
