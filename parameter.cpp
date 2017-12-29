#include "parameter.h"

Parameter::Parameter(int argc, char **argv) {
	this->argc = argc;
	this->argv = new char*[argc + 1];
	for(int i = 0; i <= argc; i++) {
		this->argv[i] = argv[i];
	}
}

Parameter::~Parameter() {}

void Parameter::print_help() {
	cout << "Detector de flujo óptico, hecho por Erick Salvador Alvarez Valencia." << endl;
	cout << "Ayuda del sistema:" << endl;
	cout << "--file1 o -F1\t" << " Frame 1 (cualquier formato bitmap de imagen)." << endl;
	cout << "--file2 o -F2\t" << " Frame 2 (cualquier formato bitmap de imagen)." << endl;
	cout << "--lambda o -L\t" << " Valor de lambda." << endl;
	cout << "--algo o -A\t" << " Algoritmo que se usará para el procesamiento: 'Gauss-Seidel' o 'Gradiente paso fijo'." << endl;
	cout << "--toler o -T\t" << " Tolerancia para la convergencia." << endl;
	cout << "--iter o -I\t" << " Número de iteraciones." << endl;
	cout << "--scale o -S\t" << " Escala del campo de velocidades." << endl;
}

map<string, string> Parameter::process() {
	map<string, string> res;
	int i = 1;
	while(i < argc) {
		string p_act = string(argv[i]);
		if(p_act == "--file1" || p_act == "-F1") {
			res["file1"] = string(argv[++i]);
		}
		else if(p_act == "--file2" || p_act == "-F2") {
			res["file2"] = string(argv[++i]);
		}
		else if(p_act == "--lambda" || p_act == "-L") {
			res["lambda"] = string(argv[++i]);
		}
		else if(p_act == "--algo" || p_act == "-A") {
			res["algo"] = string(argv[++i]);
		}
		else if(p_act == "--toler" || p_act == "-T") {
			res["toler"] = string(argv[++i]);
		}
		else if(p_act == "--iter" || p_act == "-I") {
			res["iter"] = string(argv[++i]);
		}
		else if(p_act == "--scale" || p_act == "-S") {
			res["scale"] = string(argv[++i]);
		}
		else if(p_act == "--test") {
			res["test"] = string(argv[++i]);
		}
		else if(p_act == "--verbose" || p_act == "-V") {
			res["verb"] = "1";	
		}
		else {
			cout << "Parámetro '" << p_act << "' no reconocido." << endl;
		}
		i++;
	}

	return res;
}