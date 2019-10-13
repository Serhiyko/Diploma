from datetime import (
    datetime,
    timedelta
)
from struct import *
import threading
import uuid

from server.constants import (
    MessageType,
    ErrorCode,
)

from server.mongodb_manager import mongo_manager


class DateTimeManager:
    def __init__(self):
        self._clients = {}
        self._pending_list = []
        self._active_events_list = []
        self.isUpdate = True

    def init_datetime_update_process(self):
        threading.Thread(target=self.run_datetime_update_process, args=()).start()

    def run_datetime_update_process(self):
        trash_list = []
        while True:
            if len(self._pending_list) > 0:
                self._active_events_list = self._active_events_list + self._pending_list.copy()
                self._pending_list.clear()

            for i in range(len(self._active_events_list)):
                doc = self._active_events_list[i]
                current_datetime = datetime.now()

                if (current_datetime.time().hour < 23) and (current_datetime.time().minute < 59):
                    self.isUpdate = True

                if self.isUpdate and (current_datetime.time().hour == 23) and (current_datetime.time().minute >= 59):
                    new_datetime = current_datetime + timedelta(days=1)
                    new_datetime = new_datetime.replace(hour=0, minute=0, second=0, microsecond=0)
                    self.get_active_datetime_events(new_datetime)
                    self.isUpdate = False
                    break

                if doc['datetime'] > current_datetime:
                    continue

                device_value = doc['value']
                device_id = doc['id']
                user_id = doc['user_key']

                if mongo_manager.update_device_value_status((device_id, device_value)):
                    clients_socket = self.get_client_socket(user_id)
                    response_message = pack('>iii', MessageType.GetDateTimeEvent.value, device_id, ErrorCode.Success.value)
                    clients_socket.send(response_message)
                    trash_list.append(doc)
                    del self._active_events_list[i]

    def get_active_datetime_events(self, current_datetime):
        self._pending_list = self._pending_list + mongo_manager.get_active_datetime_records(current_datetime)

    def get_user_id(self, client_socket):
        client_key = [key for key, value in self._clients.items() if value.getpeername() == client_socket.getpeername()]
        if len(client_key) == 0:
            client_key.append(uuid.uuid4())
            self._clients[client_key[0]] = client_socket

        return client_key[0]

    def get_client_socket(self, user_id):
        result = None

        if user_id in self._clients:
            result = self._clients[user_id]

        return result


datetime_manager = DateTimeManager()
