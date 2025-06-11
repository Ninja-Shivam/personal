
all:
	gcc main_controller.c input_handler.c client_app.c -o app
	gcc main_controller.c input_handler.c client_app.c -o app_net -DSERVER_CLIENT
	gcc middle_client.c -o middle_client
	gcc server.c -o server
