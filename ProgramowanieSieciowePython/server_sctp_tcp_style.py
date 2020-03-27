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
server = sctp.sctpsocket(socket.AF_INET, sctp.TCP_STYLE, 0)

server.bind((serv_add))
server.listen(5)
print ("[*] listening on {}:{}".format(bind_ip,bind_port))

signal.signal(signal.SIGCHLD,signal.SIG_IGN)
    
while True:
    conn,addr = server.accept()
    print('Accepted connection from {} and port {}'.format(addr[0],addr[1]))

    process_id = os.fork()

 
    if process_id == 0:
        server.close()
        while True:

            fromaddr, flags, data, notif = conn.sctp_recv(1024)
            if data[:2].decode("utf-8") == 'cd':
                os.chdir(data[3:].decode("utf-8"))
            if len(data) > 0:
                cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                output_bytes = cmd.stdout.read()
                output_str = str(output_bytes, "utf-8")
                conn.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'))
            if data[:4].decode("utf-8") == 'quit':
                child_pid = os.getpid()
                print('Child procees with PID {} has been terminated'.format(child_pid))
                os.kill(child_pid,signal.SIGKILL)
                break
            
        
    if process_id > 0:
        conn.close()


server.close()
conn.close()