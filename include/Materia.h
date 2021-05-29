#ifndef MATERIA_H
#define MATERIA_H
#include <list>

using namespace std;

struct comision{
    int nroComision;
    int comienzoDeLaClase;
    int finDeLaClase;
};

class Materia
{
    public:
        Materia();
        Materia(string nombre);
        //Materia(nombre);
        virtual ~Materia();
        void setNombreMateria(string nombre);
        void agregarComision(comision c1);
        string getNombreMateria();
        void getComisiones(list<comision> comisiones);


    private:
        string nombreDeLaMateria;
        list<comision> comisiones;
};

Materia :: Materia(string nombre){
    this->nombreDeLaMateria = nombre;
}


void Materia::setNombreMateria(string nombre){
    this->nombreDeLaMateria = nombre;
}

void Materia::agregarComision(comision c1){
    this->comisiones.push_back(c1);
}

string Materia::getNombreMateria(){
    return this->nombreDeLaMateria;
}

void Materia::getComisiones(list<comision> comisiones){
    list<comision>::iterator iterador = this->comisiones.begin();
    while(iterador != this->comisiones.end()){
        comisiones.push_back(*iterador);
        iterador++;
    }
}

#endif // MATERIA_H
