import threading

import server


SERVER_IP = "127.0.0.1"
SEND_PORT = 8888
RECV_PORT = 9999


def main() -> None:
    send_server = server.Server()
    send_server_thread = threading.Thread(target=server.Server.start, args=[send_server, SERVER_IP, SEND_PORT])
    send_server_thread.start()

    recv_server = server.Server()
    recv_server_thread = threading.Thread(target=server.Server.start, args=[recv_server, SERVER_IP, RECV_PORT])
    recv_server_thread.start()

    send_server_thread.join()
    recv_server_thread.join()


if __name__ == "__main__":
    main()