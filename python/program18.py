import random
import heapq

nums = [random.randint(1, 100) for _ in range(10)]

print("List:", nums)

n = int(input("Enter N: "))

print("Largest N items:", heapq.nlargest(n, nums))
print("Smallest N items:", heapq.nsmallest(n, nums))