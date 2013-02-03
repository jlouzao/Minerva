#pragma once

#include "resource.h"
#include "atltime.h"
#include "BD.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgDesglose

class CDlgDesglose : public CDialog
{
	DECLARE_DYNAMIC(CDlgDesglose)

public:
	CDlgDesglose(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDesglose();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetCobroPadre(CCobros *rsCobrosPadre);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DESGLOSE };

private:
	CDatabase *m_db;
	CCobros m_rsCobro;
	CCobros *m_rsCobrosPadre;

	CDialogBusqueda m_dlgBusquedaFCobro;

	void GetSeguienteCobroDesglosado();
	void RellenaCobro();
	BOOL BuscaFCobro();
	BOOL CompruebaNumero(CString strNumero);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNumEfec;
	CString m_strNumEfec2;
	CString m_strNumEfec3;
	CString m_strFCobro;
	CString m_strDesFCobro;
	CString m_strImporte;
	CTime m_fechaVenci;
	CString m_strObservaciones;
	CTime m_fechaRecep;
	afx_msg void OnEnKillfocusEditFcobro();
	afx_msg void OnBnClickedBtnFcobro();
	afx_msg void OnEnKillfocusImporte();
	afx_msg void OnBnClickedOk();
};
