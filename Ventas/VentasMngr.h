#pragma once


// CVentasMngr

class __declspec(dllexport) CVentasMngr : public CWnd
{
	DECLARE_DYNAMIC(CVentasMngr)

public:
	CVentasMngr();
	virtual ~CVentasMngr();
	void Init(CDatabase *db, CWnd* pParent);
	void GestionOfertas();
	void AceptaOferta();
	void GestionPedidos();
	void GestionAlbaranes();
	void PreparacionAlbaranes();
	void AltaModObra();
	void CierreObra();
	void ConsultaObra();
	void Facturacion();
	void ModificaFactura();
	void CalendarioLaboral();
	void EmitirOfertas();
	void EmitirPedidos();
	void EmitirAlbaranes();
	void EmitirFacturas();
	void EmitirFacturasOrigen();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CWnd *m_pParent;

};


