import socket
import threading
import signal
import sys
import random
import time

host = "127.0.0.1"
port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen()

words = ["python"]
player_count = 0
player_count_lock = threading.Lock()


def play_game(client_socket, word):
    global player_count
    max_attempts = 9
    attempts = 0
    guessed_letters = set()
    word_set = set(word)
    hidden_word = ["_" if letter.isalpha() else letter for letter in word]
    start_time = 0
    try:
        while attempts < max_attempts:
            guess = client_socket.recv(1024).decode().lower()
            start_time = start_timer() if start_time == 0 else start_time
            response = ""

            if len(guess) != 1 or not guess.isalpha() or guess in guessed_letters:
                response = "Invalid guess. Try again."
                client_socket.send(response.encode())
                continue

            guessed_letters.add(guess)

            if guess in word_set:
                for i, letter in enumerate(word):
                    if letter == guess:
                        hidden_word[i] = guess

                if set(hidden_word) == word_set:
                    elapsed_time = end_timer(start_time)
                    client_socket.send(
                            (f"You win ! The word was: {word} and it took you: {elapsed_time:.2f} seconds").encode())
                    break
                else:
                    response = "".join(hidden_word)
            else:
                attempts += 1
                response = "Wrong guess (" + str(max_attempts - attempts) + \
                    " attempts left)." if attempts < max_attempts else ""
            client_socket.send(response.encode())

        if attempts == max_attempts:
            elapsed_time = end_timer(start_time)
            client_socket.send(
                            (f"You lose ! The word was: {word} and it took you: {elapsed_time:.2f} seconds").encode())
    except ConnectionError:
        pass
    finally:
        print("Client disconnected")
        with player_count_lock:
            player_count -= 1
            print("Current player count: {}".format(player_count))
        client_socket.close()

def signal_handler(sig, frame):
    print('Close server')
    server_socket.close()
    sys.exit(0)

def start_timer():
    return time.time()

def end_timer(start_time):
    return time.time() - start_time

def main():
    global player_count
    signal.signal(signal.SIGINT, signal_handler)
    print("Server listening on {}:{}".format(host, port))

    while True:
        client_socket, _ = server_socket.accept()
        word = words[random.randint(0, len(words)-1)]

        with player_count_lock:
            player_count += 1
            print("Current player count: {}".format(player_count))
        game_thread = threading.Thread(
            target=play_game, args=(client_socket, word))
        game_thread.start()


if __name__ == "__main__":
    main()

