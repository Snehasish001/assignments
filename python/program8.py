n = int(input("Enter the number : "))
l = list(filter(lambda x : x % 5 == 0, range(n + 1)))
print(l)