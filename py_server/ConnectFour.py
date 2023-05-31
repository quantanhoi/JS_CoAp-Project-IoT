import sys
import threading

# ConnectFour.py

from PyQt5.QtCore import pyqtSlot
from PyQt5.QtWidgets import QMainWindow, QStackedWidget, QApplication

from aiocoap import Context
import asyncio

from MenuScreen import *
from GameScreen import *
from ControllerResource import *


class ConnectFour(QMainWindow):
    def __init__(self):
        super().__init__()

        # ---UI---
        self.setWindowTitle("4-Gewinnt")
        self.setGeometry(150, 100, 800, 800)

        self.stacked_widget = QStackedWidget()
        self.currentScreenIndex = 0

        self.menu_screen = MenuScreen()  # index 0
        self.stacked_widget.addWidget(self.menu_screen)

        self.game_screen = GameScreen()  # index 1
        self.stacked_widget.addWidget(self.game_screen)

        self.setCentralWidget(self.stacked_widget)

        self.switch_to_menu_screen()

        self.show()

        # ---CoAP---
        self.context = None
        self.loop = None

        self.controller_resource = ControllerResource()
        self.controller_resource.signal_emitter.payload_received.connect(self.handle_payload)

        # Start CoAP server in separate thread
        self.coap_thread = threading.Thread(target=self.start_coap_server, daemon=True)
        self.coap_thread.start()

    #############################################################################################

    # ---UI---------------------------------------------------
    def switch_to_menu_screen(self):
        self.stacked_widget.setCurrentWidget(self.menu_screen)
        self.updateScreenIndex()

    def switch_to_game_screen(self):
        self.game_screen.reset_game()
        self.stacked_widget.setCurrentWidget(self.game_screen)
        self.updateScreenIndex()

    def updateScreenIndex(self):
        self.currentScreenIndex = self.stacked_widget.currentIndex()

    def sendInputToCurrentScreen(self, controllerInput):
        #print(self.currentScreenIndex)
        if self.currentScreenIndex == 0:
            self.menu_screen.triggerAction(controllerInput)
        elif self.currentScreenIndex == 1:
            self.game_screen.triggerAction(controllerInput)
        else:
            print("Error: Screen-Index out of range (in sendInputToCurrentScreen)")

    # ---CoAP---------------------------------------------------
    async def create_coap_server(self):
        root = resource.Site()
        root.add_resource(('hello',), self.controller_resource)

        ip_address = "192.168.50.39"
        port = 5683

        self.context = await Context.create_server_context(root, bind=(ip_address, port))
        print(f"CoAP server is up and running. Listening on {ip_address}:{port}.")

    def start_coap_server(self):
        self.loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self.loop)

        self.loop.run_until_complete(self.create_coap_server())
        self.loop.run_forever()

    @pyqtSlot(int)
    # def handle_payload(self, payload):
    #     if payload == "3":
    #         self.sendInputToCurrentScreen("left")  # left
    #     elif payload == "0":
    #         self.sendInputToCurrentScreen("enter")  # enter
    #     elif payload == "1":
    #         self.sendInputToCurrentScreen("right")  # right
    #     else:
    #         print("Warning: ControllerInput not listed for game action -->" + payload)
    def handle_payload(self, payload):
        data = payload  # payload is now an integer
        isConnected = (data & 0b10000000) >> 7  # extract the first bit
        number = data & 0b01111111  # extract the remaining bits
        if isConnected == 1:
            if number == 3:
                self.sendInputToCurrentScreen("left")  # left
            elif number == 0:
                self.sendInputToCurrentScreen("enter")  # enter
            elif number == 1:
                self.sendInputToCurrentScreen("right")  # right
            else:
                print("Warning: ControllerInput not listed for game action -->" + str(number))
        else:
            print("Controller is not connected")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ConnectFour()
    sys.exit(app.exec_())
