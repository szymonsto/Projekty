import socket
import threading
import os
import sys

class ClientTCP:

    def __init__(self , target_host, target_port):
        client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        client.connect((target_host,target_port))
    
    def send_commands(self, client):
        
        cmd = 'clear'

        while True:
                        
            if len(str.encode(cmd)) > 0:
                client.send(str.encode(cmd))

                if cmd == 'quit':
                    client.close()
                    sys.exit()

                server_response = str(client.recv(1024), "utf-8")
                print(server_response, end="")
            
            cmd = input()
        
    def close(self)
        client.close()

       
