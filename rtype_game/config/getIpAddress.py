import re
import socket

def get_local_ip():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.connect(("8.8.8.8", 80))
            local_ip = s.getsockname()[0]
        return local_ip
    except Exception as e:
        print(f"Error retrieving local IP address : {e}")
        return None

def update_config(file_path, new_ip):
    try:
        with open(file_path, 'r') as file:
            config_content = file.read()

        updated_content = re.sub(r'ip\s*=\s*"\d+\.\d+\.\d+\.\d+"', f'ip = "{new_ip}"', config_content)
        with open(file_path, 'w') as file:
            file.write(updated_content)

        print(f"Configuration successfully updated : {new_ip}")
    except Exception as e:
        print(f"Error updating the file : {e}")

if __name__ == "__main__":
    config_file_path = "udp_config.conf"
    local_ip = get_local_ip()
    if local_ip:
        update_config(config_file_path, local_ip)