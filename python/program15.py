import random as r

class BankAccount:
    def __init__(self, name, mobile, pin):
        self.name = name
        self.mobile = mobile
        self.balance = 0.0
        self.account = str(r.randint(100000000, 999999999))
        self.pin = pin

    def deposit(self, amount, pin):
        if pin != self.pin:
            raise Exception("Pin not matched.")

        self.balance += amount
        return f"Deposited ₹{amount}. Balance = ₹{self.balance:.2f}"

    def withdraw(self, amount, pin):
        if pin != self.pin:
            raise Exception("Pin not matched.")

        if amount > self.balance:
            raise Exception("Insufficient balance.")

        self.balance -= amount
        return f"Withdrawn ₹{amount}. Balance = ₹{self.balance:.2f}"

    def get_balance(self, pin):
        if pin != self.pin:
            raise Exception("Pin not matched.")

        return self.balance

    def change_pin(self, old_pin, new_pin):
        if old_pin != self.pin:
            raise Exception("Pin not matched.")

        self.pin = new_pin
        return "PIN changed successfully."


class SavingsAccount(BankAccount):
    def __init__(self, name, mobile, pin, interest_rate):
        super().__init__(name, mobile, pin)
        self.interest_rate = interest_rate

    def add_interest(self):
        interest = self.balance * self.interest_rate / 100
        self.balance += interest

        return (f"Interest Added = ₹{interest:.2f}, "
                f"New Balance = ₹{self.balance:.2f}")


class FeeSavingsAccount(SavingsAccount):
    def __init__(self, name, mobile, pin, interest_rate, fee):
        super().__init__(name, mobile, pin, interest_rate)
        self.fee = fee

    def withdraw(self, amount, pin):
        total = amount + self.fee

        if pin != self.pin:
            raise Exception("Pin not matched.")

        if total > self.balance:
            raise Exception("Insufficient balance.")

        self.balance -= total

        return (f"Withdrawn ₹{amount}, "
                f"Fee ₹{self.fee}, "
                f"Balance = ₹{self.balance:.2f}")



acc = FeeSavingsAccount(
    "Rahul",
    "9876543210",
    1234,
    5,      
    10      
)

print(acc.deposit(5000, 1234))
print(acc.add_interest())
print(acc.withdraw(1000, 1234))
print("Balance =", acc.get_balance(1234))
print(acc.change_pin(1234, 4321))