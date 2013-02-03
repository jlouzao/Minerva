// Almacen.h: declaración de CAlmacen

#pragma once

// código generado el miércoles, 22 de junio de 2005, 15:35

class __declspec(dllexport) CAlmacen : public CRecordset
{
public:
	CAlmacen(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAlmacen)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ARTI;
	double	m_CANTI;
	double	m_CANTIENT;
	double	m_CANTISAL;
	CStringA	m_ALMACEN;
	CStringA	m_CAMPAN1;
	CStringA	m_CAMPAN2;
	CStringA	m_CAMPAN3;
	double	m_NDOC;
	CTime	m_FECHA;
	double	m_MOVEXI;
	double	m_MOVENT;
	double	m_MOVSAL;
	CStringA	m_TIPOMOV;
	CStringA	m_CUENTA;
	CStringA	m_OBSER;
	CStringA	m_CENTRO;
	double	m_COSART1;
	double	m_COSART2;
	double	m_COSART3;
	double	m_CLAVE;
	double	m_CANTITOTAL;
	double	m_CANTIDISPONIBLE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT DeleteMovientosAlbaran();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


