import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('memory.csv', sep=';', names=["data structure", "type", "n", "size"])

df['size'] = pd.to_numeric(df['size'])

avg_df = df.groupby(['data structure', 'type', 'n']).mean().reset_index()

ids_df = avg_df[avg_df['data structure'].str.contains('ids')]
names_df = avg_df[avg_df['data structure'].str.contains('names')]

fig, ax = plt.subplots(2, 1, figsize=(12, 10), sharex=True)

for key, grp in ids_df.groupby(['data structure', 'type']):
    ax[0].plot(grp['n'], grp['size'], marker='o', linestyle='-', label=f'{key[0]} - {key[1]}')

ax[0].set_title('Uso de memoria promedio(ids)')
ax[0].set_ylabel('Tamaño (Kilobytes)')
#ax.set_yscale('log')
ax[0].legend()

for key, grp in names_df.groupby(['data structure', 'type']):
    ax[1].plot(grp['n'], grp['size'], marker='o', linestyle='-', label=f'{key[0]} - {key[1]}')

ax[1].set_title('Uso de memoria promedio(usernames)')
ax[1].set_ylabel('Tamaño (Kilobytes)')
#ax.set_yscale('log')
ax[1].legend()

plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)')

plt.tight_layout()
plt.show()