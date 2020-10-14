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

// MainRun.cpp: implementation of the CMainRun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "com_struct.h"
#include "MainDlg.h"

//--------------------------------------------------------------------

INT32		CMainDlg::SyncDatabase()
{
	{
		TListStr tQueryList;

		tQueryList.push_back("ALTER TABLE env_license ADD COLUMN sup_os BIGINT DEFAULT 2;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=71;");
		m_tDBSyncMap[69] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE log_notify_file (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, order_id BIGINT DEFAULT 0, notify_file_path TEXT);");

		tQueryList.push_back("UPDATE schema_info SET db_ver=70;");
		m_tDBSyncMap[69] = tQueryList;	
	}
	
	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE env_socket (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("ALTER TABLE po_in_vuln_sw_pkg ADD COLUMN sw_version TEXT;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=69;");
		m_tDBSyncMap[68] = tQueryList;	
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("ALTER TABLE log_deploy_file ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_device ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_doc ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_patch ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_rs ADD COLUMN user_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_secu ADD COLUMN user_id BIGINT DEFAULT 0;");


		tQueryList.push_back("UPDATE schema_info SET db_ver=68;");
		m_tDBSyncMap[67] = tQueryList;	
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("ALTER TABLE env_notify_info ADD COLUMN notify_skip_day BIGINT DEFAULT 0;");
		tQueryList.push_back("UPDATE schema_info SET db_ver=67;");
		m_tDBSyncMap[66] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("ALTER TABLE po_power ADD COLUMN fastboot_ctrl BIGINT DEFAULT 0;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=66;");
		m_tDBSyncMap[65] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("ALTER TABLE po_in_ptn_no ADD COLUMN req_skip_opt BIGINT DEFAULT 0;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=65;");
		m_tDBSyncMap[64] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_in_rs_op					(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_pkg				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0,  notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_unit				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_unit_sub_pkg		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0,  notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_unit_obj_pkg		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0,  notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_sub_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, sb_type TEXT, sb_proc TEXT, ac_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_op_obj_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, chk_type TEXT, chk_path TEXT, chk_ext TEXT);");	
		tQueryList.push_back("INSERT INTO po_in_rs_op				(reg_date, name, admin_id) VALUES (1585048737, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN piro_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN piro_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_in_rs_no				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, msg_type BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_rs_no_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("INSERT INTO po_in_rs_no				(reg_date, name, admin_id) VALUES (1585048737, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pirn_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pirn_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_in_rs_bk				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("INSERT INTO po_in_rs_bk				(reg_date, name, admin_id) VALUES (1585048737, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pirb_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pirb_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE log_rs		 	(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, evt_time BIGINT DEFAULT 0, evt_ecode BIGINT DEFAULT 0, skip_target BIGINT DEFAULT 0, notify_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, policy_type BIGINT DEFAULT 0, op_type BIGINT DEFAULT 0, reg_svr_id BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0, block_type BIGINT DEFAULT 0, object_type BIGINT DEFAULT 0, subject_path TEXT, subject_name TEXT, object_path TEXT, object_name TEXT, object_wpath BLOB);");

		tQueryList.push_back("DROP TABLE po_in_ac_doc;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_obj_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_sub_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_unit_obj_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_doc_unit_sub_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_file;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_obj_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_sch_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_sub_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_unit_obj_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_unit_rul_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_unit_sch_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_file_unit_sub_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_obj_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_sub_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_unit;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_unit_obj_pkg;");
		tQueryList.push_back("DROP TABLE po_in_ac_sf_unit_sub_pkg;");

		//second add query : 2020-03-31 14:22

		tQueryList.push_back("ALTER TABLE po_in_rs_op_unit ADD COLUMN ac_mode BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_op_unit ADD COLUMN log_mode TEXT;");

		//third add query : 2020-04-06 15:55
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN keep_size BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN free_size BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN file_max_size BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN file_keep_num BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN fext_type BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE po_in_rs_bk ADD COLUMN fext_info TEXT;");

		tQueryList.push_back("CREATE TABLE log_rs_bk (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, evt_time BIGINT DEFAULT 0, evt_ecode BIGINT DEFAULT 0, skip_target BIGINT DEFAULT 0, notify_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, policy_type BIGINT DEFAULT 0, op_type BIGINT DEFAULT 0, reg_svr_id BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0, backup_size BIGINT DEFAULT 0, backup_type BIGINT DEFAULT 0, backup_time BIGINT DEFAULT 0, subject_path TEXT, subject_name TEXT, object_path TEXT, object_name TEXT, object_wpath BLOB, bk_file_name TEXT, or_file_hash TEXT);");

		tQueryList.push_back("UPDATE schema_info SET db_ver=64;");

		m_tDBSyncMap[63] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_in_devo_notify				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, msg_type BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_in_devo_notify_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("INSERT INTO po_in_devo_notify				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pidn_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pidn_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("UPDATE schema_info SET db_ver=63;");

		m_tDBSyncMap[62] = tQueryList;	
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("ALTER TABLE env_license ADD COLUMN right_class TEXT;");

		tQueryList.push_back("ALTER TABLE user ADD COLUMN src_group_name TEXT;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=62;");
		m_tDBSyncMap[61] = tQueryList;
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("ALTER TABLE po_in_vuln_sw_pkg ADD COLUMN sw_chk_key TEXT;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=61;");
		m_tDBSyncMap[60] = tQueryList;
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("DROP TABLE po_in_vuln_patch_exception_unit;");
		tQueryList.push_back("CREATE TABLE po_in_vuln_patch_exception_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, patch_info TEXT);");

		tQueryList.push_back("ALTER TABLE po_host_run ADD COLUMN once_pkt_num BIGINT DEFAULT 0;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=60;");
		m_tDBSyncMap[59] = tQueryList;
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("ALTER TABLE po_fa_env ADD COLUMN sys_off_max_work_time BIGINT DEFAULT 0;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=59;");
		m_tDBSyncMap[58] = tQueryList;
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE log_device			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, evt_time BIGINT DEFAULT 0, evt_ecode BIGINT DEFAULT 0, skip_target BIGINT DEFAULT 0, notify_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, policy_type BIGINT DEFAULT 0, op_type BIGINT DEFAULT 0, reg_svr_id BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0,block_type BIGINT DEFAULT 0,dv_instance_id TEXT);");

		tQueryList.push_back("DROP TABLE site_vuln;");
		tQueryList.push_back("DROP TABLE site_vuln_scan;");
		tQueryList.push_back("DROP TABLE site_vuln_repair;");
		tQueryList.push_back("DROP TABLE site_vuln_lock;");

		tQueryList.push_back("CREATE TABLE site_vuln			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, admin_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, class BIGINT DEFAULT 0, name TEXT, descr TEXT, sys_type TEXT, sys_sp_type BIGINT DEFAULT 0, sys_arch_type BIGINT DEFAULT 0, support_option BIGINT DEFAULT 0, risk_level  BIGINT DEFAULT 0, def_score  BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE site_vuln_scan		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, admin_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, name TEXT, vuln_id  BIGINT DEFAULT 0, vuln_sub_id  BIGINT DEFAULT 0, scan_order  BIGINT DEFAULT 0, sys_type TEXT, sys_sp_type BIGINT DEFAULT 0, sys_arch_type BIGINT DEFAULT 0, scan_type  BIGINT DEFAULT 0, custom_id  BIGINT DEFAULT 0, scan_path TEXT, value_type  BIGINT DEFAULT 0, decision_type  BIGINT DEFAULT 0, comp_type  BIGINT DEFAULT 0, comp_value TEXT);");

		tQueryList.push_back("UPDATE schema_info SET db_ver=58;");
		m_tDBSyncMap[57] = tQueryList;
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("DROP TABLE po_in_vuln_sw_version;");
		tQueryList.push_back("DROP TABLE po_in_vuln_sw_version_pkg;");
		tQueryList.push_back("DROP TABLE po_in_vuln_sw_version_unit;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_patch_exception				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_patch_exception_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_patch_exception_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, patch_id BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_in_vuln_patch_exception				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");

		tQueryList.push_back("DROP TABLE host_policy;");
		tQueryList.push_back("DROP TABLE user_policy;");

		tQueryList.push_back("CREATE TABLE host_policy					(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, pup_id BIGINT DEFAULT 0, psil_id BIGINT DEFAULT 0, phrmi_id BIGINT DEFAULT 0, phr_id BIGINT DEFAULT 0, phc_id BIGINT DEFAULT 0, pp_id BIGINT DEFAULT 0, pcp_id BIGINT DEFAULT 0, pcpr_id BIGINT DEFAULT 0, psp_id BIGINT DEFAULT 0, pdf_id BIGINT DEFAULT 0, pfao_id BIGINT DEFAULT 0, pfac_id BIGINT DEFAULT 0, pfap_id BIGINT DEFAULT 0, pfae_id BIGINT DEFAULT 0, pfab_id BIGINT DEFAULT 0, pwr_id BIGINT DEFAULT 0, psiu_id BIGINT DEFAULT 0, psim_id BIGINT DEFAULT 0, pfepo_id BIGINT DEFAULT 0, pfepb_id BIGINT DEFAULT 0, pfepw_id BIGINT DEFAULT 0, pfee_id BIGINT DEFAULT 0, pfen_id BIGINT DEFAULT 0, pfesp_id BIGINT DEFAULT 0, pfepl_id BIGINT DEFAULT 0, pfan_id BIGINT DEFAULT 0, pcm_id BIGINT DEFAULT 0, ps_id BIGINT DEFAULT 0, pipo_id BIGINT DEFAULT 0, pipb_id BIGINT DEFAULT 0, pipw_id BIGINT DEFAULT 0, pipe_id BIGINT DEFAULT 0, pips_id BIGINT DEFAULT 0, pipn_id BIGINT DEFAULT 0, reserved_a BIGINT DEFAULT 0, reserved_b BIGINT DEFAULT 0, reserved_c BIGINT DEFAULT 0, pivo_id BIGINT DEFAULT 0, pivs_id BIGINT DEFAULT 0, phn_id BIGINT DEFAULT 0, pido_id BIGINT DEFAULT 0, pidb_id BIGINT DEFAULT 0, pidw_id BIGINT DEFAULT 0, pide_id BIGINT DEFAULT 0, piva_id BIGINT DEFAULT 0, pive_id BIGINT DEFAULT 0, pivq_id BIGINT DEFAULT 0, pivu_id BIGINT DEFAULT 0, pivw_id BIGINT DEFAULT 0, pivpe_id BIGINT DEFAULT 0, ppmop_id BIGINT DEFAULT 0, ppmdm_id BIGINT DEFAULT 0, ppmscan_id BIGINT DEFAULT 0, ppmex_id BIGINT DEFAULT 0, ppmno_id BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE user_policy 					(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, user_id BIGINT DEFAULT 0, pup_id BIGINT DEFAULT 0, psil_id BIGINT DEFAULT 0, phrmi_id BIGINT DEFAULT 0, phr_id BIGINT DEFAULT 0, phc_id BIGINT DEFAULT 0, pp_id BIGINT DEFAULT 0, pcp_id BIGINT DEFAULT 0, pcpr_id BIGINT DEFAULT 0, psp_id BIGINT DEFAULT 0, pdf_id BIGINT DEFAULT 0, pfao_id BIGINT DEFAULT 0, pfac_id BIGINT DEFAULT 0, pfap_id BIGINT DEFAULT 0, pfae_id BIGINT DEFAULT 0, pfab_id BIGINT DEFAULT 0, pwr_id BIGINT DEFAULT 0, psiu_id BIGINT DEFAULT 0, psim_id BIGINT DEFAULT 0, pfepo_id BIGINT DEFAULT 0, pfepb_id BIGINT DEFAULT 0, pfepw_id BIGINT DEFAULT 0, pfee_id BIGINT DEFAULT 0, pfen_id BIGINT DEFAULT 0, pfesp_id BIGINT DEFAULT 0, pfepl_id BIGINT DEFAULT 0, pfan_id BIGINT DEFAULT 0, ppre_id BIGINT DEFAULT 0, pprn_id BIGINT DEFAULT 0, ppro_id BIGINT DEFAULT 0, pprr_id BIGINT DEFAULT 0, ps_id BIGINT DEFAULT 0, pipo_id BIGINT DEFAULT 0, pipb_id BIGINT DEFAULT 0, pipw_id BIGINT DEFAULT 0, pipe_id BIGINT DEFAULT 0, pips_id BIGINT DEFAULT 0, pipn_id BIGINT DEFAULT 0, reserved_a BIGINT DEFAULT 0, reserved_b BIGINT DEFAULT 0, reserved_c BIGINT DEFAULT 0, pivo_id BIGINT DEFAULT 0, pivs_id BIGINT DEFAULT 0, phn_id BIGINT DEFAULT 0, pido_id BIGINT DEFAULT 0, pidb_id BIGINT DEFAULT 0, pidw_id BIGINT DEFAULT 0, pide_id BIGINT DEFAULT 0, piva_id BIGINT DEFAULT 0, pive_id BIGINT DEFAULT 0, pivq_id BIGINT DEFAULT 0, pivu_id BIGINT DEFAULT 0, pivw_id BIGINT DEFAULT 0, pivpe_id BIGINT DEFAULT 0, ppmop_id BIGINT DEFAULT 0, ppmdm_id BIGINT DEFAULT 0, ppmscan_id BIGINT DEFAULT 0, ppmex_id BIGINT DEFAULT 0, ppmno_id BIGINT DEFAULT 0);");

		tQueryList.push_back("DROP TABLE po_in_vuln_op;");
		tQueryList.push_back("CREATE TABLE po_in_vuln_op				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, ptn_file_sv_name TEXT, ptn_version TEXT, ptn_file_name TEXT, ptn_file_hash TEXT, ptn_dn_file_type BIGINT DEFAULT 0, ptn_dn_file_name TEXT, ptn_dn_file_hash TEXT);");

		tQueryList.push_back("UPDATE schema_info SET db_ver=57;");
		m_tDBSyncMap[56] = tQueryList;
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_pm_op				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, log_sync_mode BIGINT DEFAULT 0, dn_try_num BIGINT DEFAULT 0, mon_rm_patch TEXT, auto_patch_type BIGINT DEFAULT 0, ptn_file_sv_name TEXT, ptn_version TEXT, ptn_file_name TEXT, ptn_file_hash TEXT, ptn_dn_file_type BIGINT DEFAULT 0, ptn_dn_file_name TEXT, ptn_dn_file_hash TEXT);");
		tQueryList.push_back("INSERT INTO po_pm_op				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN ppmop_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN ppmop_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_pm_dm				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_dm_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_dm_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, apply_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, patch_id TEXT);");
		tQueryList.push_back("INSERT INTO po_pm_dm				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN ppmdm_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN ppmdm_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_pm_scan				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_scan_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_scan_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, scan_type BIGINT DEFAULT 0, scan_time TEXT, scan_svr_type BIGINT DEFAULT 0, scan_last_time BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_pm_scan				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN ppmscan_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN ppmscan_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_pm_ex				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_ex_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_ex_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, ex_mode BIGINT DEFAULT 0, patch_id TEXT);");
		tQueryList.push_back("INSERT INTO po_pm_ex				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN ppmex_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN ppmex_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_pm_no				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, msg_type BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_pm_no_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_pm_no				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN ppmno_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN ppmno_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE host_patch 			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, find_type BIGINT DEFAULT 0, kb_id BIGINT DEFAULT 0, category TEXT, name TEXT, publisher TEXT, ins_date TEXT, guid TEXT, no_remove BIGINT DEFAULT 0, uninstall TEXT);");		
		tQueryList.push_back("CREATE TABLE log_patch			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, evt_time BIGINT DEFAULT 0, evt_ecode BIGINT DEFAULT 0, skip_target BIGINT DEFAULT 0, notify_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, reg_svr_id BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0, patch_id BIGINT DEFAULT 0, patch_status BIGINT DEFAULT 0, patch_type BIGINT DEFAULT 0, apply_num BIGINT DEFAULT 0);");

		tQueryList.push_back("CREATE TABLE env_local 			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, chk_type BIGINT DEFAULT 0, chk_code BIGINT DEFAULT 0, n_value TEXT, s_value TEXT);");
		tQueryList.push_back("ALTER TABLE env_notify_info ADD COLUMN match_info TEXT;");

		tQueryList.push_back("UPDATE schema_info SET db_ver=56;");
		m_tDBSyncMap[55] = tQueryList;
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("CREATE TABLE po_dv_default			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, policy_perm BIGINT DEFAULT 0, device_pa_name TEXT, device_name TEXT, device_ins_id TEXT, device_pa_ins_id TEXT);");
		tQueryList.push_back("ALTER TABLE po_in_devo_info ADD COLUMN device_pa_ins_id TEXT;");	
		tQueryList.push_back("UPDATE schema_info SET db_ver=55;");
		m_tDBSyncMap[54] = tQueryList;	
	}

	{	
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_in_vuln_ax				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, unuse_day BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_ax_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_ax_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, ax_filter BIGINT DEFAULT 0, ax_name TEXT, ax_clsid TEXT, download_site TEXT, publisher TEXT, ax_path TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_ax					(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN piva_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN piva_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_edit_app			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_edit_app_pkg		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_edit_app_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, class_name TEXT, product_name TEXT, reg_key TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_edit_app			(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pive_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pive_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_qna				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_qna_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_qna_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, msg_question TEXT, msg_answer TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_qna				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pivq_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pivq_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_secu_usb			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_secu_usb_pkg		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_secu_usb_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, usb_value TEXT, reg_value TEXT, process_value TEXT, file_value TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_secu_usb			(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pivu_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pivu_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_sw				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_sw_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_sw_unit			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, sw_id BIGINT DEFAULT 0, class_name TEXT, sw_regkey TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_sw					(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pivw_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pivw_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE po_in_vuln_sw_version		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_sw_version_pkg	(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_vuln_sw_version_unit	(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, patch_id BIGINT DEFAULT 0, chk_type BIGINT DEFAULT 0, sw_product TEXT, sw_name TEXT, reg_key TEXT, reg_value TEXT, file_name TEXT, sw_version TEXT);");
		tQueryList.push_back("INSERT INTO po_in_vuln_sw_version			(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pivv_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pivv_id BIGINT DEFAULT 0;");

		tQueryList.push_back("CREATE TABLE host_vuln_rst 			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0, scan_mon BIGINT DEFAULT 0, scan_date BIGINT DEFAULT 0, group_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, ip_addr TEXT, user_name TEXT, sys_name TEXT, module_version TEXT, scan_score BIGINT DEFAULT 0, scan_rst TEXT);");
		tQueryList.push_back("CREATE TABLE host_vuln_rst_unit 		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, rst_vuln_id BIGINT DEFAULT 0, site_vuln_id BIGINT DEFAULT 0, default_score BIGINT DEFAULT 0, scan_result_type BIGINT DEFAULT 0, scan_result_info TEXT);");

		tQueryList.push_back("UPDATE schema_info SET db_ver=54;");
		m_tDBSyncMap[53] = tQueryList;
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_in_devo_op			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, block_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("INSERT INTO po_in_devo_op				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pido_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pido_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_in_devo_info		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, policy_type TEXT, device_name TEXT, device_type BIGINT DEFAULT 0, device_ins_id TEXT);");

		tQueryList.push_back("CREATE TABLE po_in_devo_bl		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_devo_bl_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_in_devo_bl		(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pidb_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pidb_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_in_devo_wl		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_devo_wl_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_in_devo_wl		(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pidw_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pidw_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("CREATE TABLE po_in_devo_ex		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_devo_ex_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");
		tQueryList.push_back("CREATE TABLE po_in_devo_ex_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, block_type BIGINT DEFAULT 0, exclude_ptn BIGINT DEFAULT 0);");
		tQueryList.push_back("INSERT INTO po_in_devo_ex		(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN pide_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN pide_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("UPDATE schema_info SET db_ver=53;");
		m_tDBSyncMap[52] = tQueryList;
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("CREATE TABLE 	doc_delete_info	(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, last_scan_time BIGINT DEFAULT 0, last_del_time BIGINT DEFAULT 0, doc_cnt BIGINT DEFAULT 0, sch_cnt BIGINT DEFAULT 0, menual_cnt BIGINT DEFAULT 0);");	

		tQueryList.push_back("UPDATE schema_info SET db_ver=52;");
		m_tDBSyncMap[51] = tQueryList;	
	}

	{
		TListStr tQueryList;

		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN skip_target BIGINT DEFAULT 0;");	

		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN host_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN reg_svr_id BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN sync_svr_mode BIGINT DEFAULT 0;");
		tQueryList.push_back("ALTER TABLE log_event ADD COLUMN sync_svr_step BIGINT DEFAULT 0;");

		tQueryList.push_back("DROP TABLE log_status;");


		tQueryList.push_back("UPDATE schema_info SET db_ver=51;");
		m_tDBSyncMap[50] = tQueryList;	
	}


	{
		TListStr tQueryList;

		tQueryList.push_back("CREATE TABLE po_host_notify				(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, msg_type BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_host_notify_pkg			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, policy_id BIGINT DEFAULT 0, unit_id BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0);");	
		tQueryList.push_back("CREATE TABLE po_host_notify_unit		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, reg_date BIGINT DEFAULT 0, seq_no BIGINT DEFAULT 0, name TEXT, descr TEXT, admin_id BIGINT DEFAULT 0, sub_admin_lock BIGINT DEFAULT 0, target_lock BIGINT DEFAULT 0, notify_info_id BIGINT DEFAULT 0, ext_option BIGINT DEFAULT 0, used_mode BIGINT DEFAULT 0, sch_time BIGINT DEFAULT 0, pos_type BIGINT DEFAULT 0, show_size BIGINT DEFAULT 0, show_pos BIGINT DEFAULT 0, show_time BIGINT DEFAULT 0, msg_fmt_type BIGINT DEFAULT 0, msg_info LTEXT);");	
		tQueryList.push_back("INSERT INTO po_host_notify				(reg_date, name, admin_id) VALUES (1462187932, 'default policy', 1);");	
		tQueryList.push_back("ALTER TABLE host_policy ADD COLUMN phn_id BIGINT DEFAULT 0;");	
		tQueryList.push_back("ALTER TABLE user_policy ADD COLUMN phn_id BIGINT DEFAULT 0;");	

		tQueryList.push_back("UPDATE schema_info SET db_ver=50;");
		m_tDBSyncMap[49] = tQueryList;	
	}

	{
		TListStr tQueryList;
		tQueryList.push_back("CREATE TABLE log_status		(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, used_flag BIGINT DEFAULT 1, skip_target BIGINT DEFAULT 0, reg_date BIGINT DEFAULT 0, evt_time BIGINT DEFAULT 0, evt_ecode BIGINT DEFAULT 0, notify_type BIGINT DEFAULT 0, notify_id BIGINT DEFAULT 0, host_id BIGINT DEFAULT 0, reg_svr_id BIGINT DEFAULT 0, sync_svr_step BIGINT DEFAULT 0, subject_type BIGINT DEFAULT 0, subject_id BIGINT DEFAULT 0, subject_info TEXT, target_type BIGINT DEFAULT 0, target_id BIGINT DEFAULT 0, target_info TEXT, object_type BIGINT DEFAULT 0, object_code BIGINT DEFAULT 0, object_id BIGINT DEFAULT 0, object_info TEXT, operation_type BIGINT DEFAULT 0, evt_descr TEXT, ext_option BIGINT DEFAULT 0);");
		tQueryList.push_back("UPDATE schema_info SET db_ver=49;");
		m_tDBSyncMap[48] = tQueryList;	
	}
	
	{
		TMapIDListStrItor begin, end;
		CDBMgrSchemaInfo tDBSchemaInfo;
		begin = m_tDBSyncMap.begin();	end = m_tDBSyncMap.end();
		for(begin; begin != end; begin++)
		{
			if(begin->first != tDBSchemaInfo.GetDBVer())
				continue;

			tDBSchemaInfo.UpdateDatabase(begin->second);

			WriteLogN("[%s] dbf schema update success : [%d]", "db sync", begin->first);
		}
	}
	return 0;
}
//--------------------------------------------------------------------

