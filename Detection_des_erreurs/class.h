#include <iostream>
#include <string>

using namespace std;

class Detection {
public:
	string FormeBinaire;

	string toString() const {
		return FormeBinaire;
	}

	Detection(string formeBinaire);

	string PolynomeFormeAlgebrique();
	string calculerDegre();
	static string multiplierPolynomeParDegreCrc(Detection& a, Detection& b);
	static pair<string, string> diviserPolynomeParG(Detection& a, Detection& b);
	static string calculerPolynomeFinal(Detection& P_prime, Detection& reste);
	static string supprimerBitAleatoire(const string& message);
};