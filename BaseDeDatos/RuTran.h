// RuTran.h: declaraci�n de CRuTran

#pragma once

// c�digo generado el lunes, 11 de julio de 2005, 15:19

class __declspec(dllexport) CRuTran : public CRecordset
{
public:
	CRuTran(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRuTran)

// Datos de campo o par�metro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizar� las conversiones necesarias.
// (Nota: la versi�n de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CRUTRAN;
	CStringA	m_DRUTRAN;
	CStringA	m_MATRICULA;
	CStringA	m_MODELO;
	double	m_TARA;
	double	m_PESOMAXIMO;

// Reemplazos
	// El asistente gener� reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexi�n predeterminada

	virtual CString GetDefaultSQL(); 	// c�digo SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateRutran();

// Implementaci�n
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


