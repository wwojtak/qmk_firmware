import hid
import platform
from time import sleep


def tobyte(data):
    if type(data) is bytes:
        return data
    else:
        return (data).to_bytes(1, 'big')


def tobytes(data):
    out = b''
    for num in data:
        out += tobyte(num)
    return out


usage_page = int.from_bytes(b'\xFF\x60', 'big')
usage_id = int.from_bytes(b'\x61', 'big')

system = platform.system()
release = platform.release()

ctrlgui_default = tobytes([0, 1, 0])
ctrlgui_swapped = tobytes([0, 1, 1])

devices = hid.enumerate()
for device in devices:
    if (device['manufacturer_string'] == "wwojtak"
            and device['usage_page'] == usage_page
            and device['usage'] == usage_id):
        device = hid.Device(path=device['path'])
        print('connected to {} by {}'.format(
            device.product, device.manufacturer))
        print('running on {} {}'.format(system, release))
        sleep(0.05)
        if system == "Darwin":
            data = ctrlgui_swapped
            print('sent ', int.from_bytes(data, 'big'))
        else:
            data = ctrlgui_default
            print('sent ', int.from_bytes(data, 'big'))
        device.write(data)
        sleep(0.05)
        ctrlgui = int.from_bytes(device.read(2), 'big')
        if ctrlgui == 0:
            print('{} using default ctrlgui'.format(device.product))
        else:
            print('received ', ctrlgui)
            print('{} using swapped ctrlgui'.format(device.product))
        device.close()

'''    raise HIDException(err)
hid.HIDException: The device is not connected.

device['product_string'] in ['crkbd', 'preonic', 'bm40hsrgb']
'''
