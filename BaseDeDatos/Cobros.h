// Cobros.h: declaración de CCobros

#pragma once

// código generado el jueves, 03 de noviembre de 2005, 9:51

class  __declspec(dllexport) CCobros : public CRecordset
{
public:
	CCobros(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCobros)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_FCOBRO;
	CStringA	m_NUMFAC;
	CTime	m_FECHA;
	double	m_IMPORTE;
	CStringA	m_CUENTA;
	double	m_GASTOS;
	CStringA	m_NREMESA;
	CStringA	m_ESTADREM;
	CStringA	m_ESTADO;
	CStringA	m_BANCO;
	CTime	m_FECHLIBRA;
	CTime	m_FECHDOC;
	CStringA	m_REPRE;
	CStringA	m_NUMEFEC;
	CTime	m_FESTADO;
	CTime	m_FRECEP;
	CStringA	m_CENTRO;
	double	m_CAMBIO;
	double	m_IMPODIVI;
	double	m_TIPOREM;
	CStringA	m_CLICON;
	CStringA	m_OBSCOBRO;
	BOOL	m_EMITIDO;
	CTime	m_FECHCONTA;
	double	m_EUROS;
	BOOL	m_VENCIDO;
	double	m_EGASTOS;
	double	m_NPAGARE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateCobros();
	HRESULT UpdateImporteCobro();
	HRESULT DeleteCobros();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


