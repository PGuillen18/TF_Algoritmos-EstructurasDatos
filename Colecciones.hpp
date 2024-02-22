#include "EstDatos.hpp"
#include "Entidades.hpp"
#include <chrono>

//ACABADO TREE CLIENTE BASICO
class TreeClienteBasico {
	ArbolAVL<ClienteBasico>* treeCliente;
	void (*imprimirPaClientesBasicos)(ClienteBasico);
	short (*criterioComparacionDineroBasicos)(ClienteBasico, ClienteBasico);

public:
	TreeClienteBasico() {
		imprimirPaClientesBasicos = [](ClienteBasico c)->void {cout << c.getDatos() << endl; };
		criterioComparacionDineroBasicos = [](ClienteBasico a, ClienteBasico b)->short {if (a.getDinero() == b.getDinero())return 0;
		else if (a.getDinero() > b.getDinero())return 1;
		else return -1; };
		treeCliente = new ArbolAVL<ClienteBasico>(imprimirPaClientesBasicos, criterioComparacionDineroBasicos);
	}
	void creacionArbolClientesBasico() {
		ifstream archivo("ListaClientes.csv");
		string linea;
		int contador = 0;
		auto start = chrono::high_resolution_clock::now();  
		while (getline(archivo, linea) && contador < NUMTOTAL) {
			stringstream ss(linea);
			string valor;
			string id;
			dineroClientes dinero;
			getline(ss, valor, ',');
			id = stoi(valor);

			ClienteBasico cliente(id);
			treeCliente->Insertar(cliente);
			contador++;
		}
		archivo.close();
		auto end = chrono::high_resolution_clock::now(); 
		double duration = chrono::duration<double, std::milli>(end - start).count(); 
		cout << "Tiempo de insercion en el arbol AVL: " << duration << " milisegundos" << std::endl;
		system("pause");
	}
	
	void print() {
		cout << "Impresion de los elementos (In-Orden): " << endl;
		treeCliente->inOrden();
		cout << endl;
	}
	ClienteBasico obtenerElementoEnPosicion(int posicion) {
	      return treeCliente->getElementoEnPosicion(posicion);
	}
	void actualizacionCliente(int n, Habitaciones habitacionAux, int costoHabitacion) {
		ClienteBasico clienteAux = obtenerElementoEnPosicion(n);
		clienteAux.setInfoHabitaciones(habitacionAux.getDatos());
		clienteAux.setEstado("Bloqueado");
		clienteAux.setReserVoCorrecto(true);
		clienteAux.setResta(costoHabitacion);
		treeCliente->actualizarElementoEnPosicion(n, clienteAux);
	}

};

//ACABADO TREE CLIENTE PREMIUM
class TreeClientePremium {
	ArbolRB<ClientePremium>* treeCliente;
	void (*imprimirPaClientesPremium)(ClientePremium);
	short (*criterioComparacionDineroPremium)(ClientePremium, ClientePremium);

public:
	TreeClientePremium() {
		imprimirPaClientesPremium = [](ClientePremium c)->void {cout << c.getDatos() << endl; };
		criterioComparacionDineroPremium = [](ClientePremium a, ClientePremium b)->short {if (a.getDinero() == b.getDinero())return 0;
		else if (a.getDinero() < b.getDinero())return 1;
		else return -1; };
		treeCliente = new ArbolRB<ClientePremium>(imprimirPaClientesPremium, criterioComparacionDineroPremium);
	}
	void creacionArbolClientesPremium() {
		ifstream archivo("ListaClientes.csv");
		string linea;
		int contador = 0;
		auto start = chrono::high_resolution_clock::now();  // Tiempo de inicio de inserción

		while (getline(archivo, linea) && contador < NUMTOTAL) {
			stringstream ss(linea);
			string valor;
			string id;
			dineroClientes dinero;
			getline(ss, valor, ',');
			id = stoi(valor);

			ClientePremium cliente(id);
			treeCliente->Insertar(cliente);
			contador++;
		}
		archivo.close();
		auto end = chrono::high_resolution_clock::now();
		double duration = chrono::duration<double, milli>(end - start).count();

		cout << "Tiempo de insercion en el arbol Rojo y Negro: " << duration << " milisegundos" << std::endl;
		system("pause");
	}
	void print() {
		cout << "Impresion de los elementos (In-Orden): " << endl;
		treeCliente->inOrden();
		cout << endl;
	}

	ClientePremium obtenerElementoEnPosicion(int posicion) {
		return treeCliente->getElementoEnPosicion(posicion);
	}
	void actualizacionCliente(int n, Habitaciones habitacionAux, int costoHabitacion) {
		ClientePremium clienteAux = obtenerElementoEnPosicion(n);

		void (*actualizarCliente)(ClientePremium&, Habitaciones&, int) = [](ClientePremium& c, Habitaciones& h, int costo) {
			c.setInfoHabitaciones(h.getDatos());
			c.setEstado("Bloqueado");
			c.setReserVoCorrecto(true);
			c.setResta(costo);
		};

		actualizarCliente(clienteAux, habitacionAux, costoHabitacion);

		treeCliente->actualizarElementoEnPosicion(n, clienteAux);
	}

	void buscarClientePorDinero(int dinero) {

		int posicion = treeCliente->BuscarRB(dinero);
		if (posicion != -1) {
			cout << "Se encontró un cliente con dinero $" << dinero << " en la posición " << posicion << endl;
		}
		else {
			cout << "No se encontró un cliente con dinero $" << dinero << endl;
		}
	}
	bool esCompleto() {
		return treeCliente->esCompleto();
	}
	NodoRB<ClientePremium>* encontrarComun_Ancestro(ClientePremium c1, ClientePremium c2)
	{
		return treeCliente->encontrarAncestroComun(c1, c2);
	}
	bool esBalnceadoNegro() {
		return treeCliente->esBalanceadoAlturaNegra();
	}
};

//TreeHabitacionesFinalizado
class TreeHabitaciones {
	ArbolAVL <Habitaciones>* treeHabitaciones;
	void (*imprimirPaHabitaciones)(Habitaciones);
	short (*criterioHabitaciones)(Habitaciones, Habitaciones);
public:
	TreeHabitaciones() {
		imprimirPaHabitaciones = [](Habitaciones h)->void {cout << h.getDatos()<<endl; };
		criterioHabitaciones = [](Habitaciones a, Habitaciones b)->short {if (a.getCosto() == b.getCosto())return 0;
		else if (a.getCosto() < b.getCosto())return 1;
		else return -1; };
		treeHabitaciones = new ArbolAVL<Habitaciones>(imprimirPaHabitaciones, criterioHabitaciones);
	}
	void creacionArbolHabitaciones() {
		for (int i = 0; i < NUMTOTAL; i++)
		{
			Habitaciones habitacion;
			treeHabitaciones->Insertar(habitacion);
		}
	}
	void print() {
		cout << "Impresion de elementos (In-Orden): " << endl;
		treeHabitaciones->inOrden();
		cout << endl;
	}
	Habitaciones obtenerElementoEnPosicion(int posicion) {
		return treeHabitaciones->getElementoEnPosicion(posicion);
	}

	//LAMBDA 1 ESTRUCTURA DE DATOS ARBOL AVL
	void actualizacionHabitaciones(int n, int cantidadTiempo) {
		Habitaciones habitacion = obtenerElementoEnPosicion(n);

		auto actualizarHabitacion = [](Habitaciones& h, int tiempo) {
			h.setReservado(false);
			h.setDias(tiempo);
		};

		actualizarHabitacion(habitacion, cantidadTiempo);

		treeHabitaciones->actualizarElementoEnPosicion(n, habitacion);
	}


	int getTamanio() {
		return treeHabitaciones->getTamanio();
	}

	//LAMBDA 2 ESTRUCTURA DE DATOS ARBOL AVL

	void buscarHabitacionPorCosto(int costo) {
		Habitaciones elementoBusqueda;
		elementoBusqueda.setCosto(costo);

		if (treeHabitaciones->BuscarAVL(elementoBusqueda, criterioHabitaciones)) {

			auto imprimirEncontrado = [](int i, Habitaciones& h) {
				cout << "Habitación encontrada en la posición " << i << ": " << endl;
				cout << "Datos de la habitación:" << endl;
				cout << h.getDatos() << endl;
			};
		}
		else
		cout << "No se encontró ninguna habitación de este tipo." << endl;
	}
	

};

//coleccionHashReservados
class HashClientesReservados
{
	HashTable <string, ClienteReservado*> hashReservados;

public:
	HashClientesReservados() {

	};
	void insertarClienteReservado(const string& clave, ClienteReservado* cliente)
	{
		hashReservados.insert(HashEntidad<string, ClienteReservado*>(clave, cliente));
	}
	ClienteReservado* buscarClienteReservado(const string& clave)
	{
		const HashEntidad<string, ClienteReservado*>* entidadEncontrada = hashReservados.search(clave);
		if (entidadEncontrada != nullptr) {
			return entidadEncontrada->getValue();
		}
		else {
			return nullptr;
		}
	}
    void imprimirClientesReservados() {
        hashReservados.print();
    }

};

