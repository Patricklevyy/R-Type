# Diagramme des Classes

Voici le diagramme des classes du projet r_type

## instruction


    aller sur ce site
[Mermaid Live Editor](https://mermaid-js.github.io/mermaid-live-editor), et rentrer le code ci dessous (sans la première ligne ```mermaid)


```mermaid
classDiagram
    class Room {
        +start(gameId: int, playerName: string, settings: Settings, map: string, difficulty: int): void
        +gameThreadFunction(gameId: int, playerName: string, settings: Settings, map: string, difficulty: int): void
        +sendMesssages(message: string): bool
        +getNbClient(): unsigned int
        +setNbClient(nb: unsigned int): void
        +getName(): string
        +createClient(addr: string, name: string): void
        +getAdress(): string
        +init_event_bus(): void
        +sendExistingEntities(addr: string, clientId: int): void
        -_window_width: int
        -_window_height: int
        -_timer: Timer
        -_port: int
        -_index_ecs: unsigned int
        -_udp_server: UDP_Manager
        -_message_compressor: MessageCompressor
        -_game_running: bool
        -_ecs: ECS
        -_eventBus: EventBus
        -_name: string
        -_nb_client: unsigned int
        -_sockfd: int
        -_addr: sockaddr_in
        -_gameThread: thread
        -_clientAdresses: vector_string

        #SYSTEM
        -_position_system: PositionSystem
        -_direction_system: DirectionSystem
        -_boundaries_system: BoundariesSystem
        #PRIVATE METHOD
        -send_client_dead_entities(deadEntities: list_size): void
        -initializeSocket(): bool
        -closeRoom(): void
        -init_ecs_server_registry(): void
        -get_player_start_position(playerId: int): pair_float_float
        -create_player(pos: pair_float_float, name: string): void
        -handleCommand(data: vector_char, clientAddr: string): void
        -sendUpdate(): void
        -send_client_new_projectile(entityId: size_t, x: float, y: float): void
        -createProjectile(message: Message): void
    }

    class Server {
        +start(): void
        -_timer: Timer
        -_running: bool
        -_rooms: vector_Rooms
        -_currentPort: int
        -_udp_manager: UDP_Manager
        -_compressor: MessageCompressor
        -_mes_checker: MessageChecker
        -_commands: map_unsigned_function
        #PRIVATE METHOD
        -initializeCommands(): void
        -handleCommand(data, client_addr): void
        -checkCreateRoomArgs(args: map_string_string): void
        #COMMAND
        -createRoom(id, clientAddr, message): void
        -joinRoom(id, clientAddr, message): void
        -getAllRooms(messages): void
    }

    class ECS {
        +init_basic_registry(): void
        +addRegistry<Component>(): void
        +addComponents<Component>(): void
        +killEntityFromRegistry<Component>(): void
        +addDeadEntity(): void
        +getIndexPLayer(): void
        +displayPlayableEntityComponent(): void
        +getDeadEntityIndex(): void
        -_components_array
        -_dead_entities
    }

    class UDP_Manager {
        +initialize(configFile: string, port: int): bool
        +startReceiving(): void
        +stopReceiving(): void
        +fetchAllMessages(): vector<pair<string, vector<char>>>
        +sendMessage(message: string, address: string): bool
        +getLastClientAdress(): string
        +receiveLoop(): void
        +enqueueMessage(message: string, clientAddress: string): void
        +receiveMessage(message: string): bool
        -sockfd: int
        -bufferSize: int
        -serverAddr: sockaddr_in
        -lastSenderAddr: sockaddr_in
        -lastSenderValid: bool
        -clientAddrStr: string
        -messageQueue: queue<pair<string, vector<char>>>
        -queueMutex: mutex
        -queueCondition: condition_variable
        -isRunning: atomic<bool>
        -receiverThread: thread
    }

    class Client {
        +start(): void
        +handle_event(): void
        +handle_message(data: vector_char, address: string): void
        -_window_width: int
        -_window_height: int
        -_in_menu: bool
        -_name: string
        -ecs_server_to_client: map<unsigned int, unsigned int>
        -ecs_client_to_server: map<unsigned int, unsigned int>
        -_eventBus: EventBus
        -_timer: shared_ptr<Timer>
        -_udpClient: shared_ptr<UDP_Manager>
        -_ecs: ECS
        -_running: bool
        -_events: queue<sf::Event>
        -_message_compressor: MessageCompressor
        -_mes_checker: MessageChecker
        -_index_ecs_client: size_t

        #SYSTEM
        -_event_window_system: EventWindow
        -_direction_system: DirectionSystem
        -_position_system: PositionSystem
        -_render_window_system: RenderWindow
        -_update_entity_system: UpdateEntitySystem

        #PRIVATE METHODS
        -killProjectiles(projectiles: list<size_t>): void
        -setRoomAdress(id: int, settings: string): void
        -createPlayer(id: int, settings: string): void
        -createEntity(id: int, x: float, y: float, sprite: string): void
        -createProjectile(message: Message): void
        -send_server_new_shoot(): void
        -send_server_player_direction(x_dir: float, y_dir: float): void
        -init_all(): void
        -init_window_size(config: string): void
        -init_window_and_background(): void
        -init_ecs_client_registry(): void
        -init_subscribe_event_bus(): void
    }

    Room --> Server
    Server --> Room
    Room --> ECS
    ECS --> Room
    Room --> UDP_Manager
    UDP_Manager --> Room
    Server --> UDP_Manager
    UDP_Manager --> Server
    Client --> ECS
    ECS --> Client
    Client --> UDP_Manager
    UDP_Manager --> Client
