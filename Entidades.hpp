#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class ClienteReservado
{
    string nombre;
    string dineroDatos;
    string infoHabitaciones;
public:
    ClienteReservado(string n, string dD, string info) :nombre(n), dineroDatos(dD), infoHabitaciones(info) {};
    ClienteReservado() {};

    string getDatos() {
        return nombre + "  " + dineroDatos + " ----- " + infoHabitaciones;
    }
};

class dineroClientes {
    short dineroDisponible;
    string tipoMoneda = "$";
    string metodoDePago;
    double bonoDescuento;
    string estado; // Agregamos una variable de estado individual

public:
    dineroClientes() {
        dineroDisponible = rand() % 1000 + 300;
        short valor = rand() % 2;
        string metodoDePagoTemp;
        estado = "Disponible";
        short random = rand() % 2;
        switch (random) {
        case 0:
            metodoDePagoTemp = "Tarjeta";
            break;
        case 1:
            metodoDePagoTemp = "Efectivo";
            break;
        }
        metodoDePago = metodoDePagoTemp;
        bonoDescuento = random * 0.05;
    }

    void setEstado(string _estado) {
        estado = _estado;
    }

    void setCantidad(int _cantidad) {
        dineroDisponible = dineroDisponible + _cantidad;
    }
    void setCantidadNormal(int _cantidad) {
        dineroDisponible = _cantidad;
    }
    double getBono() {
        return bonoDescuento;
    }
    string getEstado() {
        return estado;
    }

    short getDinero() {
        return dineroDisponible;
    }

    void setOperacionResta(short _costo) {
        dineroDisponible = dineroDisponible - _costo;
    }
    string getMetodoDePago() {
        return metodoDePago;
    }
    string getDatos() {
        if (bonoDescuento == 0)
            return tipoMoneda + to_string(dineroDisponible) + " MetodoPago: " + metodoDePago + " EstadoDinero: " + estado + " Bono: " + "0%";
        else
            return tipoMoneda + to_string(dineroDisponible) + " MetodoPago: " + metodoDePago + " EstadoDinero: " + estado + " Bono: " + "5%";
    };
};

class ClientePadre {
protected:
    string nombre;
    dineroClientes dinero;
    string infoHabitaciones;
    bool ReservoCorrecto = false;
public:
    ClientePadre(string n) :nombre(n) {}
    ClientePadre() {
        dinero = dineroClientes();
    }

    short getDinero() { return dinero.getDinero(); }
    dineroClientes getDineroClase() {
        return dinero;
    }
    string getNombre() {
        return nombre;
    }
    bool getReservado() {
        return ReservoCorrecto;
    }
    string getInfoHabitaciones() {
        return infoHabitaciones;
    }
    void setInfoHabitaciones(string _info) {
        infoHabitaciones = _info;
    }
    void setReserVoCorrecto(bool _valor) {
        ReservoCorrecto = _valor;
    }
    void setResta(short _valor) {
        dinero.setOperacionResta(_valor);
    }
    void setEstado(string estado) {
        dinero.setEstado(estado);
    }
  
    string getDatos() {
        if (ReservoCorrecto == false)
            return nombre + "  " + dinero.getDatos();
        else
            return nombre + "  " + dinero.getDatos() + " ----- " + infoHabitaciones;
    }
};

class ClienteBasico :public ClientePadre{
public:
    ClienteBasico(string n){
        nombre = "Basico: "+n;
    }
    ClienteBasico(){
    }
    void setRestaBasic(int _valor) {
        dinero.setOperacionResta(_valor);
    }
    void setReservoBasic(bool _valor) {
        ReservoCorrecto = _valor;
    }

};

class ClientePremium :public ClientePadre {
public:
  
    ClientePremium(string n) {
        nombre = "Premium: " + n;
        dinero.setCantidad(1000);
    }
    ClientePremium(int _n) {
        dinero.setCantidadNormal(_n);
    }
    ClientePremium() {
    }
    
};

class Habitaciones {
    short costo;
    short camas;
    short ubicacion;
    short dias = 0;
    bool reservadoCorrecto = true;

public:
  
    Habitaciones() {
        ubicacion = rand() % 5 + 1;
        camas = rand() % 3 + 1;
        costo = ((rand() % 6 + 3) * 100) + camas * 5;
    }
  
    short getCosto() {
        return costo;
    }
    short getUbicacion() {
        return ubicacion;
    }

    bool getReservado() {
        return reservadoCorrecto;
    }
    void setReservado(bool _valor) {
        reservadoCorrecto = _valor;
  }
    void setDias(short _dias) {
        dias = _dias;
    }
    void setCosto(int _costo) {
        costo = _costo;
    }
    string getDatos() {
        if (getReservado() == true)
            return "Piso: " + to_string(ubicacion) + "    Camas: " + to_string(camas) + "    Precio: $" + to_string(costo) + "    Días: " + "0" + " Disponible";
        else
            return "Piso: " + to_string(ubicacion) + "    Camas: " + to_string(camas) + "    Precio: $" + to_string(costo) + "    Días: " + to_string(dias) + " Ocupado";

    }
};