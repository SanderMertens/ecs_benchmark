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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.1.5

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 300.43us     |
| world_init_fini                     | 1.12ms       |
| has_empty_entity                    | 1.89ns       |
| has_id_not_found                    | 3.46ns       |
| has_id                              | 4.40ns       |
| has_16_ids                          | 4.66ns       |
| get_empty_entity                    | 1.89ns       |
| get_id_not_found                    | 3.77ns       |
| get_id                              | 3.71ns       |
| get_16_ids                          | 3.95ns       |
| get_pair                            | 4.60ns       |
| get_pair_16_targets                 | 4.87ns       |
| get_mut_id                          | 7.33ns       |
| get_mut_16_ids                      | 7.60ns       |
| set_id                              | 11.58ns      |
| set_16_ids                          | 12.07ns      |
| get_mut_remove_id                   | 21.01ns      |
| get_mut_remove_16_ids               | 83.09ns      |
| get_mut_remove_32_ids               | 143.93ns     |
| ref_init                            | 4.39ns       |
| ref_get                             | 2.20ns       |
| add_remove_1_tag                    | 17.55ns      |
| add_remove_2_tags                   | 22.65ns      |
| add_remove_16_tags                  | 27.69ns      |
| add_remove_32_tags                  | 27.82ns      |
| add_remove_1_component              | 18.62ns      |
| add_remove_2_components             | 26.74ns      |
| add_remove_16_components            | 80.31ns      |
| add_remove_32_components            | 139.29ns     |
| add_existing_1_tag                  | 9.73ns       |
| add_existing_16_tags                | 10.06ns      |
| add_existing_1_component            | 9.72ns       |
| add_existing_16_components          | 10.07ns      |
| add_remove_override_1               | 68.85ns      |
| add_remove_override_2               | 74.12ns      |
| add_remove_override_4               | 83.01ns      |
| add_remove_override_16              | 129.27ns     |
| add_remove_cmd_1_tag                | 28.75ns      |
| add_remove_cmd_2_tags               | 24.06ns      |
| add_remove_cmd_16_tags              | 17.66ns      |
| add_remove_cmd_32_tags              | 17.62ns      |
| add_remove_cmd_1_components         | 30.39ns      |
| add_remove_cmd_2_components         | 26.06ns      |
| add_remove_cmd_16_components        | 19.71ns      |
| add_remove_cmd_32_components        | 19.76ns      |
| get_mut_cmd_1                       | 28.16ns      |
| get_mut_cmd_2                       | 22.74ns      |
| get_mut_cmd_16                      | 18.89ns      |
| get_mut_cmd_32                      | 18.90ns      |
| set_cmd_1                           | 40.70ns      |
| set_cmd_2                           | 26.96ns      |
| set_cmd_16                          | 22.63ns      |
| set_cmd_32                          | 22.68ns      |
| get_mut_remove_cmd_1                | 36.35ns      |
| get_mut_remove_cmd_2                | 34.79ns      |
| get_mut_remove_cmd_16               | 27.86ns      |
| get_mut_remove_cmd_32               | 27.38ns      |
| add_remove_hooks_1                  | 21.38ns      |
| add_remove_hooks_2                  | 33.41ns      |
| add_remove_hooks_16                 | 108.60ns     |
| add_remove_hooks_32                 | 180.29ns     |
| create_delete_empty                 | 5.48ns       |
| create_delete_1_tag                 | 13.00ns      |
| create_delete_2_tags                | 16.77ns      |
| create_delete_16_tags               | 25.71ns      |
| create_delete_1_component           | 13.75ns      |
| create_delete_2_components          | 19.23ns      |
| create_delete_16_components         | 73.37ns      |
| create_delete_tree_depth_1          | 1.17us       |
| create_delete_tree_depth_10         | 8.97us       |
| create_delete_tree_depth_100        | 90.75us      |
| create_delete_tree_depth_1000       | 930.34us     |
| change_parent                       | 249.44ns     |
| change_parent_root                  | 119.48ns     |
| change_parent_w_name                | 337.53ns     |
| lookup_depth_0                      | 40.49ns      |
| lookup_depth_1                      | 71.08ns      |
| lookup_depth_10                     | 365.55ns     |
| lookup_depth_100                    | 3.71us       |
| emit_0_observers                    | 21.54ns      |
| emit_1_observer                     | 34.76ns      |
| emit_10_observers                   | 70.61ns      |
| emit_100_observers                  | 442.67ns     |
| emit_propagate_depth_1              | 28.27ns      |
| emit_propagate_depth_10             | 174.95ns     |
| emit_propagate_depth_100            | 2.08us       |
| emit_propagate_depth_1000           | 32.51us      |
| emit_forward_1_ids_depth_1          | 288.04ns     |
| emit_forward_1_ids_depth_1000       | 285.40ns     |
| emit_forward_16_ids_depth_1         | 864.35ns     |
| emit_forward_16_ids_depth_1000      | 884.18ns     |
| modified_0_observers                | 10.39ns      |
| modified_1_observer                 | 46.92ns      |
| modified_10_observers               | 82.20ns      |
| modified_100_observers              | 457.70ns     |
| filter_init_fini_1_ids              | 70.11ns      |
| filter_init_fini_16_ids             | 508.30ns     |
| filter_init_fini_inline_1_ids       | 58.80ns      |
| filter_init_fini_inline_16_ids      | 499.64ns     |
| filter_iter_8_tags_1_term           | 2.28us       |
| filter_iter_8_tags_4_terms          | 4.55us       |
| filter_iter_16_tags_1_term          | 1.17ms       |
| filter_iter_16_tags_4_terms         | 2.45ms       |
| filter_iter_8_components_1_term     | 2.42us       |
| filter_iter_8_components_4_terms    | 4.68us       |
| filter_iter_16_components_1_term    | 1.47ms       |
| filter_iter_16_components_4_terms   | 2.66ms       |
| filter_iter_up_8_tags               | 6.50ms       |
| filter_iter_up_8_tags_w_self        | 6.45ms       |
| filter_iter_up_w_mut_8_tags         | 6.50ms       |
| filter_iter_up_w_mut_8_tags_w_self  | 6.44ms       |
| query_init_fini_1_ids               | 722.82ns     |
| query_init_fini_16_ids              | 9.93us       |
| query_iter_8_tags_1_term            | 33.74ns      |
| query_iter_8_tags_4_terms           | 33.72ns      |
| query_iter_16_tags_1_term           | 34.09ns      |
| query_iter_16_tags_4_terms          | 26.27ns      |
| query_iter_8_components_1_term      | 53.98ns      |
| query_iter_8_components_4_terms     | 54.16ns      |
| query_iter_16_components_1_term     | 26.25ns      |
| query_iter_16_components_4_terms    | 74.36ns      |
| progress_0_systems                  | 85.74ns      |
| progress_1_system                   | 170.98ns     |
| progress_10_systems                 | 537.79ns     |
| progress_100_systems                | 4.08us       |
| create_delete_table_1_id            | 147.56ns     |
| create_delete_table_10_ids          | 285.32ns     |
| create_delete_table_100_ids         | 1.75us       |
| create_delete_table_1000_ids        | 20.86us      |
| match_table_1_of_10_queries         | 260.34ns     |
| match_table_5_of_10_queries         | 531.60ns     |
| match_table_10_of_10_queries        | 866.25ns     |
| match_table_1_of_100_queries        | 260.75ns     |
| match_table_10_of_100_queries       | 858.15ns     |
| match_table_50_of_100_queries       | 3.76us       |
| match_table_100_of_100_queries      | 8.29us       |
| match_table_1_of_1000_queries       | 260.99ns     |
| match_table_10_of_1000_queries      | 860.55ns     |
| match_table_100_of_1000_queries     | 8.32us       |
| match_table_1000_of_1000_queries    | 91.14us      |
| rematch_1_of_1000_tables            | 67.80us      |
| rematch_10_of_1000_tables           | 68.24us      |
| rematch_100_of_1000_tables          | 67.15us      |
| rematch_1000_of_1000_tables         | 47.60us      |
| fill_empty_table_0_queries          | 249.10ns     |
| fill_empty_table_1_query            | 397.56ns     |
| fill_empty_table_10_queries         | 620.65ns     |
| fill_empty_table_100_queries        | 3.86us       |
| fill_empty_table_1000_queries       | 44.81us      |
| table_add_remove_1_id               | 3.66ns       |
| table_add_remove_4_ids              | 3.65ns       |
| table_add_remove_16_ids             | 4.18ns       |
| table_add_remove_32_ids             | 4.45ns       |
| table_add_remove_64_ids             | 4.66ns       |
