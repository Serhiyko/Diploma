from server.net_object import NetObject
from server.datetime_manager import datetime_manager


if __name__ == "__main__":
    net_object = NetObject()

    net_object.init_connection()
    net_object.run_listening()

    datetime_manager.init_datetime_update_process()
