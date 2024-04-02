import socket

ESP32_IP = '192.168.160.48'  # Dirección IP del ESP32
ESP32_PORT = 8888
# Dirección IP y puerto en el que el servidor estará escuchando
HOST = '192.168.160.91'  # Escucha en todas las interfaces de red disponibles
PORT = 8888

def main():
    # Crear un socket TCP/IP
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        # Enlazar el socket a la dirección y puerto
        server_socket.bind((HOST, PORT))
        # Escuchar por conexiones entrantes
        server_socket.listen(1)
        print(f"Servidor escuchando en {HOST}:{PORT}")

        while True:
            # Aceptar la conexión entrante
            conn, addr = server_socket.accept()
            with conn:
                print(f"Conexión establecida desde: {addr}")
                # Recibir datos del cliente
                data = conn.recv(1024)
                if not data:
                    break
                # Mostrar los datos recibidos
                print(f"Datos recibidos del cliente: {data.decode('utf-8')}")

                send_to_esp32(data.decode('utf-8'))

def send_to_esp32(distance):
    # Crear un socket TCP/IP
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        # Conectar al ESP32
        client_socket.connect((ESP32_IP, ESP32_PORT))
        # Enviar la distancia al ESP32
        client_socket.sendall(str(distance).encode('utf-8'))
        print(f"Distancia enviada al ESP32: {distance}")

if _name_ == "_main_":
    main()
