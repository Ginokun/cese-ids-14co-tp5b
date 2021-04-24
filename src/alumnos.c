/*=====[Module Name]===========================================================
 * Copyright 2019 Esteban Daniel VOLENTINI <evolentini@gmail.com>
 * All rights reserved.
 * License: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.1.0
 * Creation Date: 2019/03/01
 */
 
/*=====[Inclusion of own header]=============================================*/

#include "alumnos.h"
#include <stdio.h>
#include <string.h>

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
/**
 * @brief Estructura con constantes con la información sobre los alumnos, como los apellidos, nombres y DNI.
 * 
 */

static const struct alumno_s ESTEBAN_VOLENTINI = {
    .apellidos = "VOLENTINI",   /**< Apellido del alumno*/
    .nombres = "Esteban Daniel",
    .documento = "23.517.968",
};

static const struct alumno_s MATIAS_MEGHINASSO = {
    .apellidos = "MEGHINASSO",
    .nombres = "Matias Gino",
    .documento = "36.806.968",
};

const alumno_t ALUMNOS[] = {
    &ESTEBAN_VOLENTINI,
    &MATIAS_MEGHINASSO,
};

const int CANTIDAD_ALUMNOS = (sizeof(ALUMNOS) / sizeof(alumno_t));

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/

/**
 * @brief           Carga los datos de un alumno en un string.
 * 
 * @param cadena    String donde se cargan los datos del alumno.
 * @param espacio   Espacio disponible del string para cargar datos.
 * @param alumno    Estructura con los datos de los alumnos. 
 * @return true     Se pudieron cargar los datos correctamente.
 * @return false    Fallo la carga de los datos.
 */
bool SerializarAlumno(char * cadena, size_t espacio, const alumno_t alumno) {
    int resultado;
    const char FORMATO[] = "{"
        "\"documento\":\"%s\","
        "\"apellidos\":\"%s\","
        "\"nombres\":\"%s\""
    "}";

    resultado = snprintf(cadena, espacio, FORMATO, 
             alumno->documento, alumno->apellidos, alumno->nombres);

    return (resultado >= 0);
}
/**
 * @brief           Carga los datos de varios alumnos en un string. 
 * 
 * @param cadena    String donde se cargan los datos de los alumnos.
 * @param espacio   Espacio disponible del string para cargar datos.
 * @return true     Se pudieron cargar los datos correctamente.
 * @return false    Fallo la carga de los datos.
 */
bool SerializarAlumnos(char * cadena, size_t espacio) {
    static const int  cantidad = sizeof(ALUMNOS) / sizeof(alumno_t);
    int posicion = snprintf(cadena, espacio, "[\r\n  ");
    bool resultado = (posicion > 0);

    if (resultado){
        for(int indice = 0; indice < cantidad; indice++ ) {
            resultado = SerializarAlumno(&cadena[posicion], espacio - posicion, ALUMNOS[indice]);
            if (resultado) {
                posicion += strlen(&cadena[posicion]);
                posicion += snprintf(&cadena[posicion], espacio - posicion, ",\r\n  ");
            } else {
                break;
            }
        }
    }

    snprintf(&cadena[posicion] - 5, espacio - posicion + 5, "\r\n]");
    return resultado;
}

/*=====[Implementations of private functions]================================*/
