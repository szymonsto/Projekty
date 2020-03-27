import socket
import os
import subprocess
import signal
import sys
import threading
import sctp
import prctl

buffer_size = 16384

class ServerTCP:

    server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

    def __init__(self, bind_ip, bind_port):
        serv_add = (bind_ip , bind_port )
        server = ServerTCP.server
        server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR or socket.SO_REUSEPORT,1)
        server.bind((serv_add))
        server.listen(5)
        print ("[*] listening on {}:{}".format(bind_ip,bind_port))

    def connect(self):
        signal.signal(signal.SIGCHLD,signal.SIG_IGN)
        server = ServerTCP.server
        
        while True:
            conn,addr = server.accept()
            print('Accepted connection from {} and port {}'.format(addr[0],addr[1]))

            process_id = os.fork()
            
            if process_id == 0:
                server.close()
                while True:
                    prctl.set_pdeathsig(signal.SIGKILL) #send SIGKILL to child if parent was killed (this is the signal that the calling process will get when its parent die)
                    data = conn.recv(buffer_size)
                    
                    if len(data) > 0: #if client pass sth
                        if data[:2].decode("utf-8") == 'cd': #cd doesen't work in subprocess.Popen
                            try:    #try-except prevents executing incorrect command
                                os.chdir(data[3:].decode("utf-8"))
                                cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                                output_bytes = cmd.stdout.read()
                                output_str = str(output_bytes, "utf-8")
                                conn.send(str.encode(output_str + str(os.getcwd()) + '$'))
                            except:
                                conn.send(str.encode('Wrong folder!\n' + str(os.getcwd()) + '$'))                        
                        else:   #executing command and sending results
                            cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                            output_bytes = cmd.stdout.read()
                            output_str = str(output_bytes, "utf-8")
                            conn.send(str.encode(output_str + str(os.getcwd()) + '$'))
                    if data[:4].decode("utf-8") == 'quit': #if client send "quit" conection will end
                        child_pid = os.getpid()
                        print('Child procees with PID {} has been terminated'.format(child_pid))
                        os.kill(child_pid,signal.SIGKILL)
                        break
                    
                
            if process_id > 0:
                conn.close()
        conn.close()

    def close(self):
        server = ServerTCP.server
        server.close()
        



class ServerSCTP_One2One:

    server = sctp.sctpsocket(socket.AF_INET, sctp.TCP_STYLE, 0)

    def __init__(self, bind_ip, bind_port):
        serv_add = (bind_ip , bind_port )
        server = ServerSCTP_One2One.server
        server.bind((serv_add))
        server.listen(5)
        print ("[*] listening on {}:{}".format(bind_ip,bind_port))

    def connect(self):
        signal.signal(signal.SIGCHLD,signal.SIG_IGN)
        server = ServerSCTP_One2One.server
        while True:
            conn,addr = server.accept()
            print('Accepted connection from {} and port {}'.format(addr[0],addr[1]))

            process_id = os.fork()

        
            if process_id == 0:
                server.close()
                while True:
                    prctl.set_pdeathsig(signal.SIGKILL) #send SIGKILL to child if parent was killed (this is the signal that the calling process will get when its parent die)
                    fromaddr, flags, data, notif = conn.sctp_recv(buffer_size)
                    
                    if len(data) > 0 and data[:4].decode("utf-8") != 'quit':    #if client pass sth
                        if data[:2].decode("utf-8") == 'cd':    #cd doesen't work in subprocess.Popen
                            try:    #try-except prevents executing incorrect command
                                os.chdir(data[3:].decode("utf-8"))
                                cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                                output_bytes = cmd.stdout.read()
                                output_str = str(output_bytes, "utf-8")
                                conn.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'))
                            except:
                                conn.sctp_send(str.encode('Wrong folder!\n' + str(os.getcwd()) + '$'))
                        else:   #executing command and sending results
                            cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                            output_bytes = cmd.stdout.read()
                            output_str = str(output_bytes, "utf-8")
                            conn.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'))
                    if data[:4].decode("utf-8") == 'quit':  #if client send "quit" conection will end
                        child_pid = os.getpid()
                        print('Child procees with PID {} has been terminated'.format(child_pid))
                        os.kill(child_pid,signal.SIGKILL)
                        break
                    
                
            if process_id > 0:
                conn.close()
        conn.close()

    def close(self):
        server = ServerSCTP_One2One.server
        server.close()
        



class ServerSCTP_One2Many:
    
    server = sctp.sctpsocket(socket.AF_INET, sctp.UDP_STYLE, 0)

    def __init__(self, bind_ip, bind_port):
        serv_add = (bind_ip , bind_port )
        server = ServerSCTP_One2Many.server
        server.bind(serv_add)
        server.listen(5)
        print ("[*] listening on {}:{}".format(bind_ip,bind_port))

    def connect(self):
        signal.signal(signal.SIGCHLD,signal.SIG_IGN)
        server = ServerSCTP_One2Many.server
        while True:

            fromaddr, flags, data, notif = server.sctp_recv(buffer_size)

            if len(data) > 0:   #if client pass sth
                if data[:2].decode("utf-8") == 'cd':    #cd doesen't work in subprocess.Popen
                    try:    #try-except prevents executing incorrect command
                        os.chdir(data[3:].decode("utf-8"))  
                        cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                        output_bytes = cmd.stdout.read()
                        output_str = str(output_bytes, "utf-8")
                        server.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'), fromaddr)
                    except:
                        server.sctp_send(str.encode('Wrong folder!\n' + str(os.getcwd()) + '$'), fromaddr)
                else:   #executing command and sending results
                    cmd = subprocess.Popen(data[:], shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE )
                    output_bytes = cmd.stdout.read()
                    output_str = str(output_bytes, "utf-8")
                    server.sctp_send(str.encode(output_str + str(os.getcwd()) + '$'), fromaddr)
            

    def close(self):
        server = ServerSCTP_One2Many.server
        server.close()
        
