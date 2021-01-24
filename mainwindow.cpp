#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "Pieza.h"

#include <iostream>
#include <string>
#include "headers.h"

using namespace std;
////////////////////////
MainWindow::MainWindow(QWidget *parent)//constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()//destructor
{
    delete ui;
}
/////////////////////////////

void MainWindow::resetValues(){

    ui->id->clear();
    ui->cant1->setValue(1);

    ui->NBi1->setValue(0);
    ui->NBi2->setValue(0);
    ui->NBi3->setValue(0);
    ui->NBi4->setValue(0);
    ui->NBi5->setValue(0);
    ui->NBi6->setValue(0);
    ui->NBi7->setValue(0);
    ui->NBi8->setValue(0);
    ui->NBi9->setValue(0);
    ui->NBi10->setValue(0);

    ui->RPi1->setValue(0);
    ui->RPi2->setValue(0);
    ui->RPi3->setValue(0);
    ui->RPi4->setValue(0);
    ui->RPi5->setValue(0);
    ui->RPi6->setValue(0);
    ui->RPi7->setValue(0);
    ui->RPi8->setValue(0);
    ui->RPi9->setValue(0);
    ui->RPi10->setValue(0);

    ui->D1->setValue(0);
    ui->SS->setValue(0);
    ui->Tsum->setValue(0);
    ui->p_def->setValue(0);

    ui->v_poliv->setValue(0);
    ui->vH->setValue(0);
    ui->vS->setValue(0);

    ui->cant1->setValue(1);
    ui->cant2->setValue(1);
    ui->cant3->setValue(1);

    ui->id_dep1->clear();
    ui->id_dep2->clear();
    ui->id_dep3->clear();





}


void MainWindow::on_newP_clicked()
{
   /*
    static int r = 0;
    r++;
    cout<<r<<endl;
    //static Pieza paux;
*/
    ////DECLARACION DE LAS VARIABLES DEL OBJETO
    char id;
    std::vector <int> LPP,RPi;

    int Di,SS,selec_TL,tSum,pDef;

    std::vector <char> Dep_pieza;
    std::vector <int> cant_Dep_pieza;

    double H;
    int S;
    int v_poliv;

    ////ASIGNACION DE LAS VARIABLES DESDE LA UI
    string straux = {};
    bool valid = true;//elemento de validacion. si esta en true el elemento se puede volcar a vector de piezas

    //Id    PONER DEPURACION DE ERRORES

    straux = ui->id->toPlainText().toStdString();
    id = straux[0];

    if (straux.empty()) {//si no hay id entonces la pieza no es valida
        valid = false;

        ui->dialog->setText(" ID DE LA PIEZA VACIO\n");
    }
    //cout<<id<<endl;

    //LPP

    LPP.push_back(ui->NBi1->value());
    LPP.push_back(ui->NBi2->value());
    LPP.push_back(ui->NBi3->value());
    LPP.push_back(ui->NBi4->value());
    LPP.push_back(ui->NBi5->value());
    LPP.push_back(ui->NBi6->value());
    LPP.push_back(ui->NBi7->value());
    LPP.push_back(ui->NBi8->value());
    LPP.push_back(ui->NBi9->value());
    LPP.push_back(ui->NBi10->value());

    //RPi

    RPi.push_back(ui->RPi1->value());
    RPi.push_back(ui->RPi2->value());
    RPi.push_back(ui->RPi3->value());
    RPi.push_back(ui->RPi4->value());
    RPi.push_back(ui->RPi5->value());
    RPi.push_back(ui->RPi6->value());
    RPi.push_back(ui->RPi7->value());
    RPi.push_back(ui->RPi8->value());
    RPi.push_back(ui->RPi9->value());
    RPi.push_back(ui->RPi10->value());

    // Di,SS,selec_TL,tSum,pDef;

    Di = ui->D1->value();
    SS = ui->SS->value();
    tSum = ui->Tsum->value();
    pDef = ui->p_def->value();
    selec_TL = ui->lot_select->currentIndex()+1;
    //cout<< selec_TL <<endl;


    //S H P v_poliv

    S = ui->vS->value();
    H = ui->vH->value();
    v_poliv = ui->v_poliv->value();



    // Dependencias

    ////1
    ///
     straux = ui->id_dep1->toPlainText().toStdString();

     if (!straux.empty()) {
         Dep_pieza.push_back(straux[0]);
         cant_Dep_pieza.push_back(ui->cant1->value());
     }

     ////2
     ///
      straux = ui->id_dep2->toPlainText().toStdString();

      if (!straux.empty()) {
          Dep_pieza.push_back(straux[0]);
          cant_Dep_pieza.push_back(ui->cant2->value());
      }

      ////3
      ///
       straux = ui->id_dep3->toPlainText().toStdString();

       if (!straux.empty()) {
           Dep_pieza.push_back(straux[0]);
           cant_Dep_pieza.push_back(ui->cant3->value());
       }


       ////// DEPURACION DE ERRORES ANTES DE VOLCAR EL ELEMENTO EN EL VECTOR
        static int c = 1;//contador de piezas introducidas

        //// Commprobacion de dependecias resueltas
        if (c>1){

            for (auto i = Dep_pieza.begin(); i !=Dep_pieza.end(); ++i) {//recorre el vector de dependecias

                bool val = false;
                for (auto j = vp.begin(); j !=vp.end(); ++j) {

                    if ((*j).id == *i) {//la dependencia coincide con alguna de las piezas
                        val = true;
                    }

                }

                if (!val) {
                    ui->dialog->setText("Dependencias no validas\n");
                    valid = false;
                    break;
                }

            }

            //comprobacion de etiqueta repetida
            for (auto i = vp.begin(); i !=vp.end(); ++i) {
                if ((*i).id==id) {
                    valid = false;
                    ui->dialog->setText("ID repetido");
                    break;
                }
            }

        }else{//estamos en la inroduccion de la primera pieza
            if (!Dep_pieza.empty()) {//no se pueden incluir dependencias en la primera pieza
                valid = false;
                ui->dialog->setText("NO incluir dependecias en la primera pieza");
            }
        }







       //static vector<Pieza> vp;

       if (valid) {
            c++;
            (this->vp).push_back(Pieza(id,LPP,RPi,Di,SS,selec_TL,tSum,pDef,Dep_pieza,cant_Dep_pieza,S,H,v_poliv));
            ui->dialog->setText("Pieza añadida");
            resetValues();


       }else{
            ui->dialog->append("Pieza no añadida");
       }

       cout<< (this->vp).size() <<endl;
/*
        for (auto i = vp.at(c).LPP.begin(); i != vp.at(c).LPP.end(); ++i) {
            cout<< *i;
        }*/
        cout<<endl;

       //ui->dialog->setText("Biach");

}

void MainWindow::on_calculate_clicked()
{

    if((this->vp).size()>1){
        vector <Pieza> v_solved;

        v_solved = calc_MRP(this->vp);

        for (auto i = v_solved.begin(); i !=v_solved.end(); ++i) {
            for (auto j = (*i).LPP.begin(); j !=(*i).LPP.end(); ++j) {
                cout<<*j<<"  ";
            }
            cout<<endl;
        }



    }else{
        ui->dialog->setText("Solo una pieza introducida.\n No se puede calcular.");
    }


}
