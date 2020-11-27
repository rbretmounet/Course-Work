fname = input("Enter file name: ")
try:
    fh = open(fname)
except:
    print('File cannot be opened:', fname)
    quit()
lst = list()
for line in fh:
    line = line.split()
    for i in range(len(line)):
        if not line[i] in lst:
            lst.append(line[i])
lst.sort()
print(lst)
