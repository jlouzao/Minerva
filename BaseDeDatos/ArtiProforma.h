// ArtiProforma.h: declaraci�n de CArtiProforma

#pragma once

// c�digo generado el martes, 26 de julio de 2005, 9:31

class _declspec(dllexport) CArtiProforma : public CRecordset
{
public:
	CArtiProforma(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiProforma)

// Datos de campo o par�metro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizar� las conversiones necesarias.
// (Nota: la versi�n de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPROFOR;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double      m_PESO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	double	m_CANTI;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente gener� reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexi�n predeterminada

	virtual CString GetDefaultSQL(); 	// c�digo SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiProforma();
	HRESULT DeleteArtiProforma();


// Implementaci�n
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


