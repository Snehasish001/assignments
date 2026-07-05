import random
from datetime import datetime, timedelta


names = [
    "Rakesh", "Ahmod", "Koushik", "Snehasish", "Devraj", "Sourav", "Dipu",
    "Dharitri", "Shreya", "Priya", "Gourav", "Roshni", "Pulak", "Puspak",
    "Abhishek", "Amit", "Aniket", "Arijit", "Arjun", "Ashish", "Avijit",
    "Bikash", "Biswajit", "Debashis", "Dipankar", "Kaushik", "Manoj",
    "Nikhil", "Partha", "Prasenjit", "Rahul", "Rajesh", "Rajat",
    "Ranjan", "Ritwik", "Sagnik", "Sanjay", "Santanu", "Shubham",
    "Subhajit", "Sudip", "Suman", "Supriyo", "Tapas", "Tanmoy",
    "Ujjwal", "Vikash", "Vivek", "Yash", "Aditya", "Akash",
    "Anirban", "Arnab", "Ayush", "Bappa", "Chandan", "Deep",
    "Harsh", "Indrajit", "Joy", "Kunal", "Mithun", "Niladri",
    "Pritam", "Rohit", "Sayan", "Siddharth", "Tushar",
    "Aditi", "Ananya", "Ankita", "Arpita", "Debjani", "Ishita",
    "Kajal", "Koel", "Madhumita", "Mousumi", "Nandini", "Pallavi",
    "Payel", "Puja", "Riya", "Rupali", "Sanchita", "Shrabani",
    "Sneha", "Sonali", "Sweta", "Tanushree", "Trisha", "Madhurima",
    "Anushka", "Tania", "Ritika", "Poulomi", "Sushmita"
]

surnames = [
    "Ghosh", "Sarkar", "Mandal", "Roy", "Barman", "Das", "Dutta",
    "Adhikari", "Singh", "Paul", "Sen", "Chakraborty", "Mukherjee",
    "Banerjee", "Bhattacharya", "Mitra", "Saha", "Biswas", "Pal",
    "Mondal", "Kar", "Majumdar", "Nandi", "Bose", "Debnath",
    "Pramanik", "Halder", "Datta", "Malakar", "Chowdhury",
    "Karmakar", "Ganguly", "Lahiri", "Bera", "Poddar",
    "Chatterjee", "Basu", "Sengupta", "Ray", "Gupta",
    "Jain", "Agarwal", "Sharma", "Verma", "Yadav",
    "Patel", "Kumar", "Reddy", "Nair", "Menon",
    "Pillai", "Iyer", "Naidu", "Mishra", "Tiwari",
    "Pandey", "Tripathi", "Dubey", "Soni", "Khanna",
    "Kapoor", "Mehta", "Joshi", "Desai", "Kulkarni"
]

cities = [
    "Kolkata", "Siliguri", "Jalpaiguri", "Malda", "Delhi",
    "Mumbai", "Bengaluru", "Chennai", "Pune", "Hyderabad",
    "Ahmedabad", "Surat", "Jaipur", "Lucknow", "Kanpur",
    "Patna", "Bhopal", "Indore", "Nagpur", "Ranchi",
    "Bhubaneswar", "Guwahati", "Chandigarh", "Amritsar",
    "Ludhiana", "Coimbatore", "Madurai", "Visakhapatnam",
    "Vijayawada", "Thiruvananthapuram", "Kochi", "Mysuru",
    "Jodhpur", "Udaipur", "Agra", "Varanasi", "Prayagraj",
    "Noida", "Gurugram", "Faridabad", "Howrah", "Durgapur",
    "Asansol", "Kharagpur", "Cooch Behar", "Alipurduar",
    "Darjeeling", "Bardhaman", "Murshidabad", "Nadia"
]

states = [
    "WB", "DL", "MH", "KA", "TN", "TS", "GJ",
    "RJ", "UP", "BR", "MP", "JH", "OD",
    "AS", "PB", "KL", "AP", "HR"
]

departments = ["DP001", "DP002", "DP003", "DP004", "DP005"]
designations = ["D001", "D002", "D003", "D004", "D005"]


def validate_length(value, max_len, field):
    if len(str(value)) > max_len:
        raise ValueError(
            f"{field} exceeds {max_len} chars -> {value}"
        )

def validate_pin(pin):
    pin = str(pin)
    if len(pin) != 6 or not pin.isdigit():
        raise ValueError(f"Invalid PIN -> {pin}")

def validate_sex(sex):
    if sex not in ["M", "F"]:
        raise ValueError(f"Invalid SEX -> {sex}")

def validate_dept(dept):
    if dept not in departments:
        raise ValueError(f"Invalid Department -> {dept}")

def validate_desig(desig):
    if desig not in designations:
        raise ValueError(f"Invalid Designation -> {desig}")


TOTAL_EMPLOYEES = 1000

start_date = datetime(1999, 1, 1)
end_date = datetime(2025, 12, 31)

used_codes = set()
rows = []


for i in range(1, TOTAL_EMPLOYEES):

    emp_code = f"E{i:04d}"

    if emp_code in used_codes:
        continue

    used_codes.add(emp_code)

    full_name = (
        f"{random.choice(names)} {random.choice(surnames)}"
    )[:20]

    dept_code = random.choice(departments)
    desg_code = random.choice(designations)

    sex = random.choice(["M", "F"])

    address = (
        f"{random.randint(1,999)} "
        f"{random.choice(['Park Road','Station Road','Main Road','Lake Road'])}"
    )[:25]

    city = random.choice(cities)[:20]

    state = random.choice(states)[:20]

    pin = str(random.randint(100000, 999999))

    basic = round(
        random.randint(18000, 90000),
        2
    )

    random_days = random.randint(
        0,
        (end_date - start_date).days
    )

    join_date = (
        start_date + timedelta(days=random_days)
    ).strftime("%Y-%m-%d")


    validate_length(emp_code, 16, "EMP_CODE")
    validate_length(full_name, 20, "EMP_NAME")
    validate_length(dept_code, 16, "DEPT_CODE")
    validate_length(desg_code, 16, "DESIG_CODE")
    validate_length(sex, 1, "SEX")
    validate_length(address, 25, "ADDRESS")
    validate_length(city, 20, "CITY")
    validate_length(state, 20, "STATE")

    validate_pin(pin)
    validate_sex(sex)
    validate_dept(dept_code)
    validate_desig(desg_code)

    rows.append(
        f"('{emp_code}','{full_name}','{dept_code}','{desg_code}',"
        f"'{sex}','{address}','{city}','{state}','{pin}',"
        f"{basic:.2f},'{join_date}')"
    )


sql = (
    "INSERT INTO EMPLOYEE "
    "(EMP_CODE,EMP_NAME,DEPT_CODE,DESIG_CODE,SEX,ADDRESS,CITY,STATE,PIN,BASIC,JN_DT)\n"
    "VALUES\n"
    + ",\n".join(rows)
    + ";"
)

with open("employee_1000.sql", "w", encoding="utf-8") as file:
    file.write(sql)

print("Successfully generated employee_1000.sql")
print(f"Total Records : {len(rows)}")