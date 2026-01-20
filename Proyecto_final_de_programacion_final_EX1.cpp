#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>   

using namespace std;

// Estructura para agrupar los datos de cada paciente [cite: 3]
struct Paciente {
    int sintomas[5]; 
    int totalSintomas;
    int valorGravedad;
    string nombreGravedad;
};

// Subprograma para validar entrada y evitar bucles infinitos por letras
int pedirNumero(string mensaje) {
    string entrada;
    while (true) {
        cout << mensaje;
        cin >> entrada;
        bool esValido = true;
        for (int i = 0; i < entrada.length(); i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                esValido = false;
                break;
            }
        }
        if (esValido) return atoi(entrada.c_str());
        cout << "Ingrese un valor valido." << endl;
    }
}

// SUBPROGRAMA: Determina la gravedad según la tabla del documento [cite: 10, 11]
void determinarGravedad(Paciente &p) {
    if (p.totalSintomas > 10) {
        p.valorGravedad = 4; p.nombreGravedad = "Critico";
    } else if (p.totalSintomas >= 7) { 
        p.valorGravedad = 3; p.nombreGravedad = "Grave";
    } else if (p.totalSintomas >= 4) { 
        p.valorGravedad = 2; p.nombreGravedad = "Poco Grave";
    } else if (p.totalSintomas >= 1) { 
        p.valorGravedad = 1; p.nombreGravedad = "Bajo observacion";
    } else {
        p.valorGravedad = 0; p.nombreGravedad = "Sin sintomas";
    }
}

int main() {
    srand(time(0)); 
    int N;

    // a y b) Cantidad y creación del array hospital [cite: 5, 6]
    N = pedirNumero("Ingrese la cantidad de pacientes: ");
    if (N <= 0) return 0;
    vector<Paciente> hospital(N);

    // c) Registro de pacientes [cite: 8]
    for (int i = 0; i < N; i++) {
        cout << "\n--- Registro Paciente " << i + 1 << " ---" << endl;
        hospital[i].totalSintomas = 0;
        string nombres[] = {"Traumatologia", "Infectologia", "Medicina General", "Neurologia", "Cardiologia"};
        
        for(int j = 0; j < 5; j++) {
            hospital[i].sintomas[j] = pedirNumero(nombres[j] + ": ");
            hospital[i].totalSintomas += hospital[i].sintomas[j];
        }
        determinarGravedad(hospital[i]); 
    }

    // d) Cantidad de casos críticos [cite: 9]
    int contCriticos = 0;
    for (int i = 0; i < N; i++) {
        if (hospital[i].valorGravedad == 4) contCriticos++;
    }
    cout << "\nCantidad de casos criticos (>10 sintomas): " << contCriticos << endl;

    // e) Retornar gravedad de un paciente dado [cite: 10]
    int pos;
    pos = pedirNumero("\nIngrese numero de paciente a consultar (1-" + to_string(N) + "): ");
    if (pos > 0 && pos <= N) {
        cout << "Gravedad: " << hospital[pos-1].nombreGravedad << " (Nivel " << hospital[pos-1].valorGravedad << ")" << endl;
    }

    // f) Promedio de sintomas y CANTIDAD de pacientes con gravedad MENOR a un valor [cite: 12]
    int vRef;
    vRef = pedirNumero("\nIngrese un valor de gravedad (1-4) para ver los menores: ");
    int sumaM = 0, cantM = 0;
    for (int i = 0; i < N; i++) {
        if (hospital[i].valorGravedad < vRef) {
            sumaM += hospital[i].totalSintomas;
            cantM++;
        }
    }
    cout << "Pacientes con gravedad menor a " << vRef << ": " << cantM << endl;
    if (cantM > 0) {
        cout << "Promedio de sintomas de estos pacientes: " << (float)sumaM / cantM << endl;
    } else {
        cout << "No existen pacientes registrados con gravedad menor a " << vRef << endl;
    }

    // g) Promedio de sintomas de un nivel EXACTO [cite: 13]
    int gEntrada;
    gEntrada = pedirNumero("\nIngrese valor de gravedad para promedio exacto: ");
    int sumaE = 0, cantE = 0;
    for (int i = 0; i < N; i++) {
        if (hospital[i].valorGravedad == gEntrada) {
            sumaE += hospital[i].totalSintomas;
            cantE++;
        }
    }
    if (cantE > 0) cout << "Promedio nivel " << gEntrada << ": " << (float)sumaE / cantE << endl;
    else cout << "No hay pacientes con ese nivel de gravedad." << endl;

    // h) Mayor cantidad de síntomas [cite: 14]
    int maxS = 0;
    for (int i = 0; i < N; i++) if (hospital[i].totalSintomas > maxS) maxS = hospital[i].totalSintomas;
    cout << "\nMayor cantidad de sintomas registrada: " << maxS << endl;

    // i) Porcentaje de Bajo Observacion y Poco Grave [cite: 15]
    int leves = 0;
    for (int i = 0; i < N; i++) {
        if (hospital[i].valorGravedad == 1 || hospital[i].valorGravedad == 2) leves++;
    }
    cout << "Porcentaje Leves (Nivel 1 y 2): " << (float)leves / N * 100 << "%" << endl;

    // j) Equivalencia (5 pacientes aleatorios) [cite: 16]
    if (N >= 5) {
        cout << "\n--- Relacion de Equivalencia (Aleatoria) ---" << endl;
        for (int k = 0; k < 5; k++) {
            int a = rand() % N;
            int b = rand() % N;
            if (a != b && hospital[a].totalSintomas == hospital[b].totalSintomas)
                cout << "Paciente " << a+1 << " tiene los mismos sintomas que el Paciente " << b+1 << endl;
        }
    }

    // k) Ortogonalidad (Primeros dos pacientes) [cite: 17]
    if (N >= 2) {
        int dot = 0;
        for (int j = 0; j < 5; j++) {
            dot += hospital[0].sintomas[j] * hospital[1].sintomas[j];
        }
        cout << "\nOrtogonalidad: " << (dot == 0 ? "SI son ortogonales" : "NO son ortogonales") << " (Suma: " << dot << ")" << endl;
    }

    return 0;
}