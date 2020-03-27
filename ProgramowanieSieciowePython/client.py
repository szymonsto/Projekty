import socket
import threading
import os
import sys
import sctp
import signal
import time

buffer_size = 16384

def signal_handler(self, sig):  #used in handling SIGINT (ctrl+C)
    try:    #try-except, because it shandler should work with TCP, SCTPOne2One and SCTPOne2Many
        client = ClientTCP.client
        client.send(str.encode('quit'))
        client.close()
    except:
        client = ClientSCTP_TCP.client
        client.sctp_send(str.encode('quit'), ('127.0.0.1',8880))
        client.close()
    finally:
        os.system('clear')
        sys.exit()



class ClientTCP:
    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    signal.signal(signal.SIGINT, signal_handler)
    
    def __init__(self , target_host, target_port):
        client = ClientTCP.client
        client.connect((target_host,target_port))
    
    def send_commands(self):
        client = ClientTCP.client
        cmd = 'clear'

        while True:

            if len(str.encode(cmd)) > 0:
                client.send(str.encode(cmd))

                if cmd == 'quit':
                    client.close()
                    sys.exit()

                server_response = str(client.recv(buffer_size), "utf-8")
                print(server_response, end="")
            
            cmd = input()
        
    def close(self):
        client = ClientTCP.client
        client.close()


class ClientSCTP_TCP:
    client = sctp.sctpsocket(socket.AF_INET, sctp.TCP_STYLE, 0)
    signal.signal(signal.SIGINT, signal_handler)
    def __init__(self, target_host, target_port):
        client = ClientSCTP_TCP.client
        targetaddr = (target_host, target_port)
        client.connect(targetaddr)

    def send_commands(self):
        client = ClientSCTP_TCP.client
        cmd = 'clear'

        while True:           
            if len(str.encode(cmd)) > 0:
                client.sctp_send(str.encode(cmd))

                if cmd == 'quit':
                    client.close()
                    sys.exit()

                framaddr, flags, msg, notif = client.sctp_recv(buffer_size)
                server_response = str(msg, "utf-8")
                print(server_response, end="")             
            
            cmd = input()
        
    def close(self):
        client = ClientSCTP_TCP.client
        client.close()

class ClientSCTP_UDP(ClientSCTP_TCP):
    client = sctp.sctpsocket(socket.AF_INET, sctp.UDP_STYLE, 0)
    def __init__(self):
        client = ClientSCTP_UDP.client
        
    def send_commands(self, target_host, target_port):
        targetaddr = (target_host, target_port)
        client = ClientSCTP_TCP.client
        cmd = 'clear'

        while True:           
            if len(str.encode(cmd)) > 0:
                client.sctp_send(str.encode(cmd), targetaddr)

                if cmd == 'quit':
                    client.close()
                    sys.exit()

                framaddr, flags, msg, notif = client.sctp_recv(buffer_size)
                server_response = str(msg, "utf-8")
                print(server_response, end="")

                
            cmd = input()



