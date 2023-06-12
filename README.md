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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.4

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 212.45us     |
| world_init_fini                     | 1.03ms       |
| has_empty_entity                    | 1.61ns       |
| has_id_not_found                    | 3.14ns       |
| has_id                              | 3.75ns       |
| has_16_ids                          | 4.08ns       |
| get_empty_entity                    | 1.57ns       |
| get_id_not_found                    | 3.76ns       |
| get_id                              | 3.47ns       |
| get_16_ids                          | 3.64ns       |
| get_pair                            | 4.74ns       |
| get_pair_16_targets                 | 4.85ns       |
| get_inherited_depth_1               | 19.15ns      |
| get_inherited_depth_2               | 30.49ns      |
| get_inherited_depth_16              | 230.74ns     |
| get_inherited_depth_32              | 474.26ns     |
| get_mut_id                          | 6.57ns       |
| get_mut_16_ids                      | 6.55ns       |
| set_id                              | 11.27ns      |
| set_16_ids                          | 11.75ns      |
| get_mut_remove_id                   | 19.25ns      |
| get_mut_remove_16_ids               | 68.57ns      |
| get_mut_remove_32_ids               | 115.22ns     |
| ref_init                            | 3.13ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 16.97ns      |
| add_remove_2_tags                   | 21.30ns      |
| add_remove_16_tags                  | 25.48ns      |
| add_remove_32_tags                  | 25.54ns      |
| add_remove_1_component              | 17.31ns      |
| add_remove_2_components             | 23.81ns      |
| add_remove_16_components            | 65.94ns      |
| add_remove_32_components            | 111.54ns     |
| add_existing_1_tag                  | 8.45ns       |
| add_existing_16_tags                | 8.90ns       |
| add_existing_1_component            | 8.46ns       |
| add_existing_16_components          | 8.92ns       |
| add_remove_tag_to_1_component       | 28.40ns      |
| add_remove_tag_to_4_components      | 47.55ns      |
| add_remove_tag_to_8_components      | 76.28ns      |
| add_remove_tag_to_16_components     | 131.87ns     |
| add_remove_tag_to_64_components     | 441.87ns     |
| add_remove_override_1               | 66.10ns      |
| add_remove_override_2               | 70.40ns      |
| add_remove_override_4               | 79.01ns      |
| add_remove_override_16              | 115.59ns     |
| add_remove_cmd_1_tag                | 23.36ns      |
| add_remove_cmd_2_tags               | 19.29ns      |
| add_remove_cmd_16_tags              | 15.06ns      |
| add_remove_cmd_32_tags              | 14.62ns      |
| add_remove_cmd_1_components         | 24.38ns      |
| add_remove_cmd_2_components         | 20.87ns      |
| add_remove_cmd_16_components        | 16.20ns      |
| add_remove_cmd_32_components        | 15.89ns      |
| get_mut_cmd_1                       | 21.88ns      |
| get_mut_cmd_2                       | 18.43ns      |
| get_mut_cmd_16                      | 15.50ns      |
| get_mut_cmd_32                      | 15.20ns      |
| set_cmd_1                           | 36.47ns      |
| set_cmd_2                           | 35.69ns      |
| set_cmd_16                          | 33.07ns      |
| set_cmd_32                          | 32.15ns      |
| get_mut_remove_cmd_1                | 29.84ns      |
| get_mut_remove_cmd_2                | 28.57ns      |
| get_mut_remove_cmd_16               | 23.83ns      |
| get_mut_remove_cmd_32               | 23.04ns      |
| add_remove_hooks_1                  | 20.28ns      |
| add_remove_hooks_2                  | 31.18ns      |
| add_remove_hooks_16                 | 95.66ns      |
| add_remove_hooks_32                 | 161.36ns     |
| create_delete_empty                 | 3.96ns       |
| create_delete_1_tag                 | 11.35ns      |
| create_delete_2_tags                | 14.95ns      |
| create_delete_16_tags               | 23.34ns      |
| create_delete_1_component           | 11.75ns      |
| create_delete_2_components          | 16.22ns      |
| create_delete_16_components         | 58.31ns      |
| entity_init_delete                  | 12.34us      |
| entity_init_w_name_delete           | 12.36us      |
| create_delete_tree_w1_d1            | 746.77ns     |
| create_delete_tree_w1_d10           | 5.00us       |
| create_delete_tree_w1_d100          | 53.29us      |
| create_delete_tree_w1_d1000         | 573.27us     |
| create_delete_tree_w10_d1           | 103.73ns     |
| create_delete_tree_w10_d10          | 788.01ns     |
| create_delete_tree_w10_d100         | 8.72us       |
| create_delete_tree_w10_d1000        | 83.01us      |
| create_delete_tree_w100_d1          | 31.92ns      |
| create_delete_tree_w100_d10         | 303.57ns     |
| create_delete_tree_w100_d100        | 3.16us       |
| create_delete_tree_w100_d1000       | 31.82us      |
| create_delete_tree_w1000_d1         | 23.74ns      |
| create_delete_tree_w1000_d10        | 248.22ns     |
| create_delete_tree_w1000_d100       | 2.49us       |
| create_delete_tree_w1000_d1000      | 27.65us      |
| change_parent                       | 25.56ns      |
| change_parent_root                  | 16.30ns      |
| change_parent_w_name                | 103.89us     |
| lookup_depth_0                      | 39.48ns      |
| lookup_depth_1                      | 69.52ns      |
| lookup_depth_10                     | 355.38ns     |
| lookup_depth_100                    | 3.38us       |
| set_name                            | 99.52ns      |
| emit_0_observers                    | 21.40ns      |
| emit_1_observer                     | 34.42ns      |
| emit_10_observers                   | 69.34ns      |
| emit_100_observers                  | 507.96ns     |
| emit_propagate_depth_1              | 29.01ns      |
| emit_propagate_depth_10             | 207.59ns     |
| emit_propagate_depth_100            | 2.41us       |
| emit_propagate_depth_1000           | 33.77us      |
| emit_forward_1_ids_depth_1          | 149.57ns     |
| emit_forward_1_ids_depth_1000       | 149.64ns     |
| emit_forward_16_ids_depth_1         | 762.22ns     |
| emit_forward_16_ids_depth_1000      | 756.33ns     |
| modified_0_observers                | 10.01ns      |
| modified_1_observer                 | 46.16ns      |
| modified_10_observers               | 80.87ns      |
| modified_100_observers              | 505.37ns     |
| filter_simple_iter_1_tags           | 6.19us       |
| filter_simple_iter_8_tags           | 6.31us       |
| filter_simple_iter_1_component      | 6.16us       |
| filter_simple_iter_8_components     | 6.32us       |
| filter_init_fini_1_ids              | 61.37ns      |
| filter_init_fini_8_ids              | 293.44ns     |
| filter_init_fini_16_ids             | 544.25ns     |
| filter_init_fini_inline_1_ids       | 54.83ns      |
| filter_init_fini_inline_8_ids       | 287.61ns     |
| filter_init_fini_inline_16_ids      | 537.96ns     |
| filter_iter_8_tags_1_term           | 6.91us       |
| filter_iter_8_tags_4_terms          | 4.98us       |
| filter_iter_16_tags_1_term          | 1.38ms       |
| filter_iter_16_tags_4_terms         | 2.43ms       |
| filter_iter_8_components_1_term     | 7.09us       |
| filter_iter_8_components_4_terms    | 5.24us       |
| filter_iter_16_components_1_term    | 1.68ms       |
| filter_iter_16_components_4_terms   | 2.64ms       |
| filter_iter_up_8_tags               | 6.38ms       |
| filter_iter_up_8_tags_w_self        | 6.27ms       |
| filter_iter_up_w_mut_8_tags         | 6.28ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.46ms       |
| rule_init_fini_1_ids                | 128.14ns     |
| rule_init_fini_8_ids                | 470.32ns     |
| rule_init_fini_16_ids               | 836.28ns     |
| rule_simple_iter_1_tags             | 6.19us       |
| rule_simple_iter_8_tags             | 6.25us       |
| rule_simple_iter_1_component        | 6.14us       |
| rule_simple_iter_8_component        | 6.29us       |
| rule_iter_8_tags_1_term             | 6.84us       |
| rule_iter_8_tags_4_terms            | 3.00us       |
| rule_iter_16_tags_1_term            | 1.09ms       |
| rule_iter_16_tags_4_terms           | 1.84ms       |
| rule_iter_8_components_1_term       | 7.04us       |
| rule_iter_8_components_4_terms      | 3.06us       |
| rule_iter_16_components_1_term      | 1.41ms       |
| rule_iter_16_components_4_terms     | 1.98ms       |
| rule_inherit_depth_1_tables_1       | 6.21us       |
| rule_inherit_depth_1_tables_1024    | 31.50us      |
| rule_inherit_depth_2_tables_1       | 6.31us       |
| rule_inherit_depth_2_tables_1024    | 31.53us      |
| rule_inherit_depth_8_tables_1       | 6.76us       |
| rule_inherit_depth_8_tables_1024    | 31.66us      |
| rule_inherit_depth_16_tables_1      | 7.24us       |
| rule_inherit_depth_16_tables_1024   | 31.64us      |
| query_init_fini_1_ids               | 679.30ns     |
| query_init_fini_8_ids               | 4.68us       |
| query_init_fini_16_ids              | 7.67us       |
| query_iter_1_table_1_tag            | 6.13us       |
| query_iter_2_tables_1_tag           | 6.26us       |
| query_iter_4_tables_1_tag           | 6.49us       |
| query_iter_8_tables_1_tag           | 6.62us       |
| query_iter_16_tables_1_tag          | 7.27us       |
| query_iter_32_tables_1_tag          | 7.51us       |
| query_iter_64_tables_1_tag          | 8.45us       |
| query_iter_128_tables_1_tag         | 9.63us       |
| query_iter_256_tables_1_tag         | 10.46us      |
| query_iter_512_tables_1_tag         | 12.79us      |
| query_iter_1024_tables_1_tag        | 17.18us      |
| query_iter_4096_tables_1_tag        | 34.32us      |
| query_iter_4096_tables_4_tags       | 34.63us      |
| query_iter_4096_tables_4_comps      | 80.55us      |
| query_iter_4096_tables_8_tags       | 34.57us      |
| query_iter_4096_tables_8_comps      | 80.66us      |
| query_iter_65536_tables_4_tags      | 849.16us     |
| query_iter_65536_tables_4_comps     | 1.95ms       |
| query_iter_65536_tables_8_tags      | 849.67us     |
| query_iter_65536_tables_8_comps     | 1.91ms       |
| query_iter_255_empty_1_fill         | 24.17ns      |
| query_iter_1023_empty_1_fill        | 24.24ns      |
| query_iter_rnd_8_tags               | 10.90us      |
| query_iter_rnd_16_tags              | 936.85us     |
| query_count_1_table                 | 2.80ns       |
| query_count_2_tables                | 3.12ns       |
| query_count_4_tables                | 4.07ns       |
| query_count_8_tables                | 6.18ns       |
| query_count_16_tables               | 12.04ns      |
| query_count_32_tables               | 26.94ns      |
| query_count_64_tables               | 61.23ns      |
| query_count_128_tables              | 144.63ns     |
| query_count_256_tables              | 281.62ns     |
| query_count_512_tables              | 846.00ns     |
| query_count_1024_tables             | 3.57us       |
| query_count_4096_tables             | 13.74us      |
| query_count_65536_tables            | 500.22us     |
| progress_0_systems                  | 94.32ns      |
| progress_1_system                   | 210.00ns     |
| progress_10_systems                 | 569.56ns     |
| progress_100_systems                | 3.98us       |
| create_delete_table_1_id            | 124.59ns     |
| create_delete_table_10_ids          | 208.93ns     |
| create_delete_table_100_ids         | 1.09us       |
| create_delete_table_1000_ids        | 14.87us      |
| match_table_1_of_10_queries         | 240.55ns     |
| match_table_5_of_10_queries         | 477.61ns     |
| match_table_10_of_10_queries        | 774.27ns     |
| match_table_1_of_100_queries        | 239.18ns     |
| match_table_10_of_100_queries       | 775.13ns     |
| match_table_50_of_100_queries       | 3.34us       |
| match_table_100_of_100_queries      | 7.55us       |
| match_table_1_of_1000_queries       | 241.17ns     |
| match_table_10_of_1000_queries      | 776.60ns     |
| match_table_100_of_1000_queries     | 7.42us       |
| match_table_1000_of_1000_queries    | 81.31us      |
| rematch_1_of_1000_tables            | 66.28us      |
| rematch_10_of_1000_tables           | 66.92us      |
| rematch_100_of_1000_tables          | 64.33us      |
| rematch_1000_of_1000_tables         | 46.87us      |
| fill_empty_table_0_queries          | 229.70ns     |
| fill_empty_table_1_query            | 376.52ns     |
| fill_empty_table_10_queries         | 604.18ns     |
| fill_empty_table_100_queries        | 3.45us       |
| fill_empty_table_1000_queries       | 43.19us      |
| table_add_remove_1_id               | 2.62ns       |
| table_add_remove_4_ids              | 2.82ns       |
| table_add_remove_16_ids             | 3.70ns       |
| table_add_remove_32_ids             | 4.08ns       |
| table_add_remove_64_ids             | 4.33ns       |
