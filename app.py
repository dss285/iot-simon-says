from flask import Flask
import atexit
import threading
import queue
import serial
import time
# if __name__ == '__main__':
#     ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
#     ser.reset_input_buffer()
#     while True:
#         ser.write(b"Hello from Raspberry Pi!\n")
#         line = ser.readline().decode('utf-8').rstrip()
#         print(line)
#         time.sleep(1)

out_queue = queue.Queue()
in_queue = queue.Queue()
def arduino():
    global out_queue
    global in_queue
    while True:
        try:
            ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
            while True:
                while not out_queue.empty():
                    ser.write(out_queue.get())
                
                
                line = ser.readline().decode('utf-8').rstrip()
                if line:
                    print(line)
                    in_queue.put(line)
            ser.close()
        except Exception as e:
            print(e)

arduino_thread = threading.Thread(target=arduino, daemon=True)
def create_app():
    app = Flask(__name__)

    def interrupt():
        global arduino_thread
    def start():
        # Do initialisation stuff here
        global arduino_thread
        arduino_thread.start()

    # Initiate
    start()
    # When you kill Flask (SIGTERM), clear the trigger for the next thread
    atexit.register(interrupt)
    return app
app = create_app()
@app.route('/')
def hello_world():
    out_queue.put(b"Hello from Flask!\n")
    return 'Hello, World!'
if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", threaded=False, processes=0)