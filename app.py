from flask import Flask, render_template
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
gameRunning = False
def arduino():
    global out_queue
    global in_queue
    global gameRunning
    while True:
        try:
            ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
            while True:
                while not out_queue.empty():
                    ser.write(out_queue.get())
                    out_queue.queue.clear()
                
                line = ser.readline().decode('utf-8').rstrip()
                if line:
                    out_queue.queue.clear()
                    in_queue.put(line)
                    print(line)
            ser.close()
        except Exception as e:
            print(e)

arduino_thread = threading.Thread(target=arduino, daemon=True)
def create_app():
    app = Flask(__name__, static_url_path='', static_folder='static')

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
    
    return render_template('home.html', testing="ok")
@app.route('/newgame')
def wait_for_queue():
    out_queue.put(b"newgame\n")
    return ""
@app.route('/lastgame')
def lastgame():
    return in_queue.get()
if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", threaded=False, processes=0)