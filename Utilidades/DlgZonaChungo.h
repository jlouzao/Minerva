#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgZona : public CDialog
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
	void ChequeaPosicion();
	void RellenaCampos();
	//BOOL ChequeaNumeros(CString);
// Datos del cuadro de diálogo
	enum { IDD = IDD_ZONA };

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
	
	BOOL bInicial;
	BOOL bNuevaBusqueda;

	BOOL bUpdate;
	CZona m_rsZona;
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
	afx_msg void OnEnKillfocusCuenta();
	CString m_strCuenta;
	CString m_strDesCuenta;
	//afx_msg void OnBnClickedBuscacuenta();
	afx_msg void OnBnClickedBuscacuenta();
};

