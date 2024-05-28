import numpy as np  # Import the numpy package
import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV files
data_linear = pd.read_csv('linear_search_ids.csv', names=['N', 'Time'])
data_quadratic = pd.read_csv('quadratic_search_ids.csv', names=['N', 'Time'])
data_double = pd.read_csv('doublehashing_search_ids.csv', names=['N', 'Time'])  
data_unordered = pd.read_csv('unorderedmap_search_ids.csv', names=['N', 'Time'])

# Create a new figure
#fig, axs = plt.subplots(4, 1, figsize=(10, 24))

plt.plot(data_linear['N'], data_linear['Time'], label='Linear', color='blue')
plt.plot(data_quadratic['N'], data_quadratic['Time'], label='Quadratic', color='g')
plt.plot(data_double['N'], data_double['Time'], label='Double', color='r')
plt.plot(data_unordered['N'], data_unordered['Time'], label='Unordered', color='purple')
plt.xlabel('Search Number')
plt.ylabel('Time (nanoseconds)')
plt.title('Search time analysis')
plt.legend()

## Plot data for linear
#axs[0].plot(data_linear['N'], data_linear['Time'], label='Linear')
#axs[0].set_xlabel('Search Number')
#axs[0].set_ylabel('Time (nanoseconds)')
#axs[0].set_title('Search Time Analysis (Linear)')
#axs[0].legend()
#
## Plot data for quadratic
#axs[1].plot(data_quadratic['N'], data_quadratic['Time'], label='Quadratic')
#axs[1].set_xlabel('Search Number')
#axs[1].set_ylabel('Time (nanoseconds)')
#axs[1].set_title('Search Time Analysis (Quadratic)')
#axs[1].legend()
#
## Plot data for double hashing  # New block
#axs[2].plot(data_double['N'], data_double['Time'], label='Double Hashing')
#axs[2].set_xlabel('Search Number')
#axs[2].set_ylabel('Time (nanoseconds)')
#axs[2].set_title('Search Time Analysis (Double Hashing)')
#axs[2].legend()
#
## Plot data for unordered map  # New block
#axs[3].plot(data_unordered['N'], data_unordered['Time'], label='Unordered Map')
#axs[3].set_xlabel('Search Number')
#axs[3].set_ylabel('Time (nanoseconds)')
#axs[3].set_title('Search Time Analysis (Unordered Map)')
#axs[3].legend() 
#
#plt.tight_layout()
plt.show()