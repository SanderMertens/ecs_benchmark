# Flecs benchmarks
Keep the following in mind when interpreting the benchmarks:
- To prevent operations from being entirely optimized away by the compiler, the benchmarks have been measured against a shared library/DLL. Performance will be better if Flecs is compiled as part of an application.
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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.2.2

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 286.66us     |
| world_init_fini                     | 1.18ms       |
| has_empty_entity                    | 1.91ns       |
| has_id_not_found                    | 3.44ns       |
| has_id                              | 4.07ns       |
| has_16_ids                          | 4.54ns       |
| get_empty_entity                    | 1.98ns       |
| get_id_not_found                    | 4.18ns       |
| get_id                              | 3.57ns       |
| get_16_ids                          | 3.87ns       |
| get_pair                            | 4.71ns       |
| get_pair_16_targets                 | 4.99ns       |
| get_mut_id                          | 7.41ns       |
| get_mut_16_ids                      | 7.62ns       |
| set_id                              | 11.87ns      |
| set_16_ids                          | 12.32ns      |
| get_mut_remove_id                   | 20.97ns      |
| get_mut_remove_16_ids               | 82.53ns      |
| get_mut_remove_32_ids               | 142.59ns     |
| ref_init                            | 4.38ns       |
| ref_get                             | 2.19ns       |
| add_remove_1_tag                    | 17.47ns      |
| add_remove_2_tags                   | 22.70ns      |
| add_remove_16_tags                  | 27.53ns      |
| add_remove_32_tags                  | 27.64ns      |
| add_remove_1_component              | 18.40ns      |
| add_remove_2_components             | 26.75ns      |
| add_remove_16_components            | 78.54ns      |
| add_remove_32_components            | 138.29ns     |
| add_existing_1_tag                  | 10.00ns      |
| add_existing_16_tags                | 10.33ns      |
| add_existing_1_component            | 9.99ns       |
| add_existing_16_components          | 10.34ns      |
| add_remove_override_1               | 69.05ns      |
| add_remove_override_2               | 74.42ns      |
| add_remove_override_4               | 82.52ns      |
| add_remove_override_16              | 127.91ns     |
| add_remove_cmd_1_tag                | 27.85ns      |
| add_remove_cmd_2_tags               | 23.93ns      |
| add_remove_cmd_16_tags              | 17.63ns      |
| add_remove_cmd_32_tags              | 17.59ns      |
| add_remove_cmd_1_components         | 29.76ns      |
| add_remove_cmd_2_components         | 26.02ns      |
| add_remove_cmd_16_components        | 19.59ns      |
| add_remove_cmd_32_components        | 19.22ns      |
| get_mut_cmd_1                       | 28.09ns      |
| get_mut_cmd_2                       | 22.98ns      |
| get_mut_cmd_16                      | 19.13ns      |
| get_mut_cmd_32                      | 19.19ns      |
| set_cmd_1                           | 40.49ns      |
| set_cmd_2                           | 39.20ns      |
| set_cmd_16                          | 35.65ns      |
| set_cmd_32                          | 34.88ns      |
| get_mut_remove_cmd_1                | 35.59ns      |
| get_mut_remove_cmd_2                | 34.58ns      |
| get_mut_remove_cmd_16               | 27.75ns      |
| get_mut_remove_cmd_32               | 27.10ns      |
| add_remove_hooks_1                  | 20.70ns      |
| add_remove_hooks_2                  | 33.23ns      |
| add_remove_hooks_16                 | 107.25ns     |
| add_remove_hooks_32                 | 179.65ns     |
| create_delete_empty                 | 4.38ns       |
| create_delete_1_tag                 | 12.45ns      |
| create_delete_2_tags                | 16.30ns      |
| create_delete_16_tags               | 25.51ns      |
| create_delete_1_component           | 13.15ns      |
| create_delete_2_components          | 18.81ns      |
| create_delete_16_components         | 71.29ns      |
| create_delete_tree_depth_1          | 1.13us       |
| create_delete_tree_depth_10         | 8.44us       |
| create_delete_tree_depth_100        | 85.84us      |
| create_delete_tree_depth_1000       | 915.99us     |
| change_parent                       | 212.85ns     |
| change_parent_root                  | 109.56ns     |
| change_parent_w_name                | 315.37ns     |
| lookup_depth_0                      | 40.97ns      |
| lookup_depth_1                      | 72.02ns      |
| lookup_depth_10                     | 368.35ns     |
| lookup_depth_100                    | 3.49us       |
| emit_0_observers                    | 22.10ns      |
| emit_1_observer                     | 35.38ns      |
| emit_10_observers                   | 71.88ns      |
| emit_100_observers                  | 445.26ns     |
| emit_propagate_depth_1              | 28.92ns      |
| emit_propagate_depth_10             | 196.27ns     |
| emit_propagate_depth_100            | 2.21us       |
| emit_propagate_depth_1000           | 33.43us      |
| emit_forward_1_ids_depth_1          | 264.25ns     |
| emit_forward_1_ids_depth_1000       | 264.63ns     |
| emit_forward_16_ids_depth_1         | 836.56ns     |
| emit_forward_16_ids_depth_1000      | 839.45ns     |
| modified_0_observers                | 10.63ns      |
| modified_1_observer                 | 46.41ns      |
| modified_10_observers               | 83.62ns      |
| modified_100_observers              | 461.91ns     |
| filter_init_fini_1_ids              | 63.34ns      |
| filter_init_fini_16_ids             | 590.17ns     |
| filter_init_fini_inline_1_ids       | 57.41ns      |
| filter_init_fini_inline_16_ids      | 587.15ns     |
| filter_iter_8_tags_1_term           | 2.04us       |
| filter_iter_8_tags_4_terms          | 4.93us       |
| filter_iter_16_tags_1_term          | 1.22ms       |
| filter_iter_16_tags_4_terms         | 2.25ms       |
| filter_iter_8_components_1_term     | 2.33us       |
| filter_iter_8_components_4_terms    | 5.10us       |
| filter_iter_16_components_1_term    | 1.39ms       |
| filter_iter_16_components_4_terms   | 2.46ms       |
| filter_iter_up_8_tags               | 5.76ms       |
| filter_iter_up_8_tags_w_self        | 5.73ms       |
| filter_iter_up_w_mut_8_tags         | 5.81ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 5.74ms       |
| query_init_fini_1_ids               | 677.28ns     |
| query_init_fini_16_ids              | 9.45us       |
| query_iter_8_tags_1_term            | 32.24ns      |
| query_iter_8_tags_4_terms           | 32.32ns      |
| query_iter_16_tags_1_term           | 32.30ns      |
| query_iter_16_tags_4_terms          | 26.73ns      |
| query_iter_8_components_1_term      | 39.48ns      |
| query_iter_8_components_4_terms     | 39.54ns      |
| query_iter_16_components_1_term     | 26.68ns      |
| query_iter_16_components_4_terms    | 44.57ns      |
| progress_0_systems                  | 82.63ns      |
| progress_1_system                   | 167.96ns     |
| progress_10_systems                 | 530.71ns     |
| progress_100_systems                | 4.03us       |
| create_delete_table_1_id            | 141.47ns     |
| create_delete_table_10_ids          | 236.52ns     |
| create_delete_table_100_ids         | 1.22us       |
| create_delete_table_1000_ids        | 15.98us      |
| match_table_1_of_10_queries         | 235.58ns     |
| match_table_5_of_10_queries         | 478.81ns     |
| match_table_10_of_10_queries        | 768.29ns     |
| match_table_1_of_100_queries        | 236.11ns     |
| match_table_10_of_100_queries       | 770.22ns     |
| match_table_50_of_100_queries       | 3.43us       |
| match_table_100_of_100_queries      | 7.88us       |
| match_table_1_of_1000_queries       | 235.90ns     |
| match_table_10_of_1000_queries      | 770.84ns     |
| match_table_100_of_1000_queries     | 7.84us       |
| match_table_1000_of_1000_queries    | 85.96us      |
| rematch_1_of_1000_tables            | 67.06us      |
| rematch_10_of_1000_tables           | 66.56us      |
| rematch_100_of_1000_tables          | 65.18us      |
| rematch_1000_of_1000_tables         | 47.45us      |
| fill_empty_table_0_queries          | 250.20ns     |
| fill_empty_table_1_query            | 400.34ns     |
| fill_empty_table_10_queries         | 640.75ns     |
| fill_empty_table_100_queries        | 3.99us       |
| fill_empty_table_1000_queries       | 45.84us      |
| table_add_remove_1_id               | 3.64ns       |
| table_add_remove_4_ids              | 3.63ns       |
| table_add_remove_16_ids             | 4.17ns       |
| table_add_remove_32_ids             | 4.44ns       |
| table_add_remove_64_ids             | 4.60ns       |
