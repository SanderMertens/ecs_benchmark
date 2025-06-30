# Flecs benchmarks
Keep the following in mind when interpreting the benchmarks:
- The measurements represent avg/operation, except where this doesn't make sense. For example, the reported time for an `add_remove_16_tags` benchmark should be read as `(add_time + remove_time) / (2 * 16)`.
- Each benchmark runs for a fixed amount of time, and counts how often the benchmarked operations ran in that time.
- The purpose of these benchmarks is to track performance regressions, and to enable others to write and test performance optimizations for Flecs. They intentionally measure as little as possible, and do not reflect real-life scenarios.
- The filter/query iterator tests are evaluated against a dataset with 2^N tables, where N is the reported number of tags/components. The tables are created by randomly adding N components to entities.

## Usage
Use these commands to run the benchmarks:
```bash
# Recursively clean benchmark project and flecs dependency
bake clean -r

# Run benchmarks with optimizations enabled
bake run --cfg release
```

Flecs can be found here:
https://github.com/SanderMertens/flecs

Installation instructions for bake can be found here:
https://github.com/SanderMertens/bake

## Environment
Benchmarks were measured on a MacBook Pro M4 from 2024, with 48GB RAM

Release: https://github.com/SanderMertens/flecs/releases/tag/v4.1.0

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                             | Measurement  |
|---------------------------------------|--------------|
| baseline                              | 0.49ns       |
| has_not_found                         | 0.61ns       |
| has                                   | 0.64ns       |
| owns_not_found                        | 0.56ns       |
| owns                                  | 0.57ns       |
| get_id_not_found                      | 0.53ns       |
| get                                   | 0.57ns       |
| get_pair                              | 1.86ns       |
| get_inherited_depth_1                 | 10.93ns      |
| get_inherited_depth_2                 | 17.26ns      |
| get_inherited_depth_16                | 141.58ns     |
| get_mut_not_found                     | 0.50ns       |
| get_mut                               | 0.51ns       |
| get_mut_sparse                        | 2.06ns       |
| get_mut_dont_fragment                 | 1.99ns       |
| get_sparse_not_found                  | 0.35ns       |
| get_sparse                            | 0.20ns       |
| get_target_not_found                  | 1.94ns       |
| get_target                            | 3.68ns       |
| get_target_dont_fragment              | 3.41ns       |
| get_target_dont_fragment_exclusive    | 3.94ns       |
| get_parent_not_found                  | 1.69ns       |
| get_parent                            | 2.11ns       |
| add_remove_1_tags                     | 15.37ns      |
| add_remove_2_tags                     | 17.25ns      |
| add_remove_16_tags                    | 17.69ns      |
| add_remove_32_tags                    | 16.85ns      |
| ensure                                | 4.19ns       |
| set_id                                | 9.42ns       |
| ensure_remove                         | 17.87ns      |
| ensure_remove_16                      | 45.72ns      |
| ensure_remove_32                      | 75.68ns      |
| ref_init                              | 3.53ns       |
| ref_get                               | 0.29ns       |
| add_remove_cmd_1_tag                  | 20.92ns      |
| add_remove_cmd_2_tags                 | 20.13ns      |
| add_remove_cmd_16_tags                | 13.90ns      |
| add_remove_cmd_32_tags                | 13.69ns      |
| add_remove_cmd_1_components           | 21.96ns      |
| add_remove_cmd_2_components           | 20.96ns      |
| add_remove_cmd_16_components          | 14.21ns      |
| add_remove_cmd_32_components          | 13.97ns      |
| ensure_cmd_1                          | 13.08ns      |
| ensure_cmd_2                          | 15.52ns      |
| ensure_cmd_16                         | 13.79ns      |
| ensure_cmd_32                         | 13.41ns      |
| set_cmd_1                             | 20.95ns      |
| set_cmd_2                             | 24.22ns      |
| set_cmd_16                            | 22.83ns      |
| set_cmd_32                            | 22.30ns      |
| ensure_remove_cmd_1                   | 25.65ns      |
| ensure_remove_cmd_2                   | 25.11ns      |
| ensure_remove_cmd_16                  | 20.41ns      |
| ensure_remove_cmd_32                  | 20.73ns      |
| create_100_w_add_in_observer          | 84.79ns      |
| create_1k_w_add_in_observer           | 84.32ns      |
| create_10k_w_add_in_observer          | 85.11ns      |
| create_50k_w_add_in_observer          | 84.44ns      |
| create_delete_empty                   | 6.42ns       |
| create_delete_1_tag                   | 10.28ns      |
| create_delete_2_tags                  | 10.73ns      |
| create_delete_16_tags                 | 14.40ns      |
| create_delete_1_component             | 9.67ns       |
| create_delete_2_components            | 11.33ns      |
| create_delete_16_components           | 36.31ns      |
| entity_init_delete                    | 14.84us      |
| entity_init_w_name_delete             | 15.25us      |
| create_children_w_reachable           | 427.18ns     |
| create_delete_tree_w1_d1              | 298.51ns     |
| create_delete_tree_w1_d10             | 3.25us       |
| create_delete_tree_w1_d100            | 38.07us      |
| create_delete_tree_w10_d1             | 44.61ns      |
| create_delete_tree_w10_d10            | 511.14ns     |
| create_delete_tree_w10_d100           | 5.68us       |
| create_delete_tree_w100_d1            | 16.48ns      |
| create_delete_tree_w100_d10           | 191.97ns     |
| create_delete_tree_w100_d100          | 2.04us       |
| instantiate_delete_tree_w0_d0         | 52.35ns      |
| instantiate_delete_tree_w1_d1         | 254.71ns     |
| instantiate_delete_tree_w5_d1         | 629.90ns     |
| instantiate_delete_tree_w10_d1        | 1.89us       |
| instantiate_delete_tree_w50_d1        | 1.90us       |
| instantiate_delete_tree_w1_d2         | 504.28ns     |
| instantiate_delete_tree_w5_d2         | 2.04us       |
| instantiate_delete_tree_w10_d2        | 3.86us       |
| instantiate_delete_tree_w50_d2        | 3.85us       |
| change_parent                         | 17.90ns      |
| change_parent_root                    | 17.03ns      |
| change_parent_w_name                  | 81.02ns      |
| lookup_depth_0                        | 28.12ns      |
| lookup_depth_1                        | 50.34ns      |
| lookup_depth_10                       | 244.11ns     |
| lookup_depth_100                      | 2.27us       |
| set_name                              | 64.96ns      |
| emit_0_observers                      | 21.09ns      |
| emit_1_observer                       | 27.16ns      |
| emit_10_observers                     | 58.16ns      |
| emit_50_observers                     | 171.41ns     |
| emit_multi_2_100_observers            | 1.69us       |
| emit_multi_4_100_observers            | 647.84ns     |
| emit_multi_8_100_observers            | 338.59ns     |
| emit_propagate_depth_1                | 23.35ns      |
| emit_propagate_depth_10               | 131.73ns     |
| emit_propagate_depth_100              | 1.69us       |
| emit_forward_1_ids_depth_1            | 107.29ns     |
| emit_forward_1_ids_depth_1000         | 106.11ns     |
| emit_forward_16_ids_depth_1           | 624.75ns     |
| emit_forward_16_ids_depth_1000        | 640.56ns     |
| modified_0_observers                  | 6.29ns       |
| modified_1_observer                   | 29.33ns      |
| modified_10_observers                 | 56.00ns      |
| modified_100_observers                | 313.85ns     |
| uncach_init_fini_1_ids                | 51.58ns      |
| uncach_init_fini_4_ids                | 61.23ns      |
| uncach_init_fini_8_ids                | 78.88ns      |
| uncach_init_fini_16_ids               | 114.94ns     |
| uncach_6_tags_1_term                  | 3.31us       |
| uncach_6_tags_4_terms                 | 306.07ns     |
| uncach_10_tags_1_term                 | 6.59us       |
| uncach_10_tags_4_terms                | 3.19us       |
| uncach_10_tags_8_terms                | 2.22us       |
| uncach_6_comps_1_term                 | 3.34us       |
| uncach_6_comps_4_terms                | 306.19ns     |
| uncach_10_comps_1_term                | 7.84us       |
| uncach_10_comps_4_terms               | 4.13us       |
| uncach_10_comps_8_terms               | 2.52us       |
| uncach_10_sparse_tags_4_terms         | 14.76us      |
| uncach_10_sparse_comps_4_terms        | 56.51us      |
| uncach_10_nofrag_tags_4_terms         | 1.24ms       |
| uncach_10_nofrag_comps_4_terms        | 1.27ms       |
| uncach_255_empty_1_fill               | 235.89ns     |
| uncach_1023_empty_1_fill              | 2.13us       |
| uncach_up_tags                        | 1.63ms       |
| uncach_up_tags_w_self                 | 2.66ms       |
| uncach_up_w_mut_8_tags                | 937.05us     |
| uncach_up_w_mut_8_tags_w_self         | 864.43us     |
| uncach_w_vars                         | 718.68us     |
| uncach_w_singleton                    | 338.95ns     |
| uncach_w_not                          | 439.42ns     |
| uncach_w_optional                     | 628.48ns     |
| uncach_inherit_depth_1_tables_1       | 4.58us       |
| uncach_inherit_depth_1_tables_1024    | 22.30us      |
| uncach_inherit_depth_2_tables_1       | 4.59us       |
| uncach_inherit_depth_2_tables_1024    | 21.78us      |
| uncach_inherit_depth_8_tables_1       | 4.91us       |
| uncach_inherit_depth_8_tables_1024    | 22.10us      |
| uncach_inherit_depth_16_tables_1      | 5.29us       |
| uncach_inherit_depth_16_tables_1024   | 22.42us      |
| cached_init_fini_1_ids                | 352.19ns     |
| cached_init_fini_4_ids                | 507.92ns     |
| cached_init_fini_8_ids                | 573.92ns     |
| cached_init_fini_16_ids               | 717.34ns     |
| cached_6_tags_1_term                  | 3.18us       |
| cached_6_tags_4_terms                 | 207.57ns     |
| cached_8_tags_1_term                  | 3.63us       |
| cached_8_tags_4_terms                 | 250.85ns     |
| cached_10_tags_1_term                 | 5.39us       |
| cached_10_tags_4_terms                | 562.78ns     |
| cached_10_tags_8_terms                | 49.27ns      |
| cached_16_tags_1_term                 | 170.17us     |
| cached_16_tags_4_terms                | 12.78us      |
| cached_16_tags_8_terms                | 604.24ns     |
| cached_6_components_1_term            | 3.26us       |
| cached_6_components_4_terms           | 212.23ns     |
| cached_8_components_1_term            | 3.91us       |
| cached_8_components_4_terms           | 274.65ns     |
| cached_10_components_1_term           | 6.26us       |
| cached_10_components_4_terms          | 644.59ns     |
| cached_10_components_8_terms          | 62.42ns      |
| cached_16_components_1_term           | 205.12us     |
| cached_16_components_4_terms          | 21.64us      |
| cached_16_components_8_terms          | 1.17us       |
| cached_6_read_1_term                  | 4.21us       |
| cached_6_read_4_terms                 | 588.87ns     |
| cached_8_read_1_term                  | 5.37us       |
| cached_8_read_4_terms                 | 827.61ns     |
| cached_10_read_1_term                 | 8.69us       |
| cached_10_read_4_terms                | 1.66us       |
| cached_10_read_8_terms                | 122.75ns     |
| cached_16_read_1_term                 | 191.92us     |
| cached_16_read_4_terms                | 21.19us      |
| cached_16_read_8_terms                | 1.03us       |
| cached_10_sparse_4_terms              | 57.59us      |
| cached_10_nofrag_4_terms              | 1.30ms       |
| cached_255_empty_1_fill               | 168.63ns     |
| cached_1023_empty_1_fill              | 653.37ns     |
| cached_up_tags                        | 332.62us     |
| cached_up_tags_w_self                 | 295.84us     |
| cached_w_vars                         | 725.26us     |
| cached_w_singleton                    | 325.03ns     |
| cached_w_not                          | 102.64ns     |
| cached_w_optional                     | 318.98ns     |
| cached_cantoggle_no_toggle_1_term     | 125.20ns     |
| cached_cantoggle_no_toggle_4_terms    | 126.40ns     |
| cached_cantoggle_no_toggle_8_terms    | 135.40ns     |
| cached_cantoggle_half_toggle_1_term   | 302.04ns     |
| cached_cantoggle_half_toggle_4_terms  | 384.05ns     |
| cached_cantoggle_half_toggle_8_terms  | 570.63ns     |
| cached_cantoggle_alt_toggle_1_term    | 4.97us       |
| cached_cantoggle_alt_toggle_4_terms   | 5.02us       |
| cached_cantoggle_alt_toggle_8_terms   | 5.23us       |
| query_transform                       | 574.06us     |
| query_depth_first                     | 3.49ms       |
| match_1_of_100_queries_1_term         | 679.08ns     |
| match_10_of_100_queries_1_term        | 1.10us       |
| match_100_of_100_queries_1_term       | 5.21us       |
| match_1_of_100_queries_4_terms        | 796.77ns     |
| match_10_of_100_queries_4_terms       | 1.20us       |
| match_100_of_100_queries_4_terms      | 5.81us       |
| match_1_of_100_queries_8_terms        | 882.50ns     |
| match_10_of_100_queries_8_terms       | 1.30us       |
| match_100_of_100_queries_8_terms      | 6.29us       |
| rematch_1_of_1000_tables              | 3.97us       |
| rematch_10_of_1000_tables             | 3.86us       |
| rematch_100_of_1000_tables            | 3.45us       |
| rematch_1000_of_1000_tables           | 2.05us       |
| world_mini_fini                       | 83.98us      |
| world_init_fini                       | 534.83us     |
| progress_0_tasks                      | 154.69ns     |
| progress_1_tasks                      | 218.47ns     |
| progress_10_tasks                     | 445.68ns     |
| progress_100_tasks                    | 2.75us       |
| progress_0_systems                    | 153.79ns     |
| progress_1_systems                    | 673.82ns     |
| progress_10_systems                   | 3.82us       |
| progress_100_systems                  | 38.29us      |
| create_delete_table_1_id              | 101.37ns     |
| create_delete_table_10_ids            | 174.46ns     |
| create_delete_table_100_ids           | 988.90ns     |
| create_delete_table_1000_ids          | 11.41us      |
| cleanup_tables_0_empty                | 149.79us     |
| cleanup_tables_half_empty             | 1.41ms       |
| cleanup_tables_all_empty              | 2.58ms       |
| cleanup_tables_0_empty_w_budget       | 222.25us     |
| cleanup_tables_half_empty_w_budget    | 1.55ms       |
| cleanup_tables_all_empty_w_budget     | 2.66ms       |
