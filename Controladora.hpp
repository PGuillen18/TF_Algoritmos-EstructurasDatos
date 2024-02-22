#include "Colecciones.hpp"

class Controladora
{
  TreeClienteBasico tCAVL;
  TreeClientePremium tPCRB;
  TreeHabitaciones tHAVL;
  HashClientesReservados hashReservados;
  bool resultado;
  short opcion = 0;
public:
	Controladora(bool resultado) {
        this->resultado = resultado;
    };
	void creacionesObjetos() {
        tCAVL.creacionArbolClientesBasico();
		tHAVL.creacionArbolHabitaciones();
        tPCRB.creacionArbolClientesPremium();
	}

    void pClienteHabitacionRojoNegro() {
        int num;
        system("CLS");
        cout << "Clientes Disponibles:" << endl;
        tPCRB.print();
        do {
            cout << "\nElija un cliente (1-" << NUMTOTAL << "): ";
            cin >> num;
        } while (num <= 0 || num > NUMTOTAL);
        cout << endl;
        cout << "\nUsted eligió el cliente en la posición: " << num << ": " << tPCRB.obtenerElementoEnPosicion(num).getDatos();
        int numHabitacionesOcupadas = 0;
        if (tPCRB.obtenerElementoEnPosicion(num).getReservado() != true) {
            for (int i = 1; i <= tHAVL.getTamanio(); i++) {
                if (tHAVL.obtenerElementoEnPosicion(i).getReservado() == true) {
                    numHabitacionesOcupadas++;
                }
            }
            if (numHabitacionesOcupadas == 0) {
                cout << "\nTodas las habitaciones están ocupadas. El programa se cerrará." << endl;
                //guardarClienteReservado(StackReservados);
                resultado = true;
            }
            cout << "Habitaciones Disponibles:" << endl;
            tHAVL.print();
            int habitacionElegida;

            do {
                cout << "Elija una habitación para el cliente " << tPCRB.obtenerElementoEnPosicion(num).getNombre() << " (1-" << tHAVL.getTamanio() << "): ";
                cin >> habitacionElegida;
            } while (habitacionElegida <= 0 || habitacionElegida > tHAVL.getTamanio());

            if (tHAVL.obtenerElementoEnPosicion(habitacionElegida).getReservado() == false) {
                cout << "\nLa habitación escogida ya se encuentra reservada...";
                system("pause");
                return;
            }

            double costoHabitacion = tHAVL.obtenerElementoEnPosicion(habitacionElegida).getCosto();
            if (tPCRB.obtenerElementoEnPosicion(num).getDineroClase().getMetodoDePago() == "Tarjeta") {
                costoHabitacion *= 1.1; // Aplicar una comisión del 5% para pagos con tarjeta
            }
            double diasHabitacion;
            do {
                cout << "\nIngrese la cantidad de días que ocupará la habitación: ";
                cin >> diasHabitacion;
            } while (diasHabitacion <= 0);

            costoHabitacion = (costoHabitacion + diasHabitacion * 5) - costoHabitacion * tPCRB.obtenerElementoEnPosicion(num).getDineroClase().getBono();
            if (tPCRB.esCompleto()||tPCRB.esBalnceadoNegro()) {
                cout << "\nFelicidades tiene una oferta, se le descuenta 100 dolares!!!";
                costoHabitacion = costoHabitacion - 100;
            }
            cout << "\nEste es el costo final de la habitación: $" << costoHabitacion << endl;

            char letra;
            do {
                cout << "\nDesea proseguir con el pago? (S/N): ";
                cin >> letra;
                letra = toupper(letra);
            } while (letra != 'S' && letra != 'N');

            if (tPCRB.obtenerElementoEnPosicion(num).getDinero() < costoHabitacion) {
                cout << "El cliente " << tPCRB.obtenerElementoEnPosicion(num).getNombre() << " no tiene suficiente dinero para pagar la habitación." << endl;
                system("pause");
                return;
            }
            else {
                tHAVL.actualizacionHabitaciones(habitacionElegida, diasHabitacion);
                tPCRB.actualizacionCliente(num, tHAVL.obtenerElementoEnPosicion(habitacionElegida), costoHabitacion);
            }
            cout << "\nLa habitación se ha reservado correctamente para el cliente " << tPCRB.obtenerElementoEnPosicion(num).getNombre() << "." << endl;
            cout << "\nEstos son los nuevos datos del cliente: " << tPCRB.obtenerElementoEnPosicion(num).getDatos();
            cout << "\n\n";
            cout << endl;
            system("pause");
        }
        else
            cout << "\nEl cliente elegido ya ocupa una habitacion...";
        system("pause");
    }

    void pClienteHabitacionAVL() {
        int num;
        system("CLS");
        cout << "Clientes Disponibles:" << endl;
        tCAVL.print();
        do {
            cout << "\nElija un cliente (1-" << NUMTOTAL << "): ";
            cin >> num;
        } while (num <= 0 || num > NUMTOTAL);
        cout << endl;
        cout << "\nUsted eligió el cliente en la posición: " << num << ": " << tCAVL.obtenerElementoEnPosicion(num).getDatos();
        int numHabitacionesOcupadas = 0;
        if (tCAVL.obtenerElementoEnPosicion(num).getReservado() != true) {

            for (int i = 1; i <= tHAVL.getTamanio(); i++) {
                if (tHAVL.obtenerElementoEnPosicion(i).getReservado() == true) {
                    numHabitacionesOcupadas++;
                }
            }
            if (numHabitacionesOcupadas == 0) {
                cout << "\nTodas las habitaciones están ocupadas. El programa se cerrará." << endl;
                //guardarClienteReservado(StackReservados);
                resultado = true;
            }
            cout << "Habitaciones Disponibles:" << endl;
            tHAVL.print();
            int habitacionElegida;

            do {
                cout << "Elija una habitación para el cliente " << tCAVL.obtenerElementoEnPosicion(num).getNombre() << " (1-" << tHAVL.getTamanio() << "): ";
                cin >> habitacionElegida;
            } while (habitacionElegida <= 0 || habitacionElegida > tHAVL.getTamanio());

            if (tHAVL.obtenerElementoEnPosicion(habitacionElegida).getReservado() == false) {
                cout << "\nLa habitación escogida ya se encuentra reservada...";
                system("pause");
                return;
            }

            double costoHabitacion = tHAVL.obtenerElementoEnPosicion(habitacionElegida).getCosto();
            if (tCAVL.obtenerElementoEnPosicion(num).getDineroClase().getMetodoDePago() == "Tarjeta") {
                costoHabitacion *= 1.1; // Aplicar una comisión del 5% para pagos con tarjeta
            }
            double diasHabitacion;
            do {
                cout << "\nIngrese la cantidad de días que ocupará la habitación: ";
                cin >> diasHabitacion;
            } while (diasHabitacion <= 0);

            costoHabitacion = (costoHabitacion + diasHabitacion * 5) - costoHabitacion * tCAVL.obtenerElementoEnPosicion(num).getDineroClase().getBono();
            cout << "\nEste es el costo final de la habitación: $" << costoHabitacion << endl;

            char letra;
            do {
                cout << "\nDesea proseguir con el pago? (S/N): ";
                cin >> letra;
                letra = toupper(letra);
            } while (letra != 'S' && letra != 'N');

            if (tCAVL.obtenerElementoEnPosicion(num).getDinero() < costoHabitacion) {
                cout << "El cliente " << tCAVL.obtenerElementoEnPosicion(num).getNombre() << " no tiene suficiente dinero para pagar la habitación." << endl;
                system("pause");
                return;
            }
            else {
                tHAVL.actualizacionHabitaciones(habitacionElegida, diasHabitacion);
                tCAVL.actualizacionCliente(num, tHAVL.obtenerElementoEnPosicion(habitacionElegida), costoHabitacion);
            }
            cout << "\nLa habitación se ha reservado correctamente para el cliente " << tCAVL.obtenerElementoEnPosicion(num).getNombre() << "." << endl;
            cout << "\nEstos son los nuevos datos del cliente: " << tCAVL.obtenerElementoEnPosicion(num).getDatos();

            hashReservados.insertarClienteReservado(to_string(tCAVL.obtenerElementoEnPosicion(num).getDinero()),
                new ClienteReservado(tCAVL.obtenerElementoEnPosicion(num).getNombre(), tCAVL.obtenerElementoEnPosicion(num).getDineroClase().getDatos(),
                    tCAVL.obtenerElementoEnPosicion(num).getInfoHabitaciones()));
            
            cout << "\n\n";
            cout << endl;
        }
        else
            cout << "\nEl cliente elegido ya ocupa una habitacion...";
        system("pause");
    }

    void verYBuscarCliente() {
        cout << "\nClientes Premium: ";
        tPCRB.print();
        cout << "\nBuscar por dinero de Cliente Premium: ";
        int num;
        cin >> num;
        auto start = chrono::high_resolution_clock::now();
        tPCRB.buscarClientePorDinero(num);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration<double, std::milli>(end - start).count();
        cout << "Tiempo de busqueda en el arbol RB: " << duration << " milisegundos" << std::endl;
        system("pause");
        cout << "\nClientes Básicos: ";
        tCAVL.print();
    }

    void verYBuscarHabitacion() {
        tHAVL.print();
        int costo;
        cout << "\nBuscar por costo de habitacion: ";
        cin >> costo;
        auto start = chrono::high_resolution_clock::now();
        tHAVL.buscarHabitacionPorCosto(costo);
        auto end = chrono::high_resolution_clock::now();
        double duration = chrono::duration<double, std::milli>(end - start).count();
        cout << "Tiempo de busqueda en el arbol AVL: " << duration << " milisegundos" << std::endl;
    }

    void encontrarAncestroParaEliminarse() {        
        int pos1, pos2;
        tPCRB.print();
        cout << "\nPonga posicion 1:"; cin >> pos1;
        cout << "\nPonga posicion 2:"; cin >> pos2;
        cout << "\nAncestro comun: " <<tPCRB.encontrarComun_Ancestro(tPCRB.obtenerElementoEnPosicion(pos1), tPCRB.obtenerElementoEnPosicion(pos2))->elemento.getDatos();
    }

    void imprimirClientesReservados() {
        hashReservados.imprimirClientesReservados();
    }
    void buscarClienteReservado(const string& clave) {
        ClienteReservado* cliente = hashReservados.buscarClienteReservado(clave);
        if (cliente != nullptr) {
            cout << "Datos Reservado: " << cliente->getDatos() << endl;       
        }
        else {
            cout << "Cliente reservado no encontrado." << endl;
        }
    }
	void menuPrincipal() {
        creacionesObjetos();
       
        do
        {
            cout << "\n\t\t\tBIENVENIDO AL MENÚ PRINCIPAL" << "\n\n";

            setlocale(LC_CTYPE, "Spanish");

            cout << "\tELIGE UNA OPCIÓN";
            cout << "\n1.Colocar un cliente en una habitación(AVL)";
            cout << "\n2.Colocar un cliente en una habitación(ArbolRB)";
            cout << "\n3.Ver habitaciones disponibles y buscarElemento";
            cout << "\n4.Ver clientes disponibles y buscarElemento";
            cout << "\n5.Ver clientes que ya reservaron habitaciones";
            cout << "\n6.Buscar en el hash ClientesReservado...";
            cout << "\n7.Ver a que cliente llego antes que ellos por igual (Ancestro Comun)";
            cout << "\n8.SALIR";

            cout << "\n\nElija opción: "; cin >> opcion;
            switch (opcion)
            {
            case 1:
                pClienteHabitacionAVL(); 
                system("pause");
                break;
            case 2:
                pClienteHabitacionRojoNegro();
                system("pause");
                break;
            case 3:
                verYBuscarHabitacion();
                system("pause");
                break;
            case 4:
                verYBuscarCliente();
                system("pause");
                break;
            case 5:
                imprimirClientesReservados();
                system("pause");
                break;
            case 6:
                int clave;
                imprimirClientesReservados();
                cout << "\nIngresar Clave del hash a buscar...: ";
                cin >> clave;
                buscarClienteReservado(to_string(clave));
                system("pause");
                break;
            case 7:
                encontrarAncestroParaEliminarse();
                system("pause");
                break;
            case 8:
                resultado = true;
                break;
            }
            system("CLS");
        } while (!resultado);
    }
};
