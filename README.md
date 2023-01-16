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

## Hardware
Benchmarks were measured on a MacBook Pro M1 from 2021, with 64GB RAM

## Benchmarks
ns = nanoseconds, us = microseconds, ms = milliseconds

| Benchmark                           | Measurement |
|-------------------------------------|-------------|
| world_mini_fini                     | 304.18us    |
| world_init_fini                     | 1.24ms      |
| has_empty_entity                    | 1.98ns      |
| has_id_not_found                    | 3.25ns      |
| has_id                              | 3.94ns      |
| has_16_ids                          | 4.25ns      |
| get_empty_entity                    | 1.97ns      |
| get_id_not_found                    | 3.95ns      |
| get_id                              | 3.97ns      |
| get_16_ids                          | 4.19ns      |
| get_pair                            | 4.87ns      |
| get_pair_16_targets                 | 5.11ns      |
| get_mut_id                          | 7.68ns      |
| get_mut_16_ids                      | 7.95ns      |
| set_id                              | 12.18ns     |
| set_16_ids                          | 12.61ns     |
| ref_init                            | 4.59ns      |
| ref_get                             | 2.21ns      |
| add_remove_1_tag                    | 18.65ns     |
| add_remove_2_tags                   | 24.16ns     |
| add_remove_16_tags                  | 29.22ns     |
| add_remove_32_tags                  | 29.48ns     |
| add_remove_1_component              | 19.56ns     |
| add_remove_2_components             | 28.05ns     |
| add_remove_16_components            | 83.94ns     |
| add_remove_32_components            | 146.02ns    |
| add_existing_1_tag                  | 10.55ns     |
| add_existing_16_tags                | 10.88ns     |
| add_existing_1_component            | 10.55ns     |
| add_existing_16_components          | 10.90ns     |
| add_remove_override_1               | 72.12ns     |
| add_remove_override_2               | 76.70ns     |
| add_remove_override_4               | 87.12ns     |
| add_remove_override_16              | 135.47ns    |
| add_remove_cmd_1_tag                | 29.84ns     |
| add_remove_cmd_2_tags               | 24.94ns     |
| add_remove_cmd_16_tags              | 18.27ns     |
| add_remove_cmd_32_tags              | 17.92ns     |
| add_remove_cmd_1_components         | 31.78ns     |
| add_remove_cmd_2_components         | 27.10ns     |
| add_remove_cmd_16_components        | 20.34ns     |
| add_remove_cmd_32_components        | 20.08ns     |
| add_remove_hooks_1                  | 22.44ns     |
| add_remove_hooks_2                  | 35.05ns     |
| add_remove_hooks_16                 | 113.39ns    |
| add_remove_hooks_32                 | 189.88ns    |
| create_delete_empty                 | 5.56ns      |
| create_delete_1_tag                 | 13.61ns     |
| create_delete_2_tags                | 17.68ns     |
| create_delete_16_tags               | 27.11ns     |
| create_delete_1_component           | 14.38ns     |
| create_delete_2_components          | 20.20ns     |
| create_delete_16_components         | 75.80ns     |
| create_delete_tree_depth_1          | 1.15us      |
| create_delete_tree_depth_10         | 8.93us      |
| create_delete_tree_depth_100        | 88.95us     |
| create_delete_tree_depth_1000       | 896.71us    |
| emit_0_observers                    | 23.13ns     |
| emit_1_observer                     | 38.04ns     |
| emit_10_observers                   | 94.42ns     |
| emit_100_observers                  | 724.95ns    |
| emit_propagate_depth_1              | 30.39ns     |
| emit_propagate_depth_10             | 208.78ns    |
| emit_propagate_depth_100            | 2.48us      |
| emit_propagate_depth_1000           | 36.57us     |
| emit_forward_1_ids_depth_1          | 334.08ns    |
| emit_forward_1_ids_depth_1000       | 333.08ns    |
| emit_forward_16_ids_depth_1         | 990.37ns    |
| emit_forward_16_ids_depth_1000      | 997.84ns    |
| modified_0_observers                | 10.37ns     |
| modified_1_observer                 | 50.61ns     |
| modified_10_observers               | 106.40ns    |
| modified_100_observers              | 706.74ns    |
| filter_init_fini_1_ids              | 70.40ns     |
| filter_init_fini_16_ids             | 482.28ns    |
| filter_init_fini_inline_1_ids       | 58.53ns     |
| filter_init_fini_inline_16_ids      | 476.24ns    |
| filter_iter_8_tags_1_term           | 2.43us      |
| filter_iter_8_tags_4_terms          | 4.57us      |
| filter_iter_16_tags_1_term          | 11.19us     |
| filter_iter_16_tags_4_terms         | 22.77us     |
| filter_iter_8_components_1_term     | 2.44us      |
| filter_iter_8_components_4_terms    | 4.64us      |
| filter_iter_16_components_1_term    | 13.97us     |
| filter_iter_16_components_4_terms   | 23.76us     |
| filter_iter_up_8_tags               | 20.54us     |
| filter_iter_up_8_tags_w_self        | 22.32us     |
| query_init_fini_1_ids               | 641.79ns    |
| query_init_fini_16_ids              | 8.72us      |
| query_iter_8_tags_1_term            | 55.86ns     |
| query_iter_8_tags_4_terms           | 55.42ns     |
| query_iter_16_tags_1_term           | 27.73ns     |
| query_iter_16_tags_4_terms          | 27.90ns     |
| query_iter_8_components_1_term      | 57.17ns     |
| query_iter_8_components_4_terms     | 57.25ns     |
| query_iter_16_components_1_term     | 27.77ns     |
| query_iter_16_components_4_terms    | 27.96ns     |
