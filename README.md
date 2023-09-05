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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.7

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 219.41us     |
| world_init_fini                     | 948.03us     |
| has_empty_entity                    | 1.56ns       |
| has_id_not_found                    | 3.12ns       |
| has_id                              | 3.91ns       |
| has_16_ids                          | 4.30ns       |
| get_empty_entity                    | 1.56ns       |
| get_id_not_found                    | 4.05ns       |
| get_id                              | 3.32ns       |
| get_16_ids                          | 3.48ns       |
| get_pair                            | 4.57ns       |
| get_pair_16_targets                 | 4.73ns       |
| get_inherited_depth_1               | 19.41ns      |
| get_inherited_depth_2               | 31.77ns      |
| get_inherited_depth_16              | 233.58ns     |
| get_inherited_depth_32              | 524.42ns     |
| get_mut_id                          | 6.86ns       |
| get_mut_16_ids                      | 6.90ns       |
| set_id                              | 12.58ns      |
| set_16_ids                          | 13.23ns      |
| get_mut_remove_id                   | 18.00ns      |
| get_mut_remove_16_ids               | 70.94ns      |
| get_mut_remove_32_ids               | 116.76ns     |
| ref_init                            | 3.12ns       |
| ref_get                             | 0.69ns       |
| add_remove_1_tag                    | 16.76ns      |
| add_remove_2_tags                   | 20.17ns      |
| add_remove_16_tags                  | 24.21ns      |
| add_remove_32_tags                  | 24.37ns      |
| add_remove_1_component              | 16.45ns      |
| add_remove_2_components             | 22.66ns      |
| add_remove_16_components            | 67.78ns      |
| add_remove_32_components            | 115.22ns     |
| add_existing_1_tag                  | 6.71ns       |
| add_existing_16_tags                | 7.14ns       |
| add_existing_1_component            | 6.79ns       |
| add_existing_16_components          | 7.15ns       |
| add_remove_tag_to_1_component       | 26.95ns      |
| add_remove_tag_to_4_components      | 46.95ns      |
| add_remove_tag_to_8_components      | 74.33ns      |
| add_remove_tag_to_16_components     | 132.72ns     |
| add_remove_tag_to_64_components     | 440.06ns     |
| add_remove_override_1               | 62.81ns      |
| add_remove_override_2               | 65.83ns      |
| add_remove_override_4               | 78.98ns      |
| add_remove_override_16              | 119.72ns     |
| add_remove_cmd_1_tag                | 23.86ns      |
| add_remove_cmd_2_tags               | 19.35ns      |
| add_remove_cmd_16_tags              | 14.39ns      |
| add_remove_cmd_32_tags              | 13.91ns      |
| add_remove_cmd_1_components         | 24.39ns      |
| add_remove_cmd_2_components         | 21.13ns      |
| add_remove_cmd_16_components        | 15.59ns      |
| add_remove_cmd_32_components        | 15.10ns      |
| get_mut_cmd_1                       | 21.68ns      |
| get_mut_cmd_2                       | 19.60ns      |
| get_mut_cmd_16                      | 16.28ns      |
| get_mut_cmd_32                      | 15.81ns      |
| set_cmd_1                           | 35.47ns      |
| set_cmd_2                           | 36.61ns      |
| set_cmd_16                          | 33.72ns      |
| set_cmd_32                          | 32.72ns      |
| get_mut_remove_cmd_1                | 29.62ns      |
| get_mut_remove_cmd_2                | 29.72ns      |
| get_mut_remove_cmd_16               | 25.20ns      |
| get_mut_remove_cmd_32               | 23.61ns      |
| add_remove_hooks_1                  | 19.23ns      |
| add_remove_hooks_2                  | 30.13ns      |
| add_remove_hooks_16                 | 95.32ns      |
| add_remove_hooks_32                 | 161.30ns     |
| create_delete_empty                 | 3.95ns       |
| create_delete_1_tag                 | 11.03ns      |
| create_delete_2_tags                | 14.04ns      |
| create_delete_16_tags               | 21.87ns      |
| create_delete_1_component           | 11.17ns      |
| create_delete_2_components          | 15.56ns      |
| create_delete_16_components         | 59.53ns      |
| entity_init_delete                  | 12.43us      |
| entity_init_w_name_delete           | 12.43us      |
| create_delete_tree_w1_d1            | 781.30ns     |
| create_delete_tree_w1_d10           | 4.96us       |
| create_delete_tree_w1_d100          | 52.90us      |
| create_delete_tree_w1_d1000         | 563.83us     |
| create_delete_tree_w10_d1           | 106.28ns     |
| create_delete_tree_w10_d10          | 781.01ns     |
| create_delete_tree_w10_d100         | 8.26us       |
| create_delete_tree_w10_d1000        | 82.52us      |
| create_delete_tree_w100_d1          | 31.13ns      |
| create_delete_tree_w100_d10         | 297.06ns     |
| create_delete_tree_w100_d100        | 3.09us       |
| create_delete_tree_w100_d1000       | 31.10us      |
| create_delete_tree_w1000_d1         | 22.87ns      |
| create_delete_tree_w1000_d10        | 239.61ns     |
| create_delete_tree_w1000_d100       | 2.42us       |
| create_delete_tree_w1000_d1000      | 26.51us      |
| change_parent                       | 24.27ns      |
| change_parent_root                  | 16.12ns      |
| change_parent_w_name                | 98.22us      |
| lookup_depth_0                      | 39.29ns      |
| lookup_depth_1                      | 69.22ns      |
| lookup_depth_10                     | 365.16ns     |
| lookup_depth_100                    | 3.44us       |
| set_name                            | 97.54ns      |
| emit_0_observers                    | 21.10ns      |
| emit_1_observer                     | 34.72ns      |
| emit_10_observers                   | 71.94ns      |
| emit_100_observers                  | 527.08ns     |
| emit_propagate_depth_1              | 28.63ns      |
| emit_propagate_depth_10             | 209.31ns     |
| emit_propagate_depth_100            | 2.44us       |
| emit_propagate_depth_1000           | 33.33us      |
| emit_forward_1_ids_depth_1          | 144.42ns     |
| emit_forward_1_ids_depth_1000       | 144.65ns     |
| emit_forward_16_ids_depth_1         | 751.94ns     |
| emit_forward_16_ids_depth_1000      | 778.10ns     |
| modified_0_observers                | 9.82ns       |
| modified_1_observer                 | 47.41ns      |
| modified_10_observers               | 83.46ns      |
| modified_100_observers              | 529.39ns     |
| filter_simple_iter_1_tags           | 6.19us       |
| filter_simple_iter_8_tags           | 6.44us       |
| filter_simple_iter_1_component      | 6.26us       |
| filter_simple_iter_8_components     | 6.22us       |
| filter_init_fini_1_ids              | 63.75ns      |
| filter_init_fini_8_ids              | 290.45ns     |
| filter_init_fini_16_ids             | 534.99ns     |
| filter_init_fini_inline_1_ids       | 54.19ns      |
| filter_init_fini_inline_8_ids       | 282.41ns     |
| filter_init_fini_inline_16_ids      | 529.26ns     |
| filter_iter_8_tags_1_term           | 6.83us       |
| filter_iter_8_tags_4_terms          | 4.82us       |
| filter_iter_16_tags_1_term          | 1.32ms       |
| filter_iter_16_tags_4_terms         | 2.32ms       |
| filter_iter_8_components_1_term     | 7.04us       |
| filter_iter_8_components_4_terms    | 4.97us       |
| filter_iter_16_components_1_term    | 1.64ms       |
| filter_iter_16_components_4_terms   | 2.46ms       |
| filter_iter_up_8_tags               | 5.76ms       |
| filter_iter_up_8_tags_w_self        | 5.86ms       |
| filter_iter_up_w_mut_8_tags         | 5.75ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.32ms       |
| rule_init_fini_1_ids                | 126.10ns     |
| rule_init_fini_8_ids                | 464.38ns     |
| rule_init_fini_16_ids               | 824.68ns     |
| rule_simple_iter_1_tags             | 6.19us       |
| rule_simple_iter_8_tags             | 6.30us       |
| rule_simple_iter_1_component        | 6.20us       |
| rule_simple_iter_8_component        | 6.26us       |
| rule_iter_8_tags_1_term             | 6.92us       |
| rule_iter_8_tags_4_terms            | 3.00us       |
| rule_iter_16_tags_1_term            | 987.96us     |
| rule_iter_16_tags_4_terms           | 1.84ms       |
| rule_iter_8_components_1_term       | 7.20us       |
| rule_iter_8_components_4_terms      | 3.12us       |
| rule_iter_16_components_1_term      | 1.41ms       |
| rule_iter_16_components_4_terms     | 2.02ms       |
| rule_inherit_depth_1_tables_1       | 6.23us       |
| rule_inherit_depth_1_tables_1024    | 31.40us      |
| rule_inherit_depth_2_tables_1       | 6.58us       |
| rule_inherit_depth_2_tables_1024    | 31.95us      |
| rule_inherit_depth_8_tables_1       | 6.70us       |
| rule_inherit_depth_8_tables_1024    | 32.18us      |
| rule_inherit_depth_16_tables_1      | 7.27us       |
| rule_inherit_depth_16_tables_1024   | 32.43us      |
| query_init_fini_1_ids               | 676.88ns     |
| query_init_fini_8_ids               | 4.77us       |
| query_init_fini_16_ids              | 7.68us       |
| query_iter_1_table_1_tag            | 6.12us       |
| query_iter_2_tables_1_tag           | 6.24us       |
| query_iter_4_tables_1_tag           | 6.37us       |
| query_iter_8_tables_1_tag           | 6.80us       |
| query_iter_16_tables_1_tag          | 7.44us       |
| query_iter_32_tables_1_tag          | 7.48us       |
| query_iter_64_tables_1_tag          | 8.49us       |
| query_iter_128_tables_1_tag         | 9.61us       |
| query_iter_256_tables_1_tag         | 10.48us      |
| query_iter_512_tables_1_tag         | 13.06us      |
| query_iter_1024_tables_1_tag        | 17.62us      |
| query_iter_4096_tables_1_tag        | 35.45us      |
| query_iter_4096_tables_4_tags       | 34.62us      |
| query_iter_4096_tables_4_comps      | 81.67us      |
| query_iter_4096_tables_8_tags       | 34.58us      |
| query_iter_4096_tables_8_comps      | 81.59us      |
| query_iter_65536_tables_4_tags      | 827.15us     |
| query_iter_65536_tables_4_comps     | 2.59ms       |
| query_iter_65536_tables_8_tags      | 824.41us     |
| query_iter_65536_tables_8_comps     | 2.64ms       |
| query_iter_255_empty_1_fill         | 28.53ns      |
| query_iter_1023_empty_1_fill        | 29.45ns      |
| query_iter_rnd_8_tags               | 11.67us      |
| query_iter_rnd_16_tags              | 847.18us     |
| query_count_1_table                 | 2.73ns       |
| query_count_2_tables                | 3.08ns       |
| query_count_4_tables                | 4.03ns       |
| query_count_8_tables                | 6.15ns       |
| query_count_16_tables               | 11.89ns      |
| query_count_32_tables               | 26.79ns      |
| query_count_64_tables               | 60.63ns      |
| query_count_128_tables              | 150.07ns     |
| query_count_256_tables              | 280.51ns     |
| query_count_512_tables              | 1.02us       |
| query_count_1024_tables             | 3.61us       |
| query_count_4096_tables             | 13.49us      |
| query_count_65536_tables            | 471.06us     |
| progress_0_systems                  | 155.57ns     |
| progress_1_system                   | 236.84ns     |
| progress_10_systems                 | 585.51ns     |
| progress_100_systems                | 4.11us       |
| create_delete_table_1_id            | 125.76ns     |
| create_delete_table_10_ids          | 214.70ns     |
| create_delete_table_100_ids         | 1.13us       |
| create_delete_table_1000_ids        | 14.96us      |
| match_table_1_of_10_queries         | 241.79ns     |
| match_table_5_of_10_queries         | 481.51ns     |
| match_table_10_of_10_queries        | 773.98ns     |
| match_table_1_of_100_queries        | 241.86ns     |
| match_table_10_of_100_queries       | 777.95ns     |
| match_table_50_of_100_queries       | 3.26us       |
| match_table_100_of_100_queries      | 7.46us       |
| match_table_1_of_1000_queries       | 246.60ns     |
| match_table_10_of_1000_queries      | 798.02ns     |
| match_table_100_of_1000_queries     | 7.56us       |
| match_table_1000_of_1000_queries    | 81.94us      |
| rematch_1_of_1000_tables            | 64.45us      |
| rematch_10_of_1000_tables           | 65.35us      |
| rematch_100_of_1000_tables          | 64.18us      |
| rematch_1000_of_1000_tables         | 45.56us      |
| fill_empty_table_0_queries          | 225.53ns     |
| fill_empty_table_1_query            | 398.52ns     |
| fill_empty_table_10_queries         | 615.50ns     |
| fill_empty_table_100_queries        | 3.71us       |
| fill_empty_table_1000_queries       | 42.77us      |
| table_add_remove_1_id               | 2.01ns       |
| table_add_remove_4_ids              | 2.14ns       |
| table_add_remove_16_ids             | 3.99ns       |
| table_add_remove_32_ids             | 4.44ns       |
| table_add_remove_64_ids             | 4.70ns       |
