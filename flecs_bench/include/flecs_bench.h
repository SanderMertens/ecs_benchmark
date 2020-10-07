#ifndef FLECS_BENCH_H
#define FLECS_BENCH_H

/* This generated file contains includes for project dependencies */
#include "flecs_bench/bake_config.h"

#ifdef __cplusplus
extern "C" {
#endif

FLECS_BENCH_API void flecs_new_id(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_id_recycle(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_w_entity(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_new_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new_recycle(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_new_16_comp(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_delete(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_delete_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_delete_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_delete_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_delete_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_delete_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_delete_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_delete_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_delete_16_comp(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_init_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_init_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_init_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_init_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_init_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_1_comp_direct_access(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_4_comp_direct_access(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_8_comp_direct_access(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_16_comp_direct_access(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_1_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_4_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_8_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_16_comp_no_type(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_add_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_1_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_4_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_8_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_16_comp_no_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_1_tag(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_4_tag(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_8_tag(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_16_tag(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_to_16_comp_16_tag(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_again(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_add_to_1(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_add_to_16(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_bulk_add_16_to_1(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_w_trigger(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_w_monitor(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_w_ctor(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_add_instanceof(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_instanceof_override(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_override(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_childof(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_instanceof_w_child(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_add_case_to_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_case_to_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_case_to_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_add_case_to_16_comp(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_remove_from_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_remove_from_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_remove_from_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_remove_from_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_remove_w_dtor(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_set(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_set_again(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_set_and_new(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_set_w_on_set(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_set_w_copy(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_mut(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_mut_existing(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_mut_modified(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_single(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_16_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_1_comp_not_found(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_4_comp_not_found(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_8_comp_not_found(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_16_comp_not_found(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_1_comp_base(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_4_comp_base(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_8_comp_base(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_16_comp_base(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_1_comp_base_4(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_4_comp_base_4(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_8_comp_base_4(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_from_16_comp_base_4(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_ref_from_single(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_ref_from_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_ref_from_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_ref_from_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_ref_from_16_comp(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_has_for_1_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_has_for_4_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_has_for_8_comp(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_has_for_16_comp(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_is_alive_for_alive(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_is_alive_for_deleted(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_is_alive_for_nonexist(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_get_type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_world(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_init_mini_world(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_iter_1m_1comp_1type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_iter_1m_2comp_1type(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_iter_1m_4comp_1type(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_iter_10k_2comp_1types(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_iter_10k_2comp_2types(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_iter_10k_2comp_64types(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_iter_10k_2comp_256types(bench_t b, bench_result_t *b_out);

FLECS_BENCH_API void flecs_progress_0_sys_user_dt(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_progress_0_sys_auto_dt(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_progress_1_sys_user_dt(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_progress_4_sys_user_dt(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_progress_8_sys_user_dt(bench_t b, bench_result_t *b_out);
FLECS_BENCH_API void flecs_progress_16_sys_user_dt(bench_t b, bench_result_t *b_out);

#ifdef __cplusplus
}
#endif

#endif
