from datetime import datetime

import socket
import threading

from server.constants import (
    MessageType,
    ErrorCode,
    devices
)
from struct import *
from server.mongodb_manager import mongo_manager
from server.datetime_manager import datetime_manager


class NetObject:
    def __init__(self):
        self.address = '127.0.0.1'
        self.port = 1234
        self._server_socket = None

    def init_connection(self):
        self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server_socket.bind((self.address, self.port))

    def run_listening(self):
        self._server_socket.listen(10)
        threading.Thread(target=self.receive_message, args=()).start()

    def receive_message(self):
        while True:
            client_socket, client_address = self._server_socket.accept()
            print(client_socket.getsockname())
            print(client_socket.getpeername())
            print(client_address)
            threading.Thread(target=self.handle_client, args=(client_socket,)).start()

    def handle_client(self, client_socket):
        try:
            while True:
                message = client_socket.recv(1024)

                response = self.deserialize_message(message, client_socket)
                response_message = pack('>iii', response[0], response[1], response[2])

                client_socket.send(response_message)
        finally:
            datetime_manager.unregister_user(client_socket)
            client_socket.close()

    def deserialize_message(self, message, client_socket):
        message_id = unpack('>i', message[0:4])
        response = ErrorCode.InvalidMessageType.value

        if message_id == MessageType.SendUserID.value:
            user_id = unpack('>i', message[4:8])
            if self.register_user(client_socket, user_id):
                response = ErrorCode.Success.value
            else:
                response = ErrorCode.InvalidUserId.value
        elif message_id == MessageType.UpdateDeviceStatus.value:
            device_metadata = self.get_update_device_value_metadata(message)
            if len(device_metadata) == 0:
                response = ErrorCode.InvalidDeviceParameters.value
            else:
                mongo_manager.update_device_value_status(device_metadata)
                response = (device_metadata[0],) + ErrorCode.Success.value
                print('update device: {}'.format(device_metadata[0]))
        elif message_id == MessageType.UpdateDevicePosition.value:
            device_metadata = self.get_device_position_metadata(message)
            mongo_manager.update_device_positions(device_metadata)
            response = (device_metadata[0],) + ErrorCode.Success.value
            print('update device position: {}'.format(device_metadata[0]))
        elif message_id == MessageType.DeleteDevice.value:
            device_id = unpack('>i', message[4:8])
            user_id = unpack('>i', message[8:12])
            if device_id and user_id:
                device_metadata = device_id + user_id
                mongo_manager.delete_device(device_metadata)
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
        elif message_id == MessageType.SetDateTimeEvent.value:
            device_metadata = self.get_datetime_event_data(message)
            datetime_manager.register_user(client_socket, device_metadata[3])
            device_metadata = device_metadata

            mongo_manager.insert_datetime_record(device_metadata)
            datetime_manager.add_new_event(device_metadata)
            response = (device_metadata[0],) + ErrorCode.Success.value
            print('date time is created: {}'.format(device_metadata[0]))
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
        user_id = unpack('>i', message[12:16])
        location_id = unpack('>i', message[16:20])
        position_x = unpack('>i', message[20:24])
        position_y = unpack('>i', message[24:28])

        return device_type, device_id[0], user_id[0], location_id[0], position_x[0], position_y[0]

    def get_update_device_value_metadata(self, message):
        device_id = unpack('>i', message[4:8])
        user_id = unpack('>i', message[8:12])
        value = unpack('>i', message[12:16])

        return device_id[0], user_id[0], value[0]

    def get_datetime_event_data(self, message):
        device_id = unpack('>i', message[4:8])
        user_id = unpack('>i', message[8:12])
        value = unpack('>i', message[12:16])
        byte_string = message[16:]
        device_datetime = byte_string.decode('utf-8')
        device_datetime = datetime.strptime(device_datetime, '%d.%m.%YT%H:%M:%S')

        return device_id[0], value[0], device_datetime, user_id[0]

    def get_device_position_metadata(self, message):
        device_id = unpack('>i', message[4:8])
        user_id = unpack('>i', message[8:12])
        position_x = unpack('>i', message[12:16])
        position_y = unpack('>i', message[16:20])

        return device_id[0], user_id[0], position_x[0], position_y[0]

    def register_user(self, client_socket, user_id):
        return True
