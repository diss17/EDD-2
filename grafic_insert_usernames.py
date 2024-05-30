import numpy as np  # Import the numpy package
import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV files
data_linear = pd.read_csv('linear_insert_usernames.csv', names=['N', 'Time'])
data_quadratic = pd.read_csv('quadratic_insert_usernames.csv', names=['N', 'Time'])
data_double = pd.read_csv('double_insert_usernames.csv', names=['N', 'Time'])
data_unordered = pd.read_csv('unorderedmap_insert_usernames.csv', names=['N', 'Time'])

# Funcion para agrupar los datos por N y promediar el tiempo
def agrupar(data):
    return data.groupby('N', as_index=False).mean()

data_linear_promedio = agrupar(data_linear)
data_quadratic_promedio = agrupar(data_quadratic)
data_double_promedio = agrupar(data_double)
data_unordered_promedio = agrupar(data_unordered)

plt.plot(data_linear_promedio['N'], data_linear_promedio['Time'], label='Linear', color='blue')
plt.plot(data_quadratic_promedio['N'], data_quadratic_promedio['Time'], label='Quadratic', color='g')
plt.plot(data_double_promedio['N'], data_double_promedio['Time'], label='Double', color='r')
plt.plot(data_unordered_promedio['N'], data_unordered_promedio['Time'], label='Unordered', color='purple')

plt.xlabel('Insertion Number')
plt.ylabel('Time (nanoseconds)')
plt.title('Insertion time analysis')
plt.legend()

plt.show()
