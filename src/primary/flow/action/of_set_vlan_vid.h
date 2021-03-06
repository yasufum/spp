/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2019 Nippon Telegraph and Telephone Corporation
 */

#ifndef _PRIMARY_FLOW_ACTION_OF_SET_VLAN_VID_H_
#define _PRIMARY_FLOW_ACTION_OF_SET_VLAN_VID_H_

extern struct flow_detail_ops of_set_vlan_vid_ops_list[];

int append_action_of_set_vlan_vid_json(const void *conf, int buf_size,
	char *action_str);

#endif
