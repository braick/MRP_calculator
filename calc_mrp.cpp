
#include <iostream>
#include <vector>
#include "Pieza.h"
#include <math.h>

using namespace std;

std::vector<Pieza> vp_ord(std::vector<Pieza> v){

    vector<Pieza> vaux1,vaux2;

    for (auto i = v.begin(); i !=v.end(); ++i) {//separar los que tienen dependencias de los que no

        if ((*i).Dep_pieza.empty()) {
            vaux1.push_back(*i);

        }else{
            vaux2.push_back(*i);
        }
    }

    int cont =0;
    while (!vaux2.empty()) {


        for (auto k = vaux2.begin(); k !=vaux2.end(); ++k) {//loop que recorre el vector de objetos restantes
            vector <bool> valid;
            for (auto n = (*k).Dep_pieza.begin(); n !=(*k).Dep_pieza.end(); ++n) {//loop que recorre las dependencias de cada objeto

                bool val = 0;
                for (auto q = vaux1.begin(); q !=vaux1.end(); ++q) {//loop que recorre el vector de elementos ya ordenados de donde se compararan los ids
                    char id_dep = *n;
                    char id_ord = (*q).id;

                    if (id_dep==id_ord) {
                        val = 1;
                    }

                }

                valid.push_back(val);
            }


            bool resu = 1;
            for (auto a = valid.begin(); a !=valid.end(); ++a) {
                if ((*a)!=1) {
                    resu =0;
                    break;
                }
            }

            if (resu) {//todas las dependencias resueltas
                vaux1.push_back(*k);
                vaux2.erase(k);
                break;

            }




        }

        cont++;
        if (cont>100) {
            cout<<"RELACIONES DE PRECEDENCIA INCORRECTAS"<<endl;
            exit(-1);
        }
    }

    return vaux1;
}



int calcLote(int selec_TL, double H, double S, int NN, int v_poliv, int D, int n_per){

    if (selec_TL ==1 || selec_TL ==5) {//lote a lote
    return NN;

    } else if (selec_TL == 2) {//lote a lote minimo
        if (NN<=v_poliv) {
            return v_poliv;
        } else {
            return NN;
        }

    }else if (selec_TL == 3){//lote a lote multiplo

        int aux = v_poliv;
        int i =1;
        while (aux<NN) {
            aux = v_poliv*i;
            i++;
        }

        return aux;


     }else if (selec_TL == 4){//lote economico

        return round(sqrt((2*D*S)/(H*n_per)));


    }else {//ERROR
        return 0;
    }


}

std::vector<int> sumVect(std::vector <int> v1, std::vector <int> v2, int fact){
    std::vector <int> res;
    for (int i = 0; i < v1.size(); ++i) {

        res.push_back(v1.at(i)+ (fact*v2.at(i)));
    }

    return res;
}


//recibe el vector de onjetos pieza piezas
std::vector<Pieza> calc_MRP(std::vector<Pieza> v_piezas){

    ////CALCULO DEL HORIZONTE DE PLANIFICACION COMO EL MAXIMO DE PERIODOS DE LPP
    int n_per = 1;

    for (auto i = v_piezas.begin(); i !=v_piezas.end(); ++i) {
        int aux = 10;
        for (auto j = (*i).LPP.rbegin(); j !=(*i).LPP.rend(); ++j) {
            if ((*j)!=0) {
                if (aux>n_per) {
                    n_per=aux;
                }
            }
            aux--;
        }
    }



    ///Insertar 10 ceros al principio de todos los elementos de los objetos
    for (auto i = v_piezas.begin(); i!=v_piezas.end(); ++i) {
        //este loop recorre todo el vector de piezas
        //damos por sentado que el vector esta ordenado

        for (int n = 0; n < 10; ++n) {
            (*i).LPP.insert((*i).LPP.begin(),0);
            (*i).RPi.insert((*i).RPi.begin(),0);
            (*i).Di.insert((*i).Di.begin(),0);

        }


    }


    for (auto p = v_piezas.begin(); p!=v_piezas.end(); ++p) {


        ////calculo de las necesidades brutas de los productos
        std::vector <int> NBi = (*p).LPP;
        cout<<(*p).id<<endl;
        if (!(*p).Dep_pieza.empty()) {
            for (int q = 0; q < (*p).Dep_pieza.size(); ++q) {//buscar piezas en la dependencia
                for (auto l = v_piezas.begin(); l!=v_piezas.end(); ++l){
                    if ((*l).id == (*p).Dep_pieza.at(q)) {

                    NBi = sumVect(NBi,(*l).LPP,(*p).cant_Dep_pieza.at(q));


                    }
                }
            }
        }


       std::vector <int> RPPi((*p).LPP.size(),0);

       ///////////calculo de la D
         int D=0;
         for (int i =0; i < NBi.size()-1; ++i) {
             D =D+NBi.at(i)-(*p).Di.at(i)-(*p).RPi.at(i);
         }
        ////////////



       //iterar a lo largo del producto
        for (int i =0; i < NBi.size()-1; ++i) {
           int NN = 0;
           if (NBi.at(i)<=0 && i<10) {
               //NN =0;
              //(*p).Di.at(i+1)= -NN;
              RPPi.at(i) = 0;
           }else{
                NN = NBi.at(i) - (*p).RPi.at(i) - (*p).Di.at(i) + (*p).SS;


                if (NN<=0 || (NBi.at(i)<=0 && i<11)) {// necesidades negativas --> no hace falta producir

                     (*p).Di.at(i+1)= -NN+ (*p).SS;
                     RPPi.at(i) = 0;

           }        else {//necesidades positivas, hace falta producir

                        RPPi.at(i)=calcLote((*p).selec_TL,(*p).H,(*p).S,NN,(*p).v_poliv,D,n_per);
                        (*p).Di.at(i+1)=RPPi.at(i)-NN+(*p).SS;
                        }
           }


        }

            if ((*p).selec_TL==5) {//periodo optimo
                int T = round(sqrt((2*(*p).S)/(D * (*p).H * n_per))*n_per);


                ///generar valor del index para el cual hay que empezar a hacer el agrupamiento
                //int u = 0;
                int indx = 0;
                while (RPPi.at(indx)==0) {

                    if (indx==10) {//si llega el index 10 empieza a agrupar desde ahi aunque no haya nada
                        break;
                    }
                   indx++;
                }

                vector <int> RPPi_aux(RPPi.size(),0);
                for (int x = indx; x < RPPi.size(); x+=T) {//incrementa de T en T
                    int aux1=0;
                    for (int y = x; y < x+T; ++y) {
                        aux1 = aux1 + RPPi.at(y);
                    }

                    for (int y = x; y < x+T; ++y) {
                        if (RPPi.at(y)!=0 || y == x+T-1) {
                            RPPi_aux.at(y)=aux1;
                            break;
                        }

                    }

                }

                RPPi=RPPi_aux;

            }

           //int lote = calcLote((*p).selec_TL,(*p).H,(*p).S,NN,(*p).v_poliv);
           //desplazar pedidos
           for (int t = 0; t < ((*p).tSum); ++t) {
               RPPi.erase(RPPi.begin());
               RPPi.push_back(0);
           }

           //DEFECTUOSOS

           for (auto l = RPPi.begin(); l !=RPPi.end(); ++l) {
                double porcent =(*p).pDef;
                double fact = porcent/100;
                *l=round((*l)/(1-fact));
           }

           //volcado de datos al atributo del objero
           (*p).LPP=RPPi;

        }
    /*
    int cont=-10;
    int a= 2;
    for (auto r = v_piezas.at(a).LPP.begin(); r != v_piezas.at(a).LPP.end(); ++r) {

        cout<<*r<<"    "<<cont++<<endl;
    }

    cout<<v_piezas.at(a).id<<endl;

    */
/*
    for (int i = 0; i < 5; ++i) {
        cout<<v_piezas.at(i).id<<endl;
    }*/

    return v_piezas;

}
