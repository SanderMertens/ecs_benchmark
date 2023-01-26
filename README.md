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

Release: https://github.com/SanderMertens/flecs/releases/tag/v3.1.4

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement  |
|-------------------------------------|--------------|
| world_mini_fini                     | 282.27us     |
| world_init_fini                     | 1.12ms       |
| progress_0_systems                  | 86.58ns      |
| progress_1_system                   | 172.01ns     |
| progress_10_systems                 | 520.06ns     |
| progress_100_systems                | 3.88us       |
| create_delete_table_1_id            | 131.59ns     |
| create_delete_table_10_ids          | 258.62ns     |
| create_delete_table_100_ids         | 1.61us       |
| create_delete_table_1000_ids        | 19.63us      |
| table_add_remove_1_id               | 3.65ns       |
| table_add_remove_4_ids              | 3.63ns       |
| table_add_remove_16_ids             | 4.18ns       |
| table_add_remove_32_ids             | 4.44ns       |
| table_add_remove_64_ids             | 4.63ns       |
| has_empty_entity                    | 1.88ns       |
| has_id_not_found                    | 3.13ns       |
| has_id                              | 3.75ns       |
| has_16_ids                          | 4.06ns       |
| get_empty_entity                    | 1.88ns       |
| get_id_not_found                    | 3.75ns       |
| get_id                              | 3.71ns       |
| get_16_ids                          | 3.95ns       |
| get_pair                            | 4.61ns       |
| get_pair_16_targets                 | 4.84ns       |
| get_mut_id                          | 7.53ns       |
| get_mut_16_ids                      | 7.64ns       |
| set_id                              | 11.88ns      |
| set_16_ids                          | 12.37ns      |
| get_mut_remove_id                   | 20.87ns      |
| get_mut_remove_16_ids               | 84.14ns      |
| get_mut_remove_32_ids               | 143.91ns     |
| ref_init                            | 4.69ns       |
| ref_get                             | 2.15ns       |
| add_remove_1_tag                    | 17.64ns      |
| add_remove_2_tags                   | 22.49ns      |
| add_remove_16_tags                  | 27.56ns      |
| add_remove_32_tags                  | 27.61ns      |
| add_remove_1_component              | 18.51ns      |
| add_remove_2_components             | 26.56ns      |
| add_remove_16_components            | 79.27ns      |
| add_remove_32_components            | 138.26ns     |
| add_existing_1_tag                  | 9.99ns       |
| add_existing_16_tags                | 10.31ns      |
| add_existing_1_component            | 10.06ns      |
| add_existing_16_components          | 10.35ns      |
| add_remove_override_1               | 68.87ns      |
| add_remove_override_2               | 73.21ns      |
| add_remove_override_4               | 83.31ns      |
| add_remove_override_16              | 127.79ns     |
| add_remove_cmd_1_tag                | 28.49ns      |
| add_remove_cmd_2_tags               | 23.78ns      |
| add_remove_cmd_16_tags              | 17.50ns      |
| add_remove_cmd_32_tags              | 17.46ns      |
| add_remove_cmd_1_components         | 30.34ns      |
| add_remove_cmd_2_components         | 25.89ns      |
| add_remove_cmd_16_components        | 19.48ns      |
| add_remove_cmd_32_components        | 19.46ns      |
| get_mut_cmd_1                       | 27.90ns      |
| get_mut_cmd_2                       | 22.40ns      |
| get_mut_cmd_16                      | 18.72ns      |
| get_mut_cmd_32                      | 18.70ns      |
| set_cmd_1                           | 39.91ns      |
| set_cmd_2                           | 26.37ns      |
| set_cmd_16                          | 22.10ns      |
| set_cmd_32                          | 22.27ns      |
| get_mut_remove_cmd_1                | 35.84ns      |
| get_mut_remove_cmd_2                | 34.06ns      |
| get_mut_remove_cmd_16               | 27.56ns      |
| get_mut_remove_cmd_32               | 27.13ns      |
| add_remove_hooks_1                  | 21.20ns      |
| add_remove_hooks_2                  | 33.45ns      |
| add_remove_hooks_16                 | 107.30ns     |
| add_remove_hooks_32                 | 178.90ns     |
| create_delete_empty                 | 5.31ns       |
| create_delete_1_tag                 | 12.91ns      |
| create_delete_2_tags                | 16.62ns      |
| create_delete_16_tags               | 25.60ns      |
| create_delete_1_component           | 13.67ns      |
| create_delete_2_components          | 19.11ns      |
| create_delete_16_components         | 72.17ns      |
| create_delete_tree_depth_1          | 1.14us       |
| create_delete_tree_depth_10         | 8.36us       |
| create_delete_tree_depth_100        | 85.52us      |
| create_delete_tree_depth_1000       | 864.59us     |
| change_parent                       | 251.96ns     |
| change_parent_root                  | 123.07ns     |
| change_parent_w_name                | 343.15ns     |
| lookup_depth_0                      | 39.45ns      |
| lookup_depth_1                      | 69.97ns      |
| lookup_depth_10                     | 363.62ns     |
| lookup_depth_100                    | 3.79us       |
| emit_0_observers                    | 21.62ns      |
| emit_1_observer                     | 35.98ns      |
| emit_10_observers                   | 89.20ns      |
| emit_100_observers                  | 671.60ns     |
| emit_propagate_depth_1              | 28.72ns      |
| emit_propagate_depth_10             | 196.62ns     |
| emit_propagate_depth_100            | 2.22us       |
| emit_propagate_depth_1000           | 33.86us      |
| emit_forward_1_ids_depth_1          | 295.98ns     |
| emit_forward_1_ids_depth_1000       | 297.74ns     |
| emit_forward_16_ids_depth_1         | 911.62ns     |
| emit_forward_16_ids_depth_1000      | 919.92ns     |
| modified_0_observers                | 9.96ns       |
| modified_1_observer                 | 48.68ns      |
| modified_10_observers               | 102.62ns     |
| modified_100_observers              | 706.21ns     |
| filter_init_fini_1_ids              | 67.25ns      |
| filter_init_fini_16_ids             | 467.92ns     |
| filter_init_fini_inline_1_ids       | 55.74ns      |
| filter_init_fini_inline_16_ids      | 456.34ns     |
| filter_iter_8_tags_1_term           | 2.34us       |
| filter_iter_8_tags_4_terms          | 4.44us       |
| filter_iter_16_tags_1_term          | 10.56us      |
| filter_iter_16_tags_4_terms         | 21.52us      |
| filter_iter_8_components_1_term     | 2.34us       |
| filter_iter_8_components_4_terms    | 4.52us       |
| filter_iter_16_components_1_term    | 13.28us      |
| filter_iter_16_components_4_terms   | 22.01us      |
| filter_iter_up_8_tags               | 48.02us      |
| filter_iter_up_8_tags_w_self        | 46.84us      |
| filter_iter_up_w_mut_8_tags         | 47.93us      |
| filter_iter_up_w_mut_8_tags_w_self  | 46.85us      |
| query_init_fini_1_ids               | 603.56ns     |
| query_init_fini_16_ids              | 8.08us       |
| query_iter_8_tags_1_term            | 52.11ns      |
| query_iter_8_tags_4_terms           | 52.25ns      |
| query_iter_16_tags_1_term           | 26.26ns      |
| query_iter_16_tags_4_terms          | 26.27ns      |
| query_iter_8_components_1_term      | 53.90ns      |
| query_iter_8_components_4_terms     | 53.85ns      |
| query_iter_16_components_1_term     | 26.28ns      |
| query_iter_16_components_4_terms    | 26.31ns      |
