// Articulo.h: declaración de CArticulo

#pragma once

// código generado el miércoles, 15 de junio de 2005, 9:31

class __declspec(dllexport) CArticulo : public CRecordset
{
public:
	CArticulo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArticulo)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CODALT;
	double	m_TARI1;
	double	m_TARI2;
	double	m_IVARTI;
	double	m_DTOARTI;
	CStringA	m_PA;
	CStringA	m_CODFAM;
	CStringA	m_CODSEC;
	CStringA	m_PROVE;
	CStringA	m_MARCA;
	CStringA	m_OBSER;
	double	m_TIPO;
	double	m_PESO;
	CStringA	m_UNI;
	double	m_COSLIFO;
	double	m_COSFIFO;
	double	m_COSPMC;
	double	m_COMISI;
	double	m_COMIPTS;
	CStringA	m_FABRI;
	CTime	m_FECHATA1;
	CTime	m_FECHATA2;
	double	m_COSMCOM;
	CTime	m_FECHAMPC;
	CStringA	m_NUMFACMPC;
	CStringA	m_CALIA1;
	CStringA	m_CALIA2;
	CStringA	m_CALIA3;
	CStringA	m_CALIA4;
	CStringA	m_CALIA5;
	double	m_TARIA2;
	double	m_TARIA3;
	double	m_TARIA4;
	double	m_TARIA5;
	double	m_NUMCAJAS;
	double	m_METCAJAS;
	double	m_METPALET;
	CStringA	m_CALIB1;
	CStringA	m_CALIB2;
	CStringA	m_CALIB3;
	CStringA	m_CALIB4;
	CStringA	m_CALIB5;
	double	m_TARIB1;
	double	m_TARIB2;
	double	m_TARIB3;
	double	m_TARIB4;
	double	m_TARIB5;
	CStringA	m_CALIC1;
	CStringA	m_CALIC2;
	CStringA	m_CALIC3;
	CStringA	m_CALIC4;
	CStringA	m_CALIC5;
	double	m_TARIC1;
	double	m_TARIC2;
	double	m_TARIC3;
	double	m_TARIC4;
	double	m_TARIC5;
	double  m_TARVEN;
	CStringA	m_CUENTA;
	double	m_DTOARCO;
	double	m_STKMIN;
	double	m_CANTREP;
	CStringA	m_PROVE1;
	CStringA	m_PROVE2;
	CStringA	m_PROVE3;
	CTime	m_FECHAA;
	CTime	m_FECHAB;
	CTime	m_FECHAC;
	double	m_TARI2A;
	double	m_TARI2B;
	double	m_TARI2C;
	double	m_DTOARTA;
	double	m_DTOARTB;
	double	m_DTOARTC;
	CStringA	m_NOMPRO1;
	CStringA	m_NOMPRO2;
	CStringA	m_NOMPRO3;
	CStringA	m_DESARTI1;
	double	m_PZMETRO;
	CStringA	m_CTAVTA;
	double	m_SUPLEM;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_RECARGO;
	CTime	m_FECALTA;
	CTime	m_FECBAJA;
	CStringA	m_UBIX;
	CStringA	m_UBIY;
	CStringA	m_UBIZ;
	CStringA	m_ARTCAR10;
	CStringA	m_ART1CAR;
	double	m_ARTNUMER;
	CStringA	m_DSUPLEM;
	double	m_ARTNUME2;
	double	m_ARTNUME3;
	double	m_ARTNUME4;
	CStringA	m_PROPOR;
	CStringA	m_ALQUILER;
	CTime	m_FECALQ;
	CTime	m_FECFIN;
	CStringA	m_CONTRATO;
	CStringA	m_TIPOALQ;
	CTime	m_ULTIFACT;
	CStringA	m_CLIENTE;
	CStringA	m_NUMALB;
	CStringA	m_ALQUIDES1;
	CStringA	m_ALQUIDES2;
	CStringA	m_ALQUIDES3;
	CStringA	m_ALQUIDES4;
	CStringA	m_ALQUIDES5;
	double	m_ALQUINUM1;
	double	m_ALQUINUM2;
	double	m_ALQUINUM3;
	double	m_ALQUINUM4;
	double	m_ALQUINUM5;
	double	m_APLICADA;
	double	m_DTOAPLI;
	CStringA	m_MOVALM;
	long	m_GENERICO;
	CStringA	m_PROPOROL;
	double	m_EAPLICADA;
	double	m_EALQUINUM1;
	double	m_EALQUINUM2;
	double	m_EALQUINUM3;
	double	m_EALQUINUM4;
	double	m_EALQUINUM5;
	CStringA	m_CODPROV;
	CStringA	m_DESPROV;
	CStringA	m_DESARTIOLD;
	CStringA	m_CTAALQ;
	CStringA	m_ALQUILADO;
	double	m_ETARI1;
	double	m_ETARIB1;
	double	m_ETARIC1;
	CStringA	m_CFAMI;
	CStringA	m_FORMATO;
	CStringA	m_SERIE;
	CStringA	m_PASTA;
	double	m_ETARI2;
	double	m_ECOSLIFO;
	double	m_ECOSFIFO;
	double	m_ECOSPMC;
	double	m_BLOQUEO;
	CStringA	m_DESARMEMO;
	CStringA	m_CSUBFAM;
	double	m_DTOTAR1;
	double	m_DTOTARB1;
	double	m_DTOTARC1;
	double	m_PTOVERDE;
	double	m_ETARID1;
	double	m_ETARIE1;
	double	m_ETARIF1;
	double	m_ETARIG1;
	double	m_ETARIH1;
	double	m_ETARII1;
	double	m_DTOTARD1;
	double	m_DTOTARE1;
	double	m_DTOTARF1;
	double	m_DTOTARG1;
	double	m_DTOTARH1;
	double	m_DTOTARI1;
	double	m_TARID5;
	double	m_TARIE5;
	double	m_TARIF5;
	double	m_TARIG5;
	double	m_TARIH5;
	double	m_TARII5;
	double	m_TARIJ5;
	double	m_DTOARTD;
	double	m_DTOARTE;
	double	m_DTOARTF;
	double	m_DTOARTG;
	double	m_DTOARTH;
	double	m_DTOARTII;
	double	m_DTOARTJ;
	CStringA	m_PROVE4;
	CStringA	m_PROVE5;
	CStringA	m_PROVE6;
	CStringA	m_PROVE7;
	CStringA	m_PROVE8;
	CStringA	m_PROVE9;
	CStringA	m_PROVE10;
	CStringA	m_UA;
	CStringA	m_APLIDCTOS;
	CStringA	m_APLIDCTOS2;
	CStringA	m_APLIDCTOS3;
	CStringA	m_APLIDCTOS4;
	CStringA	m_APLIPP;
	double	m_EUROSUV;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	CArticulo& operator =(CArticulo& Other);

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX
	HRESULT Insert();
	HRESULT UpdateRegistro();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


};


