import bson
from datetime import timedelta
from pymongo import MongoClient


class MongoDBManager():
    def __init__(self):
        connection = MongoClient('localhost', 27017)
        self._db = connection.get_database(
            'dyploma_db',
            bson.codec_options.CodecOptions(uuid_representation=bson.binary.UUID_SUBTYPE)
        )

    def create_new_device(self, device_metadata):
        '''
        create new device
        :param device_metadata: (type, id, user_id, location_id, position_x, position_y)
        :type device_metadata: tuple
        :return: ObjectId
        '''
        return self._db.devices.insert_one(
            {
                'type': device_metadata[0],
                'id': device_metadata[1],
                'user_id': device_metadata[2],
                'value': 0,
                'location_id': device_metadata[3],
                'position_x': device_metadata[4],
                'position_y': device_metadata[5]
            }
        )

    def update_device_value_status(self, device_metadata):
        '''
        update value for some device
        :param device_metadata: device_metadata = (id, user_id, value)
        :type device_metadata: tuple
        :return: document
        '''
        return self._db.devices.update_one(
            {'$and': [
                {'id': device_metadata[0]},
                {'user_id': device_metadata[1]}
            ]},
            {
                '$set': {'value': device_metadata[2]}
            }
        )

    def delete_device(self, device_metadata):
        '''
        delete device
        :param device_metadata: device id, user id
        :type device_metadata: tuple
        :return: None
        '''
        self._db.devices.delete_one(
            {'$and': [
                {'id': device_metadata[0]},
                {'user_id': device_metadata[1]}
            ]}
        )

        self._db.datetime_requests.delete_one(
            {'$and': [
                {'id': device_metadata[0]},
                {'user_id': device_metadata[1]}
            ]}
        )

    def insert_datetime_record(self, device_metadata):
        '''
        insert datetime record for device
        :param device_metadata: (id, value, datetime, user_id)
        :return: document
        '''
        return self._db.datetime_requests.update_one(
            {'$and': [
                {'id': device_metadata[0]},
                {'user_id': device_metadata[3]}
            ]},
            {
                '$set': {
                    'id': device_metadata[0],
                    'value': device_metadata[1],
                    'datetime': device_metadata[2],
                    'user_id': device_metadata[3]
                }
            }, upsert=True
        )

    def get_active_datetime_records(self, current_datetime):
        '''
        :return: record with valid datetime
        '''
        limit_datetime = current_datetime + timedelta(days=1)

        responce = self._db.datetime_requests.find({
            '$and': [
                {'datetime': {'$gte': current_datetime}},
                {'datetime': {'$lt': limit_datetime}}
            ]
        })

        return [document for document in responce]

    def update_device_positions(self, device_metadata):
        '''
        update device_metadata
        :param device_metadata: (device_id, user_id, position_x, position_y)
        :return: document
        '''

        return self._db.devices.update_one(
            {'$and': [
                {'id': device_metadata[0]},
                {'user_id': device_metadata[1]}
            ]},
            {
                '$set': {
                    'position_x': device_metadata[2],
                    'position_y': device_metadata[3]
                }
            }
        )


mongo_manager = MongoDBManager()
