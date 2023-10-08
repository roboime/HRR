/*
 * Defines.hpp
 *
 *  Created on: Oct 3, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_DEFINES_HPP_
#define SRC_COMPONENTS_DEFINES_HPP_

//#define SETID
//#define POSTE
//#define FACTORY_RESET


#endif /* SRC_COMPONENTS_DEFINES_HPP_ */

//Para resetar o motor usando o factory reset => SETID e FACTORY_RESET não comentados
//Caso tenha resetado, mude o Baud Rate para 57600(default) no .ioc // iSSO SE FOR O MOTOR MX
//Depois altere o ID address para 0x04 (modificação), daí será modificado também o Baud Rate com o botão azul //pro motor MX
//Para setar ID => SETID não comentado, porém FACTORY_RESET comentado
//Pra setar o ID 0 não precisa apertar nada, para o ID 1 aperte o botão azul(irá acender 1 led)
//para o ID 2 aperte duas vezes o botão azul(irá acender 2 leds)
//Em seguida, comente o SETID e mexa o motor
// LEMBRE DE RESETAR O ID/ FACTORY RESET SOMENTE COM O MOTOR QUE VOCÊ QUER MUDAR
