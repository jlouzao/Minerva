#pragma once


// Cuadro de di�logo de D

class D : public CDialog
{
	DECLARE_DYNAMIC(D)

public:
	D(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~D();

// Datos del cuadro de di�logo
	enum { IDD = 50319 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
};
