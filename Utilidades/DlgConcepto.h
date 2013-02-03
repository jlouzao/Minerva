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

