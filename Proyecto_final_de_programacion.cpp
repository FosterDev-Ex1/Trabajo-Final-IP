#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib> 
#include <ctime>   

using namespace std;

struct Paciente {
    vector<int> sintomasPorEspecialidad; 
    int totalSintomas;
    int valorGravedad;
    string nombreGravedad;
};

void determinarGravedad(Paciente &p) {
    if (p.totalSintomas >= 1 && p.totalSintomas <= 3) {
        p.valorGravedad = 1;
        p.nombreGravedad = "Bajo observacion";
    } else if (p.totalSintomas >= 4 && p.totalSintomas <= 7) {
        p.valorGravedad = 2;
        p.nombreGravedad = "Poco Grave";
    } else if (p.totalSintomas > 7 && p.totalSintomas <= 10) {
        p.valorGravedad = 3;
        p.nombreGravedad = "Grave";
    } else if (p.totalSintomas > 10) {
        p.valorGravedad = 4;
        p.nombreGravedad = "Critico";
    } else {
        p.valorGravedad = 0;
        p.nombreGravedad = "Sin sintomas";
    }
}

int main() {
    srand(time(0)); 

    // Inciso a
    int cantidadPacientes;
    cout << "Ingrese la cantidad de pacientes que desea registrar: ";
    cin >> cantidadPacientes;

    // Inciso b
    vector<Paciente> hospital(cantidadPacientes);

    // Inciso c
    for (int i = 0; i < cantidadPacientes; ++i) {
        cout << "\n--- Registrando Paciente " << i + 1 << " ---" << endl;
        hospital[i].totalSintomas = 0;
        
        cout << "Ingrese sintomas de Traumatologia: ";
        int s1; cin >> s1; hospital[i].sintomasPorEspecialidad.push_back(s1);
        
        cout << "Ingrese sintomas de Infectologia: ";
        int s2; cin >> s2; hospital[i].sintomasPorEspecialidad.push_back(s2);
        
        cout << "Ingrese sintomas de Medicina General: ";
        int s3; cin >> s3; hospital[i].sintomasPorEspecialidad.push_back(s3);
        
        cout << "Ingrese sintomas de Neurologia: ";
        int s4; cin >> s4; hospital[i].sintomasPorEspecialidad.push_back(s4);
        
        cout << "Ingrese sintomas de Cardiologia: ";
        int s5; cin >> s5; hospital[i].sintomasPorEspecialidad.push_back(s5);

        hospital[i].totalSintomas = s1 + s2 + s3 + s4 + s5;
        determinarGravedad(hospital[i]); 
    }

    // Inciso d
    int contCriticos = 0;
    for (int i = 0; i < cantidadPacientes; ++i) {
        if (hospital[i].totalSintomas > 10) {
            contCriticos++;
        }
    }
    cout << "\nCantidad de casos criticos: " << contCriticos << endl;

    // Inciso e
    int indiceBusqueda;
    cout << "\nIngrese el numero de paciente (1 a " << cantidadPacientes << ") para ver su gravedad: ";
    cin >> indiceBusqueda;
    if (indiceBusqueda > 0 && indiceBusqueda <= cantidadPacientes) {
        cout << "El paciente tiene gravedad nivel: " << hospital[indiceBusqueda - 1].valorGravedad 
             << " (" << hospital[indiceBusqueda - 1].nombreGravedad << ")" << endl;
    }

    // Inciso f
    int valorGravedadRef;
    cout << "\nIngrese un valor de gravedad (1-4) para filtrar: ";
    cin >> valorGravedadRef;
    
    int sumaSintomasMenor = 0;
    int countMenor = 0;
    
    for (int i = 0; i < cantidadPacientes; ++i) {
        if (hospital[i].valorGravedad < valorGravedadRef) {
            sumaSintomasMenor += hospital[i].totalSintomas;
            countMenor++;
        }
    }
    
    if (countMenor > 0) {
        cout << "Promedio sintomas (gravedad < " << valorGravedadRef << "): " << (double)sumaSintomasMenor / countMenor << endl;
        cout << "Cantidad de pacientes con gravedad menor: " << countMenor << endl;
    } else {
        cout << "No hay pacientes con gravedad menor a " << valorGravedadRef << endl;
    }

    // Inciso g
    int gravedadEntrada;
    cout << "\nIngrese valor de gravedad para promediar sintomas de esa categoria: ";
    cin >> gravedadEntrada;
    int sumaSintomasIgual = 0;
    int countIgual = 0;

    for (int i = 0; i < cantidadPacientes; ++i) {
        if (hospital[i].valorGravedad == gravedadEntrada) {
            sumaSintomasIgual += hospital[i].totalSintomas;
            countIgual++;
        }
    }

    if (countIgual > 0) {
        cout << "Promedio de sintomas para gravedad " << gravedadEntrada << ": " << (double)sumaSintomasIgual / countIgual << endl;
    } else {
        cout << "No hay pacientes con ese valor de gravedad." << endl;
    }

    // Inciso h
    int maxSintomas = -1;
    for (int i = 0; i < cantidadPacientes; ++i) {
        if (hospital[i].totalSintomas > maxSintomas) {
            maxSintomas = hospital[i].totalSintomas;
        }
    }
    cout << "\nMayor cantidad de sintomas registrada por un paciente: " << maxSintomas << endl;

    // Inciso i
    int countBajoPoco = 0;
    for (int i = 0; i < cantidadPacientes; ++i) {
        if (hospital[i].nombreGravedad == "Bajo observacion" || hospital[i].nombreGravedad == "Poco Grave") {
            countBajoPoco++;
        }
    }
    if (cantidadPacientes > 0) {
        double porcentaje = ((double)countBajoPoco / cantidadPacientes) * 100.0;
        cout << "Porcentaje de pacientes Bajo observacion y Poco Grave: " << porcentaje << "%" << endl;
    }

    // Inciso j
    cout << "\n--- Relacion de Equivalencia (5 pacientes aleatorios) ---" << endl;
    if (cantidadPacientes >= 5) {
        vector<int> indicesAleatorios;
        for (int k = 0; k < 5; k++) {
            indicesAleatorios.push_back(rand() % cantidadPacientes);
        }

        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 5; j++) {
                int p1 = indicesAleatorios[i];
                int p2 = indicesAleatorios[j];
                if (hospital[p1].totalSintomas == hospital[p2].totalSintomas) {
                    cout << "Paciente " << p1 + 1 << " es equivalente a Paciente " << p2 + 1 
                         << " (Mismo numero de sintomas: " << hospital[p1].totalSintomas << ")" << endl;
                }
            }
        }
    } else {
        cout << "No hay suficientes pacientes para tomar 5 aleatorios." << endl;
    }

    // Inciso k
    cout << "\n--- Ortogonalidad de los dos primeros pacientes ---" << endl;
    if (cantidadPacientes >= 2) {
        int productoPunto = 0;
        for (int k = 0; k < 5; k++) {
            productoPunto += hospital[0].sintomasPorEspecialidad[k] * hospital[1].sintomasPorEspecialidad[k];
        }

        if (productoPunto == 0) {
            cout << "Los vectores de sintomas son ORTOGONALES." << endl;
        } else {
            cout << "Los vectores de sintomas NO son ortogonales (Producto punto: " << productoPunto << ")." << endl;
        }
    } else {
        cout << "Se necesitan al menos 2 pacientes para este calculo." << endl;
    }

    return 0;
}