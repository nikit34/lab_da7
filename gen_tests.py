from random import *


NUMBERS_LINES = 100

with open('tests', 'w') as f:
    f.write(f'{choice(range(NUMBERS_LINES))} {choice(range(5000))}\n')
    for i in range(1, NUMBERS_LINES):
        f.write(f'{choice(range(100))} {choice(range(100))}\n')