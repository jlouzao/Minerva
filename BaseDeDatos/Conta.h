// Conta.h: declaración de CConta

#pragma once

// código generado el martes, 02 de agosto de 2005, 13:11

class  __declspec(dllexport) CConta : public CRecordset
{
public:
	CConta(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CConta)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPEDIDO;
	float	m_C_ASIENTO;
	float	m_C_REAL;
	CStringA	m_NUMALBA;
	CStringA	m_NUMALBB;
	CStringA	m_NUMALBC;
	CStringA	m_NUMALBD;
	CStringA	m_NUMALBE;
	CStringA	m_DNUMALBA;
	CStringA	m_DNUMALBB;
	CStringA	m_DNUMALBC;
	CStringA	m_DNUMALBD;
	CStringA	m_DNUMALBE;
	CStringA	m_NUMFACA;
	CStringA	m_NUMFACB;
	CStringA	m_NUMFACC;
	CStringA	m_NUMFACD;
	CStringA	m_NUMFACE;
	CStringA	m_DNUMFACA;
	CStringA	m_DNUMFACB;
	CStringA	m_DNUMFACC;
	CStringA	m_DNUMFACD;
	CStringA	m_DNUMFACE;
	CStringA	m_NPEDCOM;
	CStringA	m_NABONO;
	CStringA	m_NREMESA;
	CStringA	m_C1;
	CStringA	m_NIMPAGADO;
	CStringA	m_NDECLARADO;
	CStringA	m_NPAGO;
	CStringA	m_NFACCOM;
	CStringA	m_NFACCOMINV;
	CStringA	m_CARGO;
	CStringA	m_ABONO;
	CStringA	m_NTALON;
	CStringA	m_NENTREGA;
	CStringA	m_NUMOP;
	CStringA	m_NUM;
	CStringA	m_ORDEN;
	CStringA	m_NUMPROFOR;
	CStringA	m_EJERCICIO;
	CStringA	m_DEJER;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT GetNextNumProfor(CString &strNextNumProfor);
	HRESULT GetNextNumPedidoVenta(CString &strNextNumPedidoVenta);
	HRESULT GetNextNumPedidoCompra(CString &strNextNumPedidoCompra);
	HRESULT GetNextNumAlbaran(CString &strNextNumAlbaran);
	HRESULT GetNextNumAlbCompra(CString &strNextNumAlbCompra);
	HRESULT GetNextNumFacturaA(CString &strNextNumFactura);
	HRESULT GetNextNumFacturaB(CString &strNextNumFactura);

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


