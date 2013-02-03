// AlbCompra.h: declaración de CAlbCompra

#pragma once

// código generado el miércoles, 31 de agosto de 2005, 12:17

class __declspec(dllexport) CAlbCompra : public CRecordset
{
public:
	CAlbCompra(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAlbCompra)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NALBCOM;
	CString m_NPEDCOM;
	CTime	m_FECHALB;
	CStringA	m_CUENTA;
	CStringA	m_ALMACEN;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_SREF;
	CStringA	m_OBSALB;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_EXPORTA;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	CStringA	m_CENTRO;
	double	m_DCTO2;
	double	m_DCTO3;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateAlbCompra();
	HRESULT DeleteAlbCompra();
// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


