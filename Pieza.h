#ifndef PIEZA_H
#define PIEZA_H

#include <vector>
class Pieza {

    public://atributos

        std::vector <int> LPP,RPi,Di;//vector de lanzamientos programados y recepciones programadas
        int SS;//disponibildades en la semana 1 y stock seguridad
        int selec_TL;//metodo de dimensionado de lote. Sera un selector de enteros que ira a la funcion de calulo de lote
        int tSum;//tiempo de suministro
        int pDef;//porcentaje de defectuosos
        char id;
        ///parametros del calculo de lote
        double S = 0;
        double H = 0;

        int v_poliv; //aqui van a ir, tamaños de lote, multiplos,

        ///// relacion de precedencia

        std::vector <char> Dep_pieza;//las piezas que dependen de esta pieza
        std::vector <int> cant_Dep_pieza;//la cantidad de ESTA pieza necesaria para hacer cada una de las piezas de arriba


        //constructores



        Pieza(char id,std::vector <int> NBi, std::vector <int> RPi, int Di, int SS, int selec_TL,int tSum, int pDef, std::vector <char> Dep_pieza, std::vector <int> cant_Dep_pieza, double S, double H, int v_poliv){

            this->id=id;
            this->LPP=NBi;
            this->RPi=RPi;

            std::vector <int> aux(10,0);
            aux.at(0)=Di;
            this->Di=aux;

            this->SS= SS;
            this->tSum=tSum;
            this->pDef=pDef;

            this->selec_TL=selec_TL;

            this->Dep_pieza=Dep_pieza;
            this->cant_Dep_pieza=cant_Dep_pieza;

            this->S=S;
            this->H=H;
            this->v_poliv=v_poliv;

        }

        //Destructor
        ~Pieza(){

        }

        //getters


};


#endif // PIEZA_H
