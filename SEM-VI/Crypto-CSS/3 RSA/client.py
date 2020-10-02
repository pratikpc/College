import socket
import rsa
import json

serverAddressPort = ("127.0.0.1", 20012)
message = 31
bufferSize = 4096

# Create a TCP socket at client side

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # Send to server using created TCP socket
        s.connect(serverAddressPort)
        print("Message Sent was "+ str(message))
        pub = s.recv(bufferSize)
        pub = json.loads(pub)
        enc = str.encode(json.dumps(rsa.EncryptRSA(message, pub)))
        s.sendall(enc)
