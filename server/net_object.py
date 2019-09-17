import socket
import threading
from struct import *


class NetObject:
    def __init__(self):
        self.address = '127.0.0.1'
        self.port = 1234
        self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.clients = []

    def init_connection(self):
        self._server_socket.bind((self.address, self.port))
        self._server_socket.listen()

    def run_listening(self):
        message_handler = threading.Thread(target=self.receive_message, args=())
        message_handler.start()

    def receive_message(self):
        while True:
            client_socket, client_address = self._server_socket.accept()
            print(client_address)
            self.add_new_client(client_address)
            request = client_socket.recv(1024)
            print(request)
            print('id, position(x, y), value = {}'.format(unpack('>iiii', (request[0:16]))))
            text = request[16:]
            print('string = {}'.format(text.decode('utf-8')))

            #client_socket.send('1')
            client_socket.close()

    def add_new_client(self, address):
        pass
