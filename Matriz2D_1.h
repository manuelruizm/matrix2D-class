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
// Declaración de la clase Matriz2D_1.
// (Incluye la sobrecarga de los operadores aritméticos, combinados y relacio-
// nales).
//
// Fichero: Matriz2D_1.h
//
//*****************************************************************************

#ifndef MATRIZ_2D_1
#define MATRIZ_2D_1

typedef int TipoBase;

//*****************************************************************************
//*****************************************************************************

class Matriz2D_1 
{

private:

	// Los datos se almacenan en filas independientes. Cada fila es 
	// accesible desde un vector de punteros (datos[0], datos[1], ...)
	// "datos" contiene la dirección de memoria del primer elemento 
	// del vector de punteros. Ese vector contiene "filas" casillas, 
	// y cada fila contiene "columnas" datos "int".
	 
	TipoBase ** datos;	// Datos. 
	int filas;		// Número de filas
	int columnas;	// Número de columnas

	// PRE: 0 <= filas
	// PRE: 0 <= columnas
	
public:

	//*************************************************************************
	// Constructor sin argumentos: crea una matriz vacía 
	Matriz2D_1(void);

	//*************************************************************************
	// Constructor de matrices cuadradas
	Matriz2D_1 (int orden);

	//*************************************************************************
	// Constructor de matrices rectangulares 
	Matriz2D_1 (int fils, int cols);

	//*************************************************************************
	// Constructor de copia
	Matriz2D_1 (const Matriz2D_1 & otro);

	//*************************************************************************
	// Destructor
	~Matriz2D_1 (void);

	//*************************************************************************
	// Rellena todas las casillas de la matriz con el valor "valor"
	void Inicializar (const TipoBase valor=0);
		
	//*************************************************************************
	// Consulta si la matriz esta vacía
	bool EstaVacia (void) const;

	//*************************************************************************
	// Consulta el número de filas y columnas
	int Filas (void) const;
	int Columnas (void) const;

	//*************************************************************************
	// Metodo de acceso individual a elementos: Operator ()
	// Metodo de escritura / lectura
	// PRE: 0 <= fila < filas
	// PRE: 0 <= columna < columnas
	TipoBase & operator () (const int fila, const int columna);
	TipoBase & operator () (const int fila, const int columna) const;

	//*************************************************************************
	// Operador de asignación 
	Matriz2D_1 & operator = (const Matriz2D_1 & otro);
	Matriz2D_1 & operator = (const TipoBase & valor);

	//*************************************************************************
	// Operadores unarios + y -
	// (+matriz) devuelve la matriz original
	// (-matriz) devuelve la matriz original con todos sus datos cambiados de
	// signo.
	Matriz2D_1 operator + (void);
	Matriz2D_1 operator - (void);

	//*************************************************************************
	// Operador binario +
	// Sobrecarga el operador +.
	// Realiza la operación matricial matemática de la suma
	// 1. m1 + m2
	// 2. m1 + un_valor
	// 3. un_valor + m1
	friend Matriz2D_1 operator + (const Matriz2D_1 & m1, 
									const Matriz2D_1 & m2);
	friend Matriz2D_1 operator + (const Matriz2D_1 & m1, 
									const TipoBase valor);
	friend Matriz2D_1 operator + (const TipoBase valor,
									const Matriz2D_1 & m1);

	//*************************************************************************
	// Operador binario -
	// Sobrecarga el operador -.
	// Realiza la operación matricial matemática de la resta
	// 1. m1 - m2
	// 2. m1 - un_valor
	// 3. un_valor - m1
	friend Matriz2D_1 operator - ( Matriz2D_1 & m1, Matriz2D_1 & m2);
	friend Matriz2D_1 operator - ( Matriz2D_1 & m1, const TipoBase valor);
	friend Matriz2D_1 operator - (const TipoBase valor, Matriz2D_1 & m1);
		
	//*************************************************************************
	// Operadores combinados += y -=
	// Sobrecarga de estos operadores.
	// En el caso: matriz1 += matriz2, equivale a matriz1 = matriz1 + matriz2.
	// En el caso: matriz1 += valor, equivale a matriz1 = matriz1 + valor.
	// En el caso: matriz1 -= matriz2, equivale a matriz1 = matriz1 - matriz2.
	// En el caso: matriz1 -= valor, equivale a matriz1 = matriz1 - valor.
	Matriz2D_1 & operator += (const Matriz2D_1 & otra);
	Matriz2D_1 & operator += (const TipoBase valor);
	Matriz2D_1 & operator -= ( Matriz2D_1 & otra);
	Matriz2D_1 & operator -= (const TipoBase valor);

	//*************************************************************************
	// Operadores relacionales == y !=
	// Se han sobrecargado estos operadores para poder establecer una razón 
	// de comparación entre dos objetos de tipo "Matriz2D_1". 
	bool operator == (const Matriz2D_1 & otra);
	bool operator != (const Matriz2D_1 & otra);

private:
		
	//*************************************************************************
	// Petición / liberación de memoria
	void ReservarMemoria (int filas, int columnas);
	void LiberarMemoria (void); 

	//*************************************************************************
       // Copiar datos desde otro objeto de la clase
	void CopiarDatos (const Matriz2D_1 & otro);
			
};


//*****************************************************************************
//*****************************************************************************
// Otras funciones no pertenecientes a la clase
//*****************************************************************************
//*****************************************************************************

// Muestra el contenido de una matriz 
void PintaMatriz (const Matriz2D_1 m, const char * const msg);


//*****************************************************************************
//*****************************************************************************
	
#endif

//*****************************************************************************
//*****************************************************************************
