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
Benchmarks were measured on a MacBook Pro M1 from 2021, with 64GB RAM

Release: https://github.com/SanderMertens/flecs/releases/tag/v4.0.1

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                             | Measurement  |
|---------------------------------------|--------------|
| baseline                              | 0.65ns       |
| world_mini_fini                       | 310.54us     |
| world_init_fini                       | 1.02ms       |
| has_empty_entity                      | 1.93ns       |
| has_id_not_found                      | 2.26ns       |
| has_id                                | 1.93ns       |
| has_16_ids                            | 1.97ns       |
| owns_empty_entity                     | 1.61ns       |
| owns_id_not_found                     | 1.62ns       |
| owns_id                               | 1.63ns       |
| owns_16_ids                           | 1.66ns       |
| get_empty_entity                      | 1.61ns       |
| get_id_not_found                      | 2.25ns       |
| get_id                                | 1.83ns       |
| get_16_ids                            | 1.88ns       |
| get_pair                              | 4.92ns       |
| get_pair_16_targets                   | 5.12ns       |
| get_inherited_depth_1                 | 20.95ns      |
| get_inherited_depth_2                 | 32.55ns      |
| get_inherited_depth_16                | 261.40ns     |
| get_inherited_depth_32                | 559.80ns     |
| get_mut_empty_entity                  | 1.61ns       |
| get_mut_id_not_found                  | 1.61ns       |
| get_mut_id                            | 1.61ns       |
| get_mut_16_ids                        | 1.65ns       |
| ensure_id                             | 5.14ns       |
| ensure_16_ids                         | 5.18ns       |
| set_id                                | 9.63ns       |
| set_16_ids                            | 10.09ns      |
| ensure_remove_id                      | 19.13ns      |
| ensure_remove_16_ids                  | 70.12ns      |
| ensure_remove_32_ids                  | 109.46ns     |
| ref_init                              | 3.22ns       |
| ref_get                               | 0.81ns       |
| add_remove_1_tag                      | 16.49ns      |
| add_remove_2_tags                     | 21.03ns      |
| add_remove_16_tags                    | 25.25ns      |
| add_remove_32_tags                    | 25.24ns      |
| add_remove_1_component                | 16.63ns      |
| add_remove_2_components               | 23.26ns      |
| add_remove_16_components              | 68.18ns      |
| add_remove_32_components              | 104.67ns     |
| add_existing_1_tag                    | 7.31ns       |
| add_existing_16_tags                  | 7.65ns       |
| add_existing_1_component              | 7.28ns       |
| add_existing_16_components            | 7.48ns       |
| add_remove_tag_to_1_component         | 28.04ns      |
| add_remove_tag_to_4_components        | 46.24ns      |
| add_remove_tag_to_8_components        | 71.32ns      |
| add_remove_tag_to_16_components       | 133.62ns     |
| add_remove_tag_to_64_components       | 437.59ns     |
| add_remove_override_1                 | 54.62ns      |
| add_remove_override_2                 | 58.59ns      |
| add_remove_override_4                 | 66.87ns      |
| add_remove_override_16                | 104.40ns     |
| add_remove_cmd_1_tag                  | 21.72ns      |
| add_remove_cmd_2_tags                 | 21.24ns      |
| add_remove_cmd_16_tags                | 17.42ns      |
| add_remove_cmd_32_tags                | 16.54ns      |
| add_remove_cmd_1_components           | 23.07ns      |
| add_remove_cmd_2_components           | 23.68ns      |
| add_remove_cmd_16_components          | 19.38ns      |
| add_remove_cmd_32_components          | 18.26ns      |
| ensure_cmd_1                          | 19.79ns      |
| ensure_cmd_2                          | 20.89ns      |
| ensure_cmd_16                         | 18.63ns      |
| ensure_cmd_32                         | 18.30ns      |
| set_cmd_1                             | 32.52ns      |
| set_cmd_2                             | 34.12ns      |
| set_cmd_16                            | 32.92ns      |
| set_cmd_32                            | 32.16ns      |
| ensure_remove_cmd_1                   | 28.05ns      |
| ensure_remove_cmd_2                   | 29.83ns      |
| ensure_remove_cmd_16                  | 25.18ns      |
| ensure_remove_cmd_32                  | 24.07ns      |
| add_remove_hooks_1                    | 18.70ns      |
| add_remove_hooks_2                    | 29.24ns      |
| add_remove_hooks_16                   | 97.99ns      |
| add_remove_hooks_32                   | 163.43ns     |
| create_100_w_add_in_observer          | 114.67ns     |
| create_1k_w_add_in_observer           | 116.79ns     |
| create_10k_w_add_in_observer          | 116.62ns     |
| create_50k_w_add_in_observer          | 115.99ns     |
| create_delete_empty                   | 3.95ns       |
| create_delete_1_tag                   | 11.14ns      |
| create_delete_2_tags                  | 14.65ns      |
| create_delete_16_tags                 | 22.60ns      |
| create_delete_1_component             | 11.08ns      |
| create_delete_2_components            | 15.46ns      |
| create_delete_16_components           | 56.64ns      |
| entity_init_delete                    | 12.47us      |
| entity_init_w_name_delete             | 12.63us      |
| create_children_w_reachable           | 622.01ns     |
| create_delete_tree_w1_d1              | 772.73ns     |
| create_delete_tree_w1_d10             | 4.92us       |
| create_delete_tree_w1_d100            | 53.43us      |
| create_delete_tree_w1_d1000           | 567.39us     |
| create_delete_tree_w10_d1             | 102.67ns     |
| create_delete_tree_w10_d10            | 762.05ns     |
| create_delete_tree_w10_d100           | 8.23us       |
| create_delete_tree_w10_d1000          | 80.78us      |
| create_delete_tree_w100_d1            | 30.02ns      |
| create_delete_tree_w100_d10           | 290.76ns     |
| create_delete_tree_w100_d100          | 3.06us       |
| create_delete_tree_w100_d1000         | 31.17us      |
| create_delete_tree_w1000_d1           | 22.20ns      |
| create_delete_tree_w1000_d10          | 241.42ns     |
| create_delete_tree_w1000_d100         | 2.42us       |
| create_delete_tree_w1000_d1000        | 26.80us      |
| instantiate_delete_tree_w0_d0         | 117.65ns     |
| instantiate_delete_tree_w1_d1         | 620.96ns     |
| instantiate_delete_tree_w5_d1         | 1.17us       |
| instantiate_delete_tree_w10_d1        | 3.05us       |
| instantiate_delete_tree_w50_d1        | 3.07us       |
| instantiate_delete_tree_w1_d2         | 1.01us       |
| instantiate_delete_tree_w5_d2         | 3.38us       |
| instantiate_delete_tree_w10_d2        | 7.05us       |
| instantiate_delete_tree_w50_d2        | 6.10us       |
| change_parent                         | 25.23ns      |
| change_parent_root                    | 16.59ns      |
| change_parent_w_name                  | 100.29ns     |
| lookup_depth_0                        | 42.36ns      |
| lookup_depth_1                        | 72.47ns      |
| lookup_depth_10                       | 357.07ns     |
| lookup_depth_100                      | 3.12us       |
| set_name                              | 85.01ns      |
| emit_0_observers                      | 29.54ns      |
| emit_1_observer                       | 39.63ns      |
| emit_10_observers                     | 102.60ns     |
| emit_100_observers                    | 755.66ns     |
| emit_propagate_depth_1                | 28.83ns      |
| emit_propagate_depth_10               | 232.94ns     |
| emit_propagate_depth_100              | 2.81us       |
| emit_propagate_depth_1000             | 44.65us      |
| emit_forward_1_ids_depth_1            | 171.74ns     |
| emit_forward_1_ids_depth_1000         | 150.75ns     |
| emit_forward_16_ids_depth_1           | 858.81ns     |
| emit_forward_16_ids_depth_1000        | 867.15ns     |
| modified_0_observers                  | 9.19ns       |
| modified_1_observer                   | 41.50ns      |
| modified_10_observers                 | 98.41ns      |
| modified_100_observers                | 764.40ns     |
| uncached_simple_iter_self_1_tags      | 6.21us       |
| uncached_simple_iter_self_8_tags      | 6.26us       |
| uncached_simple_iter_self_1_component | 6.23us       |
| uncached_simple_iter_self_8_components | 6.28us      |
| uncached_simple_iter_1_tags           | 6.28us       |
| uncached_simple_iter_8_tags           | 6.44us       |
| uncached_simple_iter_1_component      | 6.29us       |
| uncached_simple_iter_8_components     | 6.36us       |
| uncached_init_fini_1_ids              | 73.15ns      |
| uncached_init_fini_4_ids              | 88.56ns      |
| uncached_init_fini_8_ids              | 106.40ns     |
| uncached_init_fini_16_ids             | 148.51ns     |
| uncached_iter_8_tags_1_term           | 6.07us       |
| uncached_iter_8_tags_4_terms          | 880.21ns     |
| uncached_iter_16_tags_1_term          | 855.90us     |
| uncached_iter_16_tags_4_terms         | 1.22ms       |
| uncached_iter_8_components_1_term     | 6.22us       |
| uncached_iter_8_components_4_terms    | 934.34ns     |
| uncached_iter_16_components_1_term    | 909.12us     |
| uncached_iter_16_components_4_terms   | 1.22ms       |
| uncached_iter_up_8_tags               | 2.18ms       |
| uncached_iter_up_8_tags_w_self        | 2.05ms       |
| uncached_iter_up_w_mut_8_tags         | 2.17ms       |
| uncached_iter_up_w_mut_8_tags_w_self  | 2.06ms       |
| uncached_inherit_depth_1_tables_1     | 6.39us       |
| uncached_inherit_depth_1_tables_1024  | 30.83us      |
| uncached_inherit_depth_2_tables_1     | 6.45us       |
| uncached_inherit_depth_2_tables_1024  | 31.60us      |
| uncached_inherit_depth_8_tables_1     | 6.84us       |
| uncached_inherit_depth_8_tables_1024  | 32.05us      |
| uncached_inherit_depth_16_tables_1    | 7.39us       |
| uncached_inherit_depth_16_tables_1024 | 32.45us      |
| query_init_fini_1_ids                 | 757.53ns     |
| query_init_fini_4_ids                 | 1.07us       |
| query_init_fini_8_ids                 | 1.22us       |
| query_init_fini_16_ids                | 1.57us       |
| query_iter_1_table_1_tag              | 6.21us       |
| query_iter_2_tables_1_tag             | 6.29us       |
| query_iter_4_tables_1_tag             | 6.46us       |
| query_iter_8_tables_1_tag             | 6.78us       |
| query_iter_16_tables_1_tag            | 7.34us       |
| query_iter_32_tables_1_tag            | 7.12us       |
| query_iter_64_tables_1_tag            | 7.38us       |
| query_iter_128_tables_1_tag           | 8.65us       |
| query_iter_256_tables_1_tag           | 9.77us       |
| query_iter_512_tables_1_tag           | 11.88us      |
| query_iter_1024_tables_1_tag          | 18.74us      |
| query_iter_4096_tables_1_tag          | 34.45us      |
| query_iter_4096_tables_4_tags         | 34.53us      |
| query_iter_4096_tables_4_comps        | 37.97us      |
| query_iter_4096_tables_8_tags         | 34.48us      |
| query_iter_4096_tables_8_comps        | 37.87us      |
| query_iter_65536_tables_4_tags        | 739.75us     |
| query_iter_65536_tables_4_comps       | 919.78us     |
| query_iter_65536_tables_8_tags        | 730.13us     |
| query_iter_65536_tables_8_comps       | 926.96us     |
| query_iter_255_empty_1_fill           | 38.05ns      |
| query_iter_1023_empty_1_fill          | 38.01ns      |
| query_iter_rnd_8_tags                 | 11.30us      |
| query_iter_rnd_16_tags                | 849.95us     |
| progress_0_systems                    | 189.20ns     |
| progress_1_system                     | 288.45ns     |
| progress_10_systems                   | 701.03ns     |
| progress_100_systems                  | 5.11us       |
| create_delete_table_1_id              | 128.73ns     |
| create_delete_table_10_ids            | 220.46ns     |
| create_delete_table_100_ids           | 1.19us       |
| create_delete_table_1000_ids          | 15.48us      |
| match_table_1_of_10_queries           | 226.65ns     |
| match_table_5_of_10_queries           | 413.22ns     |
| match_table_10_of_10_queries          | 644.53ns     |
| match_table_1_of_100_queries          | 227.46ns     |
| match_table_10_of_100_queries         | 648.06ns     |
| match_table_50_of_100_queries         | 2.86us       |
| match_table_100_of_100_queries        | 6.43us       |
| match_table_1_of_1000_queries         | 226.16ns     |
| match_table_10_of_1000_queries        | 645.13ns     |
| match_table_100_of_1000_queries       | 6.53us       |
| match_table_1000_of_1000_queries      | 72.78us      |
| rematch_1_of_1000_tables              | 31.44us      |
| rematch_10_of_1000_tables             | 32.13us      |
| rematch_100_of_1000_tables            | 31.30us      |
| rematch_1000_of_1000_tables           | 25.87us      |
| fill_empty_table_0_queries            | 229.45ns     |
| fill_empty_table_1_query              | 291.69ns     |
| fill_empty_table_10_queries           | 548.58ns     |
| fill_empty_table_100_queries          | 4.58us       |
| fill_empty_table_1000_queries         | 55.08us      |
| table_add_remove_1_id                 | 2.55ns       |
| table_add_remove_4_ids                | 3.00ns       |
| table_add_remove_16_ids               | 4.12ns       |
| table_add_remove_32_ids               | 4.57ns       |
| table_add_remove_64_ids               | 4.82ns       |
