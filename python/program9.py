import random

first_names = [
    "Rahul", "Amit", "Sita", "Rani", "Gita",
    "Soham", "Priya", "Ankit", "Rohit", "Puja"
]

subjects_pool = [
    "Math", "Physics", "Chemistry",
    "Biology", "English", "History",
    "Geography", "Computer"
]

n = int(input("Enter number of students: "))

# Generate random data
students = [random.choice(first_names) for _ in range(n)]
subjects = [random.choice(subjects_pool) for _ in range(n)]
marks = [random.randint(0, 100) for _ in range(n)]

print("\nStudent List:")
print(students)

print("\nSubject List:")
print(subjects)

print("\nMarks List:")
print(marks)

# Zip the lists
data = list(zip(students, subjects, marks))

print("\nZipped Data:")
for record in data:
    print(record)

# Find maximum element from each tuple
result = list(map(lambda t: max(t, key=str), data))

print("\nMaximum Element from Each Tuple:")
for item in result:
    print(item)