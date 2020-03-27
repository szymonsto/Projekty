from daemon import daemon
import server

class TCP_daemon(daemon):
 
    def run(self):
        daemonserv = server.ServerTCP('127.0.0.1',8880)
        daemonserv.connect()
        daemonserv.close()
    

class SCTP_One2One_daemon(daemon):

    def run(self):
        daemonserv = server.ServerSCTP_One2One('127.0.0.1',8880)
        daemonserv.connect()
        daemonserv.close()

class SCTP_One2Many_daemon(daemon):

    def run(self):
        daemonserv = server.ServerSCTP_One2Many('127.0.0.1',8880)
        daemonserv.connect()
        daemonserv.close()
    
