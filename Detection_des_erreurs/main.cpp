#include "class.h"
#include <cassert>

int main() {
    // Message original
    Detection message("111010000101010");
    Detection generateur("1101001");

    cout << "===============Codage===============" << endl;
    cout << endl;
    cout << "P(x) = " + message.PolynomeFormeAlgebrique() << endl;
    cout << "G(x) = " + generateur.PolynomeFormeAlgebrique() << endl;
    cout << "Degre de G(x) = " + generateur.calculerDegre() << endl;
    cout << endl;

    // etape 1 : Multiplier P(x) par x^(deg(G(x)))
    Detection P_prime(Detection::multiplierPolynomeParDegreCrc(message, generateur));
    cout << "P'(x) = P(x) * x^(deg(G(x))) = " + P_prime.PolynomeFormeAlgebrique() << endl;
    cout << endl;

    // etape 2 : Diviser P'(x) par G(x) pour obtenir le reste R(x)
    pair<string, string> divisionResult = Detection::diviserPolynomeParG(P_prime, generateur);
    Detection quotient(divisionResult.first);
    Detection reste(divisionResult.second);

    cout << "Diviser P'(x) par G(x) : " << endl;
    cout << "Quotient = " + quotient.PolynomeFormeAlgebrique() << endl;
    cout << "R(x) = " + reste.PolynomeFormeAlgebrique() << endl;
    cout << endl;

    // etape 3 : Generer le message final M(x) = P'(x) + R(x)
    Detection M_final(Detection::calculerPolynomeFinal(P_prime, reste));
    cout << "M(x) = P'(x) + R(x) = " + M_final.PolynomeFormeAlgebrique() << endl;

    cout << endl;
    cout << "===============Decodage===============" << endl;
    cout << endl;

    pair<string, string> verificationResult = Detection::diviserPolynomeParG(M_final, generateur);
    Detection quotientVerification(verificationResult.first);
    Detection resteVerification(verificationResult.second);

    cout << "Diviser M(x) par G(x) : " << endl;
    cout << "Quotient = " + quotientVerification.PolynomeFormeAlgebrique() << endl;
    cout << "R(x) = " + resteVerification.toString() << endl;

    if (resteVerification.toString().find('1') == string::npos) {
        cout << "Message recu est correct : aucune erreur detectee." << endl;
    }
    else {
        cout << "Erreur detectee dans le message recu !" << endl;
    }

    // etape 4 : Supprimer un bit aleatoire dans M(x)
    //try {
    //    string M = Detection::calculerPolynomeFinal(P_prime, reste);
    //    string M_modified = Detection::supprimerBitAleatoire(M);
    //    Detection M_modified_final(M_modified);
    //    cout << "M(x) apres suppression aleatoire d'un bit = " + M_modified_final.PolynomeFormeAlgebrique() << endl;

    //    cout << endl;
    //    cout << "===============Decodage===============" << endl;
    //    cout << endl;

    //    // Decodage
    //    pair<string, string> verificationResult = Detection::diviserPolynomeParG(M_modified_final, generateur);
    //    Detection quotientVerification(verificationResult.first);
    //    Detection resteVerification(verificationResult.second);

    //    cout << "Diviser M(x) par G(x) : " << endl;
    //    cout << "Quotient = " + quotientVerification.PolynomeFormeAlgebrique() << endl;
    //    cout << "R(x) = " + resteVerification.toString() << endl;

    //    if (resteVerification.toString().find('1') == string::npos) {
    //        cout << "Message recu est correct : aucune erreur detectee." << endl;
    //    }
    //    else {
    //        cout << "Erreur detectee dans le message recu !" << endl;
    //    }
    //}
    //catch (const std::exception& e) {
    //    cerr << "Erreur : " << e.what() << endl;
    //}

    return 0;
}