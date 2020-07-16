/*
 * Copyright (C) 2020-2025 ASHINi corp. 
 * 
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * 
 */


#ifndef	COM_DEFINE_DBMS_QUERY_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8
#define COM_DEFINE_DBMS_QUERY_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8


//DBMS Policy Query
//------------------------------------------------------------------------------
#define		DBMS_POLICY_QUERY_SELECT				"pup_id, psil_id, phrmi_id, phr_id, phc_id, pp_id, pcp_id, pcpr_id, psp_id, pdf_id, pfao_id, pfac_id, pfap_id, pfae_id, pfab_id, pwr_id, psiu_id, psim_id, pfepo_id, pfepb_id, pfepw_id, pfee_id, pfen_id, pfesp_id, pfepl_id, pfan_id, ps_id, pipo_id, pipb_id, pipw_id, pipe_id, pips_id, pipn_id, piad_id, pias_id, piaf_id, pivo_id, pivs_id"
#define		DBMS_POLICY_QUERY_INSERT_NAME			"pup_id, psil_id, phrmi_id, phr_id, phc_id, pp_id, pcp_id, pcpr_id, psp_id, pdf_id, pfao_id, pfac_id, pfap_id, pfae_id, pfab_id, pwr_id, psiu_id, psim_id, pfepo_id, pfepb_id, pfepw_id, pfee_id, pfen_id, pfesp_id, pfepl_id, pfan_id, ps_id, pipo_id, pipb_id, pipw_id, pipe_id, pips_id, pipn_id, piad_id, pias_id, piaf_id, pivo_id, pivs_id"
#define		DBMS_POLICY_QUERY_INSERT_VALUE			"%u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u"

#define		DBMS_POLICY_QUERY_UPDATE				"pup_id=%u, psil_id=%u, phrmi_id=%u, phr_id=%u, phc_id=%u, pp_id=%u, pcp_id=%u, pcpr_id=%u, psp_id=%u, pdf_id=%u, pfao_id=%u, pfac_id=%u, pfap_id=%u, pfae_id=%u, pfab_id=%u, pwr_id=%u, psiu_id=%u, psim_id=%u\
, pfepo_id=%u, pfepb_id=%u, pfepw_id=%u, pfee_id=%u, pfen_id=%u, pfesp_id=%u, pfepl_id=%u, pfan_id=%u\
, ps_id=%u\
, pipo_id=%u, pipb_id=%u, pipw_id=%u, pipe_id=%u, pips_id=%u, pipn_id=%u\
, piad_id=%u, pias_id=%u, piaf_id=%u\
, pivo_id=%u, pivs_id=%u"

//------------------------------------------------------------------------------

#define		DBMS_POLICY_QUERY_HDR_SELECT			"SELECT id, reg_date, seq_no, name, descr, admin_id, sub_admin_lock, target_lock, notify_info_id, ext_option, used_mode"
#ifdef _DB_DEMAND_GEN_INDEX
#define		DBMS_POLICY_QUERY_HDR_INSERT_NAME		"id, used_flag, reg_date, seq_no, name, descr, admin_id, sub_admin_lock, target_lock, notify_info_id, ext_option, used_mode"
#define		DBMS_POLICY_QUERY_HDR_INSERT_VALUE		"%u, %u, %u, %u, '%s', '%s', %u, %u, %u, %u, %u, %u"
#else
#define		DBMS_POLICY_QUERY_HDR_INSERT_NAME		"used_flag, reg_date, seq_no, name, descr, admin_id, sub_admin_lock, target_lock, notify_info_id, ext_option, used_mode"
#define		DBMS_POLICY_QUERY_HDR_INSERT_VALUE		"%u, %u, %u, '%s', '%s', %u, %u, %u, %u, %u, %u"
#endif
#define		DBMS_POLICY_QUERY_HDR_UPDATE			"reg_date=%u, seq_no=%u, name='%s', descr='%s', admin_id=%u, sub_admin_lock=%u, target_lock=%u, notify_info_id=%u, ext_option=%u, used_mode=%u"
//------------------------------------------------------------------------------

#define		DBMS_POLICY_QUERY_PKG_HDR_SELECT		"SELECT id, reg_date, name, descr, admin_id, sub_admin_lock, policy_id, unit_id, notify_info_id, ext_option, used_mode"
#ifdef _DB_DEMAND_GEN_INDEX
#define		DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME	"id, used_flag, reg_date, name, descr, admin_id, sub_admin_lock, policy_id, unit_id, notify_info_id, ext_option, used_mode"
#define		DBMS_POLICY_QUERY_PKG_HDR_INSERT_VALUE	"%u, %u, %u, '%s', '%s', %u, %u, %u, %u, %u, %u, %u"
#else
#define		DBMS_POLICY_QUERY_PKG_HDR_INSERT_NAME	"used_flag, reg_date, name, descr, admin_id, sub_admin_lock, policy_id, unit_id, notify_info_id, ext_option, used_mode"
#define		DBMS_POLICY_QUERY_PKG_HDR_INSERT_VALUE	"%u, %u, '%s', '%s', %u, %u, %u, %u, %u, %u, %u"
#endif
#define		DBMS_POLICY_QUERY_PKG_HDR_UPDATE		"used_flag=%u, reg_date=%u, name='%s', descr='%s', admin_id=%u, sub_admin_lock=%u, policy_id=%u, unit_id=%u, notify_info_id=%u, ext_option=%u, used_mode=%u"
//------------------------------------------------------------------------------

#ifdef _DB_DEMAND_GEN_INDEX
#define		DBMS_DEFAULT_QUERY_TYPE_DELETE			"DELETE FROM %s WHERE id=%u;"
#else
#define		DBMS_DEFAULT_QUERY_TYPE_DELETE			"UPDATE %s SET used_flag=0 WHERE id=%u;"
#endif

#define		DBMS_DEFAULT_QUERY_TYPE_DELETE_FP		"DELETE FROM %s WHERE %s=%I64u;"
//
////////////////////////////////////////////////////////////////////////////////



#endif //COM_DEFINE_DBMS_QUERY_H_6AB3CD45_6B1E_4bCB_9AE9_F7924A2FF8B8