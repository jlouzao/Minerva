#define IDD_DLG_DIRECCION_ENVIO         50002
#define IDD_DLG_IDIOMAS                 50003
#define IDD_DLG_PAIS                    50004
#define IDD_DLG_FPAGCOB                 50005
#define IDD_DLG_CENTROS                 50006
#define IDD_DLG_SEGUROS                 50007
#define IDD_DLG_DIVISAS                 50008
#define IDD_DLG_ZONA                    50009
#define IDD_DLG_RUTRAN                  50010
#define IDD_DLG_CONCEPTO                50011

#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgCentros : public CDialog
{
	DECLARE_DYNAMIC(CDlgCentros)

public:
	CDlgCentros(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgCentros();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetCentros(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarCentros();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CENTROS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;
	BOOL bUpdate;

	CCentros m_rsCentros;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/*******************************************/
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};
#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgConcepto : public CDialog
{
	DECLARE_DYNAMIC(CDlgConcepto)

public:
	CDlgConcepto(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgConcepto();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetConcepto(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarConceptos();
	void ChequeaPosicion();
	void RellenaCampos();
	void Limpiar();
	BOOL ChequeaNumeros(CString);
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CONCEPTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;
	
	CString strPrimero;
	CString strUltimo;
	
	int iEstado;
	BOOL bUpdate;

	CConcepto m_rsConcepto;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
	//afx_msg void OnEnKillfocusCuenta();
	//CString m_strCuenta;
	//CString m_strEjercicio;
	//afx_msg void OnEnKillfocusEjercicio();
};

#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxwin.h"
#include "BD.h"
#include "Utilidades.h"

class __declspec(dllexport) CDlgDireccionEnvio : public CDialog
{
	DECLARE_DYNAMIC(CDlgDireccionEnvio)

public:
	CDlgDireccionEnvio(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDireccionEnvio();
	
	virtual BOOL OnInitDialog();

	void BuscarDirEnv();
	BOOL RellenaCampos();
	BOOL ChequeaNumeros(CString);
	void ChequeaPosicion();
	void SetCliente(CString, CString);
	void SetTipo(BOOL);
	void SetObra(CString);
	void SetConexion(CDatabase*);
	void SetCreado(BOOL);
	BOOL GetCreado();
	void Limpia();
	void BuscarUltimoDirEnv();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DIRECCION_ENVIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strObra;
	CString m_strNombre;
	CString m_strDireccion;
	CString m_strCP;
	CString m_strPoblacion;
	CString m_strProvincia;
	CString m_strDistancia;
	CString m_strContacto;
	CString m_strTelefono;
	CTime m_FechAlta;
	CTime m_FechBaja;
	CString m_strCliente;
	CString m_strDesCliente;
	BOOL m_bCerrada;
	
	CEdit m_ctrlObra;
	CEdit m_ctrlDistancia;

	CDialogBusqueda m_dlgBusquedaDirEnv;

	BOOL bUpdate;
	BOOL bNuevo;
	BOOL bCreado;

	int iEstado;

	BOOL bBuscado;
	CString strPrimero;
	CString strUltimo;

	CDirEnv m_rsDirEnv;
	CDatabase* m_db;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusDistancia();
	afx_msg void OnEnKillfocusObra();
	CEdit m_ctrlNombre;
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
};
#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgDivisas : public CDialog
{
	DECLARE_DYNAMIC(CDlgDivisas)

public:
	CDlgDivisas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDivisas();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetDivisas(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarDivisas();
	BOOL ChequeaNumeros(CString);
	void ChequeaPosicion();
	void Limpiar();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DIVISAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;
	BOOL bUpdate;

	CDivisas m_rsDivisas;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
	CString m_strCambio;
	afx_msg void OnEnKillfocusCambio();
};
#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgFPagCob : public CDialog
{
	DECLARE_DYNAMIC(CDlgFPagCob)

public:
	CDlgFPagCob(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgFPagCob();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetFPagCob(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarFPagCob();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_FPAGCOB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;
	
	int iEstado;
	BOOL bUpdate;

	CFPagCob m_rsFPagCob;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};

#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgIdiomas : public CDialog
{
	DECLARE_DYNAMIC(CDlgIdiomas)

public:
	CDlgIdiomas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgIdiomas();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetIdioma(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarIdioma();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_IDIOMAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;
	
	int iEstado;
	BOOL bUpdate;

	CIdiomas m_rsIdioma;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/*******************************************/
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};

#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgPais : public CDialog
{
	DECLARE_DYNAMIC(CDlgPais)

public:
	CDlgPais(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPais();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetPais(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarPais();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PAIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;
	BOOL bUpdate;

	CPais m_rsPais;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/*******************************************/
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};
#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgRutran : public CDialog
{
	DECLARE_DYNAMIC(CDlgRutran)

public:
	CDlgRutran(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgRutran();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetRuTran(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarRuTrans();
	void ChequeaPosicion();
	void RellenaCampos();
	void Limpiar();
	BOOL ChequeaNumeros(CString);
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_RUTRAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;
	CString m_strModelo;
	CString m_strMatricula;
	CString m_strTara;
	CString m_strTaraMax;

	CString strPrimero;
	CString strUltimo;
	int iEstado;;

	BOOL bNuevaBusqueda;

	BOOL bUpdate;
	CRuTran m_rsRuTran;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusTara();
	afx_msg void OnEnKillfocusTaraMax();
};

#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgSeguros : public CDialog
{
	DECLARE_DYNAMIC(CDlgSeguros)

public:
	CDlgSeguros(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgSeguros();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetSeguros(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarSeguros();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_SEGUROS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;;
	BOOL bUpdate;
	CSeguro m_rsSeguros;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación *******
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;*/
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};
#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgZona

class  __declspec(dllexport)CDlgZona : public CDialog
{
	DECLARE_DYNAMIC(CDlgZona)

public:
	CDlgZona(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgZona();

	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetZona(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarZonas();
	BOOL BuscarCuenta();
	void ChequeaPosicion();
	void RellenaCampos();
	void Limpiar();

	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusCuenta();
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedBuscarcuenta();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_ZONA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

public:
	CString m_strCodigo;
	CString m_strDescripcion;
	CString m_strCuenta;
	CString m_strDesCuenta;

	CString strPrimero;
	CString strUltimo;
	
	int iEstado;
	BOOL bNuevaBusqueda;

	BOOL bUpdate;
	CZona m_rsZona;
	CDialogBusqueda m_dlgBusquedaZona;
	CDialogBusqueda m_dlgBusquedaCuenta;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
};