__author__ = 'rama'

import matplotlib.pyplot as plt
import cairocffi
import urllib3, requests, re
from bs4 import BeautifulSoup
import networkx as nx

from collections import deque, Counter
G = nx.Graph()

headers ={}
headers['User-Agent'] = "Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.27 Safari/537.17"

d = deque() #lista duplamente encadeada para colocar os sites
num = 0
while str!='FIM': #faca enquanto nao str for diferente de FIM
    str = input() #ler do teclado e grava em str
   # print (str)

    if str != 'FIM':
        G.add_node(num,url=str)
        num = num+1

    d.append(str) # grava str no fim do deque
d.remove('FIM') # remove todos as ocorrencias de FIM da lista



#print(G.nodes('url'))


#recebe uma url e devolve o codigo em html dela
def urlToHtml (website_url):
    print("buscando codigo fonte de ",website_url)

    try:
        session = requests.Session()
        session.mount("http://",requests.adapters.HTTPAdapter(max_retries=99))
        session.mount("https://",requests.adapters.HTTPAdapter(max_retries=99))
        response = session.get(url=website_url, headers= headers)
        fonteHtml = BeautifulSoup(response.content,'html.parser')

        #if(website_url=="http://www.bb.com.br"):
            #print(fonteHtml)
    except requests.exceptions.ConnectionError as e:
        print ("These aren't the domains we're looking for.")


    print ("codigo fonte adquirido")
    return fonteHtml


#recebe um codigo html e retorna um array com os links que ele contem
def htmlToLink (codFonte):
    arrayLinks = []
    for link in codFonte.find_all('a'):
        try:
            if is_http_url(link.get('href'))==True:
                arrayLinks.append(link.get('href'))
        except:
            pass
            #print(link.get('href'),"não é link")

       # print(arrayLinks)

    return arrayLinks

#testa url
def is_http_url(s):
    if re.match('https?://(?:www)?(?:[\w-]{2,255}(?:\.\w{2,6}){1,2})(?:/[\w&%?#-]{1,300})?',s):
        return True
    else:
        return False



#declaracao de vetor que recebe o codigo fonte html
arraySites = []


#busca o cod html de cada url em um grafo
for i in G:
    codHtml=urlToHtml(G.node[i]['url'])
    #print(G.node[i]['url'])
    arraySites.append(codHtml)

count1=0

for item in arraySites:


    #print(item)
    arrayLinkSites =htmlToLink(item)
    for link in arrayLinkSites:
        G.add_node(G.number_of_nodes()+1,url=link)
        G.add_edge(count1,G.number_of_nodes(),url=link)
        #print(link)
        pass
    count1 = count1+1


#layout do grafo
pos = nx.spring_layout(G)

#desenha o grafo com o layout
nx.draw(G, pos)


#desenha rotulos
#node_labels= nx.get_node_attributes(G,'url')
#nx.draw_networkx_labels(G,pos,labels = node_labels, font_size=5)
#edge_labels = nx.get_edge_attributes(G,'url')
#nx.draw_networkx_edge_labels(G,pos,labels = edge_labels, font_size=0.1)


#mostra o grafo
plt.show()