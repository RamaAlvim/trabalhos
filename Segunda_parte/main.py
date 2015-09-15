__author__ = 'rama'

from lxml import html
import urllib3, certifi, requests
from bs4 import BeautifulSoup
from array import *
import sys
from collections import deque, Counter
import time
import re

headers ={}
headers['User-Agent'] = "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.27 Safari/537.17"

d = deque() #lista duplamente encadeada para colocar os sites

while str!='FIM': #faca enquanto nao str for diferente de FIM
    str = input() #ler do teclado e grava em str
   # print (str)
    d.append(str) # grava str no fim do deque
d.remove('FIM') # remove todos as ocorrencias de FIM da lista




#recebe uma url e devolve o codigo em html dela
def urlToHtml (website_url):
    print("buscando codigo fonte de ",website_url)

    try:
        session = requests.Session()
        session.mount("http://",requests.adapters.HTTPAdapter(max_retries=99))
        session.mount("https://",requests.adapters.HTTPAdapter(max_retries=99))
        response = session.get(url=website_url, headers= headers)
        fonteHtml = BeautifulSoup(response.content,'html.parser')
        #print(fonteHtml)
        time.sleep(1)
    except requests.exceptions.ConnectionError as e:
        print ("These aren't the domains we're looking for.")


    print ("codigo fonte adquirido")
    return fonteHtml


#recebe um codigo html e retorna um array com os links que ele contem
def htmlToLink (codFonte):
    arrayLinks = []

    for link in codFonte:
        codFonte.find('a')==True
            arrayLinks.append(link.get('href'))

       # print(arrayLinks)
    return arrayLinks



#declaracao de vetor que recebe o codigo fonte html
arraySites = []


for i in list(d):
    #chamada da funcao urlToHtml(url)
    #a lista e decrescida a cada iteracao
    codHtml=urlToHtml(d.pop())
    time.sleep(2)
    #vetor recebe a url
    arraySites.append(codHtml)

#print (range(len(arraySites)))

for item in arraySites:
    arrayLinkSites =htmlToLink(item)
    print(arrayLinkSites)
    for link in arrayLinkSites:
        print(link)
        print('batata')
