/*
 * Defines.hpp
 *
 *  Created on: Oct 3, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_DEFINES_HPP_
#define SRC_COMPONENTS_DEFINES_HPP_

#define SETID

#define FACTORY_RESET


#endif /* SRC_COMPONENTS_DEFINES_HPP_ */

//Para resetar o motor usando o factory reset => SETID e FACTORY_RESET não comentados
//Caso tenha resetado, mude o Baud Rate para 57600(default) no .ioc
//Depois altere o ID address para 0x04 (modificação), daí será modificado também o Baud Rate com o botão azul
//Para setar ID => SETID não comentado, porém FACTORY_RESET comentado
//Em seguida, comente o SETID e mexa o motor
