import unittest

from datetime import datetime
from server.net_object import NetObject
from struct import *


class TestMessageDeserialization(unittest.TestCase):
    def setUp(self) -> None:
        self.net_object = NetObject()

    def test_create_device(self):
        device_type = 0
        device_id = 1
        user_id = 2
        location_id = 1
        position_x = 124
        position_y = 68

        message = pack('>iiiiiii',
                       0,
                       device_type,
                       device_id,
                       user_id,
                       location_id,
                       position_x,
                       position_y)

        response = self.net_object.get_create_device_metadata(message)
        expected_result = ('simple_lamp', 1, 2, 1, 124, 68)

        self.assertEqual(response, expected_result)

    def test_get_update_device_value_metadata(self):
        device_id = 1
        user_id = 2
        value = 100

        message = pack('>iiii', 0, device_id, user_id, value)
        response = self.net_object.get_update_device_value_metadata(message)
        expected_result = (1, 2, 100)

        self.assertEqual(response, expected_result)

    def test_get_device_position_metadata(self):
        device_id = 1
        user_id = 2
        position_x = 100
        position_y = 200

        message = pack('>iiiii', 0, device_id, user_id, position_x, position_y)
        response = self.net_object.get_device_position_metadata(message)
        expected_result = (1, 2, 100, 200)

        self.assertEqual(response, expected_result)

    def test_get_datetime_event_data(self):
        device_id = 1
        user_id = 2
        value = 100
        date_value = '10.11.2019T14:22:00'
        device_datetime = datetime.strptime(date_value, '%d.%m.%YT%H:%M:%S')

        message = pack('>iiii', 0, device_id, user_id, value)
        message = message + bytes(date_value, 'utf-8')
        response = self.net_object.get_datetime_event_data(message)
        expected_result = (1, 100, device_datetime, 2)

        self.assertEqual(response, expected_result)


if __name__ == "__main__":
    unittest.main()
