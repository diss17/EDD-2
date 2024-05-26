import numpy as np  # Import the numpy package
import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV files
data_linear = pd.read_csv('linear_insert.csv', names=['N', 'Time'])
data_quadratic = pd.read_csv('quadratic_insert.csv', names=['N', 'Time'])
data_double = pd.read_csv('doblehashing_insert.csv', names=['N', 'Time'])
data_unordered = pd.read_csv('unorderedmap_insert.csv', names=['N', 'Time'])

# Create a new figure with 4 subplots
fig, axs = plt.subplots(4, 1, figsize=(10, 20))

# Plot data for linear
axs[0].plot(data_linear['N'], data_linear['Time'], label='Linear', color='blue')
axs[0].set_xlabel('Insertion Number')
axs[0].set_ylabel('Time (nanoseconds)')
axs[0].set_title('Insertion Time Analysis (Linear)')
axs[0].legend()
axs[0].grid(True)

# Plot data for quadratic
axs[1].plot(data_quadratic['N'], data_quadratic['Time'], label='Quadratic', color='green')
axs[1].set_xlabel('Insertion Number')
axs[1].set_ylabel('Time (nanoseconds)')
axs[1].set_title('Insertion Time Analysis (Quadratic)')
axs[1].legend()
axs[1].grid(True)

# Plot data for double hashing
axs[2].plot(data_double['N'], data_double['Time'], label='Double Hashing', color='red')
axs[2].set_xlabel('Insertion Number')
axs[2].set_ylabel('Time (nanoseconds)')
axs[2].set_title('Insertion Time Analysis (Double Hashing)')
axs[2].legend()
axs[2].grid(True)

# Plot data for unordered map
axs[3].plot(data_unordered['N'], data_unordered['Time'], label='Unordered Map', color='purple')
axs[3].set_xlabel('Insertion Number')
axs[3].set_ylabel('Time (nanoseconds)')
axs[3].set_title('Insertion Time Analysis (Unordered Map)')
axs[3].legend()
axs[3].grid(True)

# Adjust layout to prevent overlap
plt.tight_layout()

# Display the plots
plt.show()
