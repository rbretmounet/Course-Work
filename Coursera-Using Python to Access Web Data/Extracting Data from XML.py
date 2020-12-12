from urllib.request import urlopen
import xml.etree.ElementTree as ET

url = input('Enter URL: ')
xml = urlopen(url).read()
tree = ET.fromstring(xml)

sum = 0
counts = tree.findall('.//count')
for item in range(len(counts)):
    sum += int(counts[item].text)
print(sum)
