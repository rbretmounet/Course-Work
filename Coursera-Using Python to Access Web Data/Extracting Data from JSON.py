from urllib.request import urlopen
import json

url = input('Enter location: ')

print ("Retrieving", url)
data = urlopen(url).read().decode()
info = json.loads(data)
jsonData = info['comments']

print('User count:', len(jsonData))

sum = 0
for items in jsonData:
    sum += items["count"]
print(sum)
