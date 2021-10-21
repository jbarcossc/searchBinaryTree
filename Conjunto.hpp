
template <class T>
Conjunto<T>::Conjunto() {
    // Completar
    _long = 0;
    _raiz = NULL;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    removerSubarbol(this->_raiz);
}

template<class T>
void Conjunto<T>::removerSubarbol(Nodo* ptr){
    if (ptr == NULL){
        return;
    } else {
        removerSubarbol(ptr->der);
        removerSubarbol(ptr->izq);
        delete ptr;
        return;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    Nodo* nd = this->_raiz;
    while (nd != NULL && !res){
        if (nd->valor == clave){
            res = true;
        } else {
            if (nd->valor > clave){
                nd = nd->izq;
            } else {
                nd = nd->der;
            }
        }
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    Nodo* act = new Nodo(clave);
    act->der = NULL;
    act->izq = NULL;
        if (clave < this->_min) {
            this->_min = clave;
        }
        if (clave > this->_max) {
            this->_max = clave;
        }
        if (this->_raiz == NULL) {
            this->_raiz = act;
            this->_min = clave;
            this->_max = clave;
            this->_long++;
        } else {
            Nodo *nd = this->_raiz;
            bool lp = false;
            while (!lp) {
                if (act->valor < nd->valor) {
                    if (nd->izq == NULL) {
                        nd->izq = act;
                        lp = true;
                        this->_long++;
                    } else {
                        nd = nd->izq;
                    }
                } else if (act->valor > nd->valor) {
                    if (nd->der == NULL) {
                        nd->der = act;
                        lp = true;
                        this->_long++;
                    } else {
                        nd = nd->der;
                    }
                } else {
                    lp = true;
                }
            }
        }
    return;
}

template <class T>
void Conjunto<T>::remover(const T& v) {
    Nodo* padre = this->_raiz;
    Nodo* act = this->_raiz;
    bool lp = false;
    while (!lp){
        // Busco a v
        if (v < act->valor) {
            if (act->izq == NULL){
                lp = true;
            } else {
                padre = act;
                act = act->izq;
            }
        } else if (v > act->valor) {
            if (act->der == NULL){
                lp = true;
            } else {
                padre = act;
                act = act->der;
            }
        } else {
            // CASO 1: v es una hoja
            if (act->der == NULL && act->izq == NULL) {
                if (this->_raiz == act) {
                    this->_raiz = NULL;
                } else {
                    if (padre->der == act) {
                        padre->der = NULL;
                    } else {
                        padre->izq = NULL;
                    }
                }
                delete act;
            } else {
                // CASO 2: v es un nodo con un solo hijo
                if (act->der != NULL && act->izq == NULL) {
                    if (act == this->_raiz) {
                        this->_raiz = act->der;
                        delete act;
                    } else {
                        if (padre->der == act){
                            padre->der = act->der;
                        } else {
                            padre->izq = act->der;
                        }
                        delete act;
                    }
                } else {
                    if (act->izq != NULL && act->der == NULL) {
                        if (act == this->_raiz) {
                            this->_raiz = act->izq;
                            delete act;
                        } else {
                            if (padre->izq == act){
                                padre->izq = act->izq;
                            } else {
                                padre->der = act->izq;
                            }
                            delete act;
                        }
                    } else {

                        // CASO 3: v es un nodo con 2 hijos
                        // BUSCO PREDECESOR INMEDIATO
                        if (act->izq != NULL && act->der != NULL) {
                            Nodo* nuevo = act->izq;
                            Nodo* prev = act;
                            while (nuevo->der != NULL) {
                                prev = nuevo;
                                nuevo = nuevo->der;
                            }
                            if (act == this->_raiz){
                                this->_raiz = nuevo;
                            } else {
                                if (padre->der == act){
                                    padre->der = nuevo;
                                } else {
                                    padre->izq = nuevo;
                                }
                            }
                            if (nuevo == act->izq){
                                nuevo->der = act->der;
                            } else {
                                prev->der = nuevo->izq;
                                nuevo->der = act->der;
                                nuevo->izq = act->izq;
                            }
                            delete act;
                        }
                    }
                }
            }
            lp = true;
            this->_long--;
        }
    }
    if (this->_long == 0){
        this->_raiz = NULL;
    } else {
        if (v == this->_min) {
            Nodo *nuevoMin = this->_raiz;
            while (nuevoMin->izq != NULL) {
                nuevoMin = nuevoMin->izq;
            }
            this->_min = nuevoMin->valor;
        }
        if (v == this->_max) {
            Nodo *nuevoMax = this->_raiz;
            while (nuevoMax->der != NULL) {
                nuevoMax = nuevoMax->der;
            }
            this->_max = nuevoMax->valor;
        }
    }
    return;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* act = this->_raiz;
    Nodo* padre = this->_raiz;
    Nodo* res = new Nodo(clave);
    bool lp = false;
    while (!lp) {
        if (act->valor == clave){
            if (act->der != NULL){
                Nodo* suc = act->der;
                while (suc->izq != NULL){
                    suc = suc->izq;
                }
                res->valor = suc->valor;
            } else {
                res->valor = padre->valor;
            }
            lp = true;
        } else {
            padre = act;
            if (clave < act->valor){
                act = act->izq;
            } else {
                act = act->der;
            }
        }
    }
    return res->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return this->_min;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return this->_max;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_long;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}





