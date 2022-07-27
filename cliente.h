class Cliente {
	/** Atributos de la Clase Cliente. */
	public:
	string nombreCompleto;
	int edad;
	int operacion;
	int destinario;
	float monto;
	bool esCliente;
	bool atendido;
	int cola_id;
	
	/** Metodos de la clase Cliente. */
	public:
	void agregar(string sNombre, int iEdad, int iCola, int iDestinario, int iOperacion, bool bCliente, float fMonto, bool bAtendido)
	{
		atendido = false;
		cola_id = iCola;
		nombreCompleto = sNombre;
		edad = iEdad;
		destinario = iDestinario;
		operacion = iOperacion;
		esCliente = bCliente;
		monto = fMonto;
		atendido = bAtendido;
	}
	
	bool existe() 
	{
		return nombreCompleto.size() > 0 ? true: false;	
	}
	
	void obtener() 
	{
		cout << "Nombre: " << nombreCompleto << " | ";
		cout << "Edad: " << edad << " | ";
		cout << "Atendido: " << ((atendido == true) ? "Si": "No") << " | ";
		cout << "Cliente: " << ((esCliente == true) ? "Si": "No") << "\n\n";
	}
	
	bool existeEnLaCola(int ColaId) 
	{
		return (cola_id == ColaId) ? true: false;
	}
	
	bool fueAtendido()
	{
		return atendido;
	}
};

