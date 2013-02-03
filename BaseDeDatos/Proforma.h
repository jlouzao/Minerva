// Proforma.h: declaración de CProforma

#pragma once

// código generado el lunes, 01 de agosto de 2005, 12:07

class __declspec(dllexport) CProforma : public CRecordset
{
public:
	CProforma(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProforma)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPROFOR;
	CStringA	m_NUMPEDIDO;
	CStringA	m_NUMALB;
	CTime	m_FECHPROF;
	CTime	m_FECHPRE;
	CTime	m_FECHALB;
	CTime	m_FECHFAC;
	CTime	m_FECHENT;
	CStringA	m_CUENTA;
	CStringA	m_REPRE;
	CStringA	m_SUBREP;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_DIRFAC;
	CStringA	m_SREF;
	CStringA	m_OBSPROF;
	CStringA	m_OBSALB;
	CStringA	m_OBSDENEGA;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_DIVISA;
	CStringA	m_IDIOMA;
	CStringA	m_PUERTO;
	CStringA	m_TIPO;
	CStringA	m_PARTIDA;
	CStringA	m_TRANS;
	CStringA	m_MERCAN;
	CStringA	m_EXPORTA;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CAM1;
	CStringA	m_CAM2;
	CStringA	m_CAM3;
	double	m_CANTI;
	CStringA	m_UNIDAD;
	CStringA	m_TARIFA;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_COMARTI;
	double	m_IVARTI;
	//CStringA	m_IVA;
	double	m_IVA;
	double	m_CANTIFAC;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_TRANSPOR;
	CStringA	m_DNI;
	CStringA	m_MATRICULA;
	CStringA	m_BULTOS;
	BOOL	m_MUESTRAS;
	double	m_CAMBIO;
	CStringA	m_INCOTERM;
	CStringA	m_EMBALAJE;
	CStringA	m_CONTAINERS;
	double	m_CAJAS;
	CStringA	m_PORTES;
	double	m_PESNETO;
	double	m_PESBRUTO;
	CStringA	m_CERTIF;
	CStringA	m_COMER;
	CStringA	m_ADUAN;
	CStringA	m_ESTADO;
	BOOL	m_SUPFAC;
	float	m_IMPABO;
	CStringA	m_LCACE;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_TOTALPAL;
	double	m_CANTRANS;
	CStringA	m_TRANSEMP;
	double	m_FLETES;
	CStringA	m_CENTRO;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_IMPODIVI;
	double	m_RECARGO;
	CStringA	m_CAMVEN;
	CStringA	m_GRUFAC;
	CStringA	m_RUTRAN;
	double	m_SUPLEM;
	CStringA	m_DSUPLEM;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS4;
	CStringA	m_CAMCVEN;
	double	m_CAMNVEN;
	double	m_EUROS;
	double	m_DTOARTI2;
	double	m_DTOARTI3;
	CStringA	m_DESARMEMO;
	CStringA	m_NOMCONTA;
	CStringA	m_CIFCONTA;
	CStringA	m_DIRCONTA;
	CStringA	m_POBCONTA;
	CStringA	m_PROVCONTA;
	CStringA	m_CPCONTA;
	CStringA	m_TELEF1;
	CStringA	m_TELEF2;
	double	m_IMPORI;
	CStringA	m_CONTRATO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	CStringA	m_OBSERV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	double	m_DIASFAC;
	CStringA	m_PREPMATE;
	CTime	m_FECALB2;
	CStringA	m_MARCA;
	double	m_DIASOLD;
	BOOL	m_PREFAC;
	CTime	m_FECPREF;
	double	m_IMPOPREF;
	double	m_DIAFACPREF;
	BOOL	m_MODIPREF;
	BOOL	m_LINPTEPRE;
	double	m_EIMPOPREF;
	CStringA	m_ATENCLI;
	CStringA	m_CCOMPET;
	CTime	m_FECHCADU;
	double	m_CLAVE;
	double	m_RETENCOM;
	double	m_RETENFIS;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateProforma();
	HRESULT UpdateEstadoProforma();
	HRESULT UpdateObsDenegaProforma();
	HRESULT UpdateNumPedido();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


