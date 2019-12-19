#ifndef RESOURCES_H
#define RESOURCES_H

enum class DeviceType
{
    SimpleLamp,
    ComplexLamp,
    Ventilator,
    Jalousie,
    Door,
    Battery,
    None
};

enum class LocationType
{
    FirstFloor,
    SecondFloor,
    None
};

enum class MessageType
{
    UpdateDeviceStatus = 1,
    UpdateDevicePosition,
    CreateDevice,
    DeleteDevice,
    GetDevices,
    SetDateTimeEvent,
    GetDateTimeEvent,
    SendUserID,
    None
};

#endif // RESOURCES_H
