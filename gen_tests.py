from random import *


NUMBERS_LINES = 10000

with open('tests', 'w') as f:
    f.write(f'{choice(range(100))} {choice(range(5000))}\n')
    for i in range(1, 100):
        f.write(f'{choice(range(100))} {choice(range(100))}\n')