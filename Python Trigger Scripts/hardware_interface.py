import requests
import time

class Hardware:
    def __init__(self, IP_ADDRESS="http://192.168.0.108/"):
        self.ip = IP_ADDRESS
        requests.post(self.ip + "pumpoff") 
        requests.post(self.ip + "ledoff")

    def pump(self, status):
        if(status):
            requests.post(self.ip + "pumpon") 
        else:
            requests.post(self.ip + "pumpoff") 

    def led(self, status):
        if(status):
            requests.post(self.ip + "ledon") 
        else:
            requests.post(self.ip + "ledoff") 


def main():
    h = Hardware()
    h.pump(1)
    time.sleep(1)
    h.pump(0)

    time.sleep(1)
    h.led(1)
    time.sleep(1)
    h.led(0)
    time.sleep(1)

if __name__ == "__main__":
    main()