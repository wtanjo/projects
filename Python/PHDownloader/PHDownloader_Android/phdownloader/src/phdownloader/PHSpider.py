from bs4 import BeautifulSoup
import requests
import re

class PHSpider:
    def __init__(self, base_url):
        """init just stores information(cover image(jpg), title, video(m3u8)) and doesn't return it"""
        self.headers = { 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/133.0.0.0 Safari/537.36 Edg/133.0.0.0' }
        find_image = re.compile(r'https://.*\.jpg')
        find_title = re.compile(r'<title>(.*)</title>')
        find_video = re.compile(r'https://.*\.m3u8')
        response = requests.get(base_url, headers=self.headers)

    def get_cover_image(self):
        """returns the cover image(jpg)"""
        return self.cover_image_url

    def get_title(self):
        """returns the title of the video"""
        return self.title

    def get_video(self):
        """returns the video(m3u8)"""
        return self.video_url