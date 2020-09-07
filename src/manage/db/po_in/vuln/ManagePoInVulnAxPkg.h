//---------------------------------------------------------------------------

#ifndef ManagePoInVulnAxPkgH
#define ManagePoInVulnAxPkgH
//---------------------------------------------------------------------------

class CManagePoInVulnAxPkg : public CManagePoBase<DB_PO_IN_VULN_AX_PKG>
{
public:
	INT32					LoadDBMS();

public:
	INT32					InitPkg();
	INT32					GetHash(UINT32 nID, String& strOrgValue);

public:
	INT32					AddPoInVulnAxPkg(DB_PO_IN_VULN_AX_PKG&	data);
    INT32					EditPoInVulnAxPkg(DB_PO_IN_VULN_AX_PKG&	data);
    INT32					DelPoInVulnAxPkg(UINT32 nID);

public:
	INT32					ClearItemByPolicyID(UINT32 nPolicyID);
	INT32					ClearPkgUnitByPolicyID(UINT32 nPolicyID);

public:
	String					GetName(UINT32 nID);    

public:
	INT32					SetPkt(MemToken& SendToken);
	INT32					SetPkt(UINT32 nID, MemToken& SendToken);
	INT32					SetPkt(PDB_PO_IN_VULN_AX_PKG pdata, MemToken& SendToken);
	INT32					GetPkt(MemToken& RecvToken, DB_PO_IN_VULN_AX_PKG& data);

public:
	INT32					SetPktHost(UINT32 nID, MemToken& SendToken);

public:
	CManagePoInVulnAxPkg();
    ~CManagePoInVulnAxPkg();

};

extern CManagePoInVulnAxPkg*	t_ManagePoInVulnAxPkg;

#endif
