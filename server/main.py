from server.net_object import NetObject


if __name__ == "__main__":
    # #b'\x00\x02'
    # var = 2
    # print(str(var).encode('utf-8'))
    net_object = NetObject()

    net_object.init_connection()
    net_object.run_listening()
