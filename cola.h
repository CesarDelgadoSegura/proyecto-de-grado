class Cola {
	public:
	string nombre;	
	int edad;
	int operacion;
	int cliente;
	
	public:
	void agregar(string iNombre, int iEdad, int iOperacion, int iCliente)
	{
		nombre = iNombre;
		edad = iEdad;
		operacion = iOperacion;
		cliente = iCliente;
	}
	
	public:
	void obtener() 
	{
		cout << "Nombre: " << nombre << " | ";
		cout << "Criterio por edad: " << ((edad == 0) ? "No": "Si") << " Habilitado | ";
		cout << "Criterio por Operacion: " << ((operacion == 0) ? "No": "Si") << " Habilitado | ";
		cout << "Criterio por Si es Cliente: " << ((cliente == 0) ? "No": "Si") << " Habilitado | ";
		cout << "\n\n";
	}
	
	bool existe()
	{
		return nombre.size() ? true: false;
	}
};

