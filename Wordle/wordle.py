from random import random
from datetime import datetime
from tkinter import Canvas, Tk, Label, StringVar
import random
import os
import sys
import numpy as np
from time import sleep


class Letter:

    def __init__(self, letter='', status='empty'):
        self.letter = letter.upper()
        self.status = status

    def update(self, letter='', status='empty'):
        self.letter = letter.upper()
        self.status = status


class Wordle:

    def __init__(self, word_size = 5, max_tries = 6):
        self.dico = {}
        self.word_today = None
        self.word_size = word_size
        self.max_tries = max_tries
        self.board = np.full((self.max_tries, self.word_size), None)
        for i in range(max_tries):
            for j in range(word_size):
                self.board[i][j] = Letter()
        self.turn = 0
        self.won = False
        self.key = 0
        self.gui = None

    def register_gui(self, gui):
        self.gui = gui

    def load_dico(self, dico_file='words.txt'):
            size = int((os.path.getsize(dico_file) + 1) / (self.word_size + 1))
            if size == 0:
                raise ValueError(f"{dico_file} is empty")
            if len(sys.argv) >= 2 and sys.argv[1] == "daily":
                random.seed(int(datetime.now().today().strftime('%j'))
                            * int(datetime.now().today().strftime('%y')))
            word_idx = random.randint(0, size - 1)
            f = open(dico_file,'r')
            idx = 0
            if idx == size - 1:
                myline = f.readline().lower()
            else:
                myline = f.readline()[:-1].lower()
            while myline:
                if not myline.isalpha() or len(myline) != self.word_size:
                    raise ValueError(f"{dico_file}: invalid format line {idx + 1}: {myline}")
                self.dico[myline] = None
                if word_idx == idx:
                    self.word_today = myline
                idx += 1
                if idx == size - 1:
                    myline = f.readline().lower()
                else:
                    myline = f.readline()[:-1].lower()

    def fill_board(self, word):
        word_nogreen = self.word_today
        for i, letter in enumerate(word):
            if letter == self.word_today[i]:
                status = 'green'
                word_nogreen = word_nogreen[:i] + '_' + word_nogreen[i + 1:]
                word = word[:i] + '_' + word[i + 1:]
                self.board[self.turn][i].update(letter, status)
        for i, letter in enumerate(word):
            if word_nogreen[i] == '_':
                continue
            elif word_nogreen.count(letter) >= word[:i + 1].count(letter):
                status = 'yellow'
            else:
                status = 'gray'
            self.board[self.turn][i].update(letter, status)

    def parse_input(self, word):
        if len(word) < self.word_size:
            raise ValueError("The word \'" + word + "\' is too short")
        if len(word) > self.word_size:
            raise ValueError("The word \'" + word + "\' is too big")
        if not word.isalpha():
            raise ValueError("The word \'" + word + "\' is not a word")
        if (word not in self.dico):
            raise ValueError("The word \'" + word + "\' is not in dictionary")
        self.fill_board(word)
        if word == self.word_today:
            self.won = True
        self.turn += 1


class Gui:

    def __init__(self, wordle = Wordle()):
        self.root_width = 800
        self.root_height = 1200
        self.canvas_width = 560
        self.canvas_height = 670
        self.keyboard_width = 700
        self.keyboard_height = 330
        self.wordle = wordle
        self.root = Tk()
        self.root.wm_title(string="Wordle")
        self.root.geometry(f"{self.root_width}x{self.root_height}")
        self.root.config(background='black')
        self.root.minsize(self.root_width, self.root_height)
        self.root.maxsize(self.root_width, self.root_height)
        self.root.bind_all('<KeyRelease>', self.handle_key_press)
        self.can = Canvas(self.root, width=self.canvas_width,
                          height=self.canvas_height, bg="black", highlightthickness=0)
        self.keyBcan = Canvas(self.root, width=self.keyboard_width,
                              height=self.keyboard_height, bg="black", highlightthickness=0)
        self.box = self.init_boxes()
        self.txt = self.init_text()
        self.init_keyB()
        self.error_msg = StringVar()
        self.error_txt = Label(self.root, textvariable=self.error_msg,
                               pady=30, font=('Arial', 14), bg='black',fg='white')
        self.can.pack()
        self.error_txt.pack()
        self.keyBcan.pack()
        self.current_word = ''
        self.shuffle_bool = False
        self.wordle.register_gui(self)
        self.prev_time = 0
        pass

    def handle_key_press(self, evt):
        key = evt.keysym
        self.handle_input(evt, key)

    def handle_input(self, evt, key):
        if key == "Escape":
            self.root.quit()
        if self.wordle.won or self.wordle.turn == self.wordle.max_tries:
            return
        if key == "BackSpace":
            self.wordle.board[self.wordle.turn][len(self.current_word) - 1].update('', 'empty')
            self.update_box(self.wordle.turn, len(self.current_word) - 1)
            self.current_word = self.current_word[:-1]
        elif (key == "KP_Enter" or key == "Return"):
            try:
                self.wordle.parse_input(self.current_word.lower())
                self.update_line_box(self.wordle.turn - 1)

                self.current_word = ''
                self.error_msg.set('')
                if self.wordle.won:
                    self.error_msg.set('You won')
                elif self.wordle.turn == self.wordle.max_tries:
                    self.error_msg.set('You loose the word was : ' + self.wordle.word_today)
            except ValueError as e:
                self.error_msg.set("Error : " + str(e))
                if self.prev_time > 0 and evt.time - self.prev_time > 200:
                    self.shuffle_line(self.wordle.turn)
        else:
            if not key.isalpha() or len(key) != 1 or len(self.current_word) == self.wordle.word_size:
                return
            self.current_word += key
            self.wordle.board[self.wordle.turn][len(self.current_word) - 1].update(key, 'filling')
            self.update_box(self.wordle.turn, len(self.current_word) - 1)
        self.prev_time = evt.time

    def loop(self):
        self.root.mainloop()

    def update_box(self, i, j):
        self.can.itemconfigure(self.box[i][j], self.box_options(self.wordle.board[i][j].status))
        self.can.itemconfigure(self.txt[i][j], text=self.wordle.board[i][j].letter)

    def update_line_box(self, line):
        for j in range(self.wordle.word_size):
            self.update_box(line, j)
        for i in range(self.wordle.word_size):
            if (self.keyBcan.itemcget(self.wordle.board[line][i].letter, 'fill') == '#538d4e'
                or (self.keyBcan.itemcget(self.wordle.board[line][i].letter, 'fill') == '#b59f3b'
                    and self.wordle.board[line][i].status == 'gray')):
                continue
            else:
                self.keyBcan.itemconfigure(self.wordle.board[line][i].letter,
                                       self.box_options(self.wordle.board[line][i].status))

    def shuffle_line(self, line):
        if  self.shuffle_bool == False:
            self.shuffle_bool = True
        else:
            return
        for x in range(7):
            if x == 0 or x == 6:
                dx = 3
            elif x % 2:
                dx = -6
            else:
                dx = 6
            for j in range(self.wordle.word_size):
                self.can.move(self.box[line][j], dx, 0)
            sleep(0.05)
            self.can.update()
        self.shuffle_bool = False

    def init_boxes(self):
        x = self.wordle.word_size
        y = self.wordle.max_tries
        x_max = self.canvas_width
        y_max = self.canvas_height
        rect = np.full((y, x), None)
        for i in range(y):
            for j in range(x):
                rect[i][j] = self.can.create_rectangle(j * ((x_max - 10) / x) + 10,
                                                       i * ((y_max - 10) / y) + 10,
                                                       (j + 1) * ((x_max - 10) / x),
                                                       (i + 1) * ((y_max - 10) / y),
                                                       self.box_options('empty'))
        return rect

    def init_text(self):
        x = self.wordle.word_size
        y = self.wordle.max_tries
        txt = np.full((y, x), None)
        for i in range(y):
            for j in range(x):
                coords = self.can.coords(self.box[i][j])
                txt[i][j] = self.can.create_text((coords[2] + coords[0]) / 2,
                                                 (coords[3] + coords[1]) / 2,
                                                 font=('Arial', 25, 'bold'),
                                                 text='', fill='white')
        return txt

    def keyB_press(self, evt, letter):
        self.handle_input(evt, letter)

    def init_keyB(self):
        x = 10
        y = 3
        x_max = self.keyboard_width
        y_max = self.keyboard_height
        lines = [['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
                ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'],
                ['Enter', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<=']]
        for i, line in enumerate(lines):
            for j, letter in enumerate(line):
                x0 = (j + 0.5 * (i != 0 and (j != 0 or i % 2))) * ((x_max - 10) / x) + 10
                y0 = i * ((y_max - 10) / y) + 10
                x1 = (j + 0.5 * (i != 0) + 0.5 * ((j == 8 and i == 2)) + 1) * ((x_max - 10) / x)
                y1 = (i + 1) * ((y_max - 10) / y)
                tag = self.keyBcan.create_rectangle(x0, y0, x1, y1,
                                                       fill='#818384')
                coords = self.keyBcan.coords(tag)
                tag2 = self.keyBcan.create_text((coords[2] + coords[0]) / 2,
                                                 (coords[3] + coords[1]) / 2,
                                                 font=('Arial', 14, 'bold'),
                                                 text=letter, fill='white')
                if letter == '<=':
                    key_tag = 'BackSpace'
                elif letter == 'Enter':
                    key_tag = 'Return'
                else:
                    key_tag = letter.upper()
                self.keyBcan.addtag_withtag(key_tag, tag)
                def gest(evt, letter=key_tag):
                    return self.keyB_press(evt, letter)
                self.keyBcan.tag_bind(tag, "<Button-1>", gest)
                self.keyBcan.tag_bind(tag2, "<Button-1>", gest)

    def box_options(self, option):
        options = {
            'empty' : {
                'fill' : 'black',
                'outline' : '#3a3a3c',
                'width' : 3
            },
            'filling' : {
                'fill' : 'black',
                'outline' : '#565758',
                'width' : 3
            },
            'green' : {
                'fill' : '#538d4e',
                'width' : 0
            },
            'yellow' : {
                'fill' : '#b59f3b',
                'width' : 0
            },
            'gray' : {
                'fill' : '#3a3a3c',
                'width' : 0
            } 
        }
        return options[option]

try:
    wd =  Wordle()
    wd.load_dico()
    # wd.load_dico(dico_file="words_fr_5.txt")
    # print(wd.word_today)
    gui = Gui(wd)
    gui.loop()

except FileNotFoundError:
    print("Dictionary file not found")
except ValueError as e:
    print(e)
