import socket


class Server:

    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)


    def __del__(self):
        self.socket.close()


    def start(self, ip: str, port: int) -> None:
        self.socket.bind((ip, port))
        self.socket.listen()
        client, (ip, port) = self.socket.accept()
        with client:
            print(f"Connected from: {ip}:{port}\n")
            while True:
                data = client.recv(1024)
                if not data:
                    break