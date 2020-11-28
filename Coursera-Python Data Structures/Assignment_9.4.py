name = input("Enter file:")
if len(name) < 1 : name = "mbox-short.txt"
try:
    handle = open(name)
except:
    print('File cannot be opened:', fname)
    quit()

histogram = dict()

for line in handle:
    if line.startswith('From '):
        line = line.split()
        histogram[line[1]] = histogram.get(line[1],0) + 1

bigcount = None
bigword = None
for word,count in histogram.items():
    if bigcount is None or count > bigcount:
        bigword = word
        bigcount = count
print (bigword,bigcount)
