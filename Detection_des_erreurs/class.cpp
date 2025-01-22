#include "class.h"

Detection::Detection(string formeBinaire) : FormeBinaire(formeBinaire) {}

string Detection::PolynomeFormeAlgebrique() {
    string polynome;
    int degre = FormeBinaire.size() - 1;

        for (size_t i = 0; i < FormeBinaire.size(); ++i) {
            if (FormeBinaire[i] == '1') {
                if (!polynome.empty()) {
                    polynome += " + ";
                }
                if (degre - i > 0) {
                    polynome += "x^" + to_string(degre - i);
                }
                else {
                    polynome += "1";
                }
            }
        }

    return polynome;
}

string Detection::calculerDegre() {
    for (size_t i = 0; i < FormeBinaire.size(); ++i) {
        if (FormeBinaire[i] == '1') {
            int degre = FormeBinaire.size() - 1 - i;
            return "x^" + to_string(degre);
        }
    }
    return "Aucun degre (message nul)";
}

string Detection::multiplierPolynomeParDegreCrc(Detection& a, Detection& b) {
    string message = a.toString();
    string degreCrc = b.toString();

    if (message.empty() || message == "0") {
        return "0";
    }
    int degre = degreCrc.size() - 1;
    string resultat = message + string(degre, '0');

    return resultat;
}

pair<string, string> Detection::diviserPolynomeParG(Detection& a, Detection& b) {
    string dividend = a.toString();  
    string divisor = b.toString();   

    while (dividend.size() < divisor.size()) {
        dividend = "0" + dividend;
    }

    string quotient = "";
    while (dividend.size() >= divisor.size()) {
        if (dividend[0] == '1') {
            quotient += "1";

            for (size_t i = 0; i < divisor.size(); ++i) {
                dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
            }
        }
        else {
            quotient += "0";
        }

        dividend = dividend.substr(1);
    }

    string reste = dividend;

    return { quotient, reste };
}

string Detection::calculerPolynomeFinal(Detection& P_prime, Detection& reste) {
    string pPrimeStr = P_prime.toString();
    string resteStr = reste.toString();

    // Trouver la taille maximale
    size_t maxSize = max(pPrimeStr.size(), resteStr.size());

    // Étendre les deux chaînes pour qu'elles aient la même taille
    while (pPrimeStr.size() < maxSize) {
        pPrimeStr = "0" + pPrimeStr;
    }
    while (resteStr.size() < maxSize) {
        resteStr = "0" + resteStr;
    }

    // Effectuer l'addition binaire (XOR)
    string resultat;
    for (size_t i = 0; i < maxSize; ++i) {
        resultat += (pPrimeStr[i] == resteStr[i]) ? '0' : '1';
    }

    return resultat;
}

string Detection::supprimerBitAleatoire(const string& message) {
    if (message.empty()) {
        throw std::invalid_argument("Le message est vide. Impossible de supprimer un bit.");
    }

    // Initialiser le générateur de nombres aléatoires
    std::srand(std::time(nullptr));

    // Générer une position aléatoire
    size_t position = std::rand() % message.size();

    // Supprimer le bit à la position générée
    string resultat = message.substr(0, position) + message.substr(position + 1);

    return resultat;
}