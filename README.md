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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.6

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 231.82us     |
| world_init_fini                     | 970.99us     |
| has_empty_entity                    | 1.61ns       |
| has_id_not_found                    | 3.22ns       |
| has_id                              | 4.08ns       |
| has_16_ids                          | 4.38ns       |
| get_empty_entity                    | 1.56ns       |
| get_id_not_found                    | 4.05ns       |
| get_id                              | 3.32ns       |
| get_16_ids                          | 3.48ns       |
| get_pair                            | 4.57ns       |
| get_pair_16_targets                 | 4.74ns       |
| get_inherited_depth_1               | 19.36ns      |
| get_inherited_depth_2               | 31.78ns      |
| get_inherited_depth_16              | 234.06ns     |
| get_inherited_depth_32              | 532.49ns     |
| get_mut_id                          | 6.86ns       |
| get_mut_16_ids                      | 6.86ns       |
| set_id                              | 12.17ns      |
| set_16_ids                          | 13.09ns      |
| get_mut_remove_id                   | 18.36ns      |
| get_mut_remove_16_ids               | 70.93ns      |
| get_mut_remove_32_ids               | 117.61ns     |
| ref_init                            | 3.12ns       |
| ref_get                             | 0.70ns       |
| add_remove_1_tag                    | 16.08ns      |
| add_remove_2_tags                   | 20.00ns      |
| add_remove_16_tags                  | 24.17ns      |
| add_remove_32_tags                  | 24.18ns      |
| add_remove_1_component              | 16.30ns      |
| add_remove_2_components             | 22.49ns      |
| add_remove_16_components            | 67.81ns      |
| add_remove_32_components            | 115.01ns     |
| add_existing_1_tag                  | 6.74ns       |
| add_existing_16_tags                | 7.09ns       |
| add_existing_1_component            | 6.80ns       |
| add_existing_16_components          | 7.03ns       |
| add_remove_tag_to_1_component       | 27.10ns      |
| add_remove_tag_to_4_components      | 46.63ns      |
| add_remove_tag_to_8_components      | 74.20ns      |
| add_remove_tag_to_16_components     | 132.56ns     |
| add_remove_tag_to_64_components     | 439.89ns     |
| add_remove_override_1               | 63.01ns      |
| add_remove_override_2               | 66.04ns      |
| add_remove_override_4               | 77.62ns      |
| add_remove_override_16              | 115.94ns     |
| add_remove_cmd_1_tag                | 23.58ns      |
| add_remove_cmd_2_tags               | 19.06ns      |
| add_remove_cmd_16_tags              | 14.46ns      |
| add_remove_cmd_32_tags              | 13.88ns      |
| add_remove_cmd_1_components         | 24.29ns      |
| add_remove_cmd_2_components         | 20.81ns      |
| add_remove_cmd_16_components        | 15.63ns      |
| add_remove_cmd_32_components        | 15.17ns      |
| get_mut_cmd_1                       | 21.76ns      |
| get_mut_cmd_2                       | 19.44ns      |
| get_mut_cmd_16                      | 16.24ns      |
| get_mut_cmd_32                      | 15.86ns      |
| set_cmd_1                           | 34.91ns      |
| set_cmd_2                           | 35.63ns      |
| set_cmd_16                          | 33.12ns      |
| set_cmd_32                          | 32.35ns      |
| get_mut_remove_cmd_1                | 29.47ns      |
| get_mut_remove_cmd_2                | 29.35ns      |
| get_mut_remove_cmd_16               | 23.83ns      |
| get_mut_remove_cmd_32               | 23.07ns      |
| add_remove_hooks_1                  | 19.40ns      |
| add_remove_hooks_2                  | 30.18ns      |
| add_remove_hooks_16                 | 93.76ns      |
| add_remove_hooks_32                 | 161.16ns     |
| create_delete_empty                 | 3.93ns       |
| create_delete_1_tag                 | 11.06ns      |
| create_delete_2_tags                | 14.11ns      |
| create_delete_16_tags               | 21.91ns      |
| create_delete_1_component           | 11.44ns      |
| create_delete_2_components          | 15.52ns      |
| create_delete_16_components         | 59.12ns      |
| entity_init_delete                  | 12.49us      |
| entity_init_w_name_delete           | 12.45us      |
| create_delete_tree_w1_d1            | 773.70ns     |
| create_delete_tree_w1_d10           | 4.89us       |
| create_delete_tree_w1_d100          | 52.29us      |
| create_delete_tree_w1_d1000         | 565.34us     |
| create_delete_tree_w10_d1           | 106.17ns     |
| create_delete_tree_w10_d10          | 777.77ns     |
| create_delete_tree_w10_d100         | 8.30us       |
| create_delete_tree_w10_d1000        | 82.91us      |
| create_delete_tree_w100_d1          | 31.35ns      |
| create_delete_tree_w100_d10         | 297.03ns     |
| create_delete_tree_w100_d100        | 3.07us       |
| create_delete_tree_w100_d1000       | 30.96us      |
| create_delete_tree_w1000_d1         | 23.14ns      |
| create_delete_tree_w1000_d10        | 238.02ns     |
| create_delete_tree_w1000_d100       | 2.40us       |
| create_delete_tree_w1000_d1000      | 27.90us      |
| change_parent                       | 24.25ns      |
| change_parent_root                  | 16.12ns      |
| change_parent_w_name                | 98.74us      |
| lookup_depth_0                      | 41.36ns      |
| lookup_depth_1                      | 71.36ns      |
| lookup_depth_10                     | 355.01ns     |
| lookup_depth_100                    | 3.29us       |
| set_name                            | 97.13ns      |
| emit_0_observers                    | 22.26ns      |
| emit_1_observer                     | 34.78ns      |
| emit_10_observers                   | 69.62ns      |
| emit_100_observers                  | 490.69ns     |
| emit_propagate_depth_1              | 28.88ns      |
| emit_propagate_depth_10             | 209.52ns     |
| emit_propagate_depth_100            | 2.36us       |
| emit_propagate_depth_1000           | 35.27us      |
| emit_forward_1_ids_depth_1          | 145.10ns     |
| emit_forward_1_ids_depth_1000       | 146.19ns     |
| emit_forward_16_ids_depth_1         | 736.32ns     |
| emit_forward_16_ids_depth_1000      | 809.86ns     |
| modified_0_observers                | 9.91ns       |
| modified_1_observer                 | 47.65ns      |
| modified_10_observers               | 82.39ns      |
| modified_100_observers              | 502.95ns     |
| filter_simple_iter_1_tags           | 6.15us       |
| filter_simple_iter_8_tags           | 6.29us       |
| filter_simple_iter_1_component      | 6.15us       |
| filter_simple_iter_8_components     | 6.23us       |
| filter_init_fini_1_ids              | 60.32ns      |
| filter_init_fini_8_ids              | 290.96ns     |
| filter_init_fini_16_ids             | 540.25ns     |
| filter_init_fini_inline_1_ids       | 54.15ns      |
| filter_init_fini_inline_8_ids       | 284.89ns     |
| filter_init_fini_inline_16_ids      | 534.88ns     |
| filter_iter_8_tags_1_term           | 6.82us       |
| filter_iter_8_tags_4_terms          | 4.86us       |
| filter_iter_16_tags_1_term          | 1.34ms       |
| filter_iter_16_tags_4_terms         | 2.30ms       |
| filter_iter_8_components_1_term     | 7.03us       |
| filter_iter_8_components_4_terms    | 4.93us       |
| filter_iter_16_components_1_term    | 1.62ms       |
| filter_iter_16_components_4_terms   | 2.48ms       |
| filter_iter_up_8_tags               | 5.96ms       |
| filter_iter_up_8_tags_w_self        | 6.13ms       |
| filter_iter_up_w_mut_8_tags         | 5.95ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.01ms       |
| rule_init_fini_1_ids                | 126.17ns     |
| rule_init_fini_8_ids                | 471.95ns     |
| rule_init_fini_16_ids               | 836.07ns     |
| rule_simple_iter_1_tags             | 6.19us       |
| rule_simple_iter_8_tags             | 6.28us       |
| rule_simple_iter_1_component        | 6.17us       |
| rule_simple_iter_8_component        | 6.39us       |
| rule_iter_8_tags_1_term             | 7.74us       |
| rule_iter_8_tags_4_terms            | 2.98us       |
| rule_iter_16_tags_1_term            | 1.00ms       |
| rule_iter_16_tags_4_terms           | 1.84ms       |
| rule_iter_8_components_1_term       | 7.09us       |
| rule_iter_8_components_4_terms      | 3.03us       |
| rule_iter_16_components_1_term      | 1.41ms       |
| rule_iter_16_components_4_terms     | 2.05ms       |
| rule_inherit_depth_1_tables_1       | 6.23us       |
| rule_inherit_depth_1_tables_1024    | 31.29us      |
| rule_inherit_depth_2_tables_1       | 6.47us       |
| rule_inherit_depth_2_tables_1024    | 31.62us      |
| rule_inherit_depth_8_tables_1       | 6.73us       |
| rule_inherit_depth_8_tables_1024    | 32.08us      |
| rule_inherit_depth_16_tables_1      | 7.18us       |
| rule_inherit_depth_16_tables_1024   | 32.17us      |
| query_init_fini_1_ids               | 684.10ns     |
| query_init_fini_8_ids               | 4.70us       |
| query_init_fini_16_ids              | 7.67us       |
| query_iter_1_table_1_tag            | 6.20us       |
| query_iter_2_tables_1_tag           | 6.21us       |
| query_iter_4_tables_1_tag           | 6.40us       |
| query_iter_8_tables_1_tag           | 6.59us       |
| query_iter_16_tables_1_tag          | 7.26us       |
| query_iter_32_tables_1_tag          | 7.39us       |
| query_iter_64_tables_1_tag          | 8.48us       |
| query_iter_128_tables_1_tag         | 9.56us       |
| query_iter_256_tables_1_tag         | 10.32us      |
| query_iter_512_tables_1_tag         | 12.74us      |
| query_iter_1024_tables_1_tag        | 16.89us      |
| query_iter_4096_tables_1_tag        | 34.51us      |
| query_iter_4096_tables_4_tags       | 34.40us      |
| query_iter_4096_tables_4_comps      | 82.51us      |
| query_iter_4096_tables_8_tags       | 34.20us      |
| query_iter_4096_tables_8_comps      | 82.78us      |
| query_iter_65536_tables_4_tags      | 822.48us     |
| query_iter_65536_tables_4_comps     | 2.73ms       |
| query_iter_65536_tables_8_tags      | 820.31us     |
| query_iter_65536_tables_8_comps     | 2.75ms       |
| query_iter_255_empty_1_fill         | 25.47ns      |
| query_iter_1023_empty_1_fill        | 25.47ns      |
| query_iter_rnd_8_tags               | 10.82us      |
| query_iter_rnd_16_tags              | 825.57us     |
| query_count_1_table                 | 2.73ns       |
| query_count_2_tables                | 3.09ns       |
| query_count_4_tables                | 4.00ns       |
| query_count_8_tables                | 6.14ns       |
| query_count_16_tables               | 11.93ns      |
| query_count_32_tables               | 27.45ns      |
| query_count_64_tables               | 62.10ns      |
| query_count_128_tables              | 147.85ns     |
| query_count_256_tables              | 280.43ns     |
| query_count_512_tables              | 1.10us       |
| query_count_1024_tables             | 4.14us       |
| query_count_4096_tables             | 13.57us      |
| query_count_65536_tables            | 468.37us     |
| progress_0_systems                  | 148.23ns     |
| progress_1_system                   | 211.15ns     |
| progress_10_systems                 | 543.64ns     |
| progress_100_systems                | 3.71us       |
| create_delete_table_1_id            | 127.26ns     |
| create_delete_table_10_ids          | 213.64ns     |
| create_delete_table_100_ids         | 1.13us       |
| create_delete_table_1000_ids        | 14.97us      |
| match_table_1_of_10_queries         | 244.81ns     |
| match_table_5_of_10_queries         | 482.16ns     |
| match_table_10_of_10_queries        | 785.63ns     |
| match_table_1_of_100_queries        | 244.96ns     |
| match_table_10_of_100_queries       | 783.02ns     |
| match_table_50_of_100_queries       | 3.24us       |
| match_table_100_of_100_queries      | 7.58us       |
| match_table_1_of_1000_queries       | 243.30ns     |
| match_table_10_of_1000_queries      | 777.70ns     |
| match_table_100_of_1000_queries     | 7.49us       |
| match_table_1000_of_1000_queries    | 82.35us      |
| rematch_1_of_1000_tables            | 64.30us      |
| rematch_10_of_1000_tables           | 65.93us      |
| rematch_100_of_1000_tables          | 64.22us      |
| rematch_1000_of_1000_tables         | 45.94us      |
| fill_empty_table_0_queries          | 222.93ns     |
| fill_empty_table_1_query            | 387.27ns     |
| fill_empty_table_10_queries         | 605.57ns     |
| fill_empty_table_100_queries        | 3.37us       |
| fill_empty_table_1000_queries       | 42.82us      |
| table_add_remove_1_id               | 2.00ns       |
| table_add_remove_4_ids              | 2.09ns       |
| table_add_remove_16_ids             | 4.05ns       |
| table_add_remove_32_ids             | 4.42ns       |
| table_add_remove_64_ids             | 4.67ns       |
