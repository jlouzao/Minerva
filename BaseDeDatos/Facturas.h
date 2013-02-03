// Facturas.h: declaraci�n de CFacturas

#pragma once

// c�digo generado el lunes, 19 de septiembre de 2005, 15:23

class __declspec(dllexport) CFacturas : public CRecordset
{
public:
	CFacturas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFacturas)

// Datos de campo o par�metro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizar� las conversiones necesarias.
// (Nota: la versi�n de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMFAC;
	CStringA	m_NUMALB;
	CStringA	m_NUMPEDIDO;
	CStringA	m_TIPO;
	CTime	m_FECHFAC;
	CTime	m_FECHALB;
	CTime	m_FECHPED;
	CStringA	m_CUENTA;
	CStringA	m_REPRE;
	CStringA	m_SUBREP;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_SREF;
	CStringA	m_OBSFAC;
	double	m_DCTOS;
	double	m_PP;
	double	m_IVA;
	CStringA	m_TARIFA;
	double	m_COMISION;
	double	m_COMISION2;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	CStringA	m_CENTRO;
	CStringA	m_GRUFAC;
	double	m_DCTOS2;
	double	m_DCTOS3;
	CStringA	m_TELEF1;
	CStringA	m_TELEF2;
	CStringA	m_ATENCLI;
	double	m_RETENCOM;
	double	m_RETENFIS;

// Reemplazos
	// El asistente gener� reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexi�n predeterminada

	virtual CString GetDefaultSQL(); 	// c�digo SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateFactura();

// Implementaci�n
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


