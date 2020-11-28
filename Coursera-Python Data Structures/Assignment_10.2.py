name = input("Enter file:")
if len(name) < 1 : name = "mbox-short.txt"
try:
    handle = open(name)
except:
    print('File cannot be opened:', fname)
    quit()
counts = dict()

for line in handle:
    if line.startswith('From '):
        line = line.split()
        line = line[5].split(':')
        counts[line[0]] = counts.get(line[0],0) + 1

lst = list()
for k,v in sorted(counts.items()):
    tupple = (v,k)
    lst.append(tupple)

for v,k in lst:
    print(k,v)
