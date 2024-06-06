from tkinter import font
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('memory.csv', sep=';', names=["data structure", "type", "n", "size"])

df['size'] = pd.to_numeric(df['size'])

avg_df = df.groupby(['data structure', 'type', 'n']).mean().reset_index()

ids_df = avg_df[avg_df['data structure'].str.contains('ids')]
names_df = avg_df[avg_df['data structure'].str.contains('names')]

fig, ax = plt.subplots(1, 1, figsize=(12, 10), sharex=True)

for key, grp in ids_df.groupby(['type']):
    ax.plot(grp['n'], grp['size'], marker='o', linestyle='-', label=f'{key}')

ax.set_title('Uso de memoria promedio(ids)', fontsize = 16, fontweight = 'bold')
ax.set_ylabel('Tamaño (Kilobytes)', fontsize = 14, fontweight = 'bold')
#ax.set_yscale('log')
ax.legend()

plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)', fontsize = 14, fontweight = 'bold')

fig, ax1 = plt.subplots(1, 1, figsize=(12, 10), sharex=True)

for key, grp in names_df.groupby(['type']):
    ax1.plot(grp['n'], grp['size'], marker='o', linestyle='-', label=f'{key}')

ax1.set_title('Uso de memoria promedio(usernames)', fontsize = 16, fontweight = 'bold')
ax1.set_ylabel('Tamaño (Kilobytes)', fontsize = 14, fontweight = 'bold')
#ax1.set_yscale('log')
ax1.legend()

plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)', fontsize = 14, fontweight = 'bold')

plt.tight_layout()
plt.show()