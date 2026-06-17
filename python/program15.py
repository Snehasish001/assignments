import random as r

class BankAccount:
    def __init__(self, name, mobile, pin):
        self.name = name
        self.mobile = mobile
        self.balance = 0.00
        self.account = str(r.randint(100000000, 999999999))
        self.pin = pin

    def deposit(self, amount: float|int, pin):
        if self.pin == pin:
            self.balance = self.balance + amount
            return f"Current balance : {self.balance}"
        else:
            raise Exception("Pin not matched.")
    
    def withdraw(self, amount, pin):
        if pin != self.pin: 
            raise Exception("Pin not matched.")
        if self.balance > amount:
            self.balance = self.balance - amount
            return f"Current balance : {self.balance}"
        else:
            raise Exception("Amount greater than balance")
        
    def get_balance(self, pin):
        if pin != self.pin:
            raise Exception("Pin not matched.")
        return self.balance
    
    def change_pin(self, pin, new_pin):
        if self.pin != pin:
            raise Exception("Pin not matched.")
        self.pin = new_pin
        return f"Pin changes : {self.pin}"


class SavingAccount(BankAccount):
    def __init__(self, name, mobile, pin):
        super().__init__(name, mobile, pin)

    def interest_rate(self, interest, time = 1):
        self.balance += ((self.balance * interest * time) / 100)
    

        

class FeeSavingAccount(SavingAccount):
    def __init__(self, name, mobile, pin):
        super().__init__(name, mobile, pin)

    def fees(self, charges):
        