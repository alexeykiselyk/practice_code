# import matplotlib.pyplot as plt
# import numpy as np
# import pandas as pd
# import importlib.util
import sys

modulename = 'pandas'
if modulename not in sys.modules:
    print('You have not imported the {} module'.format(modulename))

path = 'init_grid.csv'

# try:
#     data = pd.read_csv(path, delimiter='\t')
#     print(data)

# except FileNotFoundError:
#     print(f"File '{path}' not found.")
# except Exception as e:
#     print(f"An error occurred: {e}")