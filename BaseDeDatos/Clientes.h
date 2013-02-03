// Clientes.h: declaración de CClientes

#pragma once

// código generado el lunes, 11 de julio de 2005, 16:00

class __declspec(dllexport) CClientes : public CRecordset
{
public:
	CClientes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClientes)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CIF;
	CStringA	m_CUENTA;
	CStringA	m_NOMBRE;
	double	m_PP;
	double	m_DCTOS;
	CStringA	m_NOMFICHA;
	CStringA	m_DIRECCION;
	CStringA	m_POBLACION;
	CStringA	m_PROVINCIA;
	CStringA	m_CP;
	CStringA	m_TELEFONO;
	CStringA	m_FAX;
	CStringA	m_IVA;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_DIVAC;
	double	m_MFVAC;
	double	m_DFVAC;
	double	m_MIVAC;
	CStringA	m_AGE;
	CStringA	m_NOMBCO;
	CStringA	m_DIRBCO;
	CStringA	m_POBCO;
	CStringA	m_CTACORR;
	CStringA	m_DIR1;
	CStringA	m_POB1;
	CStringA	m_CP1;
	CStringA	m_PROV1;
	CStringA	m_DIR2;
	CStringA	m_POB2;
	CStringA	m_CP2;
	CStringA	m_PROV2;
	CStringA	m_CONTACTO;
	CStringA	m_CARGO;
	CStringA	m_TEL2;
	CStringA	m_REPRE;
	CStringA	m_REPRE2;
	double	m_DCTOS2;
	double	m_DCTOS3;
	CStringA	m_OBSER1;
	CStringA	m_OBSER2;
	CStringA	m_OBSER3;
	double	m_RIACCLI;
	double	m_RIESCLI;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_IDIOMA;
	CStringA	m_DIVISA;
	CStringA	m_TRANSPOR;
	CStringA	m_MATRICULA;
	CStringA	m_DNI;
	CStringA	m_TELTRAN;
	CStringA	m_TARIFA;
	CStringA	m_ZONA;
	double	m_COPFAC;
	CStringA	m_CPAIS;
	CStringA	m_PAIS;
	CStringA	m_IVAIDEN;
	CStringA	m_SEGURO;
	double	m_AABONAR;
	CStringA	m_ABOPFAC;
	CStringA	m_NUMCOMPA;
	double	m_NUMEXP;
	CStringA	m_SG;
	CStringA	m_DIRHACIEN;
	CStringA	m_NUMERO;
	CStringA	m_CTRCTA;
	CStringA	m_DC;
	CStringA	m_CC1;
	CStringA	m_CC2;
	CStringA	m_CC3;
	CStringA	m_CPBCO;
	CStringA	m_TIPO;
	CStringA	m_CAMCLI;
	CStringA	m_GRUFAC;
	CStringA	m_EMAIL;
	CStringA	m_CTRANS;
	double	m_DCTOS4;
	double	m_ERIESCLI;
	double	m_ERIACCLI;
	double	m_IVACLIENTE;
	CStringA	m_NOMFAC;
	CStringA	m_DIREFAC;
	CStringA	m_SGFAC;
	CStringA	m_NUMEFAC;
	CStringA	m_CPFAC;
	CStringA	m_POBFAC;
	CStringA	m_PROVFAC;
	CStringA	m_CPAISFAC;
	CStringA	m_DPAISFAC;
	CTime	m_FECHALTA;
	CTime	m_FECHBAJA;
	long	m_BLOQUEOCLI;
	CStringA	m_OBSCOBCLI;
	double	m_PORRETE;
	CStringA	m_CTARETE;
	CStringA	m_RETFISCAL;
	CStringA	m_RETCOMER;
	CStringA	m_IBAN;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateClientes();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


