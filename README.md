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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.8

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 232.48us     |
| world_init_fini                     | 998.84us     |
| has_empty_entity                    | 1.61ns       |
| has_id_not_found                    | 3.20ns       |
| has_id                              | 4.17ns       |
| has_16_ids                          | 4.51ns       |
| get_empty_entity                    | 1.61ns       |
| get_id_not_found                    | 4.17ns       |
| get_id                              | 3.41ns       |
| get_16_ids                          | 3.58ns       |
| get_pair                            | 4.64ns       |
| get_pair_16_targets                 | 4.71ns       |
| get_inherited_depth_1               | 19.36ns      |
| get_inherited_depth_2               | 31.65ns      |
| get_inherited_depth_16              | 234.53ns     |
| get_inherited_depth_32              | 514.91ns     |
| get_mut_id                          | 6.87ns       |
| get_mut_16_ids                      | 6.86ns       |
| set_id                              | 12.15ns      |
| set_16_ids                          | 13.17ns      |
| get_mut_remove_id                   | 18.23ns      |
| get_mut_remove_16_ids               | 69.34ns      |
| get_mut_remove_32_ids               | 116.48ns     |
| ref_init                            | 3.13ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 16.07ns      |
| add_remove_2_tags                   | 20.42ns      |
| add_remove_16_tags                  | 24.62ns      |
| add_remove_32_tags                  | 24.71ns      |
| add_remove_1_component              | 16.72ns      |
| add_remove_2_components             | 22.75ns      |
| add_remove_16_components            | 66.44ns      |
| add_remove_32_components            | 114.05ns     |
| add_existing_1_tag                  | 6.69ns       |
| add_existing_16_tags                | 7.08ns       |
| add_existing_1_component            | 6.69ns       |
| add_existing_16_components          | 7.03ns       |
| add_remove_tag_to_1_component       | 26.96ns      |
| add_remove_tag_to_4_components      | 47.09ns      |
| add_remove_tag_to_8_components      | 74.32ns      |
| add_remove_tag_to_16_components     | 133.24ns     |
| add_remove_tag_to_64_components     | 440.34ns     |
| add_remove_override_1               | 63.64ns      |
| add_remove_override_2               | 66.31ns      |
| add_remove_override_4               | 75.64ns      |
| add_remove_override_16              | 112.94ns     |
| add_remove_cmd_1_tag                | 23.70ns      |
| add_remove_cmd_2_tags               | 18.68ns      |
| add_remove_cmd_16_tags              | 14.13ns      |
| add_remove_cmd_32_tags              | 13.81ns      |
| add_remove_cmd_1_components         | 24.64ns      |
| add_remove_cmd_2_components         | 20.26ns      |
| add_remove_cmd_16_components        | 15.35ns      |
| add_remove_cmd_32_components        | 15.04ns      |
| get_mut_cmd_1                       | 21.28ns      |
| get_mut_cmd_2                       | 19.10ns      |
| get_mut_cmd_16                      | 16.12ns      |
| get_mut_cmd_32                      | 15.81ns      |
| set_cmd_1                           | 35.35ns      |
| set_cmd_2                           | 35.73ns      |
| set_cmd_16                          | 32.95ns      |
| set_cmd_32                          | 33.56ns      |
| get_mut_remove_cmd_1                | 30.74ns      |
| get_mut_remove_cmd_2                | 29.23ns      |
| get_mut_remove_cmd_16               | 23.88ns      |
| get_mut_remove_cmd_32               | 23.18ns      |
| add_remove_hooks_1                  | 19.61ns      |
| add_remove_hooks_2                  | 30.44ns      |
| add_remove_hooks_16                 | 94.41ns      |
| add_remove_hooks_32                 | 161.50ns     |
| create_delete_empty                 | 3.92ns       |
| create_delete_1_tag                 | 11.20ns      |
| create_delete_2_tags                | 14.34ns      |
| create_delete_16_tags               | 22.46ns      |
| create_delete_1_component           | 11.50ns      |
| create_delete_2_components          | 15.62ns      |
| create_delete_16_components         | 58.58ns      |
| entity_init_delete                  | 12.39us      |
| entity_init_w_name_delete           | 12.38us      |
| create_delete_tree_w1_d1            | 755.50ns     |
| create_delete_tree_w1_d10           | 4.98us       |
| create_delete_tree_w1_d100          | 52.61us      |
| create_delete_tree_w1_d1000         | 568.67us     |
| create_delete_tree_w10_d1           | 102.33ns     |
| create_delete_tree_w10_d10          | 792.20ns     |
| create_delete_tree_w10_d100         | 8.25us       |
| create_delete_tree_w10_d1000        | 82.24us      |
| create_delete_tree_w100_d1          | 31.19ns      |
| create_delete_tree_w100_d10         | 298.97ns     |
| create_delete_tree_w100_d100        | 3.08us       |
| create_delete_tree_w100_d1000       | 31.07us      |
| create_delete_tree_w1000_d1         | 23.19ns      |
| create_delete_tree_w1000_d10        | 241.32ns     |
| create_delete_tree_w1000_d100       | 2.44us       |
| create_delete_tree_w1000_d1000      | 26.78us      |
| change_parent                       | 24.27ns      |
| change_parent_root                  | 15.96ns      |
| change_parent_w_name                | 99.10us      |
| lookup_depth_0                      | 39.79ns      |
| lookup_depth_1                      | 69.41ns      |
| lookup_depth_10                     | 353.85ns     |
| lookup_depth_100                    | 3.41us       |
| set_name                            | 96.95ns      |
| emit_0_observers                    | 21.41ns      |
| emit_1_observer                     | 35.22ns      |
| emit_10_observers                   | 69.70ns      |
| emit_100_observers                  | 493.41ns     |
| emit_propagate_depth_1              | 29.20ns      |
| emit_propagate_depth_10             | 219.50ns     |
| emit_propagate_depth_100            | 2.46us       |
| emit_propagate_depth_1000           | 33.77us      |
| emit_forward_1_ids_depth_1          | 148.92ns     |
| emit_forward_1_ids_depth_1000       | 147.35ns     |
| emit_forward_16_ids_depth_1         | 748.15ns     |
| emit_forward_16_ids_depth_1000      | 771.02ns     |
| modified_0_observers                | 9.56ns       |
| modified_1_observer                 | 47.78ns      |
| modified_10_observers               | 83.09ns      |
| modified_100_observers              | 504.52ns     |
| filter_simple_iter_1_tags           | 6.18us       |
| filter_simple_iter_8_tags           | 6.23us       |
| filter_simple_iter_1_component      | 6.25us       |
| filter_simple_iter_8_components     | 6.26us       |
| filter_init_fini_1_ids              | 60.41ns      |
| filter_init_fini_8_ids              | 290.72ns     |
| filter_init_fini_16_ids             | 539.70ns     |
| filter_init_fini_inline_1_ids       | 54.16ns      |
| filter_init_fini_inline_8_ids       | 284.48ns     |
| filter_init_fini_inline_16_ids      | 533.63ns     |
| filter_iter_8_tags_1_term           | 6.86us       |
| filter_iter_8_tags_4_terms          | 4.67us       |
| filter_iter_16_tags_1_term          | 1.33ms       |
| filter_iter_16_tags_4_terms         | 2.33ms       |
| filter_iter_8_components_1_term     | 7.01us       |
| filter_iter_8_components_4_terms    | 4.94us       |
| filter_iter_16_components_1_term    | 1.62ms       |
| filter_iter_16_components_4_terms   | 2.48ms       |
| filter_iter_up_8_tags               | 5.96ms       |
| filter_iter_up_8_tags_w_self        | 6.11ms       |
| filter_iter_up_w_mut_8_tags         | 5.96ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.13ms       |
| rule_init_fini_1_ids                | 126.15ns     |
| rule_init_fini_8_ids                | 471.54ns     |
| rule_init_fini_16_ids               | 843.88ns     |
| rule_simple_iter_1_tags             | 6.22us       |
| rule_simple_iter_8_tags             | 6.29us       |
| rule_simple_iter_1_component        | 6.17us       |
| rule_simple_iter_8_component        | 6.28us       |
| rule_iter_8_tags_1_term             | 6.89us       |
| rule_iter_8_tags_4_terms            | 2.99us       |
| rule_iter_16_tags_1_term            | 991.31us     |
| rule_iter_16_tags_4_terms           | 1.80ms       |
| rule_iter_8_components_1_term       | 7.11us       |
| rule_iter_8_components_4_terms      | 3.13us       |
| rule_iter_16_components_1_term      | 1.43ms       |
| rule_iter_16_components_4_terms     | 2.01ms       |
| rule_inherit_depth_1_tables_1       | 6.25us       |
| rule_inherit_depth_1_tables_1024    | 31.86us      |
| rule_inherit_depth_2_tables_1       | 6.38us       |
| rule_inherit_depth_2_tables_1024    | 32.28us      |
| rule_inherit_depth_8_tables_1       | 6.72us       |
| rule_inherit_depth_8_tables_1024    | 31.73us      |
| rule_inherit_depth_16_tables_1      | 7.21us       |
| rule_inherit_depth_16_tables_1024   | 32.25us      |
| query_init_fini_1_ids               | 666.65ns     |
| query_init_fini_8_ids               | 4.77us       |
| query_init_fini_16_ids              | 7.71us       |
| query_iter_1_table_1_tag            | 6.17us       |
| query_iter_2_tables_1_tag           | 6.17us       |
| query_iter_4_tables_1_tag           | 6.38us       |
| query_iter_8_tables_1_tag           | 6.78us       |
| query_iter_16_tables_1_tag          | 7.29us       |
| query_iter_32_tables_1_tag          | 7.63us       |
| query_iter_64_tables_1_tag          | 8.48us       |
| query_iter_128_tables_1_tag         | 9.63us       |
| query_iter_256_tables_1_tag         | 10.41us      |
| query_iter_512_tables_1_tag         | 13.08us      |
| query_iter_1024_tables_1_tag        | 17.21us      |
| query_iter_4096_tables_1_tag        | 34.27us      |
| query_iter_4096_tables_4_tags       | 34.50us      |
| query_iter_4096_tables_4_comps      | 81.16us      |
| query_iter_4096_tables_8_tags       | 34.48us      |
| query_iter_4096_tables_8_comps      | 80.94us      |
| query_iter_65536_tables_4_tags      | 826.28us     |
| query_iter_65536_tables_4_comps     | 2.76ms       |
| query_iter_65536_tables_8_tags      | 818.10us     |
| query_iter_65536_tables_8_comps     | 2.78ms       |
| query_iter_255_empty_1_fill         | 28.92ns      |
| query_iter_1023_empty_1_fill        | 29.66ns      |
| query_iter_rnd_8_tags               | 11.45us      |
| query_iter_rnd_16_tags              | 832.04us     |
| query_count_1_table                 | 2.73ns       |
| query_count_2_tables                | 3.13ns       |
| query_count_4_tables                | 4.02ns       |
| query_count_8_tables                | 6.14ns       |
| query_count_16_tables               | 11.90ns      |
| query_count_32_tables               | 26.80ns      |
| query_count_64_tables               | 60.94ns      |
| query_count_128_tables              | 148.60ns     |
| query_count_256_tables              | 280.83ns     |
| query_count_512_tables              | 1.03us       |
| query_count_1024_tables             | 3.66us       |
| query_count_4096_tables             | 13.62us      |
| query_count_65536_tables            | 476.75us     |
| progress_0_systems                  | 154.42ns     |
| progress_1_system                   | 222.62ns     |
| progress_10_systems                 | 580.78ns     |
| progress_100_systems                | 4.06us       |
| create_delete_table_1_id            | 126.91ns     |
| create_delete_table_10_ids          | 217.35ns     |
| create_delete_table_100_ids         | 1.13us       |
| create_delete_table_1000_ids        | 14.96us      |
| match_table_1_of_10_queries         | 243.64ns     |
| match_table_5_of_10_queries         | 479.79ns     |
| match_table_10_of_10_queries        | 778.54ns     |
| match_table_1_of_100_queries        | 244.80ns     |
| match_table_10_of_100_queries       | 789.07ns     |
| match_table_50_of_100_queries       | 3.24us       |
| match_table_100_of_100_queries      | 7.50us       |
| match_table_1_of_1000_queries       | 243.11ns     |
| match_table_10_of_1000_queries      | 778.91ns     |
| match_table_100_of_1000_queries     | 7.42us       |
| match_table_1000_of_1000_queries    | 80.78us      |
| rematch_1_of_1000_tables            | 65.13us      |
| rematch_10_of_1000_tables           | 63.71us      |
| rematch_100_of_1000_tables          | 62.87us      |
| rematch_1000_of_1000_tables         | 45.74us      |
| fill_empty_table_0_queries          | 216.94ns     |
| fill_empty_table_1_query            | 387.99ns     |
| fill_empty_table_10_queries         | 606.64ns     |
| fill_empty_table_100_queries        | 3.71us       |
| fill_empty_table_1000_queries       | 43.30us      |
| table_add_remove_1_id               | 2.00ns       |
| table_add_remove_4_ids              | 2.10ns       |
| table_add_remove_16_ids             | 3.96ns       |
| table_add_remove_32_ids             | 4.46ns       |
| table_add_remove_64_ids             | 4.69ns       |
