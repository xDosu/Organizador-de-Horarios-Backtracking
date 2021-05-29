#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

/*
Estructura comision
*/
struct comision{
    string dia;
    int nroComision;
    int comienzoDeLaClase;
    int finDeLaClase;
};

/*
Clase Materia
*/
class Materia
{
    public:
        Materia(){};  //Funciona
        Materia(string nombre);  //Funciona
        virtual ~Materia(){};
        void setNombreMateria(string nombre);
        void agregarComision(comision c1);  //Funciona
        string getNombreMateria();  //Funciona
        void getComisiones(list<comision> &comisiones);
        void imprimirComisiones();  //Funciona
    private:
        string nombreDeLaMateria;
        list<comision> comisiones;
};

Materia::Materia(string nombre){
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

void Materia::getComisiones(list<comision> &comisiones){
    list<comision>::iterator iterador = this->comisiones.begin();
    while(iterador != this->comisiones.end()){
        comisiones.push_back(*iterador);
        iterador++;
    }
}

void Materia::imprimirComisiones(){
    list<comision>::iterator iterador = this->comisiones.begin();
    comision c;
    string horario;
    while(iterador != this->comisiones.end()){
        c = *iterador;
        cout << "Comision: " << c.nroComision;
        cout << "  Dia: " << c.dia;
        horario = to_string(c.comienzoDeLaClase);
        cout << "  Horario: " << horario[0] << horario[1] << ":" << horario[2] << horario[3];
        horario = to_string(c.finDeLaClase);
        cout << " -- " << horario[0] << horario[1] << ":" << horario[2] << horario[3] << endl;
        iterador++;
    }
}

/*
Fin Clase Materia
*/


/*
Declaracion de funciones.
*/

bool son_compatibles(comision c1, comision c2);
bool podar(map<string,comision> combinacion);
string pasarAMinisculas(string cadena);
int backtracking(map<string,comision> &combinacionPosible, list<map<string,comision>> &combinacionesPosibles, int cantM, list<Materia> materias, int contador);
void imprimirSolucion(list<map<string,comision>> solucion);
void imprimirMenu();
void imprimirMaterias(list<Materia> materias);


/*
Fin de declaracion de funciones.
*/

/*
Inicio Main
*/
int main()
{
    /*
    Instancias de la clase Materia
    */
    Materia m1 = Materia("Programacion 1");
    Materia m2 = Materia("Web 1");
    Materia m3 = Materia("Ingles 1");
    Materia m4 = Materia("Taller de Matematica Computacional");

    /*
    Agrego comisiones
    */
    //Programacion 1
    comision c;
    c.dia = "Lunes";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1500;
    c.finDeLaClase = 1800;
    m1.agregarComision(c);
    c.dia = "Lunes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1800;
    c.finDeLaClase = 2100;
    m1.agregarComision(c);
    c.dia = "Miercoles";
    c.nroComision = 2;
    c.comienzoDeLaClase = 1500;
    c.finDeLaClase = 1800;
    m1.agregarComision(c);
    //Web 1
    c.dia = "Lunes";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1700;
    c.finDeLaClase = 1900;
    m2.agregarComision(c);
    c.dia = "Lunes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1000;
    c.finDeLaClase = 1200;
    m2.agregarComision(c);
    //Ingles 1
    c.dia = "Jueves";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1000;
    c.finDeLaClase = 1200;
    m3.agregarComision(c);
    c.dia = "Martes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1400;
    c.finDeLaClase = 1600;
    m3.agregarComision(c);
    //Taller de Matematica Computacional
    c.dia = "Jueves";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1100;
    c.finDeLaClase = 1300;
    m4.agregarComision(c);

    /*
    Estructuras
    */

    map<string,comision> combinacionPosible;
    list<map<string,comision>> combinacionesPosibles;
    list<Materia> materias;

    materias.push_back(m1);
    materias.push_back(m2);
    materias.push_back(m3);
    materias.push_back(m4);

    /*
    Menu
    */

    int opcion = -1;
    string auxiliar;
    while(opcion != 0){
        system("cls");
        imprimirMenu();
        cin >> opcion;
        system("cls");
        switch (opcion)
        {
            case 1:
                imprimirMaterias(materias);
                cout << "Ingrese cualquier caracter para volver al menu: ";
                cin >> auxiliar;
                break;
            case 2:
                backtracking(combinacionPosible,combinacionesPosibles,4,materias,1);
                imprimirSolucion(combinacionesPosibles);
                combinacionPosible.clear();
                combinacionesPosibles.clear();
                cout << "Ingrese cualquier caracter para volver al menu: ";
                cin >> auxiliar;
                break;
            case 0:
                cout << "Cerrando programa" << endl;
                break;
            default:
                cout << "Ha ingresado una opcion incorrecta" << endl;
                cout << "Ingrese cualquier caracter para volver al menu: ";
                cin >> auxiliar;
                break;
        }
    }

    return 0;
}

/*
Fin del Main
*/

bool son_compatibles(comision c1,comision c2){
    if(c1.dia != c2.dia){ // No son del mismo dia, por lo tanto son compatibles y no comparo horarios.
        return true;
    }else{ //Son del mismo dia, por lo tanto comparo horarios.
        if((c2.comienzoDeLaClase >= c1.comienzoDeLaClase) & (c2.comienzoDeLaClase < c1.finDeLaClase)){
            return false;
        }else if((c1.comienzoDeLaClase >= c2.comienzoDeLaClase) & (c1.comienzoDeLaClase < c2.finDeLaClase)){
            return false;
        }else if((c2.finDeLaClase > c1.comienzoDeLaClase) & (c2.finDeLaClase <= c1.finDeLaClase)){
            return false;
        }else if((c1.finDeLaClase > c2.comienzoDeLaClase) & (c1.finDeLaClase <= c2.finDeLaClase)){
            return false;
        }
    }
    return true;
}

bool podar(map<string,comision> combinacion){
    map<string,comision>::iterator iteradorC1 = combinacion.begin();
    map<string,comision>::iterator iteradorC2 ;
    while(iteradorC1 != combinacion.end()){
        iteradorC2 = combinacion.begin();
        while(iteradorC2 != combinacion.end()){
            if(iteradorC2->first != iteradorC1->first){
                if(!son_compatibles(iteradorC1->second,iteradorC2->second))
                    return true;
            }
            iteradorC2++;
        }
        iteradorC1++;
    }
    return false;
}

int backtracking(map<string,comision> &combinacionPosible, list<map<string,comision>> &combinacionesPosibles, int cantM, list<Materia> materias, int contador){
    if(cantM + 1 == contador){
        combinacionesPosibles.push_back(combinacionPosible); //Agrego la combinacion a la lista con todas las combinaciones.
        return 1; //Encontre solucion
    }else{
        int solucion = 0;
        list<comision> comisiones;
        Materia m = materias.front();
        materias.pop_front();
        m.getComisiones(comisiones);
        list<comision>::iterator iterador = comisiones.begin();

        while((iterador != comisiones.end()) & (solucion == 0)){
            combinacionPosible[m.getNombreMateria()] = *iterador;
            if(!podar(combinacionPosible)){
                comision c = *iterador;
                solucion = backtracking(combinacionPosible,combinacionesPosibles,cantM,materias,contador + 1);
            }
            iterador++;
        }
    }
    return 0; //No encontre solucion
}

void imprimirSolucion(list<map<string,comision>> solucion){
    list<map<string,comision>>::iterator iteradorLista = solucion.begin();
    map<string,comision> combinacion;
    map<string,comision>::iterator iteradorMateria;
    comision c;
    while(iteradorLista != solucion.end()){
        combinacion = *iteradorLista;
        iteradorMateria = combinacion.begin();
        cout << "Combinacion Posible :" << endl;
        while(iteradorMateria != combinacion.end()){
            c = iteradorMateria->second;
            cout << "Materia: " << iteradorMateria->first << " -- Comision :" << c.nroComision << endl;
            iteradorMateria++;
        }
        cout << "------------------" << endl;
        iteradorLista++;
    }
}

void imprimirMenu(){
    cout << "Organizador de comisiones : " << endl;
    cout << "--------------------------" << endl;
    cout << "1. Imprimir las materias con sus respectivas comisiones" << endl;
    cout << "2. Imprimir todas las combinaciones posibles para cursar sin superposicion de horarios" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "----------------------" << endl;
    cout << "Elija una de las siguientes opciones : ";
}

void imprimirMaterias(list<Materia> materias){
    list<Materia>::iterator iterador = materias.begin();
    cout << "Materias : " << endl;
    cout << "-----------------------" << endl;
    while(iterador != materias.end()){
        Materia m = *iterador;
        cout << m.getNombreMateria() << endl;
        m.imprimirComisiones();
        cout << "-----------------------" << endl;
        iterador++;
    }
}
