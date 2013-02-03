#pragma once

#include "resource.h"
#include "BD.h"
#include "Utilidades.h"
#include "afxwin.h"


// Cuadro de diálogo de CDlgDatosCobro

class CDatosCobro
{
public:
	CStringA m_FCOBRO;
	double m_NCOBROS;
	double m_VTO1;
	double m_DVTO;
	double m_DIA1;
	double m_DIA2;
	double m_DIA3;
	double m_RETENFIS;
};


class CDlgDatosCobro : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosCobro)

public:
	CDlgDatosCobro(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosCobro();
	virtual BOOL OnInitDialog();

	void SetDatosCobro(CDatosCobro *datosCobro);
	void SetConexion(CDatabase *db);
	void SetReadOnly();


// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DATOS_COBRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private: 
	CDatabase *m_db;
	BOOL m_bReadOnly;
	CDatosCobro *m_datosCobro;

	CDialogBusqueda m_dlgBusquedaFCobros;

	BOOL BuscaFCobro();
	BOOL CompruebaNumero(CString strNumero);

public:
	CString m_strFCobro;
	CString m_strDesFCobro;
	double m_dNumCobros;
	double m_d1Vto;
	double m_dDiasVto;
	double m_dDiasPago1;
	CString m_strRetFiscal;
	double m_dDiasPago2;
	double m_dDiasPago3;
	afx_msg void OnBnClickedBtnFcobro();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusEditFcobro();
	afx_msg void OnEnKillfocusEditRetFiscal();
//	afx_msg void OnEnKillfocusEditRetComercial();
//	CString m_strRetCom;
//	CEdit m_cRetComercial;
	CEdit m_cRetFiscal;
	CEdit m_cFCobro;
	CEdit m_cNumCobros;
	CEdit m_c1Vto;
	CEdit m_cDiasVto;
	CEdit m_cDiasPago1;
	CEdit m_cDiasPago2;
	CEdit m_cDiasPago3;
};
