from collections import defaultdict

# First Stock Dictionary
stock1 = {
    "TCS": 3500,
    "INFY": 1800,
    "WIPRO": 500,
    "HCL": 1500,
    "TECHM": 1800,
    "LT": 3500,
    "SBI": 800
}

# Second Stock Dictionary
stock2 = {
    "TCS": 3500,
    "INFY": 2000,
    "WIPRO": 500,
    "RELIANCE": 3000,
    "SBI": 800,
    "ICICI": 1200
}

print("Stock Dictionary 1:")
print(stock1)

print("\nStock Dictionary 2:")
print(stock2)

# --------------------------------------------------
# Minimum and Maximum Price
# --------------------------------------------------
print("\nMinimum Price:", min(stock1.values()))
print("Maximum Price:", max(stock1.values()))

# --------------------------------------------------
# Sort items according to prices
# --------------------------------------------------
print("\nStock1 Sorted by Price:")
sorted_stock1 = dict(sorted(stock1.items(), key=lambda x: x[1]))
print(sorted_stock1)

# --------------------------------------------------
# Items only in first dictionary
# --------------------------------------------------
only_first = stock1.keys() - stock2.keys()

print("\nItems only in Stock1:")
for item in only_first:
    print(item, ":", stock1[item])

# --------------------------------------------------
# Items whose prices do not match
# --------------------------------------------------
print("\nItems with Different Prices:")

for key in stock1.keys() & stock2.keys():
    if stock1[key] != stock2[key]:
        print(key, "->", stock1[key], stock2[key])

# --------------------------------------------------
# Remove duplicate prices from first dictionary
# Keep first occurrence only
# --------------------------------------------------
unique_stock = {}

for k, v in stock1.items():
    if v not in unique_stock.values():
        unique_stock[k] = v

print("\nStock1 after Removing Duplicate Prices:")
print(unique_stock)

# --------------------------------------------------
# Sort both dictionaries by increasing prices
# --------------------------------------------------
print("\nStock1 Sorted:")
print(dict(sorted(stock1.items(), key=lambda x: x[1])))

print("\nStock2 Sorted:")
print(dict(sorted(stock2.items(), key=lambda x: x[1])))

# --------------------------------------------------
# Group items by price ranges of 500
# --------------------------------------------------
groups = defaultdict(list)

for stock, price in stock1.items():
    group = (price // 500) * 500
    groups[group].append(stock)

print("\nGrouped by Price Multiples of 500:")

for group, stocks in groups.items():
    print(f"{group}-{group+499} :", stocks)

# --------------------------------------------------
# Find items with price = 800
# --------------------------------------------------
print("\nItems with Price = 800")

for stock, price in stock1.items():
    if price == 800:
        print("Stock1 ->", stock)

for stock, price in stock2.items():
    if price == 800:
        print("Stock2 ->", stock)