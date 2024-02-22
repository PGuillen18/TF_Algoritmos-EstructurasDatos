#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <vector>

using namespace std;
#define NUMTOTAL 40

template<class T>
class NodoArbol {
public:
    T elemento;
    NodoArbol* izq;
    NodoArbol* der;
    int altura;

    NodoArbol() {
        izq = nullptr;
        der = nullptr;
        altura = 0;
    }
};

template<class T>
class ArbolAVL {
private:
    NodoArbol<T>* raiz;
    void(*procesar)(T); // puntero a función
    short(*criterio)(T, T);

    // Operaciones privadas
    int _altura(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return -1;
        return nodo->altura;
    }

    void _rotarDerecha(NodoArbol<T>*& nodo) {
        NodoArbol<T>* p = nodo->izq;
        nodo->izq = p->der;
        p->der = nodo;
        actualizaAltura(nodo);
        nodo = p;
        actualizaAltura(nodo);
    }

    void _rotarIzquierda(NodoArbol<T>*& nodo) {
        NodoArbol<T>* p = nodo->der;
        nodo->der = p->izq;
        p->izq = nodo;
        actualizaAltura(nodo);
        nodo = p;
        actualizaAltura(nodo);
    }

    void actualizaAltura(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            int hizq = _altura(nodo->izq);
            int hder = _altura(nodo->der);
            nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
        }
    }

    void _balanceo(NodoArbol<T>*& nodo) {
        int hizq = _altura(nodo->izq);
        int hder = _altura(nodo->der);
        int fb = hder - hizq;

        if (fb > 1) {
            int hhizq = _altura(nodo->der->izq);
            int hhder = _altura(nodo->der->der);
            if (hhizq > hhder) {
                _rotarDerecha(nodo->der);
            }
            _rotarIzquierda(nodo);
        }
        else if (fb < -1) {
            int hhizq = _altura(nodo->izq->izq);
            int hhder = _altura(nodo->izq->der);
            if (hhizq < hhder) {
                _rotarIzquierda(nodo->izq);
            }
            _rotarDerecha(nodo);
        }
        else {
            actualizaAltura(nodo);
        }
    }

    bool _insertar(NodoArbol<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new NodoArbol<T>();
            nodo->elemento = e;
            return true;
        }
        else if (criterio(e, nodo->elemento) == 0)
            return _insertar(nodo->der, e);
        else if (criterio(e, nodo->elemento) < 0) {
            return _insertar(nodo->izq, e);
        }
        else if (criterio(e, nodo->elemento) > 0) {
            return _insertar(nodo->der, e);
        }
        _balanceo(nodo);
        return true;
    }

    void _inOrden(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return;
        _inOrden(nodo->izq);
        procesar(nodo->elemento);
        _inOrden(nodo->der);
    }

    T _getElementoEnPosicionINOrden(NodoArbol<T>* nodo, int& contador, int posicion) {
        if (nodo == nullptr) return T();
        T resultado = _getElementoEnPosicionINOrden(nodo->izq, contador, posicion);
        contador++;
        if (contador == posicion) return nodo->elemento;
        if (contador > posicion) return resultado;
        return _getElementoEnPosicionINOrden(nodo->der, contador, posicion);
    }

 

    NodoArbol<T>* _actualizarElementoEnPosicion(NodoArbol<T>* nodo, int& contador, int posicionObjetivo, T elemento) {
        if (nodo == nullptr) return nullptr;

        nodo->izq = _actualizarElementoEnPosicion(nodo->izq, contador, posicionObjetivo, elemento);
        contador++;

        if (contador == posicionObjetivo) {
            nodo->elemento = elemento;
        }

        nodo->der = _actualizarElementoEnPosicion(nodo->der, contador, posicionObjetivo, elemento);

        actualizaAltura(nodo);
        _balanceo(nodo);
        return nodo;
    }
    
    bool _BuscarAVL(NodoArbol<T>* nodo, T elemento, short (*comparador)(T, T)) {
        if (nodo == nullptr)
            return false;

        if (comparador(nodo->elemento, elemento) == 0)
            return true;
        else if (comparador(nodo->elemento, elemento) < 0)
            return _BuscarAVL(nodo->der, elemento, comparador);
        else
            return _BuscarAVL(nodo->izq, elemento, comparador);
    }
    int getTamanio(NodoArbol<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        int tamanioIzq = getTamanio(nodo->izq);
        int tamanioDer = getTamanio(nodo->der);
        return 1 + tamanioIzq + tamanioDer;
    }

public:
    ArbolAVL(void(*nuevaFuncion)(T), short(*criterio)(T, T)) {
        this->procesar = nuevaFuncion;
        this->raiz = nullptr;
        this->criterio = criterio;
    }

    bool Insertar(T e) {
        return _insertar(raiz, e);
    }

    void inOrden() {
        _inOrden(raiz);
    }
    T getElementoEnPosicion(int posicion) {
        int contador = 0;
        return _getElementoEnPosicionINOrden(raiz, contador, posicion);
    }

    void actualizarElementoEnPosicion(int posicion, T elemento) {
        int contador = 0;
        raiz = _actualizarElementoEnPosicion(raiz, contador, posicion, elemento);
    }

    bool Eliminar(T elemento) {
        int tamanioAntes = getTamanio();
        raiz = _eliminar(raiz, elemento);
        int tamanioDespues = getTamanio();
        return (tamanioDespues < tamanioAntes);
    }

    int getTamanio() {
        return getTamanio(raiz);
    }
    bool BuscarAVL(T elemento, short (*comparador)(T, T)) {
        return _BuscarAVL(raiz, elemento,comparador);
    }

};


//ARBOL ROJO Y NEGRO ACÁ PARA COMPARACION

template<class T>
class NodoRB {
public:
    T elemento;
    NodoRB<T>* izq;
    NodoRB<T>* der;
    bool esRojo;

    NodoRB() {
        izq = nullptr;
        der = nullptr;
        esRojo = true;
    }
};

template<class T>
class ArbolRB {
private:
    NodoRB<T>* raiz;
    void (*procesar)(T); 
    short (*criterio)(T, T);

   
    int _altura(NodoRB<T>* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + max(_altura(nodo->izq), _altura(nodo->der));
    }

    void _rotarDerecha(NodoRB<T>*& nodo) {
        NodoRB<T>* p = nodo->izq;
        nodo->izq = p->der;
        p->der = nodo;
        nodo = p;
    }

    bool esCompletoAux(NodoRB<T>* nodo, int nivel, int altura) {
        if (nodo == nullptr) {
            return true;
        }

        if (nodo->izq == nullptr && nodo->der == nullptr) {
            return nivel == altura - 1;
        }

        if (nodo->izq != nullptr && nodo->der != nullptr) {
            return esCompletoAux(nodo->izq, nivel + 1, altura) && esCompletoAux(nodo->der, nivel + 1, altura);
        }

        return false;
    }

    void _rotarIzquierda(NodoRB<T>*& nodo) {
        NodoRB<T>* p = nodo->der;
        nodo->der = p->izq;
        p->izq = nodo;
        nodo = p;
    }

    void _balanceo(NodoRB<T>*& nodo) {
        if (nodo == nullptr) return;

        if (nodo->der != nullptr && nodo->der->esRojo && (nodo->izq == nullptr || !nodo->izq->esRojo)) {
            _rotarIzquierda(nodo);
        }
        else if (nodo->izq != nullptr && nodo->izq->esRojo && nodo->izq->izq != nullptr && nodo->izq->izq->esRojo) {
            _rotarDerecha(nodo);
        }
        else if (nodo->izq != nullptr && nodo->izq->esRojo && nodo->der != nullptr && nodo->der->esRojo) {
            nodo->esRojo = true;
            nodo->izq->esRojo = false;
            nodo->der->esRojo = false;
        }
    }
  
    void _inOrden(NodoRB<T>* nodo) {
        if (nodo == nullptr) return;
        _inOrden(nodo->izq);
        procesar(nodo->elemento);
        _inOrden(nodo->der);
    }

    T _getElementoEnPosicion(NodoRB<T>* nodo, int& contador, int posicion) {
        if (nodo == nullptr) return T();
        T resultado = _getElementoEnPosicion(nodo->izq, contador, posicion);
        contador++;
        if (contador == posicion) return nodo->elemento;
        if (contador > posicion) return resultado;
        return _getElementoEnPosicion(nodo->der, contador, posicion);
    }


    int _BuscarRB(NodoRB<T>* nodo, T elemento, int& contador) {
        if (nodo == nullptr || criterio(elemento, nodo->elemento) == 0) {
            return contador;
        }

        if (criterio(elemento, nodo->elemento) < 0) {
            return _BuscarRB(nodo->izq, elemento, contador);
        }
        contador += 1 + getTamanio(nodo->izq);
        return _BuscarRB(nodo->der, elemento, contador);
    }


    NodoRB<T>* encontrarSucesor(NodoRB<T>* nodo) {
        while (nodo->izq != nullptr) {
            nodo = nodo->izq;
        }
        return nodo;
    }

    NodoRB<T>* _actualizarElementoEnPosicion(NodoRB<T>* nodo, int& contador, int posicionObjetivo, T elemento) {
        if (nodo == nullptr) return nullptr;

        nodo->izq = _actualizarElementoEnPosicion(nodo->izq, contador, posicionObjetivo, elemento);
        contador++;

        if (contador == posicionObjetivo) {
            nodo->elemento = elemento;
        }

        nodo->der = _actualizarElementoEnPosicion(nodo->der, contador, posicionObjetivo, elemento);

        return nodo;
    }

    int getTamanio(NodoRB<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + getTamanio(nodo->izq) + getTamanio(nodo->der);
    }

    bool _insertar(NodoRB<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new NodoRB<T>();
            nodo->elemento = e;
            return true;
        }
        else if (criterio(e, nodo->elemento) == 0)
            return _insertar(nodo->der, e);
        else if (criterio(e, nodo->elemento) < 0) {
            return _insertar(nodo->izq, e);
        }
        else if (criterio(e, nodo->elemento) > 0) {
            return _insertar(nodo->der, e);
        }
        return false;
    }

    NodoRB<T>* _encontrarAncestroComun(NodoRB<T>* nodo, T elemento1, T elemento2) {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (criterio(elemento1, nodo->elemento) < 0 && criterio(elemento2, nodo->elemento) < 0) {
            return _encontrarAncestroComun(nodo->izq, elemento1, elemento2);
        }
        else if (criterio(elemento1, nodo->elemento) > 0 && criterio(elemento2, nodo->elemento) > 0) {
            return _encontrarAncestroComun(nodo->der, elemento1, elemento2);
        }
        else {
            return nodo;
        }
    } 
    int _esBalanceadoAlturaNegra(NodoRB<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        int alturaIzq = _esBalanceadoAlturaNegra(nodo->izq);
        int alturaDer = _esBalanceadoAlturaNegra(nodo->der);
        if (alturaIzq == -1 || alturaDer == -1) {
            return -1;
        }

        if (alturaIzq != alturaDer) {
            return -1;
        }

        int alturaNegra = alturaIzq + (!nodo->esRojo ? 1 : 0);

        return alturaNegra;
    }

public:
    ArbolRB(void (*nuevaFuncion)(T), short (*criterio)(T, T)) {
        this->procesar = nuevaFuncion;
        this->raiz = nullptr;
        this->criterio = criterio;
    } 
    int obtenerPosicion(T elemento) {
        return obtenerPosicionAux(raiz, elemento, getTamanio(raiz->izq));
    }
    bool esBalanceadoAlturaNegra() {
        return _esBalanceadoAlturaNegra(raiz) != -1;
    }
    bool Insertar(T e) {
        if (_insertar(raiz, e)) {
            raiz->esRojo = false;
            return true;
        }
        return false;
    }

    void inOrden() {
        _inOrden(raiz);
    }
    NodoRB<T>* encontrarAncestroComun(T elemento1, T elemento2) {
        return _encontrarAncestroComun(raiz, elemento1, elemento2);
    }
    T getElementoEnPosicion(int posicion) {
        int contador = 0;
        return _getElementoEnPosicion(raiz, contador, posicion);
    }

    void actualizarElementoEnPosicion(int posicion, T elemento) {
        int contador = 0;
        raiz = _actualizarElementoEnPosicion(raiz, contador, posicion, elemento);
    }

    int getTamanio() {
        return getTamanio(raiz);
    }

    int BuscarRB(T elemento) {
        int contador = 1;
        return _BuscarRB(raiz, elemento, contador);
    }

    bool esCompleto() {
        int altura = _altura(raiz);
        return esCompletoAux(raiz, 0, altura);
    }
};


//HASHTABLE
template <typename K, typename V>
class HashEntidad {
private:
    K key;
    V value;

public:
    HashEntidad(const K& key, const V& value) {
        this->key = key;
        this->value = value;
    }

    K getKey() const { return key; }
    V getValue() const { return value; }
};

template <typename K, typename V>
class HashTable {
private:
    static const int TABLE_SIZE = NUMTOTAL+NUMTOTAL;
    vector<vector<HashEntidad<K, V>>> table;

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

 //Hash Function de Bernstein
    /*int hashFunction(const string& key) {
        int hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + static_cast<uint32_t>(c);
        }
        return hash % TABLE_SIZE;
    }
    */

 //Mixing Hash Function 
    /*int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash ^= c + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash % TABLE_SIZE;
    }
    */
   
 //Jenkin's Hash Function 

    int hashFunction(const std::string& key) {
        int hash = 0;   
        for (char c : key) {
            hash += static_cast<uint32_t>(c);
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return hash % TABLE_SIZE;
    }
        
    void insert(const HashEntidad<K, V>& element) {
        int index = hashFunction(element.getKey());
        table[index].push_back(element);
    }

    const HashEntidad<K, V>* search(const K& key) {
        int index = hashFunction(key);
        vector<HashEntidad<K, V>>& bucket = table[index];
        for (const auto& element : bucket) {
            if (element.getKey() == key) {
                return &element;
            }
        }
        return nullptr;
    }

    void remove(const K& key) {
        int index = hashFunction(key);
        vector<HashEntidad<K, V>>& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getKey() == key) {
                bucket.erase(it);
                return;
            }
        }
    }

    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Tabla " << i + 1 << ": ";
            vector<HashEntidad<K, V>>& bucket = table[i];
            if (bucket.empty()) {
                cout << "vacio" << endl;
            }
            else {
                cout << '"';
                for (int j = 0; j < bucket.size(); j++) {
                    cout << bucket[j].getKey() << "\",\"" << bucket[j].getValue() << '"';
                    if (j < bucket.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << " respectivo" << endl;
            }
        }
    }
};
