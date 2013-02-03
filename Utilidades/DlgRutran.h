#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de di�logo de CDlgIdiomas

class __declspec(dllexport) CDlgRutran : public CDialog
{
	DECLARE_DYNAMIC(CDlgRutran)

public:
	CDlgRutran(CWnd* pParent = NULL);   // Constructor est�ndar
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
// Datos del cuadro de di�logo
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

	/************ Botones de navegaci�n ********/
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

