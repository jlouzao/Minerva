// Subfami.h: declaraci�n de CSubfami

#pragma once

// c�digo generado el mi�rcoles, 15 de junio de 2005, 15:57

class __declspec(dllexport) CSubfami : public CRecordset
{
public:
	CSubfami(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubfami)

// Datos de campo o par�metro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizar� las conversiones necesarias.
// (Nota: la versi�n de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CSUBFAM;
	CStringA	m_DSUBFAM;
	CStringA	m_ARTI;
	CStringA	m_CFAMILIA;
	double	m_DTOVSFAM;
	double	m_DTOCSFAM;

// Reemplazos
	// El asistente gener� reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexi�n predeterminada

	virtual CString GetDefaultSQL(); 	// c�digo SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX
	HRESULT UpdateRegistro();
	HRESULT Insert();

// Implementaci�n
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


