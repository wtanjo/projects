"""
Download videos from PornHub
"""

import toga
from toga.style import Pack
from toga.style.pack import COLUMN, ROW
import phdownloader.PHSpider as PHSpider

class PHDownloader(toga.App):
    def startup(self):
        """Construct and show the Toga application.

        Usually, you would add your application to a main content box.
        We then create a main window (with a name matching the app), and
        show the main window.
        """

        main_box = toga.Box(style=Pack(direction=COLUMN))
        
        url_label = toga.Label(
            "url: ",
            style=Pack(padding=(0, 5))
        )
        self.url_input = toga.TextInput(style=Pack(flex=1))

        url_box = toga.Box(style=Pack(direction=ROW, padding=5))
        url_box.add(url_label)
        url_box.add(self.url_input)
        check_button = toga.Button(
            "Check",
            on_press=self.check,
            style=Pack(padding=5)
        )

        main_box.add(url_box)
        main_box.add(check_button) 

        self.main_window = toga.MainWindow(title=self.formal_name)
        self.main_window.content = main_box
        self.main_window.show()

    def check(self):
        """show the video preview"""
        PHSpider(self.url_input.value)

def main():
    return PHDownloader()
