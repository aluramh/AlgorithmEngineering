#ifndef ListaLineal_ListaLineal_h
#define ListaLineal_ListaLineal_h
using namespace std;

class Node {
public:
	int info;
	double x;
	double y;
	double z;
	Node *sig;
	Node() { sig = NULL; }
	Node(int dato) { info = dato; sig = NULL; }
	Node(int dato, double xval, double yval, double zval) {
		info = dato; 
		x = xval;
		y = yval; 
		z = zval; 
		sig = NULL; 
	}
	Node(int dato, double xval, double yval, double zval, Node* siguiente) {
		info = dato; 
		sig = siguiente;
		x = xval;
		y = yval;
		z = zval;
	}
	double getInfo() {return this->info;}
	double getX() { return this->x; }
	double getY() { return this->y; }
	double getZ() { return this->z; }
};

class ListaLineal {
	friend ostream& operator << (ostream& os, const ListaLineal& a) {
		Node *p = a.inicio;
		while (p != NULL) {
			cout << p->info << " ";
			p = p->sig;
		}
		os << endl;
		return os;
	}
	friend istream& operator >> (istream& is, ListaLineal& a) {
		int valor;
		is >> valor;
		is.ignore();
		return is;
	}
public:
	ListaLineal() {
		inicio = NULL;
	}
	ListaLineal(const ListaLineal &L) { //Copy constructor
		inicio = NULL;
		Node *P = L.inicio;
		if (L.inicio != NULL) {
			inicio = new Node(P->info);
			Node *R = inicio;
			P = P->sig;
			while (P != NULL) {
				R->sig = new Node(P->info);
				R = R->sig;
				P = P->sig;
			}
		}
	}
	ListaLineal &operator =(const ListaLineal &L) { //Sobrecarga de asignacion
		if (this != &L) {
			while (!listaVacia()) {
				borrarInicio();
			}
			Node *P = L.inicio;
			if (L.inicio != NULL) {
				inicio = new Node(P->info);
				Node *R = inicio;
				P = P->sig;
				while (P != NULL) {
					R->sig = new Node(P->info);
					R = R->sig;
					P = P->sig;
				}
			}
		}
		return *this;
	}
	~ListaLineal() {
		while (!listaVacia())
			borrarInicio();
	}
	int observaLista() {
		return inicio->info;
	}
	void meterInicio(int dato, float x, float y, float z) {
		Node *p = new Node(dato, x, y, z, inicio);
		inicio = p;
	}
	void borrarInicio() {
		Node *p = inicio;
		inicio = inicio->sig;
		delete p;
	}
	void meterFinal(int valor) {
		Node *q = new Node(valor);
		if (inicio == NULL)
			inicio = q;
		else {
			Node *p = inicio;
			while (p->sig != NULL)
				p = p->sig;
			p->sig = q;
		}
	}
	void borrarFinal() {
		Node *q = NULL;
		Node *p = inicio;
		while (p->sig != NULL) {
			q = p;
			p = p->sig;
		}
		if (q == NULL)
			inicio = NULL;
		else
			q->sig = NULL;
		delete p;
	}
	bool busca(int valor) {
		Node *p = inicio;
		while (p != NULL && p->info != valor)
			p = p->sig;
		return !(p == NULL);
	}

	void desplegar() {
		Node *p = inicio;
		while (p != NULL) {
			cout << p->info << ": (" << p->x << ", " << p->y << ", " << p->z << ")" << endl;
			p = p->sig;
		}
		cout << endl;
	}
	bool listaVacia() {
		return inicio == NULL;
	} //Regresa true o false
	int cantidadPares() {
		int pares = 0;
		Node *p = inicio;
		while (p != NULL) {
			if (p->info % 2 == 0) {
				pares++;
			}
			p = p->sig;
		}
		return pares;
	}
	int sumaRecursivo() {
		return suma(inicio);
	}
	int cuentaPares() {
		return cuenta(inicio);
	}
private:
	int cuenta(Node* actual) {
		if (actual == NULL) {
			return 0;
		}
		if (actual->info % 2 == 0) {
			return 1 + cuenta(actual->sig);
		}
		return 0 + cuenta(actual->sig); //Error tipico, hay que poner la instruccion
	}
	int suma(Node* actual) {
		if (actual == NULL) {
			return 0;
		}
		return actual->info + suma(actual->sig);
	}
	Node *inicio;
};

#endif
