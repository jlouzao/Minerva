// ProveArti.h: declaración de CProveArti

#pragma once

// código generado el miércoles, 13 de julio de 2005, 15:38

class __declspec(dllexport) CProveArti : public CRecordset
{
public:
	CProveArti(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProveArti)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ARTI;
	CStringA	m_CUENTA;
	CStringA	m_SREF;
	CStringA	m_NOMPROVE;
	double	m_TARIFA;
	double	m_DESCUENTO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	CProveArti& operator =(CProveArti& Other);
	HRESULT Insert();
	HRESULT UpdateProveArti();
	HRESULT DeleteProveArti();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


