# Use words.txt as the file name
fname = input("Enter file name: ")
try:
    fh = open(fname)
except:
    print('File cannot be opened:', fname)
    quit()
for content in fh:
    print(content.rstrip().upper())
