

file = ""

with open("./lab4/idk.txt", "r") as f:
    file = f.read()
    
reverse = file[::-1]

with open("./lab4/oq1.txt", "w") as f:
    f.write(reverse)


