from django.shortcuts import render
from django.http import HttpResponse

import requests
import codecs



def index(request):
    r = requests.get('http://192.168.1.41/test.txt')

    content = r.text
    decoded_content = codecs.decode(content, 'hex')

    # a test of saving .ts file?
    dest = open('thebigboi.ts', 'wb')
    dest.write(decoded_content)
    dest.close()

    # return HttpResponse(content)
    return render(request,'template.htm')
