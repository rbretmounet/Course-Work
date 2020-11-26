# Use the file name mbox-short.txt as the file name
fname = input("Enter file name: ")
count = 0
total = 0
average = 0
try:
    fh = open(fname)
except:
    print('File cannot be opened:', fname)
    quit()
for line in fh:
    if line.startswith('X-DSPAM-Confidence:'):
        count += 1
        start = line.find('0')
        end = line.find('/n')
        total += float(line[start:end])
    if not line.startswith("X-DSPAM-Confidence:") : continue
average = total/count
print("Average spam confidence:",average)
