#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Estructura para manejar los datos del paciente
struct Paciente {
    vector<int> sintomasPorEspecialidad;
    int totalSintomas;
    int valorGravedad;
    string nombreGravedad;
};

// Subprograma para calcular la gravedad segun la tabla del inciso e
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

        // Pedimos los 5 sintomas uno por uno
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

        // Sumamos y calculamos gravedad inmediatamente
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
    cout << "\nCantidad de casos criticos (>10 sintomas): " << contCriticos << endl;

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
    cout << "\nIngrese un valor de gravedad (1-4) para filtrar promedio de menores a este: ";
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
    cout << "\nIngrese valor de gravedad para promediar sintomas EXACTOS de esa categoria: ";
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
    cout << "\nMayor cantidad de sintomas registrada en un solo paciente: " << maxSintomas << endl;

   

    return 0;
}