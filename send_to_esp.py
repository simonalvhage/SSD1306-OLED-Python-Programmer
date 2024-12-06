import serial
import time

class EspDisplay:
    def __init__(self):
        self.serial_port = '/dev/ttyUSB0'
        self.baud_rate = 115200

    def print_on_line(self, line, font_size, text):
        line = (line - 1) * 25
        with serial.Serial(self.serial_port, self.baud_rate, timeout=1) as ser:
            command = f"F{font_size}XY0,{line} {text}\n"
            ser.write(command.encode())
            time.sleep(0.1)

    def clear_display(self):
        with serial.Serial(self.serial_port, self.baud_rate, timeout=1) as ser:
            ser.write("CLEAR\n".encode())
            time.sleep(0.1)

def main():
    e = EspDisplay()
    e.print_on_line(1, 2, "Hello")
    e.print_on_line(2, 2, "There")
    time.sleep(5)
    e.clear_display()

if __name__ == '__main__':
    main()
