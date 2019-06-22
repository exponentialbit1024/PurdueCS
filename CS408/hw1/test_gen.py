import random

n = int(input("Enter N: "))
a = int(input("Enter A: "))
b = int(input("Enter B: "))

input_file_name = input("Enter output test file name: ")

f = open(input_file_name, "w")
f.write(str(n) + " " + str(a) + " " + str(b) + "\n")

sword_choices = ['NS', 'S']
time_choices = list(range(1, 1000000000))

chosen_times = []

for i in range(n):
    sword_choice = random.choice(sword_choices)
    time_choice = random.choice(time_choices)
    while time_choice in chosen_times:
        time_choices.pop(time_choices.index(time_choice))
        time_choice = random.choice(time_choices)
    if time_choice not in chosen_times:
        chosen_times.append(time_choice)
        f.write(sword_choice + " " + str(time_choice) + "\n")

f.close()
