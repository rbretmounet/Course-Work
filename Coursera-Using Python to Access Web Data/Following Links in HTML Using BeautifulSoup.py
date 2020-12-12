from urllib.request import urlopen
from bs4 import BeautifulSoup
import ssl


# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

url = input('Enter URL: ')
count = int(input('Enter count: '))
position = int(input('Enter position: '))

while count >= 0:
    print('Retrieving:', url)
    html = urlopen(url, context=ctx).read()
    soup = BeautifulSoup(html, "html.parser")

    data = soup.find_all('a')
    foundUrl = data[position-1].get('href',None)
    url = foundUrl

    count -= 1
