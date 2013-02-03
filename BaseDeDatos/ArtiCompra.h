// ArtiCompra.h: declaración de CArtiCompra

#pragma once

// código generado el miércoles, 10 de agosto de 2005, 13:26

class  __declspec(dllexport) CArtiCompra : public CRecordset
{
public:
	CArtiCompra(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiCompra)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NPEDCOM;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double	    m_CANTI;
	double	    m_RECIBIDOS;
	double   	m_IMPOARTI;
	double	    m_DTOARTI;
	double	    m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiCompra();
	HRESULT DeleteArtiCompra();
	HRESULT UpdateRecibidos();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


