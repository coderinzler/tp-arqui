import pyfirmata
import time
import serial


board = pyfirmata.Arduino('COM1')

temp_sensor_pin = 'A0'
relay_pin = 9

sensor = board.get_pin('a:' + str(temp_sensor_pin) + ':i')
relay = board.get_pin('d:' + str(relay_pin) + ':o')

def read():
    return sensor
def sensor_celsius(value):
    # 5/1024 es 0,0048 V
    voltage = value * (5/1024)
    tmp_celsius = voltage * 100

while True:
    sens_value = read(sensor)
    celsius = sensor_celsius(sens_value)
    print('Temperature: ' + celsius + 'C')
    if celsius >= 21 and celsius <= 300:
        relay.write(1)
        print('Motor speed:')
    else:
        relay.write(0)
        print('Motor apagado')
    time.sleep(1)


board.exit()