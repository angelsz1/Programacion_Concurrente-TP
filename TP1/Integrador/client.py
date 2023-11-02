import signal
import sys
import socket
import curses
from curses import wrapper

host = "127.0.0.1"
port = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

stick_man_parts = [
    (4, 2, "|"),
    (5, 2, "|"),
    (6, 2, "O"),
    (7, 1, "/"),
    (7, 2, "|"),
    (7, 3, "\\"),
    (8, 2, "|"),
    (9, 2, "/"),
    (9, 3, "\\"),
]


def signal_handler(sig, frame):
    print('Close client')
    client_socket.close()
    sys.exit(0)


def draw_stick_man(stdscr, attempts):
    for i in range(attempts):
        y, x, char = stick_man_parts[i]
        stdscr.addstr(y, x, char)


def display_message(stdscr, y, message):
    stdscr.move(y, 0)
    stdscr.clrtoeol()
    stdscr.addstr(message)
    stdscr.refresh()


def display_welcome(stdscr):
    display_message(stdscr, 0, "Welcome to Hangman! Guess a letter.")
    display_message(stdscr, 1, "Input letter: ")


def process_response(stdscr, attempts, response):
    if "Invalid" in response:
        display_message(stdscr, 3, response)
    elif "Wrong" in response:
        attempts += 1
        draw_stick_man(stdscr, attempts)
        display_message(stdscr, 3, response)
    elif "lose" in response or "win" in response:
        display_exit_message(stdscr, response)
        attempts = -1
    else:
        display_message(stdscr, 2, response)
    return attempts


def display_exit_message(stdscr, response):
    stdscr.move(0, 0)
    stdscr.clrtobot()
    display_message(stdscr, 0, response)
    display_message(stdscr, 1, "Press any key to exit.")
    stdscr.refresh()
    stdscr.getch()

def get_input_letter(stdscr):
    stdscr.move(1, 14)
    guess = chr(stdscr.getch()).lower()
    stdscr.addch(guess)
    stdscr.refresh()
    return guess

def main(stdscr):
    signal.signal(signal.SIGINT, signal_handler)

    client_socket.connect((host, port))

    stdscr.clear()
    display_welcome(stdscr)
    stdscr.refresh()

    attempts = 0
    while attempts != -1:
        guess = get_input_letter(stdscr)

        client_socket.send(guess.encode())

        response = client_socket.recv(1024).decode()
        attempts = process_response(stdscr, attempts, response)

    client_socket.close()


if __name__ == "__main__":
    wrapper(main)
