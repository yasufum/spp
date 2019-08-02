/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2017-2019 Nippon Telegraph and Telephone Corporation
 */

#ifndef _CLASSIFIER_MAC_H_
#define _CLASSIFIER_MAC_H_

#include "shared/secondary/spp_worker_th/cmd_utils.h"

/**
 * @file
 * SPP Classifier
 *
 * Classifier component provides packet forwarding function from
 * one port to one port. Classifier has table of virtual MAC address.
 * According to this table, classifier lookups L2 destination MAC address
 * and determines which port to be transferred to incoming packets.
 */

struct spp_iterate_classifier_table_params;
/**
 * Define func to iterate classifier for showing status or so, as a member
 * member of struct `spp_iterate_classifier_table_params`.
 */
typedef int (*spp_iterate_classifier_element_proc)(
		struct spp_iterate_classifier_table_params *params,
		enum sppwk_cls_type cls_type,
		int vid, const char *mac,
		const struct sppwk_port_idx *port);

/**
 * iterate classifier table parameters which is used when listing classifier
 * table content for status command or so.
 */
struct spp_iterate_classifier_table_params {
	void *output;  /* Buffer used for output */
	/* The function for creating classifier table information */
	spp_iterate_classifier_element_proc element_proc;
};

int append_classifier_element_value(
		struct spp_iterate_classifier_table_params *params,
		enum sppwk_cls_type cls_type,
		int vid, const char *mac,
		const struct sppwk_port_idx *port);

/**
 * Setup data of classifier table and call iterator function for getting
 * each of entries.
 *
 * @params[in] params Object which has pointer of operator func and attrs.
 */
int add_classifier_table_val(
		struct spp_iterate_classifier_table_params *params);

int add_classifier_table(const char *name, char **output,
		void *tmp __attribute__ ((unused)));

/**
 * classifier(mac address) initialize globals.
 *
 * @retval SPPWK_RET_OK succeeded.
 * @retval SPPWK_RET_NG failed.
 */
int init_cls_mng_info(void);

/**
 * initialize classifier information.
 *
 * @param component_id
 *  The unique component ID.
 *
 */
void init_classifier_info(int comp_id);


/**
 * Classify incoming packets.
 *
 * @param id Component ID.
 * @retval SPPWK_RET_OK succeeded.
 * @retval SPPWK_RET_NG failed.
 */
int classify_packets(int comp_id);

/**
 * Get classifier status.
 *
 * @param[in] lcore_id Lcore ID for classifier.
 * @param[in] id Unique component ID.
 * @param[in,out] params Pointer to detailed data of classifier status.
 * @retval SPPWK_RET_OK If succeeded.
 * @retval SPPWK_RET_NG If failed.
 */
/**
 * TODO(yasufum) Consider to move this function to `vf_cmd_runner.c`.
 * This function is called only from `vf_cmd_runner.c`, but
 * must be defined in `classifier_mac.c` because it refers g_mng_info defined
 * in this file. It is bad dependency for the global variable.
 */
int get_classifier_status(unsigned int lcore_id, int id,
		struct spp_iterate_core_params *params);

#endif /* _CLASSIFIER_MAC_H_ */
