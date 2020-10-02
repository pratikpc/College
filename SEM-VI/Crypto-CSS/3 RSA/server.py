import socket
import rsa
import json
import Crypto;

localIP = "127.0.0.1"
localPort = 20012

bufferSize = 4096

# Create a datagram socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

      # Bind to address and ip

      s.bind((localIP, localPort))
      s.listen(1)
      print("TCP server up and listening")
      conn, addr = s.accept()

      p = rsa.GetPrime(500,500)
      q = rsa.GetPrime(500,500)
      (pub, priv) = rsa.RSAKeyFind(p, q)
      bytesToSend = str.encode(json.dumps(pub))
      conn.send(bytesToSend, localPort)
      enc = int(conn.recv(bufferSize).decode())
      dec = rsa.DecryptRSA(enc, priv)
      print("Decrypted is " + str(dec) + " Enc was "+ str(enc))
      # Listen for incoming datagrams