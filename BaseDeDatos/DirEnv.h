// DirEnv.h: declaración de CDirEnv

#pragma once

// código generado el viernes, 08 de julio de 2005, 10:17

class __declspec(dllexport) CDirEnv : public CRecordset
{
public:
	CDirEnv(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDirEnv)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CLIENTE;
	CStringA	m_DIRENV;
	CStringA	m_DDIRENV;
	CStringA	m_POBL;
	CStringA	m_CP;
	CStringA	m_PROV;
	CStringA	m_CONTACTO;
	CStringA	m_TELEFONO;
	double	m_DISTANCIA;
	CStringA	m_DIVISA;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_DIVAC;
	double	m_DFVAC;
	double	m_MIVAC;
	double	m_MFVAC;
	CStringA	m_NUMCOMPA;
	CStringA	m_SEGURO;
	double	m_RIESCLI;
	double	m_ERIESCLI;
	double	m_RIACCLI;
	double	m_ERIACCLI;
	CStringA	m_CC1;
	CStringA	m_CC2;
	CStringA	m_DC;
	CStringA	m_CTACORR;
	CStringA	m_NOMBCO;
	CStringA	m_AGE;
	CStringA	m_DIRBCO;
	CStringA	m_CPBCO;
	CStringA	m_POBCO;
	CStringA	m_TARIFA;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_CTRCTA;
	CStringA	m_GRUFAC;
	double	m_COPFAC;
	double	m_ABFAC;
	double	m_AABONAR;
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
	double	m_TIEMPOTRAN;
	double	m_TIEMPOOBRA;
	CStringA	m_ESTAOBRA;
	CStringA	m_ZONA;
	CStringA	m_NOMDIRENV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	CTime	m_FECFINOBRA;
	CStringA	m_OBRACERRA;
	CStringA	m_FINOBRA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateDirEnv();
	HRESULT DeleteDirEnv();
	HRESULT UpdateCierreObra();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


