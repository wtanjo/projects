import io
from PIL import Image, ImageTk
import subprocess
import tkinter as tk
from PHSpider import *

class PHDownloader():
    def __init__(self):
        REQUIREMENTS_ERROR = ""
        FFmpeg_test = subprocess.run(['FFmpeg', '-version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if FFmpeg_test.stderr.decode('utf-8') != '':
            Winget_install_test = subprocess.run(['winget', 'install', 'ffmpeg'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            if Winget_install_test.stderr.decode('utf-8') != '':
                pip_install_test = subprocess.run(['pip', 'install', 'ffmpeg-python'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                if pip_install_test.stderr.decode('utf-8') != '':
                    REQUIREMENTS_ERROR = "FFmpeg is not installed, neither is winget or pip. Please install it manually."

        self.main_window = tk.Tk()
        self.main_window.title("PH Downloader")
        self.main_window.geometry("1300x800")
        if REQUIREMENTS_ERROR != "":
            self.requirements_error_label = tk.Label(self.main_window, text=REQUIREMENTS_ERROR, fg="red", font=("Cascadia Mono", 20))
            self.requirements_error_label.pack()
        else:
            self.url_label = tk.Label(self.main_window, text="URL:", font=("Cascadia Mono", 15))
            self.url_label.grid(row=0, column=0)
            self.url_textbox = tk.Entry(self.main_window, font=("Cascadia Mono", 15), width=100)
            self.url_textbox.grid(row=0, column=1)
            self.check_button = tk.Button(self.main_window, text="Check", font=("Cascadia Mono", 15), command=self.url_check)
            self.check_button.grid(row=1, column=1)
        self.main_window.mainloop()

    def url_check(self):
        PHSpider(self.url_textbox.get())
        self.cover_image_bytes = requests.get(PHSpider.cover_image_url).content
        self.cover_image_pil = Image.open(io.BytesIO(self.cover_image_bytes))
        self.cover_image_tk = ImageTk.PhotoImage(self.cover_image)
        self.cover_image_label = tk.Label(self.main_window, image=self.cover_image_tk, width=750, height=400)
        self.cover_image_label.grid(row=2, column=1)
        self.title_label = tk.Label(self.main_window, text=PHSpider.title, font=("Cascadia Mono", 10))
        self.title_label.grid(row=3, column=1)
        self.download_button = tk.Button(self.main_window, text="Download", font=("Cascadia Mono", 15), command=self.download)
        self.download_button.grid(row=4, column=1)

    def download(self):
        download_result = subprocess.run(['FFmpeg', '-allowed_extensions', 'ALL', '-protocol_whitelist', '"file,http,https,tls,tcp,crypto"', '-i', PHSpider.video_url, '-c', 'copy', f'{PHSpider.title}.mp4'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if download_result.stderr.decode('utf-8') != '':
            self.download_error_label = tk.Label(self.main_window, text=f"Download failed: {download_result.stderr.decode('utf-8')}", fg="red", font=("Cascadia Mono", 15))
            self.download_error_label.grid(row=5, column=1)
        else:
            self.download_success_label = tk.Label(self.main_window, text=f"Download successful: {PHSpider.title}.mp4", font=("Cascadia Mono", 15))
            self.download_success_label.grid(row=5, column=1)

def main():
    return PHDownloader()