import re
name = "regex_sum_1083176.txt"
try:
    handle = open(name)
except:
    print('File cannot be opened:', fname)
    quit()
finalSum = 0
for line in handle:
    data = re.findall('[0-9]+',line)
    if len(data) > 0:
        data = [int(i) for i in data]
        total = sum(data)
        finalSum = finalSum + total
print(finalSum)
