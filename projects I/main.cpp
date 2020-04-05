/*
Creador: Eduardo Javier Maldonado Acevedo
Carrera: Ingenieria en informatica
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void presentaMenuGeneral();

int main(){
  presentaMenuGeneral();
}

void presentaMenuGeneral() {
  string contenido;
  string contenido2;
  int opcion;
  do {
    system("cls");
    cout << "Menu principal" << endl;
    cout << "=====================================================" << endl;
    cout << "=====================================================" << endl;
    cout << "	[1]Crear archivo de texto" << endl;
    cout << "		[2]Abrir archivo de texto" << endl;
    cout << "			[3]Modificar archivo de texto" << endl<<endl;
    cout << "=====================================================" << endl;
    cout << "				[0]Salir del programa" << endl;
    cout << "=====================================================" << endl;
    cout << "Ingresa la opcion: ";
    cin >> opcion;
    switch (opcion) {
    case 0:
      break;
    case 1:
      {
        cout << "Ingresa el nombre del archivo a crear(sin el .txt): ";
        cin.ignore();
        getline(cin, contenido2);
        cout << "Ingresa el contenido del archivo: ";
        getline(cin, contenido);
        contenido2 += ".txt";
        ofstream fs(contenido2.c_str());
        fs << contenido << endl;
        fs.close();
        cout << "El archivo ha sido creado correctamente" << endl;
        system("pause");
        break;
      }
    case 2:
      {
        cout << "Ingresa el nombre del archivo que quieres leer(sin el .txt): ";
        cin.ignore();
        getline(cin, contenido2);
        contenido2 += ".txt";
        ifstream fs(contenido2.c_str(), ios:: in );
        char linea[128];
        long contador = 0L;
        if (fs.fail())
          cerr << "El fichero no existe" << endl;
        else
          while (!fs.eof()) {
            fs.getline(linea, sizeof(linea));
            cout << linea << endl;
            if ((++contador % 24) == 0) {
              cout << "continuar...";
              cin.get();
            }
          }
        fs.close();
        system("pause");
        break;
      }
    case 3:
      {
        cout << "Ingresa el nombre del archivo que quieres modificar(sin el .txt): ";
        cin.ignore();
        getline(cin, contenido2);
        contenido2 += ".txt";
        cout << "Ingresa el NUEVO contenido del archivo: ";
        getline(cin, contenido);
        ofstream fs(contenido2.c_str(), ios::out);
        fs << contenido << endl;
        fs.close();
        cout << "El archivo ha sido modificado correctamente" << endl;
        system("pause");
        break;
      }
    default:
      cout << "\nEl numero de opcion escrito no es valido\n" << endl;
      system("pause");
    }
  } while (opcion != 0);
}
