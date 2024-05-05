#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;

const double tax = 0.25; // constante hecha para el impuesto del casino
//Jeremy Santos Garcia
// primera funcion narrativa
void narrativa() {
    cout << "Nuestro protagonista camina tranquilamente y se aproxima al casino." << endl;
    cout << "Con el cheque de su salario en mano, siente que hoy podria ser su dia de suerte." << endl;
    cout << "Un dilema se presenta ante el: ¿Entrara al casino y jugara en la rueda de la suerte?" << endl;
    cout << "Escribe 'si' para jugar o 'no' para seguir caminando y continuar con tu vida:" << endl;
}

// funcion de la rueda de la suerte
int ruleta() {
    return rand() % 50 + 1; // con esto generas un numero alteatorio del 1 al 50
}

// funcion para calcular el impuesto y las ganancias
double calculateGains(double credits) {
    if (credits >= 1000) {
        double impuesto = credits * tax;
        return credits - impuesto;
    }
    else {
        return credits;
    }
}

// funcion para guardar las victorias y creditos en un archivo
void saveWins(int apuestas, double credits) {
    ofstream file("Stats.txt");
    if (file.is_open()) {
        file << "🔹 Apuestas ganadas: " << apuestas << endl;
        file << "🔹 Creditos: " << credits << endl;
        file.close();
    }
    else {
        cout << "No se pudo abrir el archivo para guardar las victorias y creditos" << endl;
    }
}

int main() {
    srand(time(NULL)); // inicializar los numeros alteatorios
    string respuesta, again;
    int creditos, apuesta, resultado, spin;
    int totalWins = 0;
    double totalCredits = 0;
    string dialogos[4] = {
        "al final del dia termino perdiendo todo su salario semanal intentando de hacer mas dinero :(",
        "no gano mas dinero pero no lo perdio todo :|",
        "al final del dia llego a ganar algo de dinero que fue mejor de lo que esperaba :)",
        "al final del día descubrio que si fue su dia de suerte al conseguir mucho mas dinero de lo que habia conseguido en toda la semana :D"
    };

    narrativa();
    cin >> respuesta;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    //Rodolfo Pereira
    if (respuesta == "si" || respuesta == "Si") {
        cout << "El protagonista decide probar suerte. Introduce su dinero en la rueda de la suerte." << endl;
        cout << "¿Cuantos creditos desea ingresar para jugar? (Tiene que ser un numero entre 1 al 350):" << endl;
        cin >> creditos;
        while (creditos <= 0 || creditos > 350) {
            cout << "La cantidad de creditos tiene que ser entre 1 y 350." << endl;
            cin >> creditos;
        }
        cout << "---------------------------------------------------------------------------------------------" << endl;

        do {
            cout << "¿Cuanto desea apostar?" << endl;
            cin >> apuesta;
            while (apuesta <= 0 || apuesta > creditos) {
                cout << "La apuesta debe ser de al menos 1 credito y no mas de " << creditos << " creditos. Intente de nuevo" << endl;
                cin >> apuesta;
            }
            creditos -= apuesta;

            system("CLS");
            cout << "🎰  Girando la ruleta..." << endl;
            spin = ruleta();

            // if else del spin
            if (spin <= 15) {
                cout << "🔴  > Le toco un X0\nPERDIO!!! 😭" << endl;
                resultado = 0;
            }
            else if (spin <= 26) {
                cout << "🟢  > Le toco un X1\nGano? si lo quieres considerar así " << endl;
                resultado = apuesta;
            }
            else if (spin <= 32) {
                cout << "🟢  > Le toco un X2!\nGano! en verdad esta vez " << endl;
                resultado = 2 * apuesta;
            }
            else if (spin <= 38) {
                cout << "🟢  > Le toco un X3!\nGano!! le llueven los créditos " << endl;
                resultado = 3 * apuesta;
            }
            else if (spin <= 44) {
                cout << "🟢  > Le toco un X4!\nGano!!! Maravillosa jugada " << endl;
                resultado = 4 * apuesta;
            }
            else if (spin <= 48) {
                cout << "🟢  > Le toco un X5!\nGano!!!! Tan cerca pero tan lejos " << endl;
                resultado = 5 * apuesta;
            }
            else {
                cout << "🎲 > JACKPOT!!!!! LE TOCO X10\nFELICIDADES!!!!! GANO EL MEJOR PREMIO 🎲" << endl;
                resultado = 10 * apuesta;
            }

            creditos += resultado;
            totalWins++;
            totalCredits += resultado;

            cout << "Usted ha ganado: " << resultado << " Creditos 🎴️" << endl;
            cout << "🎴 El total de creditos que tiene ahora mismo es de: " << creditos << endl;
            cout << "¿Desea intentar de nuevo? (Y/N)" << endl;
            cin >> again;
        } while ((again == "Y" or again == "y") and creditos > 0);

        double ganancia = calculateGains(creditos);
        saveWins(totalWins, totalCredits);
        system("CLS");
        cout << "Usted tiene un total de: " << creditos << " creditos disponible para convertir en ganancia 🎴" << endl;
        if (creditos >= 1000) {
            cout << "💰 El impuesto que se quita del 25% es de: $ " << creditos * tax << endl;
            cout << "💰 La ganancia de usted despues del impuesto es de: $ " << ganancia << endl;
        }
        else {
            cout << "💰 La ganancia de usted total es de: $ " << ganancia << endl;
        }

        cout << "---------------------------------------------------------------------------------------------" << endl;

        if (ganancia == 0) {
            cout << dialogos[0] << endl;
        }
        else if (ganancia > 1 && ganancia <= 350) {
            cout << dialogos[1] << endl;
        }
        else if (ganancia > 351 && ganancia <= 999) {
            cout << dialogos[2] << endl;
        }
        else if (ganancia > 1000) {
            cout << dialogos[3] << endl;

             
        }
    }
    else {
        cout << "El protagonista decidio seguir con su vida... 🌆" << endl;
    }

    return 0;
}
