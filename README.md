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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.5

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 217.26us     |
| world_init_fini                     | 1.08ms       |
| has_empty_entity                    | 1.61ns       |
| has_id_not_found                    | 3.20ns       |
| has_id                              | 4.17ns       |
| has_16_ids                          | 4.49ns       |
| get_empty_entity                    | 1.61ns       |
| get_id_not_found                    | 3.85ns       |
| get_id                              | 3.55ns       |
| get_16_ids                          | 3.64ns       |
| get_pair                            | 4.72ns       |
| get_pair_16_targets                 | 4.84ns       |
| get_inherited_depth_1               | 19.04ns      |
| get_inherited_depth_2               | 30.44ns      |
| get_inherited_depth_16              | 229.87ns     |
| get_inherited_depth_32              | 471.61ns     |
| get_mut_id                          | 6.64ns       |
| get_mut_16_ids                      | 6.65ns       |
| set_id                              | 11.38ns      |
| set_16_ids                          | 11.87ns      |
| get_mut_remove_id                   | 19.49ns      |
| get_mut_remove_16_ids               | 68.06ns      |
| get_mut_remove_32_ids               | 115.31ns     |
| ref_init                            | 3.11ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 16.84ns      |
| add_remove_2_tags                   | 21.12ns      |
| add_remove_16_tags                  | 25.66ns      |
| add_remove_32_tags                  | 25.87ns      |
| add_remove_1_component              | 17.53ns      |
| add_remove_2_components             | 24.08ns      |
| add_remove_16_components            | 65.57ns      |
| add_remove_32_components            | 111.88ns     |
| add_existing_1_tag                  | 8.50ns       |
| add_existing_16_tags                | 8.89ns       |
| add_existing_1_component            | 8.53ns       |
| add_existing_16_components          | 9.04ns       |
| add_remove_tag_to_1_component       | 28.36ns      |
| add_remove_tag_to_4_components      | 47.16ns      |
| add_remove_tag_to_8_components      | 75.90ns      |
| add_remove_tag_to_16_components     | 131.16ns     |
| add_remove_tag_to_64_components     | 438.85ns     |
| add_remove_override_1               | 66.42ns      |
| add_remove_override_2               | 69.09ns      |
| add_remove_override_4               | 78.25ns      |
| add_remove_override_16              | 113.26ns     |
| add_remove_cmd_1_tag                | 23.64ns      |
| add_remove_cmd_2_tags               | 19.01ns      |
| add_remove_cmd_16_tags              | 14.68ns      |
| add_remove_cmd_32_tags              | 14.44ns      |
| add_remove_cmd_1_components         | 24.24ns      |
| add_remove_cmd_2_components         | 20.57ns      |
| add_remove_cmd_16_components        | 16.07ns      |
| add_remove_cmd_32_components        | 15.63ns      |
| get_mut_cmd_1                       | 22.27ns      |
| get_mut_cmd_2                       | 18.59ns      |
| get_mut_cmd_16                      | 15.47ns      |
| get_mut_cmd_32                      | 15.37ns      |
| set_cmd_1                           | 36.66ns      |
| set_cmd_2                           | 35.98ns      |
| set_cmd_16                          | 33.15ns      |
| set_cmd_32                          | 32.72ns      |
| get_mut_remove_cmd_1                | 30.02ns      |
| get_mut_remove_cmd_2                | 28.50ns      |
| get_mut_remove_cmd_16               | 24.04ns      |
| get_mut_remove_cmd_32               | 23.25ns      |
| add_remove_hooks_1                  | 20.29ns      |
| add_remove_hooks_2                  | 31.60ns      |
| add_remove_hooks_16                 | 95.58ns      |
| add_remove_hooks_32                 | 160.84ns     |
| create_delete_empty                 | 3.99ns       |
| create_delete_1_tag                 | 11.52ns      |
| create_delete_2_tags                | 15.02ns      |
| create_delete_16_tags               | 23.22ns      |
| create_delete_1_component           | 11.69ns      |
| create_delete_2_components          | 16.13ns      |
| create_delete_16_components         | 58.03ns      |
| entity_init_delete                  | 12.44us      |
| entity_init_w_name_delete           | 12.48us      |
| create_delete_tree_w1_d1            | 761.96ns     |
| create_delete_tree_w1_d10           | 4.95us       |
| create_delete_tree_w1_d100          | 52.64us      |
| create_delete_tree_w1_d1000         | 568.28us     |
| create_delete_tree_w10_d1           | 103.66ns     |
| create_delete_tree_w10_d10          | 779.02ns     |
| create_delete_tree_w10_d100         | 8.43us       |
| create_delete_tree_w10_d1000        | 83.34us      |
| create_delete_tree_w100_d1          | 31.50ns      |
| create_delete_tree_w100_d10         | 300.01ns     |
| create_delete_tree_w100_d100        | 3.17us       |
| create_delete_tree_w100_d1000       | 31.69us      |
| create_delete_tree_w1000_d1         | 23.54ns      |
| create_delete_tree_w1000_d10        | 245.28ns     |
| create_delete_tree_w1000_d100       | 2.46us       |
| create_delete_tree_w1000_d1000      | 26.99us      |
| change_parent                       | 25.86ns      |
| change_parent_root                  | 16.16ns      |
| change_parent_w_name                | 102.76us     |
| lookup_depth_0                      | 39.23ns      |
| lookup_depth_1                      | 69.09ns      |
| lookup_depth_10                     | 353.76ns     |
| lookup_depth_100                    | 3.34us       |
| set_name                            | 99.80ns      |
| emit_0_observers                    | 21.40ns      |
| emit_1_observer                     | 34.47ns      |
| emit_10_observers                   | 69.24ns      |
| emit_100_observers                  | 488.91ns     |
| emit_propagate_depth_1              | 28.50ns      |
| emit_propagate_depth_10             | 204.93ns     |
| emit_propagate_depth_100            | 2.38us       |
| emit_propagate_depth_1000           | 33.59us      |
| emit_forward_1_ids_depth_1          | 149.37ns     |
| emit_forward_1_ids_depth_1000       | 148.07ns     |
| emit_forward_16_ids_depth_1         | 758.56ns     |
| emit_forward_16_ids_depth_1000      | 745.47ns     |
| modified_0_observers                | 9.94ns       |
| modified_1_observer                 | 46.49ns      |
| modified_10_observers               | 81.29ns      |
| modified_100_observers              | 507.69ns     |
| filter_simple_iter_1_tags           | 6.14us       |
| filter_simple_iter_8_tags           | 6.26us       |
| filter_simple_iter_1_component      | 6.20us       |
| filter_simple_iter_8_components     | 6.33us       |
| filter_init_fini_1_ids              | 61.81ns      |
| filter_init_fini_8_ids              | 294.69ns     |
| filter_init_fini_16_ids             | 539.24ns     |
| filter_init_fini_inline_1_ids       | 54.89ns      |
| filter_init_fini_inline_8_ids       | 285.81ns     |
| filter_init_fini_inline_16_ids      | 532.31ns     |
| filter_iter_8_tags_1_term           | 6.95us       |
| filter_iter_8_tags_4_terms          | 5.14us       |
| filter_iter_16_tags_1_term          | 1.46ms       |
| filter_iter_16_tags_4_terms         | 2.42ms       |
| filter_iter_8_components_1_term     | 7.20us       |
| filter_iter_8_components_4_terms    | 5.38us       |
| filter_iter_16_components_1_term    | 1.84ms       |
| filter_iter_16_components_4_terms   | 2.74ms       |
| filter_iter_up_8_tags               | 6.83ms       |
| filter_iter_up_8_tags_w_self        | 6.44ms       |
| filter_iter_up_w_mut_8_tags         | 6.08ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.49ms       |
| rule_init_fini_1_ids                | 129.69ns     |
| rule_init_fini_8_ids                | 470.46ns     |
| rule_init_fini_16_ids               | 824.62ns     |
| rule_simple_iter_1_tags             | 6.27us       |
| rule_simple_iter_8_tags             | 6.29us       |
| rule_simple_iter_1_component        | 6.14us       |
| rule_simple_iter_8_component        | 6.40us       |
| rule_iter_8_tags_1_term             | 6.89us       |
| rule_iter_8_tags_4_terms            | 2.99us       |
| rule_iter_16_tags_1_term            | 1.12ms       |
| rule_iter_16_tags_4_terms           | 1.91ms       |
| rule_iter_8_components_1_term       | 7.12us       |
| rule_iter_8_components_4_terms      | 3.14us       |
| rule_iter_16_components_1_term      | 1.45ms       |
| rule_iter_16_components_4_terms     | 2.05ms       |
| rule_inherit_depth_1_tables_1       | 6.28us       |
| rule_inherit_depth_1_tables_1024    | 30.95us      |
| rule_inherit_depth_2_tables_1       | 6.35us       |
| rule_inherit_depth_2_tables_1024    | 31.30us      |
| rule_inherit_depth_8_tables_1       | 6.86us       |
| rule_inherit_depth_8_tables_1024    | 31.80us      |
| rule_inherit_depth_16_tables_1      | 7.25us       |
| rule_inherit_depth_16_tables_1024   | 31.67us      |
| query_init_fini_1_ids               | 683.89ns     |
| query_init_fini_8_ids               | 4.70us       |
| query_init_fini_16_ids              | 7.88us       |
| query_iter_1_table_1_tag            | 6.17us       |
| query_iter_2_tables_1_tag           | 6.30us       |
| query_iter_4_tables_1_tag           | 6.62us       |
| query_iter_8_tables_1_tag           | 7.01us       |
| query_iter_16_tables_1_tag          | 7.38us       |
| query_iter_32_tables_1_tag          | 7.62us       |
| query_iter_64_tables_1_tag          | 8.69us       |
| query_iter_128_tables_1_tag         | 9.77us       |
| query_iter_256_tables_1_tag         | 10.47us      |
| query_iter_512_tables_1_tag         | 12.97us      |
| query_iter_1024_tables_1_tag        | 17.35us      |
| query_iter_4096_tables_1_tag        | 35.63us      |
| query_iter_4096_tables_4_tags       | 35.86us      |
| query_iter_4096_tables_4_comps      | 82.81us      |
| query_iter_4096_tables_8_tags       | 35.91us      |
| query_iter_4096_tables_8_comps      | 82.08us      |
| query_iter_65536_tables_4_tags      | 841.00us     |
| query_iter_65536_tables_4_comps     | 1.79ms       |
| query_iter_65536_tables_8_tags      | 847.11us     |
| query_iter_65536_tables_8_comps     | 1.76ms       |
| query_iter_255_empty_1_fill         | 25.95ns      |
| query_iter_1023_empty_1_fill        | 25.90ns      |
| query_iter_rnd_8_tags               | 10.96us      |
| query_iter_rnd_16_tags              | 920.93us     |
| query_count_1_table                 | 2.79ns       |
| query_count_2_tables                | 3.09ns       |
| query_count_4_tables                | 4.00ns       |
| query_count_8_tables                | 6.13ns       |
| query_count_16_tables               | 11.99ns      |
| query_count_32_tables               | 26.89ns      |
| query_count_64_tables               | 61.08ns      |
| query_count_128_tables              | 144.19ns     |
| query_count_256_tables              | 281.62ns     |
| query_count_512_tables              | 999.63ns     |
| query_count_1024_tables             | 3.59us       |
| query_count_4096_tables             | 13.40us      |
| query_count_65536_tables            | 487.26us     |
| progress_0_systems                  | 141.53ns     |
| progress_1_system                   | 206.24ns     |
| progress_10_systems                 | 555.26ns     |
| progress_100_systems                | 3.87us       |
| create_delete_table_1_id            | 122.59ns     |
| create_delete_table_10_ids          | 205.72ns     |
| create_delete_table_100_ids         | 1.10us       |
| create_delete_table_1000_ids        | 14.79us      |
| match_table_1_of_10_queries         | 239.18ns     |
| match_table_5_of_10_queries         | 474.93ns     |
| match_table_10_of_10_queries        | 772.44ns     |
| match_table_1_of_100_queries        | 240.98ns     |
| match_table_10_of_100_queries       | 778.00ns     |
| match_table_50_of_100_queries       | 3.26us       |
| match_table_100_of_100_queries      | 7.40us       |
| match_table_1_of_1000_queries       | 240.66ns     |
| match_table_10_of_1000_queries      | 773.05ns     |
| match_table_100_of_1000_queries     | 7.50us       |
| match_table_1000_of_1000_queries    | 82.73us      |
| rematch_1_of_1000_tables            | 66.01us      |
| rematch_10_of_1000_tables           | 66.71us      |
| rematch_100_of_1000_tables          | 65.85us      |
| rematch_1000_of_1000_tables         | 46.45us      |
| fill_empty_table_0_queries          | 216.12ns     |
| fill_empty_table_1_query            | 379.03ns     |
| fill_empty_table_10_queries         | 607.95ns     |
| fill_empty_table_100_queries        | 3.36us       |
| fill_empty_table_1000_queries       | 41.85us      |
| table_add_remove_1_id               | 2.63ns       |
| table_add_remove_4_ids              | 2.83ns       |
| table_add_remove_16_ids             | 3.84ns       |
| table_add_remove_32_ids             | 4.18ns       |
| table_add_remove_64_ids             | 4.32ns       |
