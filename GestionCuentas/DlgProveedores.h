#pragma once

#include "Resource.h"
#include "BD.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "atltime.h"
#include "utilidades.h"
#include "DlgDatosFacturacion.h"
#include "DlgDatosPago.h"

// Cuadro de diálogo de CDlgProveedores

class CDlgProveedores : public CDialog
{
	DECLARE_DYNAMIC(CDlgProveedores)

public:
	CDlgProveedores(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgProveedores();
	virtual BOOL OnInitDialog();
	
	BOOL EncuentraPais(CString);
	BOOL EncuentraIdioma(CString);
	void SetCodigo(CString strAux);//trae el codigo desde donde le llamen
	void SetConexion(CDatabase *db);
	void EsNuevo(BOOL);

// Datos del cuadro de diálogo
	enum { IDD = IDD_PROVEEDORES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCodCuenta;
	CTime m_timeAlta;

	CDatabase *m_db;
	CProve m_rsProve;
	BOOL m_bUpdate;

	CString m_strNombre;
	CString m_strNomFicha;

	CDialogBusqueda m_dlgBusquedaPais;
	CDialogBusqueda m_dlgBusquedaIdioma;

	char m_cTipo;
	BOOL m_bTipo1;
	int m_iTipo2;
	CString m_strDire;
	CString m_strSg;
	CString m_strNum;
	CString m_strCP;
	CString m_strProvincia;
	CString m_strPoblacion;
	CString m_strPais;
	CString m_strCIF;
	CString m_strIdentificacion;
	CString m_strTelf1;
	CString m_strTelf2;
	CString m_strFax;
	CString m_strEmail;
	CString m_strContacto;
	CString m_strCargo;
	CString m_strIdioma;
	CString m_strPlazo;
	CString m_strObservaciones;
	CString m_strDesPais;
	CString m_strDesIdioma;
	CTime m_datetimeFechaBaja;
	CTime m_datetimeFechaAlta;
	CTime m_timeBaja;
	/////////////////////////////////////
	afx_msg void OnBnClickedInversion1();
	afx_msg void OnBnClickedInversion2();
	afx_msg void OnBnClickedAceptar();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedIva1();
	afx_msg void OnBnClickedIva2();
	afx_msg void OnBnClickedIva3();
	afx_msg void OnBnClickedBotonPais();
	afx_msg void OnBnClickedBotonIdioma();

	afx_msg void OnBnClickedBotonFacturacion();
	afx_msg void OnBnClickedBotonPagos();
	
	afx_msg void OnEnKillfocusPais();
	afx_msg void OnEnKillfocusIdioma();

};
