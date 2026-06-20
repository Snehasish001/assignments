# # import random

# # first_names = [
# #     "Rahul", "Amit", "Sita", "Rani", "Gita",
# #     "Soham", "Priya", "Ankit", "Rohit", "Puja"
# # ]

# # subjects_pool = [
# #     "Math", "Physics", "Chemistry",
# #     "Biology", "English", "History",
# #     "Geography", "Computer"
# # ]

# # n = int(input("Enter number of students: "))

# # # Generate random data
# # students = [random.choice(first_names) for _ in range(n)]
# # subjects = [random.choice(subjects_pool) for _ in range(n)]
# # marks = [random.randint(0, 100) for _ in range(n)]

# # print("\nStudent List:")
# # print(students)

# # print("\nSubject List:")
# # print(subjects)

# # print("\nMarks List:")
# # print(marks)

# # # Zip the lists
# # data = list(zip(students, subjects, marks))

# # print("\nZipped Data:")
# # for record in data:
# #     print(record)

# # # Find maximum element from each tuple
# # result = list(map(lambda t: max(t, key=str), data))

# # print("\nMaximum Element from Each Tuple:")
# # for item in result:
# #     print(item)
# import string
# import random as r
# sub = ['cs', 'maths', 'phys', 'che']
# l = []
# for _ in range(r.randint(1, 1000)):
#     d = {
#         "name" : string.ascii_lowercase[r.randint(1,10):r.randint(15,26)],
#         "subject" : sub,
#         "marks" : [r.randint(1, 100) for _ in range(4)]
#     }
#     l.append(d)

# def marks_dic(l: list, subcode: int)->list:
#     cs = []
#     for i in l:
#         c = {
#             'name' : i['name'],
#             'marks' : i['marks'][subcode]
#         }
#         cs.append(c)
#     return cs

# cs = marks_dic(l, 0)
# maths = marks_dic(l, 1)
# phys = marks_dic(l, 2)
# che = marks_dic(l, 3)

# def max_fun(cs: list[dict]):
#     l = []
#     ans = {
#         'name' : "default",
#         'marks' : 0
#     }

#     for i in cs:
#         if i['marks'] > ans['marks']:
#             ans = i

#     for i in cs:
#         if i['marks'] == ans['marks']:
#             l.append(i)
#     return l
        


# print(F" cs : {max_fun(cs)}")
# print(F" maths : {max_fun(maths)}")
# print(F" phy : {max_fun(phys)}")
# print(F" che : {max_fun(che)}")


import random

students = ["Rahul", "Amit", "Sita", "Rani", "Priya"]
subjects = ["Math", "Physics", "Chemistry", "Biology", "English"]
marks = [random.randint(0, 100) for _ in range(5)]

print("Students :", students)
print("Subjects :", subjects)
print("Marks    :", marks)


result = list(map(lambda t: max(t, key=str), zip(students, subjects, marks)))

print("\nElement-wise Maximum:")
print(result)