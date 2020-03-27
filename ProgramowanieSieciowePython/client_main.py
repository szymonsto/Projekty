import client

print("Choose type of client:")
print("[1]-TCP [2]-SCTP ONE TO ONE [3]-SCTP ONE TO MANY")

choice = input()

if choice == '1':

    clienttcp = client.ClientTCP('127.0.0.1',8880)
    clienttcp.send_commands()
    clienttcp.close()

if choice == '2':

    clientsctptcp = client.ClientSCTP_TCP('127.0.0.1',8880)
    clientsctptcp.send_commands()
    clientsctptcp.close()

if choice == '3':

    clientsctpudp = client.ClientSCTP_UDP()
    clientsctpudp.send_commands('127.0.0.1',8880)
    clientsctpudp.close()