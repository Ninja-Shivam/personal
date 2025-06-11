
# Modular Client-Server Project (C)

## Structure

- `main_controller.c`: Entry point for reading input.
- `input_handler.c/h`: Dispatch input to client app or print locally.
- `client_app.c`: Sends data to middle client over TCP.
- `middle_client.c`: Acts as intermediary between client and server.
- `server.c`: Processes request (e.g., converts to uppercase).

## Build

```
make
```

## Run

In separate terminals:

1. `./server`
2. `./middle_client`
3. `./app_net` (or `./app` for local-only)

