import server
import server_daemon
import sys
import signal


if len(sys.argv)==1: #if user didn't pass any arguments
    print("Choose type of server:")
    print("[1]-TCP [2]-SCTP ONE TO ONE [3]-SCTP ONE TO MANY")

    choice = input()

    if choice == '1':

        servertcp = server.ServerTCP('127.0.0.1',8880)
        servertcp.connect()
        servertcp.close()

    if choice == '2':

        serversctp_tcp = server.ServerSCTP_One2One('127.0.0.1',8880)
        serversctp_tcp.connect()
        serversctp_tcp.close()

    if choice == '3':

        serversctp_udp = server.ServerSCTP_One2Many('127.0.0.1',8880)
        serversctp_udp.connect()
        serversctp_udp.close()

else: #if user didn't pass two arguments

    if sys.argv[1] == 'tcp':
        daemontcp = server_daemon.TCP_daemon("/home/patryk/daemon_tcp.pid")

        if sys.argv[2] == 'start':
            
            daemontcp.start()
        
        if sys.argv[2] == 'stop':

            daemontcp.stop()

        if sys.argv[2] == 'restart':

            daemontcp.restart()
    

    if sys.argv[1] == 'sctptcp':
        daemonsctptcp = server_daemon.SCTP_One2One_daemon("/home/patryk/daemon_sctptcp.pid")

        if sys.argv[2] == 'start':
            
            daemonsctptcp.start()
        
        if sys.argv[2] == 'stop':
            
            daemonsctptcp.stop()

        if sys.argv[2] == 'restart':

            daemonsctptcp.restart()

    if sys.argv[1] == 'sctpudp':
        daemonsctpudp = server_daemon.SCTP_One2Many_daemon("/home/patryk/daemon_sctpudp.pid")

        if sys.argv[2] == 'start':
            
            daemonsctpudp.start()
        
        if sys.argv[2] == 'stop':
            
            daemonsctpudp.stop()

        if sys.argv[2] == 'restart':

            daemonsctpudp.restart()
