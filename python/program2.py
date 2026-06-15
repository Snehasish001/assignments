
coupons = {
    "monday": 10,
    "tuesday": 15,
    "wednesday": 20,
    "thursday": 12,
    "friday": 25,
    "saturday": 30,
    "sunday": 35
}

day = input("Enter the day of the week: ").lower()

if day in coupons:
    print("Discount Coupon Rate =", coupons[day], "%")
else:
    print("Invalid day entered")