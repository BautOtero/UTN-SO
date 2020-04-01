/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* respuesta;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger, "soy un log");

	config = leer_config();

	ip = config_get_string_value(config, "IP");

	puerto = config_get_string_value(config, "PUERTO");

	log_info(logger, ip);

	log_info(logger, puerto);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion

	conexion = crear_conexion(ip, puerto);

	char str[2];

	sprintf(str, "%d", conexion);

	char c = conexion;

	log_info(logger, str);

	//enviar mensaje
	enviar_mensaje("TuVieja", conexion);

	//recibir mensaje
	respuesta = recibir_mensaje(conexion);

	//loguear mensaje recibido
	log_info(logger, respuesta);

	free(respuesta);

	terminar_programa(conexion, logger, config);
}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("/home/utnso/Game-watch-client/tp0.log", "Game-watch-client", true, LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config(void)
{
	t_config* tp0Config = config_create("/home/utnso/Game-watch-client/tp0.config");

	config_set_value(tp0Config, "IP", "127.0.0.1");

	config_set_value(tp0Config, "PUERTO", "4444");

	return tp0Config;
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	config_destroy(config);
	log_destroy(logger);

	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
