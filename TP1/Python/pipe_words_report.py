from multiprocessing import Pipe
import os
import sys

CHILD = 0
EXIT = 'close'

def main():
  pipe_child, pipe_parent = Pipe(True) # bidirectional

  process = os.fork()
  if process < 0:
    sys.exit('Error al crear el nuevo proceso')

  if process == CHILD:
    pipe_parent.close() # not used
    tuple_result = receiving_words(pipe_child)
    send_result(pipe_child, tuple_result)
    pipe_child.close()
    os._exit(0) # child finishing
  else:
    pipe_child.close() # not used
    sending_words(pipe_parent)
    show_result(pipe_parent)
    pipe_parent.close()
    os.wait() # wait child

def sending_words(sender):
  result = ''
  finish = False
  while not finish:
    input_to_send = input('Ingrese:')
    if ' ' not in input_to_send:
      input_to_send = input_to_send.lower()
      finish = EXIT == input_to_send
      sender.send(input_to_send)
    else:
      print('No se admiten espacios.')

def receiving_words(receiver):
  total_character_count = 0
  total_letter_count = 0
  total_digit_count = 0

  max_length_word = ''
  max_length_word_qty = 0

  min_length_word = ''
  min_length_word_qty = 0

  received_input = receiver.recv()

  while received_input != EXIT:
    character_qty, letter_qty, digit_qty = calculate_qty(received_input)
    total_character_count += character_qty
    total_letter_count += letter_qty
    total_digit_count += digit_qty

    if character_qty > max_length_word_qty:
      max_length_word_qty = character_qty
      max_length_word = received_input

    if character_qty < min_length_word_qty or not min_length_word:
      min_length_word_qty = character_qty
      min_length_word = received_input

    received_input = receiver.recv()

  return (total_character_count, total_letter_count, total_digit_count, 
          max_length_word, min_length_word)

def calculate_qty(text):
  character_qty = len(text)
  letter_qty = sum(1 for c in text if c.isalpha())
  digit_qty = sum(1 for c in text if c.isdigit())
  return character_qty, letter_qty, digit_qty

def send_result(sender, tuple_result):
  dictionary_result = {
    'Cantidad de caracteres totales' : tuple_result[0],
    'Cantidad de letras' : tuple_result[1],
    'Cantidad de dígitos' : tuple_result[2],
    'Palabra de mayor longitud' : tuple_result[3],
    'Palabra de menor longitud' : tuple_result[4],
  }
  sender.send(dictionary_result)

def show_result(receiver):
  dictionary_result = receiver.recv()
  print('-----------------Resultado-----------------')
  for name, result in dictionary_result.items():
    print(name, ":", result)

if __name__ == '__main__':
  main()