import serial
import os
import time

import codecs

ser = serial.Serial('COM4', 115200, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)

dirname = 'transportfiles/'

for file in os.listdir(dirname):
    with open(dirname+file, 'rb') as f:
        # print(str(file))
        # all_content = str(f.read())
        all_content = f.read()
        # .decode('latin1')
        # .encode('utf-8'); # attempting to address decoding issues

        all_content = codecs.encode(all_content, 'hex')

        print(len(all_content))
        f.close()



        # all_content = bytes(all_content, 'latin1')
        n = 64 # max buffer length? fuckin Uno piece of trash lookin ass = 64,
        # esp32 = 256 (allegedly)
        chunked_data = [all_content[i:i+n] for i in range(0, len(all_content), n)]
        counter = 1

        ser.flushInput()
        ser.flushOutput()

        ser.write(bytes('START', 'utf-8'))

        time.sleep(1)

        ser.flushInput()
        ser.flushOutput()


        for chunk in chunked_data:
            # ser.write(bytes(chunk, 'utf-8'))
            ser.write(chunk)
            # ser.write(bytes(chunk, 'latin1')) # again, addresing decoding issues
            print('Sending chunk ' + str(counter) + '/'+ str(len(chunked_data)) + ': ' + str(chunk))
            # print(chunk) # changed from str(chunk)
            # ser.flushOutput()
            counter += 1
            time.sleep(0.1)

            ser.flushInput()
            ser.flushOutput()


        time.sleep(1)
        # ser.write(bytes('STOP', 'utf-8'))
        ser.write(bytes('STOP', 'utf-8'))
