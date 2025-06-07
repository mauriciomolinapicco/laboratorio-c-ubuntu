import os
import requests
from urllib.parse import urljoin
from bs4 import BeautifulSoup

# URL del servidor
url = 'http://192.168.15.65:8000/'


# Obtener el contenido de la página
response = requests.get(url)
soup = BeautifulSoup(response.text, 'html.parser')

# Crear una carpeta para guardar los archivos descargados
os.makedirs('descargados', exist_ok=True)

# Buscar todos los enlaces de archivos en la página
for link in soup.find_all('a'):
    file_url = urljoin(url, link.get('href'))
    if file_url.endswith('/'):  # Si es un directorio, saltar
        continue
    file_name = os.path.join('descargados', os.path.basename(file_url))
    print(f'Descargando {file_url}')
    with open(file_name, 'wb') as f:
        f.write(requests.get(file_url).content)

print('Descarga completa.')