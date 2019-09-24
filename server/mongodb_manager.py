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
        create new device
        :param device_metadata: (type, id, value, location_id, position_x, position_y)
        :type device_metadata: tuple
        :return: ObjectId
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

    def update_device_value_status(self, device_metadata):
        '''
        update value for some device
        :param device_metadata: device_metadata = (id, value)
        :type device_metadata: tuple
        :return: document
        '''
        return self._db.devices.update_one(
            {'id': device_metadata[0]},
            {
                '$set': {'value': device_metadata[1]}
            }
        )

    def delete_device(self, device_id):
        '''
        delete device
        :param device_id: device id
        :type device_id: tuple
        :return: document
        '''
        return  self._db.devices.delete_one(
            {'id': device_id[0]}
        )

mongo_manager = MongoDBManager()
