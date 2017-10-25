//*****************************************************************************
//
// METODOLOGÍA DE LA PROGRAMACIÓN
// Grado en Ingeniería Informática
//
// Curso 2014-2015
// 1º Grupo C(2)
//
// Manuel Ruiz Maldonado
//
//*****************************************************************************
//
// RELACIÓN DE PROBLEMAS 4
// EJERCICIO 2
//
// Implementación de la clase Matriz2D_1.
// (Incluye la sobrecarga de los operadores aritméticos, combinados y relacio-
// nales).
//
// Fichero: Matriz2D_1.cpp
//
//*****************************************************************************

#include <iostream>
#include <cstring>

#include "Matriz2D_1.h"
	
using namespace std;

//*****************************************************************************
// Constructor sin argumentos: crea una matriz vacia
Matriz2D_1 :: Matriz2D_1(void)       
		: filas(0), columnas(0), datos(0) 
{ }

//*****************************************************************************
// Constructor de matrices cuadradas
Matriz2D_1 :: Matriz2D_1 (int orden)	
		: filas(orden), columnas(orden) 
{
	ReservarMemoria(filas, columnas);
}

//*****************************************************************************
// Constructor de matrices rectangulares
Matriz2D_1 :: Matriz2D_1 (int filitas, int columnitas) 
		: filas(filitas), columnas(columnitas) 
{
	ReservarMemoria(filas, columnas);
}

//*****************************************************************************
// Constructor de copia
Matriz2D_1 :: Matriz2D_1 (const Matriz2D_1 & otro)
{
	// Reserva de memoria para los valores de la matriz
	ReservarMemoria (otro.filas, otro.columnas);

	// Copia el contenido de la matriz y los campos privados
	CopiarDatos(otro);
}	
		
//*****************************************************************************
// Destructor
Matriz2D_1 :: ~Matriz2D_1 (void)
{
	LiberarMemoria ();				
}

//*****************************************************************************
// Rellena todas las casillas de la matriz con el valor "valor"
void Matriz2D_1 :: Inicializar (const int valor)
{
	for(int i = 0; i < filas; i++)
		for(int j = 0; j < columnas; j++)
			datos[i][j] = valor;	
}
	
//*****************************************************************************
// Consulta si la matriz esta vacia
bool Matriz2D_1 :: EstaVacia (void) const
{
	return (datos == 0);
}

//*****************************************************************************
// Consulta el número de filas
int Matriz2D_1 :: Filas (void) const
{		
	return (filas);
}

//*****************************************************************************
// Consulta el número de columnas
int Matriz2D_1 :: Columnas (void) const
{
	return (columnas);
}

//*****************************************************************************
// Metodo de acceso individual a elementos: operator []
// Metodo de escritura / lectura
// PRE: 0 <= posicion < usados 
TipoBase & Matriz2D_1 :: operator () (const int fila, 
								      const int columna)
{
	return (datos[fila][columna]);
}
TipoBase & Matriz2D_1 :: operator () (const int fila, 
									  const int columna) const
{
	return (datos[fila][columna]);
}

//*****************************************************************************
// Operador de asignación desde otro dato Matriz2D_1
Matriz2D_1 & Matriz2D_1 :: operator = (const Matriz2D_1 & otro)
{
    if (this != &otro) { // Evitar autoasignación

        // Libera la memoria ocupada
        LiberarMemoria();

        // Reserva de memoria para los valores de la matriz
        ReservarMemoria (otro.filas, otro.columnas);

        // Copia el contenido de la matriz y los campos privados
        CopiarDatos(otro);
    }
    return (*this);  // Objeto implicito: parte
                     // izquierda de la asignación
}
	
//*****************************************************************************
// Operador de asignación desde otro dato TipoBase
Matriz2D_1 & Matriz2D_1 :: operator = (const TipoBase & valor)
{
	// Escribir "valor" en todas las casillas 
    Inicializar(valor);
 
    return (*this);  // Objeto implicito: parte
                     // izquierda de la asignación
}

//*****************************************************************************
// Operador unario +
// (+matriz) devuelve la matriz original
Matriz2D_1 Matriz2D_1 :: operator + (void)
{
	return (*this);
}

//*****************************************************************************
// Operador unario -
// (-matriz) devuelve la matriz original con todos sus datos cambiados de signo
Matriz2D_1 Matriz2D_1 :: operator - (void)
{
	// Matriz local, para el resultado
	Matriz2D_1 tmp = (*this);
	
	for (int f = 0; f < filas; f++)
	{
		for (int c = 0; c < columnas; c++)
		{
			tmp(f, c) = -(tmp(f, c)); // Cambio de signo
		}
	}
	return (tmp);
}

//*****************************************************************************
// Operador binario +
// Sobrecarga el operador +.
// Realiza la operación matricial matemática de la suma
// 1. m1 + m2
// 2. m1 + un_valor
// 3. un_valor + m1

// CASO 1
Matriz2D_1 operator + (const Matriz2D_1 & m1, const Matriz2D_1 & m2)
{
	Matriz2D_1 tmp; // Constructor sin argumentos -> matriz vacía

	if ((m1.Filas() == m2.Filas()) && (m1.Columnas() == m2.Columnas()) 
		&& (!(m1.EstaVacia()))) 
	// Para poder realizar la suma el número de filas y columnas entre las dos
	// matrices debe de ser igual
	{
		tmp = m1;
		int filas = tmp.Filas();
		int columnas = tmp.Columnas();

		for (int f = 0; f < filas; f++)
		{
			for (int c = 0; c < columnas; c++)
			{
				tmp(f, c) += m2(f, c); // Operación combinada entre "int"
			}
		}
	} // Si no se puede hacer la suma, "tmp" se mantiene vacía

	return (tmp);
}

// CASO 2
Matriz2D_1 operator + (const Matriz2D_1 & m1, const TipoBase valor)
{
	// Creo una matriz con las mismas filas y columnas que m1.
	Matriz2D_1 m2(m1.Filas(), m1.Columnas());

	// La inicializo con el valor "valor".
	m2.Inicializar(valor);

	// Devuelvo la suma de matrices previamente definida.
	return (m1+m2);
}

// CASO 3
Matriz2D_1 operator + (const TipoBase valor, const Matriz2D_1 & m1)
{
	// Aplico la asociatividad de la suma de matrices.
	return (m1+valor);
}

//*****************************************************************************
// Operador binario -
// Sobrecarga el operador -.
// Realiza la operación matricial matemática de la resta
// 1. m1 - m2
// 2. m1 - un_valor
// 3. un_valor - m1

// CASO 1
Matriz2D_1 operator - ( Matriz2D_1 & m1,  Matriz2D_1 & m2)
{
	return (m1+(-m2));
}

// CASO 2
Matriz2D_1 operator - ( Matriz2D_1 & m1, const TipoBase valor)
{
	// Crea una matriz a partir de un valor
	Matriz2D_1 m2(m1.Filas(), m1.Columnas());
	m2.Inicializar(valor);

	return (m1-m2);
}

Matriz2D_1 operator - (const TipoBase valor,  Matriz2D_1 & m1)
{
	// Crea una matriz a partir de un valor
	Matriz2D_1 m2(m1.Filas(), m1.Columnas());
	m2.Inicializar(valor);

	return (m2-m1);
}

//*****************************************************************************
// Operador combinado +=

// En el caso: matriz1 += matriz2, equivale a matriz1 = matriz1 + matriz2.
Matriz2D_1 & Matriz2D_1 :: operator += (const Matriz2D_1 & otra)
{
	(*this) = (*this) + otra;
	return (*this);
}

// En el caso: matriz1 += valor, equivale a matriz1 = matriz1 + valor.
Matriz2D_1 & Matriz2D_1 :: operator += (const TipoBase valor)
{
	(*this) = (*this) + valor;
	return (*this);
}

//*****************************************************************************
// Operador combinado -=

// En el caso: matriz1 -= matriz2, equivale a matriz1 = matriz1 - matriz2.
Matriz2D_1 & Matriz2D_1 :: operator -= ( Matriz2D_1 & otra)
{
	(*this) = (*this) - otra;
	return (*this);
}

// En el caso: matriz1 -= valor, equivale a matriz1 = matriz1 - valor.
Matriz2D_1 & Matriz2D_1 :: operator -= (const TipoBase valor)
{
	(*this) = (*this) - valor;
	return (*this);
}	

//*****************************************************************************
// Operador ==
bool Matriz2D_1 :: operator == (const Matriz2D_1 & otra)
{
	int filas_este = filas;
	int columnas_este = columnas;
	int filas_otra = otra.Filas();
	int columnas_otra = otra.Columnas();

	// Dos matrices son iguales si tienen el mismo número de filas y columnas... 
	bool iguales = ((filas_este == filas_otra) && (columnas_este == columnas_otra));

	int f=0, c=0;
	while (iguales && (f < filas_este) && (c < columnas_este))
	{
		if ((*this)(f,c) != otra(f,c)) // ... y si el contenido de cada 
			iguales = false;		   // posición es idéntico.

		f++;
		c++;
	}

	return (iguales);
}

//*****************************************************************************
// Operador !=
// "matriz1 != matriz2", si, y solo si, "!(matriz1 == matriz2)"
// Es decir, son distintas si no son iguales.
bool Matriz2D_1 :: operator != (const Matriz2D_1 & otra)
{
	return (! ((*this) == otra));
}

//*****************************************************************************
// Pide memoria para la estructura de datos
void Matriz2D_1 :: ReservarMemoria (int fils, int cols)
{
	// Reservar para el vector de punteros
	datos = new int * [fils];

	// Reservar para cada fila
	for(int i = 0; i < fils; i++)
		datos[i] = new int[cols];
}

//*****************************************************************************
// Liberar memoria
void Matriz2D_1 :: LiberarMemoria (void)
{
	if (datos) {

		for (int i = 0; i < filas; i++)
			// Libera cada fila
			delete [] datos[i]; 

		// Libera el vector de punteros
		delete [] datos; 
		
		datos = 0;
	}
}

//*****************************************************************************
// Copiar datos desde otro objeto de la clase
// PRE: Se ha reservado memoria para los datos
void Matriz2D_1 :: CopiarDatos (const Matriz2D_1 & otro)
{
	// Copiar datos privados
	filas = otro.filas;
	columnas = otro.columnas;

	// Copiar los valores de cada una de las filas
	for (int f=0; f<filas; f++)
		memcpy (datos[f], otro.datos[f], columnas*sizeof(int));
}


//*****************************************************************************
//*****************************************************************************
// Otras funciones no pertenecientes a la clase
//*****************************************************************************
//*****************************************************************************
    
//*****************************************************************************
// Muestra el contenido de una matriz, precedido del mensaje "msg"
void PintaMatriz (const Matriz2D_1 m, const char * const msg)
{
	cout << endl; 
	cout << msg << endl;
	
	for (int f=0; f<m.Filas(); f++) {
		
		for (int c=0; c<m.Columnas(); c++)
			cout << m (f,c) << " "; // Prueba del operador de acceso () 
									// para lectura
		cout << endl;
	}
	cout << endl;
}
	
//*****************************************************************************
//*****************************************************************************
