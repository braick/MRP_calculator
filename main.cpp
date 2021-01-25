#include "mainwindow.h"

#include <QApplication>
#include "Pieza.h"
#include "headers.h"
#include <vector>
#include <iostream>

using namespace std;

vector <Pieza> piezas;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();



/*


    vector <char> id ={'R','E','C','B','M','S'};
    //vector <int> id ={1,2,};
    vector<vector <int>> NBi = {
        {0,0,400,0,4000,1000,0,0,0,0},
        {3000,0,4000,3000,4000,0,0,0,0,0},
        {3000,0,4000,3000,4000,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},

    };
    vector<vector <int>> Rpi = {
        {0,0,0,0,0,0,0,0,0,0},
        {4000,0,0,0,0,0,0,0,0,0},
        {4500,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},


                               };
    vector <int> Di = {500,100,500,2000,200,150};

    vector <int> SS = {500,100,500,1000,100,100};

    vector <int> tSum = {1,1,1,1,1,1};
    vector <int> pDef ={0,0,0,20,0,0};


    //datos del arbol de relaciones
    vector <vector <char>> id_pieza{
        {'E'},
        {},//no hay relaciones de precedencia en los primeros dos productos
        {},
        {'E','C'},
        {'C'},
        {'C'},


    };
    vector <vector <int>> rel_piezas{
        {2},
        {},
        {},
        {2,3},
        {1},
        {1},

    };

    vector <int> select_TL = {2,4,2,5,3,1};
    vector <double> S = {0,2909,0,2500,0,0};
    vector <double> H = {0,0.6,0,0.14,0,0};
    vector <int> v_poliv = {10000,4000,5000,1000,700,1000};



    vector <Pieza> vp;

    for (int k=0; k < NBi.size(); ++k) {

        vp.push_back(Pieza(id.at(k),NBi.at(k),Rpi.at(k),  Di.at(k),  SS.at(k),  select_TL.at(k), tSum.at(k), pDef.at(k),  id_pieza.at(k), rel_piezas.at(k),  S.at(k),  H.at(k),  v_poliv.at(k) ));

    }


    vector <Pieza> vp_o = vp_ord(vp);

    vector <Pieza> v_res;

    v_res = calc_MRP(vp_o);

    vector <vector <int>> LP_mat;




    for (auto i = LLP_mat.begin(); i !=LLP_mat.end(); ++i) {
        for (auto j = (*i).begin(); j !=(*i).end(); ++j) {
            cout<<*j<<"  ";
        }
        cout<<endl;
    }
*/
/*
    for (auto i = v_res.begin(); i !=v_res.end(); ++i) {
        for (auto j = (*i).LPP.begin(); j !=(*i).LPP.end(); ++j) {
            cout<<*j<<"  ";
        }
        cout<<endl;
    }
*/

   //
}
