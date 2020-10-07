#include "ecs_benchmark.h"

int main(int argc, char *argv[]) {
    BENCH_HEADER ("Entity creation");
    BENCH_RUN    (flecs, new_id, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_id_recycle, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_w_entity, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, new_16_comp, 1000 * 1000, 100);
    BENCH_RUN_EX (flecs, bulk_new, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_new_recycle, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_new_1_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_new_4_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_new_8_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_new_16_comp, 1000 * 1000, 1, 100);

    BENCH_HEADER ("Entity deletion");
    BENCH_RUN    (flecs, delete, 1000 * 1000, 100);
    BENCH_RUN    (flecs, delete_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, delete_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, delete_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, delete_16_comp, 1000 * 1000, 100);
    BENCH_RUN_EX (flecs, bulk_delete_1_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_delete_4_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_delete_8_comp, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_delete_16_comp, 1000 * 1000, 1, 100);

    BENCH_HEADER ("Adding components");
    BENCH_RUN    (flecs, add_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_16_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_16_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_1_tag, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_4_tag, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_8_tag, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_to_16_tag, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_again, 1000 * 1000, 100);
    BENCH_RUN_EX (flecs, bulk_add_to_1, 1000 * 1000, 1, 100);
    BENCH_RUN_EX (flecs, bulk_add_to_16, 1000 * 1000, 1, 100);

    BENCH_HEADER ("Adding case tags");
    BENCH_RUN    (flecs, add_case_to_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_case_to_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_case_to_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_case_to_16_comp, 1000 * 1000, 100);

    BENCH_HEADER ("Removing components");
    BENCH_RUN    (flecs, remove_from_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, remove_from_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, remove_from_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, remove_from_16_comp, 1000 * 1000, 100);

    BENCH_HEADER ("Setting components");
    BENCH_RUN    (flecs, set, 1000 * 1000, 100);
    BENCH_RUN    (flecs, set_again, 1000 * 1000, 100);
    BENCH_RUN    (flecs, set_and_new, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_mut, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_mut_existing, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_mut_modified, 1000 * 1000, 100);

    BENCH_HEADER ("Instancing / Hierachies");
    BENCH_RUN    (flecs, add_instanceof, 1000 * 1000, 25);
    BENCH_RUN    (flecs, add_instanceof_override, 1000 * 1000, 25);
    BENCH_RUN    (flecs, override, 1000 * 1000, 25);
    BENCH_RUN    (flecs, add_childof, 1000 * 1000, 25);
    BENCH_RUN    (flecs, add_instanceof_w_child, 1000, 25);
    
    BENCH_HEADER ("Callbacks");
    BENCH_RUN    (flecs, set_w_on_set, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_w_trigger, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_w_monitor, 1000 * 1000, 100);
    BENCH_RUN    (flecs, add_w_ctor, 1000 * 1000, 100);
    BENCH_RUN    (flecs, remove_w_dtor, 1000 * 1000, 100);
    BENCH_RUN    (flecs, set_w_copy, 1000 * 1000, 100);

    BENCH_HEADER ("Getting components");
    BENCH_RUN    (flecs, get_from_single, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_from_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_from_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_from_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_from_16_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_ref_from_single, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_ref_from_1_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_ref_from_4_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_ref_from_8_comp, 1000 * 1000, 100);
    BENCH_RUN    (flecs, get_ref_from_16_comp, 1000 * 1000, 100);

    BENCH_HEADER ("Has component");
    BENCH_RUN    (flecs, has_for_1_comp, 1000 * 1000, 50);
    BENCH_RUN    (flecs, has_for_4_comp, 1000 * 1000, 50);
    BENCH_RUN    (flecs, has_for_8_comp, 1000 * 1000, 50);
    BENCH_RUN    (flecs, has_for_16_comp, 1000 * 1000, 50);

    BENCH_HEADER ("Misc");
    BENCH_RUN    (flecs, is_alive_for_alive, 1000 * 1000, 50);
    BENCH_RUN    (flecs, is_alive_for_deleted, 1000 * 1000, 50);
    BENCH_RUN    (flecs, is_alive_for_nonexist, 1000 * 1000, 50);
    BENCH_RUN    (flecs, get_type, 1000 * 1000, 50);
    BENCH_RUN    (flecs, init_world, 1, 50);
    BENCH_RUN    (flecs, init_mini_world, 1, 50);

    BENCH_HEADER ("Iterate single type");
    BENCH_RUN    (flecs, iter_1m_1comp_1type, 1, 100);
    BENCH_RUN    (flecs, iter_1m_2comp_1type, 1, 100);
    BENCH_RUN    (flecs, iter_1m_4comp_1type, 1, 100);

    BENCH_HEADER ("Iterate multiple type");
    BENCH_RUN    (flecs, iter_10k_2comp_1types, 100, 50);
    BENCH_RUN    (flecs, iter_10k_2comp_2types, 100, 50);
    BENCH_RUN    (flecs, iter_10k_2comp_64types, 100, 50);
    BENCH_RUN    (flecs, iter_10k_2comp_256types, 100, 50);

    BENCH_HEADER ("World progress");
    BENCH_RUN    (flecs, progress_0_sys_user_dt, 1000 * 1000, 20);
    BENCH_RUN    (flecs, progress_0_sys_auto_dt, 1000 * 1000, 20);
    BENCH_RUN    (flecs, progress_1_sys_user_dt, 1000 * 1000, 20);
    BENCH_RUN    (flecs, progress_4_sys_user_dt, 1000 * 1000, 20);
    BENCH_RUN    (flecs, progress_8_sys_user_dt, 1000 * 1000, 20);
    BENCH_RUN    (flecs, progress_16_sys_user_dt, 1000 * 1000, 20);
}
