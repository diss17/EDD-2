import pandas as pd
import matplotlib.pyplot as plt

# Leer los datos desde el archivo CSV
df = pd.read_csv('results_ids.csv', sep=';', names=["hash_type", "operation", "n", "duration"])

# Convertir la columna 'duration' a valores numéricos
df['duration'] = pd.to_numeric(df['duration'])

# Calcular el promedio de los tiempos de duración para cada combinación de hash_type, operation y n
avg_df = df.groupby(['hash_type', 'operation', 'n']).mean().reset_index()

# Crear subgráficas para inserciones y búsquedas
fig, ax = plt.subplots(1, 1, figsize=(12, 10), sharex=True)

# Graficar los tiempos de inserción promedio
insert_df = avg_df[avg_df['operation'].str.contains('insert')]
for key, grp in insert_df.groupby(['hash_type', 'operation']):
    ax.plot(grp['n'], grp['duration'], marker='o', linestyle='-', label=f'{key}')

ax.set_title('Tiempos de Inserción Promedio', fontsize = 16, fontweight = 'bold')
ax.set_ylabel('Duración Promedio (ns)', fontsize = 14, fontweight = 'bold')
#ax.set_yscale('log')
#ax.set_xscale('log')
ax.legend()

plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)', fontsize = 14, fontweight = 'bold')

fig, ax = plt.subplots(1, 1, figsize=(12, 10), sharex=True)
# Graficar los tiempos de búsqueda promedio
search_df = avg_df[avg_df['operation'].str.contains('search')]
for key, grp in search_df.groupby(['hash_type', 'operation']):
    ax.plot(grp['n'], grp['duration'], marker='o', linestyle='-', label=f'{key}')

ax.set_title('Tiempos de Búsqueda Promedio', fontsize = 16, fontweight = 'bold')
ax.set_ylabel('Duración Promedio (ns)', fontsize = 14, fontweight = 'bold')
#ax.set_yscale('log')
#ax.set_xscale('log')
ax.legend()

# Ajustar la rotación de las etiquetas en el eje x
plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)', fontsize = 14, fontweight = 'bold')

# Leer los datos desde el archivo CSV
df_random = pd.read_csv('results_ids_random.csv', sep=';', names=["hash_type", "operation", "n", "duration"])

# Convertir la columna 'duration' a valores numéricos
df_random['duration'] = pd.to_numeric(df_random['duration'])

# Calcular el promedio de los tiempos de duración para cada combinación de hash_type, operation y n
avg_df_random = df_random.groupby(['hash_type', 'operation', 'n']).mean().reset_index()

# Crear subgráficas para inserciones y búsquedas
fig, ax = plt.subplots(1, 1, figsize=(12, 10), sharex=True)

# Graficar los tiempos de búsqueda promedio
search_df_random = avg_df_random[avg_df_random['operation'].str.contains('search')]
for key, grp in search_df_random.groupby(['hash_type', 'operation']):
    ax.plot(grp['n'], grp['duration'], marker='o', linestyle='-', label=f'{key}')

ax.set_title('Tiempos promedio de Búsqueda con datos que no estan en la tabla', fontsize = 16, fontweight = 'bold')
ax.set_ylabel('Duración Promedio (ns)', fontsize = 14, fontweight = 'bold')
#ax.set_yscale('log')
#ax.set_xscale('log')
ax.legend()

# Ajustar la rotación de las etiquetas en el eje x
plt.xticks(rotation=45)
plt.xlabel('Cantidad de Datos (n)', fontsize = 14, fontweight = 'bold')

# Mostrar la gráfica
plt.tight_layout()
plt.show()
