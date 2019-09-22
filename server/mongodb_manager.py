from pymongo import (
    MongoClient,
    errors
)


class MongoDBManager():
    def __init__(self):
        connection = MongoClient('localhost', 27017)
        self._db = connection.dyploma_db

    def create_new_device(self, device_metadata):
        '''
        :param device_metadata: device metadata
        :type device_metadata: tuple
        (type, id, value, location_id, position_x, position_y)
        :return:
        '''
        return self._db.devices.insert_one(
            {
                'type': device_metadata[0],
                'id': device_metadata[1],
                'value': 0,
                'location_id': device_metadata[2],
                'position_x': device_metadata[3],
                'position_y': device_metadata[4]
            }
        )

    def test(self):
        collection = self._db.devices
        for post in collection.find():
            print(post)


mongo_manager = MongoDBManager()
