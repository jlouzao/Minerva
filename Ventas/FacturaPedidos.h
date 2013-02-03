#pragma once

#include "BD.h"

class CArtiEntrega
{
public:
	CString m_strArti;
	CString m_strNumAlb;
	double m_dCanti;
	CString m_strTipoAlq;
	CTime m_fechaIniAlq;
};

class CArtiRecogida
{
public:
	CString m_strArti;
	double m_dCanti;
	CTime m_fechaFinAlq;
};

class CArtiFacturado
{
public:
	CString m_strArti;
	CString m_strNumAlb;
	double m_dCanti;
	CTime m_fechaIniAlq;
	CTime m_fechaFinAlq;
	int m_iDiasAlquilado;
};


class CFacturaPedidos
{
public:
	CFacturaPedidos(void);
	~CFacturaPedidos(void);
	void SetConexion(CDatabase *db);
	void SetPedidos(CList <CPedidos, CPedidos&> *lPedidos);
	void SetFinAlq(CTime fechaFinAlq);
	void SetTipoFac(int iTipoFac);
	void SetContador(int iContador);
	HRESULT FacturaPedido(CPedidos *Pedido);
	HRESULT GuardaCobros(CFacturas *rsFactura, double dImporte);
//	void FacturaPedidos();
	int CalculaDiasMes(int iMes, int iAgno);
	int CalculaDiasAlquiler(CTime fechaIniAlq, CTime fechaFinAlq, CString strTipoAlq);
	CString GetFacturaIni();
	CString GetFacturaFin();

private:
	CDatabase *m_db;
	CList <CPedidos, CPedidos&> *m_lPedidos;
	int m_iTipoFac;
	int m_iContador;
	double m_dTotalBruto;
	BOOL m_bPendientes;
	CString m_OldDirEnv;
	CString m_OldCliente;
	CString m_strOldNumFactura;
	CFacturas m_rsFactura;
	CTime m_fechaFinAlq;
	CString m_strFacturaIni;
	CString m_strFacturaFin;
	CList <CArtiEntrega, CArtiEntrega> m_lArtiEntrega;
	CList <CArtiRecogida, CArtiRecogida> m_lArtiRecogida;
	CList <CArtiFacturado, CArtiFacturado> m_lArtiFacturado;
	CStringList lstArtiVenta;

	HRESULT BuscaArtiAlbaranEntrega(CString strPedido);
	HRESULT BuscaArtiAlbaranRecogida(CString strPedido);
	HRESULT PrepararArtiAlquilados(CString strPedido);
	CTime CalculaDiaSiguiente(CTime fecha);
	//int CalculaMesSiguiente(int iMes);
	BOOL EsAgnoBisiesto(int iAgno);
	int CalculaFestivos(CTime fechaIni, CTime fechaFin);
	HRESULT GuardaFactura(CPedidos *Pedido);
	void RellenaFactura(CPedidos *Pedido);
	void RellenaArtiFactura(CArtiFactura *rsArtiFactura, CArtiVenta *rsArtiVenta);
	void LimpiaArtiFactura(CArtiFactura *rsArtiFactura);
	double CalculaValorNetoFactura();

};
