largest = None
smallest = None
while True:
    num = input("Enter a number: ")
    if num == "done" : break
    try:
    	num = int(num)
        if largest == None:
            largest = num
        if smallest == None:
            smallest = num
        if largest < num:
            largest = num
        if smallest > num:
            smallest = num
    except ValueError:
        print("Invalid input")


print("Maximum is", largest)
print("Minimum is", smallest)
