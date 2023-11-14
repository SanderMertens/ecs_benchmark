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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.9

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 221.98us     |
| world_init_fini                     | 984.15us     |
| has_empty_entity                    | 1.61ns       |
| has_id_not_found                    | 3.21ns       |
| has_id                              | 3.88ns       |
| has_16_ids                          | 4.19ns       |
| get_empty_entity                    | 1.61ns       |
| get_id_not_found                    | 4.18ns       |
| get_id                              | 3.41ns       |
| get_16_ids                          | 3.60ns       |
| get_pair                            | 4.76ns       |
| get_pair_16_targets                 | 4.86ns       |
| get_inherited_depth_1               | 19.93ns      |
| get_inherited_depth_2               | 32.45ns      |
| get_inherited_depth_16              | 239.15ns     |
| get_inherited_depth_32              | 514.68ns     |
| get_mut_id                          | 6.86ns       |
| get_mut_16_ids                      | 7.01ns       |
| set_id                              | 12.15ns      |
| set_16_ids                          | 13.47ns      |
| get_mut_remove_id                   | 17.43ns      |
| get_mut_remove_16_ids               | 68.67ns      |
| get_mut_remove_32_ids               | 115.15ns     |
| ref_init                            | 3.12ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 15.05ns      |
| add_remove_2_tags                   | 18.78ns      |
| add_remove_16_tags                  | 22.75ns      |
| add_remove_32_tags                  | 22.83ns      |
| add_remove_1_component              | 15.49ns      |
| add_remove_2_components             | 21.15ns      |
| add_remove_16_components            | 65.53ns      |
| add_remove_32_components            | 113.66ns     |
| add_existing_1_tag                  | 6.96ns       |
| add_existing_16_tags                | 7.43ns       |
| add_existing_1_component            | 6.96ns       |
| add_existing_16_components          | 7.28ns       |
| add_remove_tag_to_1_component       | 26.14ns      |
| add_remove_tag_to_4_components      | 46.12ns      |
| add_remove_tag_to_8_components      | 71.64ns      |
| add_remove_tag_to_16_components     | 131.97ns     |
| add_remove_tag_to_64_components     | 441.08ns     |
| add_remove_override_1               | 61.44ns      |
| add_remove_override_2               | 64.44ns      |
| add_remove_override_4               | 72.52ns      |
| add_remove_override_16              | 113.74ns     |
| add_remove_cmd_1_tag                | 21.08ns      |
| add_remove_cmd_2_tags               | 19.16ns      |
| add_remove_cmd_16_tags              | 16.39ns      |
| add_remove_cmd_32_tags              | 15.92ns      |
| add_remove_cmd_1_components         | 21.96ns      |
| add_remove_cmd_2_components         | 20.86ns      |
| add_remove_cmd_16_components        | 17.67ns      |
| add_remove_cmd_32_components        | 17.13ns      |
| get_mut_cmd_1                       | 19.47ns      |
| get_mut_cmd_2                       | 18.99ns      |
| get_mut_cmd_16                      | 17.81ns      |
| get_mut_cmd_32                      | 17.57ns      |
| set_cmd_1                           | 32.86ns      |
| set_cmd_2                           | 34.61ns      |
| set_cmd_16                          | 33.22ns      |
| set_cmd_32                          | 32.97ns      |
| get_mut_remove_cmd_1                | 27.40ns      |
| get_mut_remove_cmd_2                | 28.14ns      |
| get_mut_remove_cmd_16               | 24.65ns      |
| get_mut_remove_cmd_32               | 23.86ns      |
| add_remove_hooks_1                  | 18.79ns      |
| add_remove_hooks_2                  | 29.35ns      |
| add_remove_hooks_16                 | 93.00ns      |
| add_remove_hooks_32                 | 159.64ns     |
| create_100_w_add_in_observer        | 112.26ns     |
| create_1k_w_add_in_observer         | 111.97ns     |
| create_10k_w_add_in_observer        | 113.89ns     |
| create_50k_w_add_in_observer        | 114.05ns     |
| create_delete_empty                 | 4.12ns       |
| create_delete_1_tag                 | 10.42ns      |
| create_delete_2_tags                | 13.33ns      |
| create_delete_16_tags               | 20.61ns      |
| create_delete_1_component           | 10.60ns      |
| create_delete_2_components          | 14.70ns      |
| create_delete_16_components         | 56.93ns      |
| entity_init_delete                  | 12.44us      |
| entity_init_w_name_delete           | 12.43us      |
| create_delete_tree_w1_d1            | 768.15ns     |
| create_delete_tree_w1_d10           | 4.80us       |
| create_delete_tree_w1_d100          | 50.83us      |
| create_delete_tree_w1_d1000         | 552.95us     |
| create_delete_tree_w10_d1           | 98.99ns      |
| create_delete_tree_w10_d10          | 763.07ns     |
| create_delete_tree_w10_d100         | 7.93us       |
| create_delete_tree_w10_d1000        | 78.56us      |
| create_delete_tree_w100_d1          | 29.21ns      |
| create_delete_tree_w100_d10         | 278.06ns     |
| create_delete_tree_w100_d100        | 2.92us       |
| create_delete_tree_w100_d1000       | 32.43us      |
| create_delete_tree_w1000_d1         | 21.54ns      |
| create_delete_tree_w1000_d10        | 230.96ns     |
| create_delete_tree_w1000_d100       | 2.30us       |
| create_delete_tree_w1000_d1000      | 24.86us      |
| change_parent                       | 23.17ns      |
| change_parent_root                  | 14.92ns      |
| change_parent_w_name                | 97.89us      |
| lookup_depth_0                      | 39.36ns      |
| lookup_depth_1                      | 69.17ns      |
| lookup_depth_10                     | 353.44ns     |
| lookup_depth_100                    | 3.34us       |
| set_name                            | 96.76ns      |
| emit_0_observers                    | 24.12ns      |
| emit_1_observer                     | 36.46ns      |
| emit_10_observers                   | 72.09ns      |
| emit_100_observers                  | 502.84ns     |
| emit_propagate_depth_1              | 30.50ns      |
| emit_propagate_depth_10             | 232.84ns     |
| emit_propagate_depth_100            | 2.55us       |
| emit_propagate_depth_1000           | 35.26us      |
| emit_forward_1_ids_depth_1          | 143.42ns     |
| emit_forward_1_ids_depth_1000       | 145.33ns     |
| emit_forward_16_ids_depth_1         | 758.63ns     |
| emit_forward_16_ids_depth_1000      | 776.61ns     |
| modified_0_observers                | 9.86ns       |
| modified_1_observer                 | 47.65ns      |
| modified_10_observers               | 82.70ns      |
| modified_100_observers              | 507.11ns     |
| filter_simple_iter_1_tags           | 6.19us       |
| filter_simple_iter_8_tags           | 6.23us       |
| filter_simple_iter_1_component      | 6.11us       |
| filter_simple_iter_8_components     | 6.25us       |
| filter_init_fini_1_ids              | 60.45ns      |
| filter_init_fini_8_ids              | 299.09ns     |
| filter_init_fini_16_ids             | 546.65ns     |
| filter_init_fini_inline_1_ids       | 54.36ns      |
| filter_init_fini_inline_8_ids       | 289.23ns     |
| filter_init_fini_inline_16_ids      | 539.29ns     |
| filter_iter_8_tags_1_term           | 6.54us       |
| filter_iter_8_tags_4_terms          | 4.63us       |
| filter_iter_16_tags_1_term          | 1.25ms       |
| filter_iter_16_tags_4_terms         | 2.24ms       |
| filter_iter_8_components_1_term     | 6.90us       |
| filter_iter_8_components_4_terms    | 4.77us       |
| filter_iter_16_components_1_term    | 1.62ms       |
| filter_iter_16_components_4_terms   | 2.49ms       |
| filter_iter_up_8_tags               | 6.00ms       |
| filter_iter_up_8_tags_w_self        | 6.02ms       |
| filter_iter_up_w_mut_8_tags         | 5.79ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 5.89ms       |
| rule_init_fini_1_ids                | 125.34ns     |
| rule_init_fini_8_ids                | 475.06ns     |
| rule_init_fini_16_ids               | 832.56ns     |
| rule_simple_iter_1_tags             | 6.14us       |
| rule_simple_iter_8_tags             | 6.37us       |
| rule_simple_iter_1_component        | 6.27us       |
| rule_simple_iter_8_component        | 6.28us       |
| rule_iter_8_tags_1_term             | 6.72us       |
| rule_iter_8_tags_4_terms            | 2.94us       |
| rule_iter_16_tags_1_term            | 886.57us     |
| rule_iter_16_tags_4_terms           | 1.77ms       |
| rule_iter_8_components_1_term       | 6.93us       |
| rule_iter_8_components_4_terms      | 3.08us       |
| rule_iter_16_components_1_term      | 1.35ms       |
| rule_iter_16_components_4_terms     | 1.97ms       |
| rule_inherit_depth_1_tables_1       | 6.20us       |
| rule_inherit_depth_1_tables_1024    | 32.05us      |
| rule_inherit_depth_2_tables_1       | 6.34us       |
| rule_inherit_depth_2_tables_1024    | 31.79us      |
| rule_inherit_depth_8_tables_1       | 6.67us       |
| rule_inherit_depth_8_tables_1024    | 32.03us      |
| rule_inherit_depth_16_tables_1      | 7.15us       |
| rule_inherit_depth_16_tables_1024   | 32.53us      |
| query_init_fini_1_ids               | 689.11ns     |
| query_init_fini_8_ids               | 4.70us       |
| query_init_fini_16_ids              | 7.67us       |
| query_iter_1_table_1_tag            | 6.11us       |
| query_iter_2_tables_1_tag           | 6.30us       |
| query_iter_4_tables_1_tag           | 6.56us       |
| query_iter_8_tables_1_tag           | 6.62us       |
| query_iter_16_tables_1_tag          | 7.30us       |
| query_iter_32_tables_1_tag          | 6.80us       |
| query_iter_64_tables_1_tag          | 7.53us       |
| query_iter_128_tables_1_tag         | 7.98us       |
| query_iter_256_tables_1_tag         | 9.04us       |
| query_iter_512_tables_1_tag         | 10.82us      |
| query_iter_1024_tables_1_tag        | 14.81us      |
| query_iter_4096_tables_1_tag        | 32.15us      |
| query_iter_4096_tables_4_tags       | 32.24us      |
| query_iter_4096_tables_4_comps      | 80.20us      |
| query_iter_4096_tables_8_tags       | 32.44us      |
| query_iter_4096_tables_8_comps      | 80.20us      |
| query_iter_65536_tables_4_tags      | 774.66us     |
| query_iter_65536_tables_4_comps     | 2.58ms       |
| query_iter_65536_tables_8_tags      | 759.25us     |
| query_iter_65536_tables_8_comps     | 2.61ms       |
| query_iter_255_empty_1_fill         | 28.59ns      |
| query_iter_1023_empty_1_fill        | 28.58ns      |
| query_iter_rnd_8_tags               | 10.94us      |
| query_iter_rnd_16_tags              | 756.18us     |
| query_count_1_table                 | 2.78ns       |
| query_count_2_tables                | 3.09ns       |
| query_count_4_tables                | 4.00ns       |
| query_count_8_tables                | 6.28ns       |
| query_count_16_tables               | 12.23ns      |
| query_count_32_tables               | 27.43ns      |
| query_count_64_tables               | 61.83ns      |
| query_count_128_tables              | 147.14ns     |
| query_count_256_tables              | 290.82ns     |
| query_count_512_tables              | 830.24ns     |
| query_count_1024_tables             | 2.85us       |
| query_count_4096_tables             | 12.68us      |
| query_count_65536_tables            | 440.64us     |
| progress_0_systems                  | 156.89ns     |
| progress_1_system                   | 224.32ns     |
| progress_10_systems                 | 601.14ns     |
| progress_100_systems                | 4.10us       |
| create_delete_table_1_id            | 128.76ns     |
| create_delete_table_10_ids          | 217.65ns     |
| create_delete_table_100_ids         | 1.14us       |
| create_delete_table_1000_ids        | 14.99us      |
| match_table_1_of_10_queries         | 241.25ns     |
| match_table_5_of_10_queries         | 481.80ns     |
| match_table_10_of_10_queries        | 778.15ns     |
| match_table_1_of_100_queries        | 242.20ns     |
| match_table_10_of_100_queries       | 779.47ns     |
| match_table_50_of_100_queries       | 3.28us       |
| match_table_100_of_100_queries      | 7.43us       |
| match_table_1_of_1000_queries       | 242.96ns     |
| match_table_10_of_1000_queries      | 783.50ns     |
| match_table_100_of_1000_queries     | 7.58us       |
| match_table_1000_of_1000_queries    | 82.31us      |
| rematch_1_of_1000_tables            | 64.93us      |
| rematch_10_of_1000_tables           | 63.56us      |
| rematch_100_of_1000_tables          | 62.80us      |
| rematch_1000_of_1000_tables         | 46.12us      |
| fill_empty_table_0_queries          | 217.53ns     |
| fill_empty_table_1_query            | 276.73ns     |
| fill_empty_table_10_queries         | 491.11ns     |
| fill_empty_table_100_queries        | 3.49us       |
| fill_empty_table_1000_queries       | 41.81us      |
| table_add_remove_1_id               | 2.00ns       |
| table_add_remove_4_ids              | 2.09ns       |
| table_add_remove_16_ids             | 3.96ns       |
| table_add_remove_32_ids             | 4.42ns       |
| table_add_remove_64_ids             | 4.69ns       |