from datetime import (
    datetime,
    timedelta
)
from struct import *
import threading

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
        self.get_active_datetime_events(datetime.now())

        while True:
            if len(self._pending_list) > 0:
                self._active_events_list = self._active_events_list + self._pending_list.copy()
                self._pending_list.clear()

            for i in range(len(self._active_events_list)):
                event_record = self._active_events_list[i]
                current_datetime = datetime.now()

                if (current_datetime.time().hour < 23) and (current_datetime.time().minute < 59) and (not self.isUpdate):
                    self.isUpdate = True

                if self.isUpdate and (current_datetime.time().hour == 23) and (current_datetime.time().minute >= 59):
                    new_datetime = current_datetime + timedelta(days=1)
                    new_datetime = new_datetime.replace(hour=0, minute=0, second=0, microsecond=0)
                    self.get_active_datetime_events(new_datetime)
                    self.isUpdate = False

                if event_record['datetime'] > current_datetime:
                    continue

                device_value = event_record['value']
                device_id = event_record['id']
                user_id = event_record['user_id']

                if mongo_manager.update_device_value_status((device_id, user_id, device_value)):
                    clients_socket = self.get_client_socket(user_id)
                    if clients_socket:
                        response_message = pack('>iiii',
                                                MessageType.GetDateTimeEvent.value[0],
                                                device_id,
                                                user_id,
                                                device_value)
                        clients_socket.send(response_message)
                    del self._active_events_list[i]

    def get_active_datetime_events(self, current_datetime):
        self._pending_list = self._pending_list + mongo_manager.get_active_datetime_records(current_datetime)

    def register_user(self, client_socket, user_id):
        client_key = [key for key, value in self._clients.items() if value.getpeername() == client_socket.getpeername()]
        if len(client_key) == 0:
            client_key.append(user_id)
            self._clients[client_key[0]] = client_socket

    def unregister_user(self, client_socket):
        self._clients = {k: v for k, v in self._clients.items() if v.getpeername() == client_socket.getpeername()}

    def get_client_socket(self, user_id):
        return self._clients[user_id] if user_id in self._clients else None

    def add_new_event(self, device_metadata):
        new_item = {
            'id': device_metadata[0],
            'value': device_metadata[1],
            'datetime': device_metadata[2],
            'user_id': device_metadata[3]
        }

        self._pending_list.append(new_item)


datetime_manager = DateTimeManager()
