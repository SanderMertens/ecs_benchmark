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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.10

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 206.78us     |
| world_init_fini                     | 951.31us     |
| has_empty_entity                    | 1.56ns       |
| has_id_not_found                    | 3.12ns       |
| has_id                              | 4.06ns       |
| has_16_ids                          | 4.42ns       |
| get_empty_entity                    | 1.56ns       |
| get_id_not_found                    | 4.07ns       |
| get_id                              | 3.32ns       |
| get_16_ids                          | 3.48ns       |
| get_pair                            | 4.58ns       |
| get_pair_16_targets                 | 4.73ns       |
| get_inherited_depth_1               | 20.39ns      |
| get_inherited_depth_2               | 31.58ns      |
| get_inherited_depth_16              | 243.10ns     |
| get_inherited_depth_32              | 545.01ns     |
| get_mut_id                          | 6.87ns       |
| get_mut_16_ids                      | 6.88ns       |
| set_id                              | 12.19ns      |
| set_16_ids                          | 12.66ns      |
| get_mut_remove_id                   | 17.40ns      |
| get_mut_remove_16_ids               | 69.85ns      |
| get_mut_remove_32_ids               | 115.94ns     |
| ref_init                            | 3.13ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 15.22ns      |
| add_remove_2_tags                   | 18.97ns      |
| add_remove_16_tags                  | 23.13ns      |
| add_remove_32_tags                  | 23.00ns      |
| add_remove_1_component              | 15.64ns      |
| add_remove_2_components             | 21.18ns      |
| add_remove_16_components            | 65.81ns      |
| add_remove_32_components            | 113.10ns     |
| add_existing_1_tag                  | 7.01ns       |
| add_existing_16_tags                | 7.33ns       |
| add_existing_1_component            | 7.03ns       |
| add_existing_16_components          | 7.36ns       |
| add_remove_tag_to_1_component       | 26.23ns      |
| add_remove_tag_to_4_components      | 46.93ns      |
| add_remove_tag_to_8_components      | 72.40ns      |
| add_remove_tag_to_16_components     | 132.63ns     |
| add_remove_tag_to_64_components     | 441.22ns     |
| add_remove_override_1               | 62.34ns      |
| add_remove_override_2               | 66.54ns      |
| add_remove_override_4               | 74.68ns      |
| add_remove_override_16              | 116.88ns     |
| add_remove_cmd_1_tag                | 21.00ns      |
| add_remove_cmd_2_tags               | 19.32ns      |
| add_remove_cmd_16_tags              | 16.47ns      |
| add_remove_cmd_32_tags              | 15.93ns      |
| add_remove_cmd_1_components         | 21.91ns      |
| add_remove_cmd_2_components         | 20.91ns      |
| add_remove_cmd_16_components        | 17.76ns      |
| add_remove_cmd_32_components        | 17.23ns      |
| get_mut_cmd_1                       | 19.08ns      |
| get_mut_cmd_2                       | 19.02ns      |
| get_mut_cmd_16                      | 17.58ns      |
| get_mut_cmd_32                      | 17.55ns      |
| set_cmd_1                           | 33.39ns      |
| set_cmd_2                           | 34.81ns      |
| set_cmd_16                          | 33.44ns      |
| set_cmd_32                          | 33.09ns      |
| get_mut_remove_cmd_1                | 27.07ns      |
| get_mut_remove_cmd_2                | 28.37ns      |
| get_mut_remove_cmd_16               | 24.74ns      |
| get_mut_remove_cmd_32               | 23.86ns      |
| add_remove_hooks_1                  | 18.70ns      |
| add_remove_hooks_2                  | 29.44ns      |
| add_remove_hooks_16                 | 92.84ns      |
| add_remove_hooks_32                 | 157.10ns     |
| create_100_w_add_in_observer        | 113.63ns     |
| create_1k_w_add_in_observer         | 112.70ns     |
| create_10k_w_add_in_observer        | 114.86ns     |
| create_50k_w_add_in_observer        | 114.26ns     |
| create_delete_empty                 | 4.03ns       |
| create_delete_1_tag                 | 10.28ns      |
| create_delete_2_tags                | 13.37ns      |
| create_delete_16_tags               | 20.66ns      |
| create_delete_1_component           | 10.50ns      |
| create_delete_2_components          | 14.65ns      |
| create_delete_16_components         | 57.80ns      |
| entity_init_delete                  | 12.48us      |
| entity_init_w_name_delete           | 12.47us      |
| create_delete_tree_w1_d1            | 756.68ns     |
| create_delete_tree_w1_d10           | 4.79us       |
| create_delete_tree_w1_d100          | 50.70us      |
| create_delete_tree_w1_d1000         | 547.29us     |
| create_delete_tree_w10_d1           | 99.92ns      |
| create_delete_tree_w10_d10          | 740.82ns     |
| create_delete_tree_w10_d100         | 7.81us       |
| create_delete_tree_w10_d1000        | 77.84us      |
| create_delete_tree_w100_d1          | 28.74ns      |
| create_delete_tree_w100_d10         | 277.38ns     |
| create_delete_tree_w100_d100        | 2.91us       |
| create_delete_tree_w100_d1000       | 29.59us      |
| create_delete_tree_w1000_d1         | 21.17ns      |
| create_delete_tree_w1000_d10        | 228.70ns     |
| create_delete_tree_w1000_d100       | 2.30us       |
| create_delete_tree_w1000_d1000      | 24.88us      |
| change_parent                       | 23.32ns      |
| change_parent_root                  | 15.15ns      |
| change_parent_w_name                | 98.38us      |
| lookup_depth_0                      | 39.50ns      |
| lookup_depth_1                      | 69.75ns      |
| lookup_depth_10                     | 355.33ns     |
| lookup_depth_100                    | 3.32us       |
| set_name                            | 97.92ns      |
| emit_0_observers                    | 22.88ns      |
| emit_1_observer                     | 37.55ns      |
| emit_10_observers                   | 71.71ns      |
| emit_100_observers                  | 491.51ns     |
| emit_propagate_depth_1              | 30.64ns      |
| emit_propagate_depth_10             | 220.63ns     |
| emit_propagate_depth_100            | 2.56us       |
| emit_propagate_depth_1000           | 35.09us      |
| emit_forward_1_ids_depth_1          | 143.31ns     |
| emit_forward_1_ids_depth_1000       | 143.77ns     |
| emit_forward_16_ids_depth_1         | 764.00ns     |
| emit_forward_16_ids_depth_1000      | 760.70ns     |
| modified_0_observers                | 9.90ns       |
| modified_1_observer                 | 48.26ns      |
| modified_10_observers               | 83.06ns      |
| modified_100_observers              | 501.19ns     |
| filter_simple_iter_self_1_tags      | 6.14us       |
| filter_simple_iter_self_8_tags      | 6.22us       |
| filter_simple_iter_self_1_component | 6.15us       |
| filter_simple_iter_self_8_components| 6.23us       |
| filter_simple_iter_1_tags           | 6.14us       |
| filter_simple_iter_8_tags           | 6.29us       |
| filter_simple_iter_1_component      | 6.15us       |
| filter_simple_iter_8_components     | 6.25us       |
| filter_init_fini_1_ids              | 62.71ns      |
| filter_init_fini_8_ids              | 301.91ns     |
| filter_init_fini_16_ids             | 560.54ns     |
| filter_init_fini_inline_1_ids       | 55.98ns      |
| filter_init_fini_inline_8_ids       | 295.27ns     |
| filter_init_fini_inline_16_ids      | 553.63ns     |
| filter_iter_8_tags_1_term           | 6.57us       |
| filter_iter_8_tags_4_terms          | 4.64us       |
| filter_iter_16_tags_1_term          | 1.27ms       |
| filter_iter_16_tags_4_terms         | 2.26ms       |
| filter_iter_8_components_1_term     | 6.94us       |
| filter_iter_8_components_4_terms    | 4.83us       |
| filter_iter_16_components_1_term    | 1.64ms       |
| filter_iter_16_components_4_terms   | 2.46ms       |
| filter_iter_up_8_tags               | 5.95ms       |
| filter_iter_up_8_tags_w_self        | 6.07ms       |
| filter_iter_up_w_mut_8_tags         | 6.01ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.11ms       |
| rule_init_fini_1_ids                | 128.74ns     |
| rule_init_fini_8_ids                | 366.44ns     |
| rule_init_fini_16_ids               | 637.34ns     |
| rule_simple_iter_self_1_tags        | 6.16us       |
| rule_simple_iter_self_8_tags        | 6.23us       |
| rule_simple_iter_self_1_component   | 6.16us       |
| rule_simple_iter_self_8_component   | 6.25us       |
| rule_simple_iter_1_tags             | 6.16us       |
| rule_simple_iter_8_tags             | 6.17us       |
| rule_simple_iter_1_component        | 6.18us       |
| rule_simple_iter_8_component        | 6.22us       |
| rule_iter_8_tags_1_term             | 6.36us       |
| rule_iter_8_tags_4_terms            | 882.69ns     |
| rule_iter_16_tags_1_term            | 741.21us     |
| rule_iter_16_tags_4_terms           | 1.14ms       |
| rule_iter_8_components_1_term       | 6.57us       |
| rule_iter_8_components_4_terms      | 1.10us       |
| rule_iter_16_components_1_term      | 1.09ms       |
| rule_iter_16_components_4_terms     | 1.38ms       |
| rule_inherit_depth_1_tables_1       | 6.23us       |
| rule_inherit_depth_1_tables_1024    | 32.50us      |
| rule_inherit_depth_2_tables_1       | 6.35us       |
| rule_inherit_depth_2_tables_1024    | 32.27us      |
| rule_inherit_depth_8_tables_1       | 6.75us       |
| rule_inherit_depth_8_tables_1024    | 32.77us      |
| rule_inherit_depth_16_tables_1      | 7.23us       |
| rule_inherit_depth_16_tables_1024   | 33.55us      |
| query_init_fini_1_ids               | 684.90ns     |
| query_init_fini_8_ids               | 4.73us       |
| query_init_fini_16_ids              | 7.65us       |
| query_iter_1_table_1_tag            | 6.21us       |
| query_iter_2_tables_1_tag           | 6.31us       |
| query_iter_4_tables_1_tag           | 6.37us       |
| query_iter_8_tables_1_tag           | 6.61us       |
| query_iter_16_tables_1_tag          | 7.31us       |
| query_iter_32_tables_1_tag          | 6.82us       |
| query_iter_64_tables_1_tag          | 7.53us       |
| query_iter_128_tables_1_tag         | 8.32us       |
| query_iter_256_tables_1_tag         | 9.08us       |
| query_iter_512_tables_1_tag         | 10.83us      |
| query_iter_1024_tables_1_tag        | 14.63us      |
| query_iter_4096_tables_1_tag        | 31.87us      |
| query_iter_4096_tables_4_tags       | 31.86us      |
| query_iter_4096_tables_4_comps      | 81.64us      |
| query_iter_4096_tables_8_tags       | 31.81us      |
| query_iter_4096_tables_8_comps      | 81.50us      |
| query_iter_65536_tables_4_tags      | 774.98us     |
| query_iter_65536_tables_4_comps     | 2.70ms       |
| query_iter_65536_tables_8_tags      | 756.45us     |
| query_iter_65536_tables_8_comps     | 2.72ms       |
| query_iter_255_empty_1_fill         | 31.35ns      |
| query_iter_1023_empty_1_fill        | 31.14ns      |
| query_iter_rnd_8_tags               | 10.90us      |
| query_iter_rnd_16_tags              | 769.62us     |
| query_count_1_table                 | 2.75ns       |
| query_count_2_tables                | 3.15ns       |
| query_count_4_tables                | 4.05ns       |
| query_count_8_tables                | 6.32ns       |
| query_count_16_tables               | 12.20ns      |
| query_count_32_tables               | 27.95ns      |
| query_count_64_tables               | 62.77ns      |
| query_count_128_tables              | 144.88ns     |
| query_count_256_tables              | 285.38ns     |
| query_count_512_tables              | 944.15ns     |
| query_count_1024_tables             | 2.93us       |
| query_count_4096_tables             | 12.76us      |
| query_count_65536_tables            | 421.66us     |
| progress_0_systems                  | 159.36ns     |
| progress_1_system                   | 229.69ns     |
| progress_10_systems                 | 615.75ns     |
| progress_100_systems                | 4.33us       |
| create_delete_table_1_id            | 126.59ns     |
| create_delete_table_10_ids          | 215.11ns     |
| create_delete_table_100_ids         | 1.13us       |
| create_delete_table_1000_ids        | 15.05us      |
| match_table_1_of_10_queries         | 243.48ns     |
| match_table_5_of_10_queries         | 483.74ns     |
| match_table_10_of_10_queries        | 781.47ns     |
| match_table_1_of_100_queries        | 245.38ns     |
| match_table_10_of_100_queries       | 780.55ns     |
| match_table_50_of_100_queries       | 3.33us       |
| match_table_100_of_100_queries      | 7.49us       |
| match_table_1_of_1000_queries       | 243.50ns     |
| match_table_10_of_1000_queries      | 782.11ns     |
| match_table_100_of_1000_queries     | 7.47us       |
| match_table_1000_of_1000_queries    | 82.60us      |
| rematch_1_of_1000_tables            | 68.16us      |
| rematch_10_of_1000_tables           | 68.27us      |
| rematch_100_of_1000_tables          | 66.15us      |
| rematch_1000_of_1000_tables         | 46.73us      |
| fill_empty_table_0_queries          | 230.59ns     |
| fill_empty_table_1_query            | 292.54ns     |
| fill_empty_table_10_queries         | 513.14ns     |
| fill_empty_table_100_queries        | 3.49us       |
| fill_empty_table_1000_queries       | 41.91us      |
| table_add_remove_1_id               | 2.65ns       |
| table_add_remove_4_ids              | 3.00ns       |
| table_add_remove_16_ids             | 4.12ns       |
| table_add_remove_32_ids             | 4.56ns       |
| table_add_remove_64_ids             | 4.83ns       |