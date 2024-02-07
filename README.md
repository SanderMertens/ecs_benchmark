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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.11

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 231.27us     |
| world_init_fini                     | 966.38us     |
| has_empty_entity                    | 1.56ns       |
| has_id_not_found                    | 3.12ns       |
| has_id                              | 4.10ns       |
| has_16_ids                          | 4.36ns       |
| get_empty_entity                    | 1.57ns       |
| get_id_not_found                    | 4.05ns       |
| get_id                              | 3.35ns       |
| get_16_ids                          | 3.47ns       |
| get_pair                            | 4.56ns       |
| get_pair_16_targets                 | 4.71ns       |
| get_inherited_depth_1               | 19.97ns      |
| get_inherited_depth_2               | 31.36ns      |
| get_inherited_depth_16              | 232.93ns     |
| get_inherited_depth_32              | 546.24ns     |
| get_mut_id                          | 6.86ns       |
| get_mut_16_ids                      | 6.88ns       |
| set_id                              | 12.46ns      |
| set_16_ids                          | 13.52ns      |
| get_mut_remove_id                   | 17.44ns      |
| get_mut_remove_16_ids               | 68.94ns      |
| get_mut_remove_32_ids               | 116.66ns     |
| ref_init                            | 3.15ns       |
| ref_get                             | 0.80ns       |
| add_remove_1_tag                    | 15.40ns      |
| add_remove_2_tags                   | 19.06ns      |
| add_remove_16_tags                  | 23.05ns      |
| add_remove_32_tags                  | 23.47ns      |
| add_remove_1_component              | 15.80ns      |
| add_remove_2_components             | 21.20ns      |
| add_remove_16_components            | 65.49ns      |
| add_remove_32_components            | 112.42ns     |
| add_existing_1_tag                  | 7.04ns       |
| add_existing_16_tags                | 7.33ns       |
| add_existing_1_component            | 7.00ns       |
| add_existing_16_components          | 7.34ns       |
| add_remove_tag_to_1_component       | 26.22ns      |
| add_remove_tag_to_4_components      | 46.48ns      |
| add_remove_tag_to_8_components      | 72.13ns      |
| add_remove_tag_to_16_components     | 131.66ns     |
| add_remove_tag_to_64_components     | 440.74ns     |
| add_remove_override_1               | 63.28ns      |
| add_remove_override_2               | 67.60ns      |
| add_remove_override_4               | 74.58ns      |
| add_remove_override_16              | 118.32ns     |
| add_remove_cmd_1_tag                | 21.14ns      |
| add_remove_cmd_2_tags               | 19.66ns      |
| add_remove_cmd_16_tags              | 17.03ns      |
| add_remove_cmd_32_tags              | 16.64ns      |
| add_remove_cmd_1_components         | 22.04ns      |
| add_remove_cmd_2_components         | 21.47ns      |
| add_remove_cmd_16_components        | 18.54ns      |
| add_remove_cmd_32_components        | 17.99ns      |
| get_mut_cmd_1                       | 19.92ns      |
| get_mut_cmd_2                       | 19.71ns      |
| get_mut_cmd_16                      | 18.43ns      |
| get_mut_cmd_32                      | 18.15ns      |
| set_cmd_1                           | 33.46ns      |
| set_cmd_2                           | 35.44ns      |
| set_cmd_16                          | 34.29ns      |
| set_cmd_32                          | 33.61ns      |
| get_mut_remove_cmd_1                | 27.10ns      |
| get_mut_remove_cmd_2                | 28.43ns      |
| get_mut_remove_cmd_16               | 25.02ns      |
| get_mut_remove_cmd_32               | 24.31ns      |
| add_remove_hooks_1                  | 18.70ns      |
| add_remove_hooks_2                  | 29.27ns      |
| add_remove_hooks_16                 | 92.84ns      |
| add_remove_hooks_32                 | 157.16ns     |
| create_100_w_add_in_observer        | 112.97ns     |
| create_1k_w_add_in_observer         | 112.39ns     |
| create_10k_w_add_in_observer        | 114.16ns     |
| create_50k_w_add_in_observer        | 114.57ns     |
| create_delete_empty                 | 4.06ns       |
| create_delete_1_tag                 | 10.39ns      |
| create_delete_2_tags                | 13.40ns      |
| create_delete_16_tags               | 20.82ns      |
| create_delete_1_component           | 10.64ns      |
| create_delete_2_components          | 14.76ns      |
| create_delete_16_components         | 57.93ns      |
| entity_init_delete                  | 12.74us      |
| entity_init_w_name_delete           | 12.76us      |
| create_delete_tree_w1_d1            | 783.67ns     |
| create_delete_tree_w1_d10           | 4.82us       |
| create_delete_tree_w1_d100          | 50.47us      |
| create_delete_tree_w1_d1000         | 550.11us     |
| create_delete_tree_w10_d1           | 100.34ns     |
| create_delete_tree_w10_d10          | 746.98ns     |
| create_delete_tree_w10_d100         | 7.82us       |
| create_delete_tree_w10_d1000        | 77.85us      |
| create_delete_tree_w100_d1          | 29.11ns      |
| create_delete_tree_w100_d10         | 277.41ns     |
| create_delete_tree_w100_d100        | 2.90us       |
| create_delete_tree_w100_d1000       | 29.47us      |
| create_delete_tree_w1000_d1         | 21.22ns      |
| create_delete_tree_w1000_d10        | 229.34ns     |
| create_delete_tree_w1000_d100       | 2.29us       |
| create_delete_tree_w1000_d1000      | 24.99us      |
| change_parent                       | 23.32ns      |
| change_parent_root                  | 14.83ns      |
| change_parent_w_name                | 98.13us      |
| lookup_depth_0                      | 40.89ns      |
| lookup_depth_1                      | 72.29ns      |
| lookup_depth_10                     | 367.78ns     |
| lookup_depth_100                    | 3.41us       |
| set_name                            | 97.56ns      |
| emit_0_observers                    | 23.56ns      |
| emit_1_observer                     | 36.99ns      |
| emit_10_observers                   | 73.49ns      |
| emit_100_observers                  | 500.68ns     |
| emit_propagate_depth_1              | 31.65ns      |
| emit_propagate_depth_10             | 211.71ns     |
| emit_propagate_depth_100            | 2.47us       |
| emit_propagate_depth_1000           | 35.04us      |
| emit_forward_1_ids_depth_1          | 143.13ns     |
| emit_forward_1_ids_depth_1000       | 142.93ns     |
| emit_forward_16_ids_depth_1         | 866.73ns     |
| emit_forward_16_ids_depth_1000      | 878.52ns     |
| modified_0_observers                | 9.98ns       |
| modified_1_observer                 | 47.31ns      |
| modified_10_observers               | 83.33ns      |
| modified_100_observers              | 512.68ns     |
| filter_simple_iter_self_1_tags      | 6.16us       |
| filter_simple_iter_self_8_tags      | 6.35us       |
| filter_simple_iter_self_1_component   | 6.17us       |
| filter_simple_iter_self_8_components    | 6.26us       |
| filter_simple_iter_1_tags           | 6.12us       |
| filter_simple_iter_8_tags           | 6.26us       |
| filter_simple_iter_1_component      | 6.11us       |
| filter_simple_iter_8_components     | 6.26us       |
| filter_init_fini_1_ids              | 64.53ns      |
| filter_init_fini_8_ids              | 317.87ns     |
| filter_init_fini_16_ids             | 599.12ns     |
| filter_init_fini_inline_1_ids       | 58.39ns      |
| filter_init_fini_inline_8_ids       | 311.31ns     |
| filter_init_fini_inline_16_ids      | 594.46ns     |
| filter_iter_8_tags_1_term           | 6.52us       |
| filter_iter_8_tags_4_terms          | 4.73us       |
| filter_iter_16_tags_1_term          | 1.24ms       |
| filter_iter_16_tags_4_terms         | 2.27ms       |
| filter_iter_8_components_1_term     | 6.93us       |
| filter_iter_8_components_4_terms    | 5.00us       |
| filter_iter_16_components_1_term    | 1.63ms       |
| filter_iter_16_components_4_terms   | 2.45ms       |
| filter_iter_up_8_tags               | 5.88ms       |
| filter_iter_up_8_tags_w_self        | 6.10ms       |
| filter_iter_up_w_mut_8_tags         | 5.91ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.06ms       |
| rule_init_fini_1_ids                | 133.29ns     |
| rule_init_fini_8_ids                | 382.03ns     |
| rule_init_fini_16_ids               | 663.28ns     |
| rule_simple_iter_self_1_tags        | 6.14us       |
| rule_simple_iter_self_8_tags        | 6.28us       |
| rule_simple_iter_self_1_component   | 6.12us       |
| rule_simple_iter_self_8_component   | 6.17us       |
| rule_simple_iter_1_tags             | 6.13us       |
| rule_simple_iter_8_tags             | 6.21us       |
| rule_simple_iter_1_component        | 6.13us       |
| rule_simple_iter_8_component        | 6.20us       |
| rule_iter_8_tags_1_term             | 6.32us       |
| rule_iter_8_tags_4_terms            | 871.70ns     |
| rule_iter_16_tags_1_term            | 701.81us     |
| rule_iter_16_tags_4_terms           | 1.25ms       |
| rule_iter_8_components_1_term       | 6.60us       |
| rule_iter_8_components_4_terms      | 1.23us       |
| rule_iter_16_components_1_term      | 1.08ms       |
| rule_iter_16_components_4_terms     | 1.37ms       |
| rule_inherit_depth_1_tables_1       | 6.29us       |
| rule_inherit_depth_1_tables_1024    | 32.14us      |
| rule_inherit_depth_2_tables_1       | 6.30us       |
| rule_inherit_depth_2_tables_1024    | 31.75us      |
| rule_inherit_depth_8_tables_1       | 6.77us       |
| rule_inherit_depth_8_tables_1024    | 32.78us      |
| rule_inherit_depth_16_tables_1      | 7.21us       |
| rule_inherit_depth_16_tables_1024   | 33.21us      |
| query_init_fini_1_ids               | 730.90ns     |
| query_init_fini_8_ids               | 4.80us       |
| query_init_fini_16_ids              | 7.74us       |
| query_iter_1_table_1_tag            | 6.09us       |
| query_iter_2_tables_1_tag           | 6.20us       |
| query_iter_4_tables_1_tag           | 6.35us       |
| query_iter_8_tables_1_tag           | 6.77us       |
| query_iter_16_tables_1_tag          | 7.25us       |
| query_iter_32_tables_1_tag          | 6.80us       |
| query_iter_64_tables_1_tag          | 7.36us       |
| query_iter_128_tables_1_tag         | 8.49us       |
| query_iter_256_tables_1_tag         | 9.02us       |
| query_iter_512_tables_1_tag         | 10.87us      |
| query_iter_1024_tables_1_tag        | 14.54us      |
| query_iter_4096_tables_1_tag        | 31.70us      |
| query_iter_4096_tables_4_tags       | 31.71us      |
| query_iter_4096_tables_4_comps      | 81.18us      |
| query_iter_4096_tables_8_tags       | 32.54us      |
| query_iter_4096_tables_8_comps      | 80.67us      |
| query_iter_65536_tables_4_tags      | 750.88us     |
| query_iter_65536_tables_4_comps     | 2.52ms       |
| query_iter_65536_tables_8_tags      | 755.13us     |
| query_iter_65536_tables_8_comps     | 2.52ms       |
| query_iter_255_empty_1_fill         | 28.75ns      |
| query_iter_1023_empty_1_fill        | 28.79ns      |
| query_iter_rnd_8_tags               | 10.91us      |
| query_iter_rnd_16_tags              | 767.68us     |
| query_count_1_table                 | 2.75ns       |
| query_count_2_tables                | 3.15ns       |
| query_count_4_tables                | 4.09ns       |
| query_count_8_tables                | 6.34ns       |
| query_count_16_tables               | 12.34ns      |
| query_count_32_tables               | 27.75ns      |
| query_count_64_tables               | 63.01ns      |
| query_count_128_tables              | 146.54ns     |
| query_count_256_tables              | 287.80ns     |
| query_count_512_tables              | 715.40ns     |
| query_count_1024_tables             | 2.98us       |
| query_count_4096_tables             | 12.90us      |
| query_count_65536_tables            | 420.37us     |
| progress_0_systems                  | 157.17ns     |
| progress_1_system                   | 227.30ns     |
| progress_10_systems                 | 594.65ns     |
| progress_100_systems                | 4.13us       |
| create_delete_table_1_id            | 129.51ns     |
| create_delete_table_10_ids          | 218.99ns     |
| create_delete_table_100_ids         | 1.13us       |
| create_delete_table_1000_ids        | 15.23us      |
| match_table_1_of_10_queries         | 243.17ns     |
| match_table_5_of_10_queries         | 487.15ns     |
| match_table_10_of_10_queries        | 782.08ns     |
| match_table_1_of_100_queries        | 244.41ns     |
| match_table_10_of_100_queries       | 784.58ns     |
| match_table_50_of_100_queries       | 3.37us       |
| match_table_100_of_100_queries      | 7.56us       |
| match_table_1_of_1000_queries       | 243.03ns     |
| match_table_10_of_1000_queries      | 784.26ns     |
| match_table_100_of_1000_queries     | 7.57us       |
| match_table_1000_of_1000_queries    | 82.75us      |
| rematch_1_of_1000_tables            | 68.60us      |
| rematch_10_of_1000_tables           | 68.07us      |
| rematch_100_of_1000_tables          | 65.83us      |
| rematch_1000_of_1000_tables         | 47.54us      |
| fill_empty_table_0_queries          | 217.24ns     |
| fill_empty_table_1_query            | 280.48ns     |
| fill_empty_table_10_queries         | 513.32ns     |
| fill_empty_table_100_queries        | 3.60us       |
| fill_empty_table_1000_queries       | 42.69us      |
| table_add_remove_1_id               | 2.66ns       |
| table_add_remove_4_ids              | 2.99ns       |
| table_add_remove_16_ids             | 4.14ns       |
| table_add_remove_32_ids             | 4.54ns       |
| table_add_remove_64_ids             | 4.86ns       |
