import random as r

# The problem requires sides smaller than 10, so n must be 10 
# (range(1, 10) gives numbers 1 through 9)
n = r.randint(1, 100)

# --- Method 1: List Comprehension ---
triples = [
    (a, b, int((a**2 + b**2)**0.5)) 
    for a in range(1, n) 
    for b in range(a, n)
    if ((a**2 + b**2)**0.5).is_integer()
]


# Step 2: Filter pairs where the hypotenuse is an integer
# We check the math on elements 0 and 1 of the incoming pair tuple
t = [(a, b, int((a**2 + b**2)**0.5)) for a, b in filter(lambda pair: ((pair[0]**2 + pair[1]**2)**0.5).is_integer(), [(x, y) for x in range(1, n) for y in range(x, n)])]

# Step 3: Map the valid pairs into the final (a, b, c) tuple format
# t = [(a, b, int((a**2 + b**2)**0.5)) for a, b in valid_pairs]


print("List Comprehension Result:")
print(triples)
print("\nFilter Result:")
print(t)