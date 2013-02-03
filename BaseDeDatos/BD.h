// BaseDeDatos.h: archivo de encabezado principal del archivo DLL de BaseDeDatos
//

#pragma once

#ifndef __AFXWIN_H__
	#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// Símbolos principales


// CBaseDeDatosApp
// Consultar BaseDeDatos.cpp para realizar la implementación de esta clase
//

class CBaseDeDatosApp : public CWinApp
{
public:
	CBaseDeDatosApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
// Empresas.h: declaración de CEmpresas

#pragma once

// código generado el jueves, 02 de junio de 2005, 11:32

class __declspec(dllexport) CEmpresas : public CRecordset
{
public:
	CEmpresas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmpresas)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ID;
	CStringA	m_DESCRIPCION;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Ejercicios.h: declaración de CEjercicios

#pragma once

// código generado el jueves, 02 de junio de 2005, 11:37

class __declspec(dllexport) CEjercicios : public CRecordset
{
public:
	CEjercicios(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEjercicios)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	long	m_ID;
	CStringA	m_DESCRIPCION;
	CStringA	m_IDEMPR;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Usuario.h: declaración de CUsuario

#pragma once

// código generado el lunes, 06 de junio de 2005, 13:52

class __declspec(dllexport) CUsuario : public CRecordset
{
public:
	CUsuario(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUsuario)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_USUARIO;
	CStringA	m_PASSWORD;
	long	    m_IDPERFIL;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX
	HRESULT Insert();
	HRESULT DeleteFromUser();
	HRESULT UpdatePassword();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Perfiles.h: declaración de CPerfiles

#pragma once

// código generado el miércoles, 08 de junio de 2005, 15:37

class __declspec(dllexport) CPerfiles : public CRecordset
{
public:
	CPerfiles(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPerfiles)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	long	m_ID;
	CStringA	m_DESCRIPCION;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Familias.h: declaración de CFamilias

#pragma once

// código generado el miércoles, 15 de junio de 2005, 15:02

class __declspec(dllexport) CFamilias : public CRecordset
{
public:
	CFamilias(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFamilias)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CFAMILIA;
	CStringA	m_DFAMILIA;
	CStringA	m_ARTI;
	double	m_CLAVE;
	double	m_DTOVFAM;
	double	m_DTOCFAM;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX
	HRESULT UpdateRegistro();
	HRESULT Insert();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Subfami.h: declaración de CSubfami

#pragma once

// código generado el miércoles, 15 de junio de 2005, 15:57

class __declspec(dllexport) CSubfami : public CRecordset
{
public:
	CSubfami(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubfami)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CSUBFAM;
	CStringA	m_DSUBFAM;
	CStringA	m_ARTI;
	CStringA	m_CFAMILIA;
	double	m_DTOVSFAM;
	double	m_DTOCSFAM;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX
	HRESULT UpdateRegistro();
	HRESULT Insert();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Cuentas.h: declaración de CCuentas

#pragma once

// código generado el miércoles, 15 de junio de 2005, 15:59

class __declspec(dllexport) CCuentas : public CRecordset
{
public:
	CCuentas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCuentas)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	float	m_DEBE;
	CStringA	m_CUENTA;
	CStringA	m_NOMBRE;
	float	m_HABER;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT UpdateRegistro();
	HRESULT Insert();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Clientes.h: declaración de CClientes

#pragma once

// código generado el lunes, 11 de julio de 2005, 16:00

class __declspec(dllexport) CClientes : public CRecordset
{
public:
	CClientes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClientes)

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
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_DIVAC;
	double	m_MFVAC;
	double	m_DFVAC;
	double	m_MIVAC;
	CStringA	m_AGE;
	CStringA	m_NOMBCO;
	CStringA	m_DIRBCO;
	CStringA	m_POBCO;
	CStringA	m_CTACORR;
	CStringA	m_DIR1;
	CStringA	m_POB1;
	CStringA	m_CP1;
	CStringA	m_PROV1;
	CStringA	m_DIR2;
	CStringA	m_POB2;
	CStringA	m_CP2;
	CStringA	m_PROV2;
	CStringA	m_CONTACTO;
	CStringA	m_CARGO;
	CStringA	m_TEL2;
	CStringA	m_REPRE;
	CStringA	m_REPRE2;
	double	m_DCTOS2;
	double	m_DCTOS3;
	CStringA	m_OBSER1;
	CStringA	m_OBSER2;
	CStringA	m_OBSER3;
	double	m_RIACCLI;
	double	m_RIESCLI;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_IDIOMA;
	CStringA	m_DIVISA;
	CStringA	m_TRANSPOR;
	CStringA	m_MATRICULA;
	CStringA	m_DNI;
	CStringA	m_TELTRAN;
	CStringA	m_TARIFA;
	CStringA	m_ZONA;
	double	m_COPFAC;
	CStringA	m_CPAIS;
	CStringA	m_PAIS;
	CStringA	m_IVAIDEN;
	CStringA	m_SEGURO;
	double	m_AABONAR;
	CStringA	m_ABOPFAC;
	CStringA	m_NUMCOMPA;
	double	m_NUMEXP;
	CStringA	m_SG;
	CStringA	m_DIRHACIEN;
	CStringA	m_NUMERO;
	CStringA	m_CTRCTA;
	CStringA	m_DC;
	CStringA	m_CC1;
	CStringA	m_CC2;
	CStringA	m_CC3;
	CStringA	m_CPBCO;
	CStringA	m_TIPO;
	CStringA	m_CAMCLI;
	CStringA	m_GRUFAC;
	CStringA	m_EMAIL;
	CStringA	m_CTRANS;
	double	m_DCTOS4;
	double	m_ERIESCLI;
	double	m_ERIACCLI;
	double	m_IVACLIENTE;
	CStringA	m_NOMFAC;
	CStringA	m_DIREFAC;
	CStringA	m_SGFAC;
	CStringA	m_NUMEFAC;
	CStringA	m_CPFAC;
	CStringA	m_POBFAC;
	CStringA	m_PROVFAC;
	CStringA	m_CPAISFAC;
	CStringA	m_DPAISFAC;
	CTime	m_FECHALTA;
	CTime	m_FECHBAJA;
	long	m_BLOQUEOCLI;
	CStringA	m_OBSCOBCLI;
	double	m_PORRETE;
	CStringA	m_CTARETE;
	CStringA	m_RETFISCAL;
	CStringA	m_RETCOMER;
	CStringA	m_IBAN;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateClientes();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Pais.h: declaración de CPais

#pragma once

// código generado el miércoles, 22 de junio de 2005, 15:37

class __declspec(dllexport) CPais : public CRecordset
{
public:
	CPais(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPais)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CPAIS;
	CStringA	m_DPAIS;
	CStringA	m_EUROPA;
	BOOL	m_INTRA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdatePais();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Concepto.h: declaración de CConcepto

#pragma once

// código generado el miércoles, 22 de junio de 2005, 15:39

class __declspec(dllexport) CConcepto : public CRecordset
{
public:
	CConcepto(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CConcepto)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CONCEPTO;
	CStringA	m_DCONCEPTO;
	double	m_CONTA;
	CStringA	m_EJERCICIO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateConcepto();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Inventario.h: declaración de CInventario

#pragma once

// código generado el jueves, 23 de junio de 2005, 13:51

class __declspec(dllexport) CInventario : public CRecordset
{
public:
	CInventario(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CInventario)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ARTI;
	CStringA	m_ALMACEN;
	long	m_UNITOTAL;
	long	m_UNIDISPONIBLE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateRegistro();
	HRESULT UpdateUniTotal();
	HRESULT UpdateUniDisponible();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Divisas.h: declaración de CDivisas

#pragma once

// código generado el viernes, 08 de julio de 2005, 9:53

class __declspec(dllexport) CDivisas : public CRecordset
{
public:
	CDivisas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDivisas)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_DIVISA;
	CStringA	m_DDIVISA;
	double	m_CAMBIO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateDivisa();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// FPagCob.h: declaración de CFPagCob

#pragma once

// código generado el viernes, 08 de julio de 2005, 9:56

class __declspec(dllexport) CFPagCob : public CRecordset
{
public:
	CFPagCob(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFPagCob)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_FCOBRO;
	CStringA	m_DFCOBRO;
	CStringA	m_ACEPTO;
	CStringA	m_DESCONTA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateFPagCob();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// DirEnv.h: declaración de CDirEnv

#pragma once

// código generado el viernes, 08 de julio de 2005, 10:17

class __declspec(dllexport) CDirEnv : public CRecordset
{
public:
	CDirEnv(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDirEnv)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CLIENTE;
	CStringA	m_DIRENV;
	CStringA	m_DDIRENV;
	CStringA	m_POBL;
	CStringA	m_CP;
	CStringA	m_PROV;
	CStringA	m_CONTACTO;
	CStringA	m_TELEFONO;
	double	m_DISTANCIA;
	CStringA	m_DIVISA;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_DIVAC;
	double	m_DFVAC;
	double	m_MIVAC;
	double	m_MFVAC;
	CStringA	m_NUMCOMPA;
	CStringA	m_SEGURO;
	double	m_RIESCLI;
	double	m_ERIESCLI;
	double	m_RIACCLI;
	double	m_ERIACCLI;
	CStringA	m_CC1;
	CStringA	m_CC2;
	CStringA	m_DC;
	CStringA	m_CTACORR;
	CStringA	m_NOMBCO;
	CStringA	m_AGE;
	CStringA	m_DIRBCO;
	CStringA	m_CPBCO;
	CStringA	m_POBCO;
	CStringA	m_TARIFA;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_CTRCTA;
	CStringA	m_GRUFAC;
	double	m_COPFAC;
	double	m_ABFAC;
	double	m_AABONAR;
	CStringA	m_NOMFAC;
	CStringA	m_DIREFAC;
	CStringA	m_SGFAC;
	CStringA	m_NUMEFAC;
	CStringA	m_CPFAC;
	CStringA	m_POBFAC;
	CStringA	m_PROVFAC;
	CStringA	m_CPAISFAC;
	CStringA	m_DPAISFAC;
	CTime	m_FECHALTA;
	CTime	m_FECHBAJA;
	double	m_TIEMPOTRAN;
	double	m_TIEMPOOBRA;
	CStringA	m_ESTAOBRA;
	CStringA	m_ZONA;
	CStringA	m_NOMDIRENV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	CTime	m_FECFINOBRA;
	CStringA	m_OBRACERRA;
	CStringA	m_FINOBRA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateDirEnv();
	HRESULT DeleteDirEnv();
	HRESULT UpdateCierreObra();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Zona.h: declaración de CZona

#pragma once

// código generado el lunes, 11 de julio de 2005, 15:18

class __declspec(dllexport) CZona : public CRecordset
{
public:
	CZona(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CZona)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_ZONA;
	CStringA	m_DZONA;
	CStringA	m_CUENTA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateZona();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// RuTran.h: declaración de CRuTran

#pragma once

// código generado el lunes, 11 de julio de 2005, 15:19

class __declspec(dllexport) CRuTran : public CRecordset
{
public:
	CRuTran(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRuTran)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CRUTRAN;
	CStringA	m_DRUTRAN;
	CStringA	m_MATRICULA;
	CStringA	m_MODELO;
	double	m_TARA;
	double	m_PESOMAXIMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateRutran();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Seguro.h: declaración de CSeguro

#pragma once

// código generado el lunes, 11 de julio de 2005, 15:19

class __declspec(dllexport) CSeguro : public CRecordset
{
public:
	CSeguro(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSeguro)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_SEGURO;
	CStringA	m_DSEGURO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateSeguro();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Centros.h: declaración de CCentros

#pragma once

// código generado el martes, 26 de julio de 2005, 9:29

class _declspec(dllexport) CCentros : public CRecordset
{
public:
	CCentros(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCentros)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_CCENTRO;
	CStringA	m_DCENTRO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateCentros();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Proforma.h: declaración de CProforma

#pragma once

// código generado el lunes, 01 de agosto de 2005, 12:07

class __declspec(dllexport) CProforma : public CRecordset
{
public:
	CProforma(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProforma)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPROFOR;
	CStringA	m_NUMPEDIDO;
	CStringA	m_NUMALB;
	CTime	m_FECHPROF;
	CTime	m_FECHPRE;
	CTime	m_FECHALB;
	CTime	m_FECHFAC;
	CTime	m_FECHENT;
	CStringA	m_CUENTA;
	CStringA	m_REPRE;
	CStringA	m_SUBREP;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_DIRFAC;
	CStringA	m_SREF;
	CStringA	m_OBSPROF;
	CStringA	m_OBSALB;
	CStringA	m_OBSDENEGA;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_DIVISA;
	CStringA	m_IDIOMA;
	CStringA	m_PUERTO;
	CStringA	m_TIPO;
	CStringA	m_PARTIDA;
	CStringA	m_TRANS;
	CStringA	m_MERCAN;
	CStringA	m_EXPORTA;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CAM1;
	CStringA	m_CAM2;
	CStringA	m_CAM3;
	double	m_CANTI;
	CStringA	m_UNIDAD;
	CStringA	m_TARIFA;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_COMARTI;
	double	m_IVARTI;
	//CStringA	m_IVA;
	double	m_IVA;
	double	m_CANTIFAC;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_TRANSPOR;
	CStringA	m_DNI;
	CStringA	m_MATRICULA;
	CStringA	m_BULTOS;
	BOOL	m_MUESTRAS;
	double	m_CAMBIO;
	CStringA	m_INCOTERM;
	CStringA	m_EMBALAJE;
	CStringA	m_CONTAINERS;
	double	m_CAJAS;
	CStringA	m_PORTES;
	double	m_PESNETO;
	double	m_PESBRUTO;
	CStringA	m_CERTIF;
	CStringA	m_COMER;
	CStringA	m_ADUAN;
	CStringA	m_ESTADO;
	BOOL	m_SUPFAC;
	float	m_IMPABO;
	CStringA	m_LCACE;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_TOTALPAL;
	double	m_CANTRANS;
	CStringA	m_TRANSEMP;
	double	m_FLETES;
	CStringA	m_CENTRO;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_IMPODIVI;
	double	m_RECARGO;
	CStringA	m_CAMVEN;
	CStringA	m_GRUFAC;
	CStringA	m_RUTRAN;
	double	m_SUPLEM;
	CStringA	m_DSUPLEM;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS4;
	CStringA	m_CAMCVEN;
	double	m_CAMNVEN;
	double	m_EUROS;
	double	m_DTOARTI2;
	double	m_DTOARTI3;
	CStringA	m_DESARMEMO;
	CStringA	m_NOMCONTA;
	CStringA	m_CIFCONTA;
	CStringA	m_DIRCONTA;
	CStringA	m_POBCONTA;
	CStringA	m_PROVCONTA;
	CStringA	m_CPCONTA;
	CStringA	m_TELEF1;
	CStringA	m_TELEF2;
	double	m_IMPORI;
	CStringA	m_CONTRATO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	CStringA	m_OBSERV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	double	m_DIASFAC;
	CStringA	m_PREPMATE;
	CTime	m_FECALB2;
	CStringA	m_MARCA;
	double	m_DIASOLD;
	BOOL	m_PREFAC;
	CTime	m_FECPREF;
	double	m_IMPOPREF;
	double	m_DIAFACPREF;
	BOOL	m_MODIPREF;
	BOOL	m_LINPTEPRE;
	double	m_EIMPOPREF;
	CStringA	m_ATENCLI;
	CStringA	m_CCOMPET;
	CTime	m_FECHCADU;
	double	m_CLAVE;
	double	m_RETENCOM;
	double	m_RETENFIS;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateProforma();
	HRESULT UpdateEstadoProforma();
	HRESULT UpdateObsDenegaProforma();
	HRESULT UpdateNumPedido();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// ArtiProforma.h: declaración de CArtiProforma

#pragma once

// código generado el martes, 26 de julio de 2005, 9:31

class _declspec(dllexport) CArtiProforma : public CRecordset
{
public:
	CArtiProforma(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiProforma)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPROFOR;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double      m_PESO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	double	m_CANTI;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiProforma();
	HRESULT DeleteArtiProforma();


// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Pedidos.h: declaración de CPedidos

#pragma once

// código generado el miércoles, 10 de agosto de 2005, 11:28

class __declspec(dllexport) CPedidos : public CRecordset
{
public:
	CPedidos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPedidos)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPEDIDO;
	CStringA	m_NUMFAC;
	CStringA	m_NUMALB;
	CTime	m_FECHPED;
	CTime	m_FECHPRE;
	CTime	m_FECHALB;
	CTime	m_FECHFAC;
	CTime	m_FECHENT;
	CStringA	m_CUENTA;
	CStringA	m_ALMACEN;
	long	m_REVISADO;
	CStringA	m_REPRE;
	CStringA	m_SUBREP;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_DIRFAC;
	CStringA	m_SREF;
	CStringA	m_OBSPED;
	CStringA	m_OBSALB;
	CStringA	m_OBSFAC;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_DIVISA;
	CStringA	m_IDIOMA;
	CStringA	m_PUERTO;
	CStringA	m_TIPO;
	CStringA	m_PARTIDA;
	CStringA	m_TRANS;
	CStringA	m_MERCAN;
	CStringA	m_EXPORTA;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CAM1;
	CStringA	m_CAM2;
	CStringA	m_CAM3;
	double	m_CANTI;
	CStringA	m_UNIDAD;
	CStringA	m_TARIFA;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_COMARTI;
	double	m_IVARTI;
	//CStringA	m_IVA;
	double m_IVA;
	double	m_CANTIFAC;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_TRANSPOR;
	CStringA	m_DNI;
	CStringA	m_MATRICULA;
	CStringA	m_BULTOS;
	BOOL	m_MUESTRAS;
	double	m_CAMBIO;
	CStringA	m_INCOTERM;
	CStringA	m_EMBALAJE;
	CStringA	m_CONTAINERS;
	double	m_CAJAS;
	CStringA	m_PORTES;
	double	m_PESNETO;
	double	m_PESBRUTO;
	CStringA	m_CERTIF;
	CStringA	m_COMER;
	CStringA	m_ADUAN;
	CStringA	m_ESTADO;
	BOOL	m_SUPFAC;
	double	m_IMPABO;
	CStringA	m_LCACE;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_TOTALPAL;
	double	m_CANTRANS;
	CStringA	m_TRANSEMP;
	double	m_FLETES;
	CStringA	m_CENTRO;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_IMPODIVI;
	double	m_RECARGO;
	CStringA	m_CAMVEN;
	CStringA	m_GRUFAC;
	CStringA	m_RUTRAN;
	double	m_SUPLEM;
	CStringA	m_DSUPLEM;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS4;
	CStringA	m_CAMCVEN;
	double	m_CAMNVEN;
	double	m_EUROS;
	double	m_DTOARTI2;
	double	m_DTOARTI3;
	CStringA	m_DESARMEMO;
	CStringA	m_NOMCONTA;
	CStringA	m_CIFCONTA;
	CStringA	m_DIRCONTA;
	CStringA	m_POBCONTA;
	CStringA	m_PROVCONTA;
	CStringA	m_CPCONTA;
	CStringA	m_TELEF1;
	CStringA	m_TELEF2;
	double	m_IMPORI;
	CStringA	m_CONTRATO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	CStringA	m_OBSERV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	double	m_DIASFAC;
	CStringA	m_PREPMATE;
	CTime	m_FECALB2;
	CStringA	m_MARCA;
	double	m_DIASOLD;
	BOOL	m_PREFAC;
	CTime	m_FECPREF;
	double	m_IMPOPREF;
	double	m_DIAFACPREF;
	CStringA	m_MODIPREF;
	CStringA	m_LINPTEPRE;
	double	m_EIMPOPREF;
	CStringA	m_ATENCLI;
	CStringA	m_CCOMPET;
	CTime	m_FECHADU;
	double	m_CLAVE;
	double	m_RETENCOM;
	double	m_RETENFIS;
	double	m_EUROSUV;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	CPedidos& operator =(CPedidos& Other);
	HRESULT Insert();
	HRESULT UpdatePedido();
	HRESULT UpdateNumAlbaran();
	HRESULT MarcaRevisado();
	HRESULT UpdateEstado();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// ArtiVenta.h: declaración de CArtiVenta

#pragma once

// código generado el miércoles, 10 de agosto de 2005, 12:18

class __declspec(dllexport) CArtiVenta : public CRecordset
{
public:
	CArtiVenta(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiVenta)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPEDIDO;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double	m_PESO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	double	m_CANTI;
	double	m_ENVIADOS;
	double	m_RECOGIDOS;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiVenta();
	HRESULT DeleteArtiVenta();
	HRESULT UpdateEnviados();
	HRESULT UpdateRecogidos();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Compras.h: declaración de CCompras

#pragma once

// código generado el miércoles, 10 de agosto de 2005, 12:52

class __declspec(dllexport) CCompras : public CRecordset
{
public:
	CCompras(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCompras)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NPEDCOM;
	double		m_DCTOGEN;
	CStringA	m_NUMFAC;
	CStringA	m_NUMALBCO;
	CTime	m_FECHPED;
	CTime	m_FECHALBCO;
	CTime	m_FECHFAC;
	CStringA	m_CUENTA;
	CStringA	m_ALMACEN;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_DIRFAC;
	CStringA	m_SREF;
	CStringA	m_OBSPED;
	CStringA	m_OBSALBCO;
	CStringA	m_OBSFAC;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_DIVISA;
	CStringA	m_IDIOMA;
	CStringA	m_PUERTO;
	CStringA	m_TIPO;
	CStringA	m_PARTIDA;
	CStringA	m_TRANS;
	CStringA	m_MERCAN;
	CStringA	m_EXPORTA;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CAM1;
	CStringA	m_CAM2;
	CStringA	m_CAM3;
	double	m_CANTI;
	CStringA	m_UNIDAD;
	CStringA	m_TARIFA;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_COMARTI;
	double	m_IVARTI;
	CStringA	m_IVA;
	double	m_CANTIFAC;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_TRANSPOR;
	CStringA	m_DNI;
	CStringA	m_MATRICULA;
	CStringA	m_BULTOS;
	BOOL	m_MUESTRAS;
	double	m_CAMBIO;
	CStringA	m_INCOTERM;
	CStringA	m_EMBALAJE;
	CStringA	m_CONTAINERS;
	double	m_CAJAS;
	CStringA	m_PORTES;
	double	m_PESNETO;
	double	m_PESBRUTO;
	CStringA	m_ESTADO;
	BOOL	m_SUPFAC;
	double	m_IMPABO;
	CStringA	m_LCACE;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_TOTALPAL;
	double	m_CANTRANS;
	CStringA	m_TRANSEMP;
	CStringA	m_CENTRO;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_IMPODIVI;
	double	m_SUPLEM;
	CStringA	m_DSUPLEM;
	CStringA	m_CAMCOMPRA;
	double	m_DCTO2;
	double	m_DCTO3;
	CStringA	m_CAMCOM2;
	CTime	m_FECHENT;
	double	m_EUROS;
	double	m_DTOARTI2;
	double	m_DTOARTI3;
	CStringA	m_DESARMEMO;
	double	m_CLAVE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateCompra();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// Albaran.h: declaración de CAlbaran

#pragma once

// código generado el jueves, 18 de agosto de 2005, 15:48

class __declspec(dllexport) CAlbaran : public CRecordset
{
public:
	CAlbaran(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAlbaran)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPEDIDO;
	CStringA	m_NUMFAC;
	CStringA	m_NUMALB;
	CTime	m_FECHPED;
	CTime	m_FECHPRE;
	CTime	m_FECHALB;
	CTime	m_FECHFAC;
	CTime	m_FECHENT;
	CStringA	m_CUENTA;
	CStringA	m_ALMACEN;
	CStringA    m_TIPOPED;
	CStringA	m_REPRE;
	CStringA	m_SUBREP;
	CStringA	m_FCOBRO;
	double	m_NCOBROS;
	double	m_VTO1;
	double	m_DVTO;
	CStringA	m_DIRENV;
	CStringA	m_DIRFAC;
	CStringA	m_SREF;
	CStringA	m_OBSPED;
	CStringA	m_OBSALB;
	CStringA	m_OBSFAC;
	double	m_DCTOS;
	double	m_PP;
	CStringA	m_DIVISA;
	CStringA	m_IDIOMA;
	CStringA	m_PUERTO;
	CStringA	m_TIPO;
	CStringA	m_PARTIDA;
	CStringA	m_TRANS;
	CStringA	m_MERCAN;
	CStringA	m_EXPORTA;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	CStringA	m_CAM1;
	CStringA	m_CAM2;
	CStringA	m_CAM3;
	double	m_CANTI;
	CStringA	m_UNIDAD;
	CStringA	m_TARIFA;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_COMARTI;
	double	m_IVARTI;
	double  m_IVA;
	//CStringA	m_IVA;
	double	m_CANTIFAC;
	double	m_COMISION;
	double	m_COMISION2;
	CStringA	m_TRANSPOR;
	CStringA	m_DNI;
	CStringA	m_MATRICULA;
	CStringA	m_BULTOS;
	BOOL	m_MUESTRAS;
	double	m_CAMBIO;
	CStringA	m_INCOTERM;
	CStringA	m_EMBALAJE;
	CStringA	m_CONTAINERS;
	double	m_CAJAS;
	CStringA	m_PORTES;
	double	m_PESNETO;
	double	m_PESBRUTO;
	CStringA	m_CERTIF;
	CStringA	m_COMER;
	CStringA	m_ADUAN;
	CStringA	m_ESTADO;
	BOOL	m_SUPFAC;
	double	m_IMPABO;
	CStringA	m_LCACE;
	double	m_DIA1;
	double	m_DIA2;
	double	m_DIA3;
	double	m_TOTALPAL;
	double	m_CANTRANS;
	CStringA	m_TRANSEMP;
	double	m_FLETES;
	CStringA	m_CENTRO;
	CStringA	m_DESARTI2;
	CStringA	m_DESARTI3;
	double	m_IMPODIVI;
	double	m_RECARGO;
	CStringA	m_CAMVEN;
	CStringA	m_GRUFAC;
	CStringA	m_RUTRAN;
	double	m_SUPLEM;
	CStringA	m_DSUPLEM;
	double	m_DCTOS2;
	double	m_DCTOS3;
	double	m_DCTOS4;
	CStringA	m_CAMCVEN;
	double	m_CAMNVEN;
	double	m_EUROS;
	double	m_DTOARTI2;
	double	m_DTOARTI3;
	CStringA	m_DESARMEMO;
	CStringA	m_NOMCONTA;
	CStringA	m_CIFCONTA;
	CStringA	m_DIRCONTA;
	CStringA	m_POBCONTA;
	CStringA	m_PROVCONTA;
	CStringA	m_CPCONTA;
	CStringA	m_TELEF1;
	CStringA	m_TELEF2;
	double	m_IMPORI;
	CStringA	m_CONTRATO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	CStringA	m_OBSERV;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	double	m_DIASFAC;
	CStringA	m_PREPMATE;
	CTime	m_FECALB2;
	CStringA	m_MARCA;
	double	m_DIASOLD;
	BOOL	m_PREFAC;
	CTime	m_FECPREF;
	double	m_IMPOPREF;
	double	m_DIAFACPREF;
	CStringA	m_MODIPREF;
	CStringA	m_LINPTEPRE;
	double	m_EIMPOPREF;
	CStringA	m_ATENCLI;
	double	m_CANTIANT;
	double	m_PENDIENTE;
	CTime	m_FECHAIN;
	CStringA	m_HORAIN;
	double	m_RECE;
	CStringA	m_ENTRECOG;
	CTime	m_ULTIFACT;
	double	m_RETENCOM;
	double	m_RETENFIS;
	double	m_CLAVE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateAlbaran();
	HRESULT DeleteAlbaran();
	HRESULT UpdateEstado();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// ArtiAlbaran.h: declaración de CArtiAlbaran

#pragma once

// código generado el viernes, 19 de agosto de 2005, 9:19

class __declspec(dllexport) CArtiAlbaran : public CRecordset
{
public:
	CArtiAlbaran(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiAlbaran)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMALB;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double	m_PESO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	double	m_CANTI;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiAlbaran();
	HRESULT DeleteArtiAlbaran();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


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


// ArtiAlbCompra.h: declaración de CArtiAlbCompra

#pragma once

// código generado el miércoles, 31 de agosto de 2005, 12:30

class __declspec(dllexport) CArtiAlbCompra : public CRecordset
{
public:
	CArtiAlbCompra(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiAlbCompra)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NALBCOM;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double	m_CANTI;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiAlbCompra();
	HRESULT DeleteArtiAlbCompra();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Facturas.h: declaración de CFacturas

#pragma once

// código generado el lunes, 19 de septiembre de 2005, 15:23

class __declspec(dllexport) CFacturas : public CRecordset
{
public:
	CFacturas(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFacturas)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
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
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateFactura();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// ArtiFactura.h: declaración de CArtiFactura

#pragma once

// código generado el lunes, 19 de septiembre de 2005, 15:51

class  __declspec(dllexport) CArtiFactura : public CRecordset
{
public:
	CArtiFactura(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiFactura)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMFAC;
	CStringA	m_NUMALB;
	CStringA	m_NUMPED;
	CStringA	m_ARTI;
	CStringA	m_DESARTI;
	double	m_PESO;
	CStringA	m_ALQUILER;
	CStringA	m_TIPOALQ;
	double	m_CANTI;
	CTime	m_FECINIALQ;
	CTime	m_FECFINALQ;
	long	m_NDIASALQ;
	double	m_IMPOARTI;
	double	m_DTOARTI;
	double	m_IVARTI;
	CStringA	m_DESARMEMO;
	double	m_CLAVE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateArtiFactura();
	HRESULT DeleteArtiFactura();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// ArtiPendiente.h: declaración de CArtiPendiente

#pragma once

// código generado el jueves, 15 de septiembre de 2005, 10:55

class __declspec(dllexport) CArtiPendiente : public CRecordset
{
public:
	CArtiPendiente(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArtiPendiente)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_NUMPEDIDO;
	CStringA	m_NUMALB;
	CStringA	m_ARTI;
	double	m_CANTI;
	CTime	m_FECINIALQ;
	CStringA	m_TIPOALQ;
	CStringA	m_ESTADO;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateEstado();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Festivos.h: declaración de CFestivos

#pragma once

// código generado el miércoles, 05 de octubre de 2005, 10:57

class __declspec(dllexport) CFestivos : public CRecordset
{
public:
	CFestivos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFestivos)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CTime m_DIA;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT DeleteFestivo();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


// Cobros.h: declaración de CCobros

#pragma once

// código generado el jueves, 03 de noviembre de 2005, 9:51

class  __declspec(dllexport) CCobros : public CRecordset
{
public:
	CCobros(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCobros)

// Datos de campo o parámetro

// Los tipos de cadena siguientes (si los hay) reflejan el tipo de datos real del
// campo de base de datos: CStringA para tipos de datos ANSI y CStringW para tipos de datos
// Unicode. Esto es para impedir que el controlador ODBC lleve a cabo conversiones
// potencialmente innecesarias. Si lo desea, puede modificar estos miembros a
// tipos CString y el controlador ODBC realizará las conversiones necesarias.
// (Nota: la versión de controlador ODBC que debe utilizar es la 3.5 o posterior
// para que admita tanto estas conversiones como las Unicode).

	CStringA	m_FCOBRO;
	CStringA	m_NUMFAC;
	CTime	m_FECHA;
	double	m_IMPORTE;
	CStringA	m_CUENTA;
	double	m_GASTOS;
	CStringA	m_NREMESA;
	CStringA	m_ESTADREM;
	CStringA	m_ESTADO;
	CStringA	m_BANCO;
	CTime	m_FECHLIBRA;
	CTime	m_FECHDOC;
	CStringA	m_REPRE;
	CStringA	m_NUMEFEC;
	CTime	m_FESTADO;
	CTime	m_FRECEP;
	CStringA	m_CENTRO;
	double	m_CAMBIO;
	double	m_IMPODIVI;
	double	m_TIPOREM;
	CStringA	m_CLICON;
	CStringA	m_OBSCOBRO;
	BOOL	m_EMITIDO;
	CTime	m_FECHCONTA;
	double	m_EUROS;
	BOOL	m_VENCIDO;
	double	m_EGASTOS;
	double	m_NPAGARE;

// Reemplazos
	// El asistente generó reemplazos de funciones virtuales
	public:
	virtual CString GetDefaultConnect();	// Cadena de conexión predeterminada

	virtual CString GetDefaultSQL(); 	// código SQL predeterminado del conjunto de registros
	virtual void DoFieldExchange(CFieldExchange* pFX);	// Compatibilidad con RFX

	HRESULT Insert();
	HRESULT UpdateCobros();
	HRESULT UpdateImporteCobro();
	HRESULT DeleteCobros();

// Implementación
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


