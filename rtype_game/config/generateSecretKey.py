import re
import random
import string

def generate_secret_key(length=32):
    """Génère une clé secrète aléatoire de la longueur spécifiée."""
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def update_secret_key_in_file(file_path, new_key):
    """Remplace la clé secrète dans le fichier de configuration."""
    with open(file_path, 'r') as file:
        content = file.read()

    updated_content = re.sub(
        r'(secrete_key_rtype\s*=\s*")[^"]*"', 
        rf'\1{new_key}"',
        content
    )

    with open(file_path, 'w') as file:
        file.write(updated_content)

if __name__ == "__main__":
    config_file = "udp_config.conf"
    new_secret_key = generate_secret_key()

    try:
        update_secret_key_in_file(config_file, new_secret_key)
        print(f"Clé secrète mise à jour avec succès : {new_secret_key}")
    except FileNotFoundError:
        print(f"Erreur : Le fichier {config_file} n'a pas été trouvé.")
    except Exception as e:
        print(f"Une erreur est survenue : {e}")
