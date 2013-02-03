// Idiomas.h: declaración de CIdiomas

#pragma once

// código generado el miércoles, 22 de junio de 2005, 15:36

class __declspec(dllexport) CIdiomas : public CRecordset
{
public:
	CIdiomas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CIdiomas)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_IDIOMA;
	CStringA	m_DIDIOMA;
	CStringA	m_IDFAC;
	CStringA	m_IDLIT;
	CStringA	m_IDREP;
	CStringA	m_IDCLI;
	CStringA	m_IDCIF;
	CStringA	m_IDFEC;
	CStringA	m_IDSR;
	CStringA	m_IDPED;
	CStringA	m_IDALB;
	CStringA	m_IDCOD;
	CStringA	m_IDDES;
	CStringA	m_IDPIE;
	CStringA	m_IDCAJ;
	CStringA	m_IDPRE;
	CStringA	m_IDDTO;
	CStringA	m_IDIMP;
	CStringA	m_IDTOT;
	CStringA	m_IDDIS;
	CStringA	m_IDPEB;
	CStringA	m_IDPEN;
	CStringA	m_IDPAL;
	CStringA	m_IDFOR;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateIdioma();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


