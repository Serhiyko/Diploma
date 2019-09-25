import socket
import threading

from server.constants import (
    MessageType,
    ErrorCode,
    devices
)
from struct import *
from server.mongodb_manager import mongo_manager


class NetObject:
    def __init__(self):
        self.address = '127.0.0.1'
        self.port = 1234
        self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def init_connection(self):
        self._server_socket.bind((self.address, self.port))

    def run_listening(self):
        self._server_socket.listen(10)
        threading.Thread(target=self.receive_message, args=()).start()

    def receive_message(self):
        while True:
            client_socket, client_address = self._server_socket.accept()
            print(client_address)
            threading.Thread(target=self.handle_client, args=(client_socket,)).start()
                #print('id, position(x, y), value = {}'.format(unpack('>iiii', (message[0:16]))))
                # text = request[16:]
                # print('string = {}'.format(text.decode('utf-8')))

    def handle_client(self, client_socket):
        try:
            while True:
                message = client_socket.recv(1024)

                response = self.deserialize_message(message)
                response_message = pack('>iii', response[0], response[1], response[2])

                client_socket.send(response_message)
        finally:
            client_socket.close()

    def deserialize_message(self, message):
        message_id = unpack('>i', message[0:4])
        response = ErrorCode.InvalidMessageType.value

        if message_id == MessageType.UpdateDeviceStatus.value:
            device_metadata = self.get_update_device_value_metadata(message)
            if len(device_metadata) == 0:
                response = ErrorCode.InvalidDeviceParameters.value
            else:
                mongo_manager.update_device_value_status(device_metadata)
                response = (device_metadata[0],) + ErrorCode.Success.value
                print('update device: {}'.format(device_metadata[0]))
        elif message_id == MessageType.UpdateDevicePosition.value:
            device_id = unpack('>i', message[4:8])
            position_x = unpack('>i', message[8:12])
            position_y = unpack('>i', message[12:16])
            #TODO: update position value
        elif message_id == MessageType.DeleteDevice.value:
            device_id = unpack('>i', message[4:8])
            if device_id:
                mongo_manager.delete_device(device_id)
                response = device_id + ErrorCode.Success.value
                print('delete device: {}'.format(device_id[0]))
        elif message_id == MessageType.CreateDevice.value:
            device_metadata = self.get_create_device_metadata(message)
            if len(device_metadata) == 0:
                response = ErrorCode.InvalidDeviceParameters.value
            else:
                mongo_manager.create_new_device(device_metadata)
                response = (device_metadata[1],) + ErrorCode.Success.value
                print('create device: {}'.format(device_metadata[1]))
        elif message_id == MessageType.GetDevices.value:
            #TODO: return all devices
            pass
        else:
            response = ErrorCode.InvalidMessageType.value

        return message_id + response

    def get_create_device_metadata(self, message):
        device_type = unpack('>i', message[4:8])
        if device_type[0] in devices:
            device_type = devices[device_type[0]]
        else:
            return ()

        device_id = unpack('>i', message[8:12])
        location_id = unpack('>i', message[12:16])
        position_x = unpack('>i', message[16:20])
        position_y = unpack('>i', message[20:24])

        return device_type, device_id[0], location_id[0], position_x[0], position_y[0]

    def get_update_device_value_metadata(self, message):
        device_id = unpack('>i', message[4:8])
        value = unpack('>i', message[8:12])

        return device_id + value
