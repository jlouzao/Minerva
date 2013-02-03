// Prove.h: declaración de CProve

#pragma once

// código generado el viernes, 08 de julio de 2005, 10:07

class __declspec(dllexport) CProve : public CRecordset
{
public:
	CProve(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProve)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CIF;
	CStringA	m_CUENTA;
	CStringA	m_NOMBRE;
	double	m_PP;
	double	m_DCTOS;
	CStringA	m_NOMFICHA;
	CStringA	m_DIRECCION;
	CStringA	m_POBLACION;
	CStringA	m_PROVINCIA;
	CStringA	m_CP;
	CStringA	m_TELEFONO;
	CStringA	m_FAX;
	CStringA	m_IVA;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_POBCO;
	CStringA	m_NOMBCO;
	CStringA	m_AGE;
	CStringA	m_DIRBCO;
	CStringA	m_RETENCION;
	CStringA	m_CONTACTO;
	CStringA	m_CARGO;
	CStringA	m_TEL2;
	double	m_COMISION;
	CStringA	m_OBSER1;
	CStringA	m_OBSER2;
	CStringA	m_OBSER3;
	CStringA	m_IDIOMA;
	CStringA	m_DIVISA;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	CStringA	m_IVAIDEN;
	double	m_AABONAR;
	double	m_DIVAC;
	double	m_MIVAC;
	double	m_DFVAC;
	double	m_MFVAC;
	CStringA	m_SG;
	CStringA	m_DIRHACIEN;
	CStringA	m_NUMERO;
	CStringA	m_CTACORR;
	CStringA	m_DC;
	CStringA	m_CC1;
	CStringA	m_CC2;
	CStringA	m_CC3;
	CStringA	m_CPBCO;
	CStringA	m_CPAIS;
	CStringA	m_TIPO;
	CStringA	m_EMAIL;
	double	m_DCTO2;
	double	m_DCTO3;
	CStringA	m_CTABANCO;
	CStringA	m_CAMPROVE1;
	CStringA	m_CAMPROVE2;
	double	m_PLAZOENT;
	CTime	m_FECHALTA;
	CTime	m_FECHBAJA;
	double	m_PORRETE;
	CStringA	m_CTARETE;
	CStringA	m_CTACOM;
	CStringA	m_IBAN;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	CProve& operator =(CProve& Other);

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateProve();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


