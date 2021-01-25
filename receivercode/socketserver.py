import socket

import codecs

s = socket.socket()

s.bind(('0.0.0.0', 8090))
s.listen(0)


while True:
    client, addr = s.accept()
    # implement START condition
    while True:
        content = client.recv(64)

        # change to STOP condition
        if len(content) ==0:
            break

        # save to file here
        # else:
        # testvid = open('testrecover2.ts', 'wb')
        testtxt = open('testrecover2.txt', 'a')

        print(content)
        # content = content.decode('utf-8')
        # decoded_content = codecs.decode(content, 'hex')

        # testvid.write(decoded_content)
        testtxt.write(content.decode('utf-8'))

        # testvid.close()
        testtxt.close()



    # print("Closing connection.")
    # client.close()
