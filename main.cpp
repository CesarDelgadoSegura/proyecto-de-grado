#include <iostream>
#include <string>

using namespace std;

#include "cliente.h"
#include "cola.h"

#define MAX_COLAS      10
#define MAX_CLIENTES   100
#define MAX_CARACTERES 256

void opciones();

string Operaciones[4] = {"Retiro", "Deposito", "Transferencia", "Pago"};
string Destinarios[3] = {"Persona", "Banco", "Impuesto"};

Cliente clientes[MAX_CLIENTES];
Cola colas[MAX_COLAS];

bool cumpleElCriterio(int ClienteID, int ColaID)
{
	/** Criterio: EDAD */
	if(clientes[ClienteID].edad >= colas[ColaID].edad && colas[ColaID].edad)
	{
		return true;
	}
	
	/** Criterio: OPERACION */
	/** Se realiza la resta porque la operacion del cliente se almacena en 0 y el de la cola en 1 y para dar
	igual debe restar en el if (1 - 1 = 0) */
	if(clientes[ClienteID].operacion == (colas[ColaID].operacion - 1) && colas[ColaID].operacion)
	{
		return true;
	}
	
	/** Criterio: CLIENTE */
	bool esCliente = (colas[ColaID].cliente - 1) == 0 ? true: false;
	if(clientes[ClienteID].esCliente == esCliente && colas[ColaID].cliente)
	{
		return true;
	}
	
	return false;
}

void asignarColaAlCliente(int ClienteID)
{
	/** Verificar que el cliente está en espera. */
	if(clientes[ClienteID].atendido == false)
	{
		/** Por defecto le asignamos al sistema 0 ya que es la Cola principal y siempre debe haber una. */
		clientes[ClienteID].cola_id = 0;
		
		/** Asignar Una Cola al cliente */
		for(int i = 0; i < MAX_COLAS; i++)
		{
			if(cumpleElCriterio(ClienteID, i) == true)
			{
				clientes[ClienteID].cola_id = i;
			}
		}
	}
}

void opcionElegida(int opcion)
{
	switch(opcion)
	{
		case 1:
		{
			string eleccion = "s";
			
			for(int i = 0; i<MAX_CLIENTES; i++)
			{
				if(eleccion == "s")
				{
					if(!clientes[i].existe())
					{
						eleccion = "";
						
						char name[MAX_CARACTERES];
						cout << "Nombre y Apellido:\n";
						
						std::cin.ignore();
						std::cin.getline(name, sizeof(name));
						
						clientes[i].atendido = false;
						clientes[i].nombreCompleto = name;
						
						int age;
						cout << "\nEdad:\n";
						cin >> age;
						clientes[i].edad = age;
						
						int operation;
						cout << "\nTipo de Operacion (1: Retiro, 2: Deposito, 3: Transferencia, 4: Pago):\n";
						cin >> operation;
						clientes[i].operacion = (operation - 1);//Como en el texto el retiro es 1 y en la variable está en la posición 0 le restamos.
						
						int destinario;
						cout << "\nIngrese el Destinario (1: Persona, 2: Banco, 3: Impuesto):\n";
						cin >> destinario;
						clientes[i].destinario = (destinario - 1);//Como en el texto el retiro es 1 y en la variable está en la posición 0 le restamos.
						
						int client;
						cout << "\nEs Cliente? (1: Si, 2: No):\n";
						cin >> client;
						clientes[i].esCliente = ((client == 1) ? true: false);
						
						float monto;
						cout << "\nIngrese el Monto de la operacion (Ejemplo: 125.30):\n";
						cin >> monto;
						clientes[i].monto = monto;
						
						asignarColaAlCliente(i);
						
						cout << "¿Desea agregar otro Cliente? s para si o n para no:\n";
						cin >> eleccion;
						
						if(eleccion == "n")
						{
							break;
						}
					}
				}
			}
			break;
		}
		case 2:
		{
			int cola;
			
			for(int i = 0; i<MAX_COLAS; i++)
			{
				if(colas[i].existe())
				{
					/** Sumamos +1 Para que la cola general no sea Cero si no Uno. */
					cout << (i + 1) << ") " << colas[i].nombre << "\n";					
				}
			}
			
			cout << "\nIndique la cola que desea llamar(Ingresar numero): \n";
			cin >> cola;
			
			for(int i = 0; i<MAX_CLIENTES; i++)
			{
				/** Luego debemos restarlo para que si elige General sea. */
				if(clientes[i].existeEnLaCola(cola - 1) && clientes[i].existe() && !clientes[i].fueAtendido())
				{
					clientes[i].atendido = true;
					clientes[i].obtener();
					break;
				}
			}
			
			break;
		}
		case 3:/** Abrir nueva cola especial con criterio. */
		{
			int IDColaCreada = -1;
			
			for(int i = 0; i<MAX_COLAS; i++)
			{
				if(!colas[i].existe())
				{
					IDColaCreada = i;
					
					cout << "Nombre de la Cola: \n";
					
					char name[MAX_CARACTERES];
					cin.ignore();
					cin.getline(name, sizeof(name));
					
					colas[i].nombre = name;
					
					int age;
					cout << "Edad minima requerida (0 = Ignorar, 18 al 99): \n";
					cin >> age;
					colas[i].edad = age;
					
					if(colas[i].edad){
						cout << "\nLa cola fue creada exitosamente. \n\n\n";
						break; /** No necesitamos preguntarle otro criterio. */
					}
					
					int operacion;
					cout << "Edad minima requerida (0 = Ignorar, 1 = Retiro, 2 = Deposito, 3 = Transferencia, 4 = Pago): \n";
					cin >> operacion;
					colas[i].operacion = operacion;
					
					if(colas[i].operacion) {
						cout << "\nLa cola fue creada exitosamente. \n\n\n";
						break; /** No necesitamos preguntarle otro criterio. */
					}
					
					int cliente;
					cout << "Edad minima requerida (0 = Ignorar, 1 = Cliente, 2 = No Cliente): \n";
					cin >> cliente;
					colas[i].cliente = cliente;
					
					cout << "\nLa cola fue creada exitosamente. \n\n\n";
					break;
				}
			}
			
			/** Reubicar clientes de la cola común. */
			if(IDColaCreada >= 0)
			{
				for(int i = 0; i<MAX_COLAS; i++)
				{
					/** Comprobar existencia de cola. */
					if(colas[i].existe())
					{
						/** Comprobar que la cola sea la general. */
						if(colas[i].edad == 0 && colas[i].operacion == 0 && colas[i].cliente == 0)
						{
							/** Todos los clientes en la Cola General lo enviaremos a la nueva cola si cumples los criterios. */
							for(int cli = 0; cli<MAX_CLIENTES; cli++)
							{
								if(clientes[cli].cola_id == i)
								{
									if(cumpleElCriterio(cli, IDColaCreada) == true)
									{
										clientes[cli].cola_id = IDColaCreada;
									}
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			for(int a = 0; a<MAX_COLAS; a++)/** Iteración de la cola. */
			{
				if(colas[a].existe())
				{
					cout << colas[a].nombre << "\n\n";
					for(int b = 0; b<MAX_CLIENTES; b++)/** Iteración de los clientes dentro de esa cola. */
					{
						if(clientes[b].existeEnLaCola(a) && clientes[b].existe())
						{
							cout << "Numero de Llegada: " << (b + 1) << " | ";
							cout << "Nombre: " << clientes[b].nombreCompleto << " | ";
							cout << "Edad: " << clientes[b].edad << " | ";
							cout << "Monto: " << clientes[b].monto << " | ";
							cout << "Destinario: " << Destinarios[clientes[b].destinario] << " | ";
							cout << "Operacion: " << Operaciones[clientes[b].operacion] << " | ";
							cout << "Atendido: " << ((clientes[b].atendido == true) ? "Si": "No") << " | ";
							cout << "Cliente: " << ((clientes[b].esCliente == true) ? "Si": "No") << "\n\n";
							cout << "\n";
						}
					}
				}
			}
			break;
		}
		case 5:
		{
			for(int i = 0; i<MAX_COLAS; i++)
			{
				if(colas[i].existe())
				{
					cout << (i + 1) << ") Nombre: " << colas[i].nombre << "\n";
				}
			}
			
			int numero;
			cout << "Ingrese el Numero de Cola que desea eliminar: " << "\n";
			cin >> numero;
			
			bool estaVacia = true;
			numero = numero - 1;//Como arriba sumamos, aquí abajo restamos.
			if(numero >= 0 && numero < MAX_COLAS)// 14 <-- Error.
			{
				//1 Verificar que la cola esté vacia.
				for(int i = 0; i<MAX_CLIENTES; i++)
				{
					// Verificar que el cliente está en la cola y fue atendido.
					if(clientes[i].cola_id == numero && clientes[i].atendido == false)// Quiere decir que el cliente aun está en la cola.
					{
						estaVacia = false;
						break;
					}
				}
				
				if(estaVacia == false)//
				{
					cout << "No se pudo eliminar la Cola porque no esta vacia." << "\n\n\n";
				}
				else
				{
					colas[numero].nombre = "";
					colas[numero].edad = 0;
					
					cout << "Se elimino la Cola correctamente." << "\n\n\n";
				}
			}
			
			break;
		}
		case 6:
		{
			float fMin, fMax;
			
			cout << "Ingrese el Monto Minimo (Ejemplo: 140.23):\n";
			cin >> fMin;
			
			cout << "Ingrese el Monto Maximo (Ejemplo: 540.23):\n";
			cin >> fMax;
			
			float fPromedio = 0.0;
			int num = 0;
			cout << "\n\n";
			for(int i = 0; i < MAX_CLIENTES; i++)
			{
				if(clientes[i].monto >= fMin && clientes[i].monto <= fMax && clientes[i].atendido == true)
				{
					num++;/** <- Para calcular el promedio. */
					cout << "Numero de Llegada: " << (i + 1) << " | ";
					cout << "Nombre: " << clientes[i].nombreCompleto << " | ";
					cout << "Edad: " << clientes[i].edad << " | ";
					cout << "Monto: " << clientes[i].monto << " | ";
					cout << "Destinario: " << Destinarios[clientes[i].destinario] << " | ";
					cout << "Operacion: " << Operaciones[clientes[i].operacion] << " | ";
					cout << "Cliente: " << ((clientes[i].esCliente == true) ? "Si": "No") << "\n";
					/** Almacenamos las edades de los clientes atendidos. */
					fPromedio += clientes[i].edad;
				}
			}
			
			fPromedio = fPromedio / num;
			cout << "\n\nPromedio de Edad es de : " << fPromedio;
			
			cout << "\n\n\n";
			break;
		}
	}
	
	opciones();
}

void opciones()
{
	int opcion = 0;
	
	cout << "1) Mesa de entrada: Ingresa un nuevo cliente.\n";
	cout << "2) Atender proximo cliente.\n";
	cout << "3) Abrir nueva cola especial con criterio.\n";
	cout << "4) Ver Colas.\n";
	cout << "5) Cerrar cola especial.\n";
	cout << "6) Listar operaciones atendidas segun rango de montos.\n";
	cout << "\nSeleccione una opcion:\n";
	cin >> opcion;
	
	opcionElegida(opcion);
}

int main(int argc, char** argv) {
	/** Definir 1 cola por defecto ya que no hay denidas. */
	/** Como 0 es NO el valor que ingresen debe restarsele 1. para poder acceder a la variable 0. */
	/** Nombre | Edad | Operación | Es Cliente */
	colas[0].agregar("Cola General", 0, 0, 0);
	colas[1].agregar("Cola para mayores de +65", 65, 0, 0);
	colas[2].agregar("Cola por Operaciones.", 0, 2, 0);
	colas[3].agregar("Cola por Clientes.", 0, 0, 1);/** 1 = Solo clientes */
	
	/** Agregamos clientes por defecto. */
	/** Nombre | Edad | ID Cola | Destinario | Operacion | Es Cliente | Monto | Fue Atendido */
	clientes[0].agregar("Cesar Delgado", 85, 1, 1, 2, true, 485.43, false);
	clientes[1].agregar("Julian Delgado", 95, 1, 2, 1, true, 565.43, true);
	clientes[2].agregar("Pablo Delgado", 25, 0, 0, 3, false, 18743.43, false);
	clientes[3].agregar("Andres Delgado", 35, 0, 1, 0, false, 1275.43, true);
	
	opciones();
	
	return 0;
}

